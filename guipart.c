#include "guipart.h"

GtkWidget* create_label_with_font(const char *text, const char *font, PangoWeight weight, const int size, gboolean selectable) {
    GtkWidget *label = gtk_label_new(text);
    gtk_label_set_selectable(GTK_LABEL(label), selectable);
    PangoAttrList *attr_list = pango_attr_list_new();
    pango_attr_list_insert(attr_list, pango_attr_family_new(font));
    pango_attr_list_insert(attr_list, pango_attr_size_new(size * PANGO_SCALE));
    pango_attr_list_insert(attr_list, pango_attr_weight_new(weight));
    gtk_label_set_attributes(GTK_LABEL(label), attr_list);
    pango_attr_list_unref(attr_list);
    return label;
}

void prevPasien(GtkWidget *widget, gpointer user_data) {
    (void) widget; // Suppress unused parameter warning
    UserData* data = (UserData*)user_data;
    int i = 0;
    if (data->current->prev != NULL) {
        data->current = data->current->prev;
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->nama);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->alamat);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->kota);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->temp_lahir);
        sprintf(data->buffer, "%02d-%02d-%4d", data->current->tgl_lahir.day, data->current->tgl_lahir.month, data->current->tgl_lahir.year);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->buffer);
        sprintf(data->buffer, "%d", data->current->umur);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->buffer);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->bpjs);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->id);
    }
}

void nextPasien(GtkWidget *widget, gpointer user_data) {
    (void) widget; // Suppress unused parameter warning
    UserData *data = (UserData *)user_data;
    int i = 0;
    if (data->current != NULL) {
        data->current = data->current->next;
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->nama);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->alamat);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->kota);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->temp_lahir);
        sprintf(data->buffer, "%02d-%02d-%4d", data->current->tgl_lahir.day, data->current->tgl_lahir.month, data->current->tgl_lahir.year);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->buffer);
        sprintf(data->buffer, "%d", data->current->umur);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->buffer);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->bpjs);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->id);
    }
}

void hapusData(GtkWidget *widget, gpointer user_data) {
    (void) widget; // Suppress unused parameter warning
    UserData *data = (UserData *)user_data;
    if (!data->current) {
        return;
    }
    if (data->current->prev) {
        data->current->prev->next = data->current->next;
    }
    if (data->current->next) {
        data->current->next->prev = data->current->prev;
    }

    Pasien *to_delete = data->current;
    if (data->current->next) {
        data->current = data->current->next;
    } else if (data->current->prev) {
        data->current = data->current->prev;
    } else {
        data->current = NULL;
    }
    free(to_delete);

    setInfo(data);
}

void setInfo(UserData *data) {
    int i = 0;
    if (data->current != NULL)
    {
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->nama);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->alamat);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->kota);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->temp_lahir);
        sprintf(data->buffer, "%02d-%02d-%4d", data->current->tgl_lahir.day, data->current->tgl_lahir.month, data->current->tgl_lahir.year);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->buffer);
        sprintf(data->buffer, "%d", data->current->umur);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->buffer);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->bpjs);
        gtk_label_set_text(GTK_LABEL(data->label[i++]), data->current->id);
    }
    else
    {
        for (int j = 0; j < 8; j++)
        {
            gtk_label_set_text(GTK_LABEL(data->label[j]), "");
        }
    }
}

void goToPage(GtkWidget *widget, gpointer user_data) {
    (void) widget; // Suppress unused parameter warning
    UserData *data = (UserData *)user_data;
    gtk_stack_set_visible_child(GTK_STACK(data->stack), data->halaman[0]);
}

void notFound() {
    GtkWidget *dialog = gtk_window_new();
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *label = gtk_label_new("Data tidak ditemukan.");
    GtkWidget *button = gtk_button_new_with_label("OK");

    gtk_window_set_title(GTK_WINDOW(dialog), "Hasil");
    gtk_window_set_default_size(GTK_WINDOW(dialog), 100, 0);
    gtk_window_set_child(GTK_WINDOW(dialog), box);
    gtk_box_append(GTK_BOX(box), label);
    gtk_box_append(GTK_BOX(box), button);

    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), dialog);
    
    gtk_window_present(GTK_WINDOW(dialog));
}

void search(GtkWidget *widget, gpointer user_data) {
    (void) widget; // Suppress unused parameter warning
    UserData *data = (UserData *)user_data;
    strcpy(data->buffer, gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(data->input))));
    int selected = gtk_drop_down_get_selected(GTK_DROP_DOWN(data->dropdown));
    data->current = data->head;

    switch (selected) {
        case 0:
            while (data->current != NULL && strcmp(data->buffer, data->current->nama)) {
                data->current = data->current->next;
            }
            if (data->current == NULL) {
                data->current = data->head;
                notFound(data);
            }
            setInfo(data);
            break;
        case 1:
            while (data->current != NULL && strcmp(data->buffer, data->current->alamat)) {
                data->current = data->current->next;
            }
            if (data->current == NULL) {
                data->current = data->head;
                notFound(data);
            }
            setInfo(data);
            break;
        case 2:
            while (data->current != NULL && strcmp(data->buffer, data->current->kota)) {
                data->current = data->current->next;
            }
            if (data->current == NULL) {
                data->current = data->head;
                notFound(data);
            }
            setInfo(data);
            break;
        case 3:
            while (data->current != NULL && strcmp(data->buffer, data->current->temp_lahir)) {
                data->current = data->current->next;
            }
            if (data->current == NULL) {
                data->current = data->head;
                notFound(data);
            }
            setInfo(data);
            break;
        case 4:
            char buffer[128];
            sprintf(buffer, "%02d-%02d-%d", data->current->tgl_lahir.day, data->current->tgl_lahir.month, data->current->tgl_lahir.year);
            while (data->current != NULL && strcmp(data->buffer, buffer)) {
                data->current = data->current->next;
                sprintf(buffer, "%02d-%02d-%d", data->current->tgl_lahir.day, data->current->tgl_lahir.month, data->current->tgl_lahir.year);
            }
            if (data->current == NULL) {
                data->current = data->head;
                notFound(data);
            }
            setInfo(data);
            break;
        case 5:
            while (data->current != NULL && atoi(data->buffer) != data->current->umur) {
                data->current = data->current->next;
            }
            if (data->current == NULL) {
                data->current = data->head;
                notFound(data);
            }
            setInfo(data);
            break;
        case 6:
            while (data->current != NULL && strcmp(data->buffer, data->current->bpjs)) {
                data->current = data->current->next;
            }
            if (data->current == NULL) {
                data->current = data->head;
                notFound(data);
            }
            setInfo(data);
            break;
        case 7:
            while (data->current != NULL && strcmp(data->buffer, data->current->id)) {
                data->current = data->current->next;
            }
            if (data->current == NULL) {
                data->current = data->head;
                notFound(data);
            }
            setInfo(data);
            break;
    }
}

void renderHalaman1(UserData *data, GtkWidget *hal1) {
    // Title Label
    GtkWidget *nama, *t_nama;
    GtkWidget *alamat, *t_alamat;
    GtkWidget *kota, *t_kota;
    GtkWidget *temp_lahir, *t_temp_lahir;
    GtkWidget *tgl_lahir, *t_tgl_lahir;
    GtkWidget *umur, *t_umur;
    GtkWidget *bpjs, *t_bpjs;
    GtkWidget *id, *t_id;
    GtkWidget *prev;
    GtkWidget *riwayat;
    GtkWidget *next;
    t_nama = create_label_with_font("Nama", "Roboto", PANGO_WEIGHT_ULTRABOLD, 14, false);
    t_alamat = create_label_with_font("Alamat", "Roboto", PANGO_WEIGHT_ULTRABOLD, 14, false);
    t_kota = create_label_with_font("Kota", "Roboto", PANGO_WEIGHT_ULTRABOLD, 14, false);
    t_temp_lahir = create_label_with_font("Tempat Lahir", "Roboto", PANGO_WEIGHT_ULTRABOLD, 14, false);
    t_tgl_lahir = create_label_with_font("Tanggal Lahir", "Roboto", PANGO_WEIGHT_ULTRABOLD, 14, false);
    t_umur = create_label_with_font("Umur", "Roboto", PANGO_WEIGHT_ULTRABOLD, 14, false);
    t_bpjs = create_label_with_font("No. BPJS", "Roboto", PANGO_WEIGHT_ULTRABOLD, 14, false);
    t_id = create_label_with_font("ID", "Roboto", PANGO_WEIGHT_ULTRABOLD, 14, false);

    // Align title
    gtk_widget_set_halign(t_nama, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(t_nama, true);

    // Create user data and data label
    int i = 0;
    nama = create_label_with_font(data->current->nama, "Roboto", PANGO_WEIGHT_NORMAL, 12, true);
    alamat = create_label_with_font(data->current->alamat, "Roboto", PANGO_WEIGHT_NORMAL, 12, true);
    kota = create_label_with_font(data->current->kota, "Roboto", PANGO_WEIGHT_NORMAL, 12, true);
    temp_lahir = create_label_with_font(data->current->temp_lahir, "Roboto", PANGO_WEIGHT_NORMAL, 12, true);
    sprintf(data->buffer, "%02d-%02d-%4d", data->current->tgl_lahir.day, data->current->tgl_lahir.month, data->current->tgl_lahir.year);
    tgl_lahir = create_label_with_font(data->buffer, "Roboto", PANGO_WEIGHT_NORMAL, 12, true);
    sprintf(data->buffer, "%d", data->current->umur);
    umur = create_label_with_font(data->buffer, "Roboto", PANGO_WEIGHT_NORMAL, 12, true);
    bpjs = create_label_with_font(data->current->bpjs, "Roboto", PANGO_WEIGHT_NORMAL, 12, true);
    id = create_label_with_font(data->current->id, "Roboto", PANGO_WEIGHT_NORMAL, 12, true);

    data->label[i] = nama;
    gtk_widget_set_margin_bottom(data->label[i++], 8);
    data->label[i] = alamat;
    gtk_widget_set_margin_bottom(data->label[i++], 8);
    data->label[i] = kota;
    gtk_widget_set_margin_bottom(data->label[i++], 8);
    data->label[i] = temp_lahir;
    gtk_widget_set_margin_bottom(data->label[i++], 8);
    data->label[i] = tgl_lahir;
    gtk_widget_set_margin_bottom(data->label[i++], 8);
    data->label[i] = umur;
    gtk_widget_set_margin_bottom(data->label[i++], 8);
    data->label[i] = bpjs;
    gtk_widget_set_margin_bottom(data->label[i++], 8);
    data->label[i] = id;
    gtk_widget_set_margin_bottom(data->label[i++], 8);

    // Align label
    for (int j = 0; j < 8; j++)
    {
        gtk_widget_set_halign(data->label[j], GTK_ALIGN_CENTER);
    }
    // Button
    prev = gtk_button_new_with_label("<- Prev");
    gtk_widget_set_halign(prev, GTK_ALIGN_START);
    g_signal_connect(prev, "clicked", G_CALLBACK(prevPasien), data);
    next = gtk_button_new_with_label("Next ->");
    gtk_widget_set_halign(next, GTK_ALIGN_END);
    g_signal_connect(next, "clicked", G_CALLBACK(nextPasien), data);
    riwayat = gtk_button_new_with_label("Riwayat");

    // Attach button to grid
    int j = 0;
    gtk_grid_attach(GTK_GRID(hal1), t_nama, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), nama, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), t_alamat, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), alamat, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), t_kota, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), kota, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), t_temp_lahir, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), temp_lahir, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), t_tgl_lahir, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), tgl_lahir, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), t_umur, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), umur, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), t_bpjs, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), bpjs, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), t_id, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), id, 1, j++, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), prev, 0, j, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), riwayat, 1, j, 1, 1);
    gtk_grid_attach(GTK_GRID(hal1), next, 2, j, 1, 1);
}

void renderHalaman2(UserData *data, GtkWidget *hal2)
{
    GtkStringList *string_list = gtk_string_list_new(NULL);
    gtk_string_list_append(string_list, "Nama");
    gtk_string_list_append(string_list, "Alamat");
    gtk_string_list_append(string_list, "Kota");
    gtk_string_list_append(string_list, "Tempat Lahir");
    gtk_string_list_append(string_list, "Tanggal Lahir");
    gtk_string_list_append(string_list, "Umur");
    gtk_string_list_append(string_list, "No. BPJS");
    gtk_string_list_append(string_list, "ID");

    GtkWidget *opt = gtk_drop_down_new(G_LIST_MODEL(string_list), NULL);
    gtk_widget_set_size_request(opt, 100, 0);

    GtkWidget *input = gtk_entry_new();
    GtkWidget *searchButton = gtk_button_new_with_label("Search");

    data->dropdown = opt;
    data->input = input;

    gtk_grid_attach(GTK_GRID(hal2), input, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(hal2), opt, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(hal2), searchButton, 0, 1, 2, 1);

    g_signal_connect(searchButton, "clicked", G_CALLBACK(search), data);
    g_signal_connect(searchButton, "clicked", G_CALLBACK(goToPage), data);
}

void renderHalaman3(UserData *data, GtkWidget *hal3)
{
    GtkWidget *hapusButton;
    GtkWidget *ubahButton;

    hapusButton = gtk_button_new_with_label("Hapus Data");
    ubahButton = gtk_button_new_with_label("Ubah Data");

    gtk_widget_set_margin_end(hapusButton, 5);
    gtk_widget_set_margin_end(ubahButton, 5);

    g_signal_connect(hapusButton, "clicked", G_CALLBACK(hapusData), data);
    g_signal_connect(hapusButton, "clicked", G_CALLBACK(goToPage), data);

    gtk_grid_attach(GTK_GRID(hal3), hapusButton, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(hal3), ubahButton, 1, 0, 1, 1);
}