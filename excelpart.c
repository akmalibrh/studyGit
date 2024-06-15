#include "excelpart.h"

int is_number(const char* str) {
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

Tanggal excel_serial_to_date(int serial_date) {
    Tanggal date;

    time_t rawtime = (serial_date - 25569) * 86400;
    struct tm *timeinfo = gmtime(&rawtime);

    date.day = timeinfo->tm_mday;
    date.month = timeinfo->tm_mon + 1;
    date.year = timeinfo->tm_year + 1900;

    return date;
}

Tanggal string_to_date(const char* date_str) {
    Tanggal date;
    int day, year;
    char month_str[10];

    const char* months[] = {
    "Januari", "Februari", "Maret", "April", "Mei", "Juni", 
    "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };

    sscanf(date_str, "%d %s %d", &day, month_str, &year);
    for (int i = 0; i < 12; ++i) {
        if (strcmp(month_str, months[i]) == 0) {
            date.month = i + 1;
            break;
        }
    }
    date.day = day;
    date.year = year;

    return date;
}

void addAktivitas(char ***aktivitas, int count, char* value) {
    if (count == 0) {
        (*aktivitas) = malloc(sizeof(char*));
    } else {
        (*aktivitas) = realloc(*aktivitas, (count+1) * sizeof(char*));
    }
    (*aktivitas)[count] = strdup(value);
}

void addBiaya(float **biaya, int count, char *value) {
    if (count == 0) {
        (*biaya) = malloc(sizeof(float));
    } else {
        (*biaya) = realloc(*biaya, (count+1) * sizeof(float));
    }
    (*biaya)[count] = atof(value);
}

void createRiwayat(Riwayat **head, Riwayat *riwayat) {
    if ((*head) == NULL) {
        (*head) = riwayat;
        (*head)->prev = NULL;
        (*head)->next = NULL;
    } else {
        Riwayat* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = riwayat;
        riwayat->prev = current;
        riwayat->next = NULL;
    }
}

void initPasien(Pasien **pasien) {
    (*pasien) = malloc(sizeof(Pasien));
    (*pasien)->riwayat = NULL;
    (*pasien)->prev = NULL;
    (*pasien)->next = NULL;
}

void createPasien(Pasien *pasien) {
    Pasien *newNode;
    initPasien(&newNode);
    pasien->next = newNode;
    newNode->prev = pasien;
}

int read_xlsx(const char* filename, Pasien *head, Tindakan *tindakan) {
    xlsxioreader file = xlsxioread_open(filename);
    if (file == NULL) {
        printf("File tidak dapat dibuka.\n");
        return 1;
    }

    xlsxioreadersheetlist sheetlist = xlsxioread_sheetlist_open(file);
    if (sheetlist == NULL) {
        printf("Tidak ada sheet.\n");
        xlsxioread_close(file);
        return 1;
    } else {
        Pasien *currentPasien = head;
        char *sheetnames[3];
        char *sheetname;
        int j = 0;
        while ((sheetname = (char *)xlsxioread_sheetlist_next(sheetlist)) != NULL) {
            // printf("Baca sheet: %s\n", sheetname);
            sheetnames[j++] = strdup(sheetname);
        }
        for (int i = 0; i < 3; i++) {
            xlsxioreadersheet current_sheet = xlsxioread_sheet_open(file, sheetnames[i], XLSXIOREAD_SKIP_EMPTY_ROWS);
            // printf("Now reading %s\n", sheetnames[i]);
            xlsxioread_sheet_next_row(current_sheet);
            while (xlsxioread_sheet_next_row(current_sheet)) {
                char* value;
                switch (i) {
                    case 0:
                        // Assume the first column needs to be skipped
                        xlsxioread_sheet_next_cell(current_sheet);

                        // Read the rest of the cells
                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        currentPasien->nama = strdup(value);
                        // printf("%-25s", value);

                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        currentPasien->alamat = strdup(value);
                        // printf("%-20s", value);

                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        currentPasien->kota = strdup(value);
                        // printf("%-20s", value);

                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        currentPasien->temp_lahir = strdup(value);
                        // printf("%-20s", value);

                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        if (is_number(value)) {
                            int serial_date = atoi(value);
                            currentPasien->tgl_lahir = excel_serial_to_date(serial_date);
                        } else {
                            currentPasien->tgl_lahir = string_to_date(value);
                        }
                        // printf("%02d-%02d-%-6d", currentPasien->tgl_lahir.day, currentPasien->tgl_lahir.month, currentPasien->tgl_lahir.year);
                        xlsxioread_free(value);

                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        currentPasien->umur = atoi(value);
                        // printf("%-4d", currentPasien->umur);

                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        currentPasien->bpjs = strdup(value);
                        // printf("%-15s", value);

                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        currentPasien->id = strdup(value);
                        // printf("%s\n", value);

                        xlsxioread_free(value);
                        createPasien(currentPasien);
                        currentPasien = currentPasien->next;
                        break;
                    case 1:;
                        Pasien *currentPasien = head;
                        Riwayat *riwayat = malloc(sizeof(Riwayat));
                        xlsxioread_sheet_next_cell(current_sheet);

                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        if (is_number(value)) {
                            int serial_date = atoi(value);
                            riwayat->tanggal = excel_serial_to_date(serial_date);
                        } else {
                            riwayat->tanggal = string_to_date(value);
                        }
                        // printf("%2d-%2d-%-6d", riwayat->tanggal.day, riwayat->tanggal.month, riwayat->tanggal.year);

                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        while (strcmp(currentPasien->id, value) != 0) {
                            currentPasien = currentPasien->next;
                        }
                        // printf("%-14s", value);
                        
                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        riwayat->diagnosis = strdup(value);
                        // printf("%-14s", riwayat->diagnosis);
                        
                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        riwayat->tindakan = strdup(value);
                        // printf("%-20s", riwayat->tindakan);
                        
                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        if (is_number(value)) {
                            int serial_date = atoi(value);
                            riwayat->kontrol = excel_serial_to_date(serial_date);
                        } else {
                            riwayat->kontrol = string_to_date(value);
                        }
                        // printf("%02d-%02d-%-6d", riwayat->kontrol.day, riwayat->kontrol.month, riwayat->kontrol.year);
                        
                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        riwayat->biaya = atof(value);
                        // printf("%-14.2f\n", riwayat->biaya);
                        
                        createRiwayat(&currentPasien->riwayat, riwayat);
                    
                        xlsxioread_free(value);
                        break;
                    case 2:
                        xlsxioread_sheet_next_cell(current_sheet);

                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        addAktivitas(&tindakan->aktivitas, tindakan->count, value);
                        // printf("%-20s | ", value);

                        xlsxioread_sheet_next_cell_string(current_sheet, &value);
                        addBiaya(&tindakan->biaya, tindakan->count++, value);
                        // printf("%s\n", value);

                        xlsxioread_free(value);
                        break;
                }
            }
            // printf("Done reading %s\n", sheetnames[i]);
        }
    }
    Pasien *current = head;
    while (current->next->nama != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    printf("Read is done.\n");
    xlsxioread_close(file);
    return 0;
}
