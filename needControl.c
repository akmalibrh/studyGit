#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xlsxio_read.h>
#include <glib.h>

typedef struct {
    char id_pasien[50];
    char nama_lengkap[100];
} Pasien;

void get_kontrol_info(const char* filename) {
    xlsxioreader file;
    xlsxioreadersheet sheet1, sheet2;
    const char* value;
    GHashTable* id_count_table = g_hash_table_new(g_str_hash, g_str_equal);
    GHashTable* id_to_name_table = g_hash_table_new(g_str_hash, g_str_equal);

    // Buka file XLSX
    if ((file = xlsxioread_open(filename)) == NULL) {
        fprintf(stderr, "Unable to open .xlsx file\n");
        return;
    }

    // Baca sheet 'Data Pasien'
    if ((sheet1 = xlsxioread_sheet_open(file, "Data Pasien", XLSXIOREAD_SKIP_EMPTY_ROWS)) == NULL) {
        fprintf(stderr, "Unable to open sheet 'Data Pasien'\n");
        xlsxioread_close(file);
        return;
    }

    // Skip header
    xlsxioread_sheet_next_row(sheet1);

    // Baca data dari sheet 'Data Pasien'
    while (xlsxioread_sheet_next_row(sheet1)) {
        Pasien p;
        int col = 0;
        while ((value = xlsxioread_sheet_next_cell(sheet1)) != NULL) {
            switch (col) {
                case 1:
                    strncpy(p.nama_lengkap, value, sizeof(p.nama_lengkap));
                    break;
                case 8:
                    strncpy(p.id_pasien, value, sizeof(p.id_pasien));
                    break;
            }
            col++;
            free((void*)value);
        }
        g_hash_table_insert(id_to_name_table, strdup(p.id_pasien), strdup(p.nama_lengkap));
    }
    xlsxioread_sheet_close(sheet1);

    // Baca sheet 'Riwayat Datang, Diag,, Tindakan'
    if ((sheet2 = xlsxioread_sheet_open(file, "Riwayat Datang, Diag,, Tindakan", XLSXIOREAD_SKIP_EMPTY_ROWS)) == NULL) {
        fprintf(stderr, "Unable to open sheet 'Riwayat Datang, Diag,, Tindakan'\n");
        g_hash_table_destroy(id_count_table);
        g_hash_table_destroy(id_to_name_table);
        xlsxioread_close(file);
        return;
    }

    // Skip header
    xlsxioread_sheet_next_row(sheet2);

    // Baca data dari sheet 'Riwayat Datang, Diag,, Tindakan'
    while (xlsxioread_sheet_next_row(sheet2)) {
        char id_pasien[50] = "";
        int col = 0;
        while ((value = xlsxioread_sheet_next_cell(sheet2)) != NULL) {
            if (col == 2) {
                strncpy(id_pasien, value, sizeof(id_pasien));
            }
            col++;
            free((void*)value);
        }
        if (strlen(id_pasien) > 0) {
            gpointer count = g_hash_table_lookup(id_count_table, id_pasien);
            if (count) {
                g_hash_table_insert(id_count_table, strdup(id_pasien), GINT_TO_POINTER(GPOINTER_TO_INT(count) + 1));
            } else {
                g_hash_table_insert(id_count_table, strdup(id_pasien), GINT_TO_POINTER(1));
            }
        }
    }
    xlsxioread_sheet_close(sheet2);
    xlsxioread_close(file);

    // Proses data untuk menemukan pasien yang memerlukan kontrol
    GHashTableIter iter;
    gpointer key, value_name;
    int kontrol_count = 0;
    GList* kontrol_list = NULL;
    
    g_hash_table_iter_init(&iter, id_count_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        if (GPOINTER_TO_INT(value) == 1) {
            char* id_pasien = (char*)key;
            char* nama_lengkap = (char*)g_hash_table_lookup(id_to_name_table, id_pasien);
            if (nama_lengkap) {
                kontrol_list = g_list_append(kontrol_list, g_strdup_printf("%s\t%s", nama_lengkap, id_pasien));
                kontrol_count++;
            }
        }
    }

    // Output
    printf("Jumlah pasien yang memerlukan kontrol: %d\n", kontrol_count);
    printf("Pasien yang memerlukan kontrol:\n");
    for (GList* l = kontrol_list; l != NULL; l = l->next) {
        printf("%d. %s\n", g_list_position(kontrol_list, l) + 1, (char*)l->data);
    }

    // Cleanup
    g_list_free_full(kontrol_list, g_free);
    g_hash_table_destroy(id_count_table);
    g_hash_table_destroy(id_to_name_table);
}

int main() {
    const char* filename = "DataPMC20232024.xlsx";
    get_kontrol_info(filename);
    return 0;
}
