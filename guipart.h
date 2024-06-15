#ifndef GUIPART_H
#define GUIPART_H

#include <gtk/gtk.h>

#include "excelpart.h"

typedef struct {
    GtkWidget *window;

    Pasien *head;
    Pasien *current;
    GtkWidget *label[8];

    GtkWidget *stack;
    GtkWidget *halaman[3];

    GtkWidget *input;
    GtkWidget *dropdown;

    char buffer[128];
} UserData;

GtkWidget* create_label_with_font(const char *text, const char *font, PangoWeight weight, const int size, gboolean selectable);

void prevPasien(GtkWidget *widget, gpointer user_data);

void nextPasien(GtkWidget *widget, gpointer user_data);

void setInfo(UserData *data);

void hapusData(GtkWidget *widget, gpointer user_data);

void goToPage(GtkWidget *widget, gpointer user_data);

void notFound();

void search(GtkWidget *widget, gpointer user_data);

void renderHalaman1(UserData *data, GtkWidget *hal1);

void renderHalaman2(UserData *data, GtkWidget *hal2);

void renderHalaman3(UserData *data, GtkWidget *hal3);

#endif