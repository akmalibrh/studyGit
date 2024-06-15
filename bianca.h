#ifndef BIANCA_H
#define BIANCA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "excelpart.h"

void tambah(Pasien **head);

int min(int a, int b);

int calcmatch(const char* str1, const char* str2);

void cari(Pasien *head, Pasien **current);

void hapus(Pasien **head);

void clear_input_buffer();

void ubah(Pasien *head);

#endif