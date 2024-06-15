#ifndef KANIA_H
#define KANIA_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <xlsxio_read.h>
#include "excelpart.h"

void addRiwayat(Riwayat* current);
void modifyRiwayat(Riwayat *current);
void deleteRiwayat(Riwayat **current);
void searchRiwayat(Pasien *current);


#endif