#ifndef EXCELPART_H
#define EXCELPART_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <xlsxio_read.h>

typedef struct _tanggal {
    int day;
    int month;
    int year;
} Tanggal;

typedef struct _riwayat {
    Tanggal tanggal;
    char* diagnosis;
    char* tindakan;
    Tanggal kontrol;
    float biaya;
    struct _riwayat *next;
    struct _riwayat *prev;
} Riwayat;

typedef struct _pasien {
    char *nama;
    char *alamat;
    char *kota;
    char *temp_lahir;
    Tanggal tgl_lahir;
    int umur;
    char *bpjs;
    char *id;
    Riwayat *riwayat; // linked list riwayat
    struct _pasien *prev;
    struct _pasien *next;
} Pasien;

typedef struct _tindakan {
    char **aktivitas;
    float *biaya;
    int count;
} Tindakan;

int is_number(const char* str);

Tanggal excel_serial_to_date(int serial_date);

Tanggal string_to_date(const char* date_str);

void addAktivitas(char ***aktivitas, int count, char* value);

void addBiaya(float **biaya, int count, char *value);

void createRiwayat(Riwayat **head, Riwayat *riwayat);

void initPasien(Pasien **pasien);

void createPasien(Pasien *pasien);

int read_xlsx(const char* filename, Pasien *head, Tindakan *tindakan);



#endif