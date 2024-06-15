#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <xlsxio_read.h>
#include "excelpart.h"
#include <stdlib.h>

#include "bianca.h"
#include "kania.h"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void mainMenu(Pasien *current) {
    printf("\033[H");
    printf("%-15s: %-50s\n", "Nama", current->nama);
    printf("%-15s: %-50s\n", "Alamat", current->alamat);
    printf("%-15s: %-50s\n", "Kota", current->kota);
    printf("%-15s: %-50s\n", "Tempat Lahir", current->temp_lahir);
    printf("%-15s: %02d-%02d-%-20d\n", "Tanggal Lahir", current->tgl_lahir.day, current->tgl_lahir.month, current->tgl_lahir.year);
    printf("%-15s: %d\n", "Umur", current->umur);
    printf("%-15s: %-50s\n", "No. BPJS", current->bpjs);
    printf("%-15s: %-50s\n", "ID Pasien", current->id);
    printf("(<-) Previous \t ( r) Riwayat \t (->) Next \t (ESC) Quit\n");
    printf("( 1) Add \t ( 2) Change \t ( 3) Hapus \t ( 4) Search\n");
}

void menu(Pasien *head) {
    clearScreen();

    Pasien *current = head;
    int menu = -1;
    mainMenu(current);
    
    /*
    Nomor tombol:
    ESC         : 27
    Left Arrow  : 0 terus 75
    Right Arrow : 0 terus 77
    */

    do {
        if (current != NULL) {
            if (menu == 0 || menu == 224) {
                menu = getch();
                if (menu == 75) {
                    if (current->prev != NULL) {
                        current = current->prev;
                    }
                } else if (menu == 77) {
                    if (current->next != NULL) {
                        current = current->next;
                    }
                }
            } else if (menu == 114) { // James Tampilan riwayat di main dengan 'r' 
                clearScreen();
                Riwayat *currentRiwayat = current->riwayat;
                int menuRiwayat;
                do {
                    if (currentRiwayat != NULL) {
                        if (menuRiwayat == 0 || menuRiwayat == 224) {
                            menuRiwayat = getch();
                            if (menuRiwayat == 75) {
                                if (currentRiwayat->prev != NULL) {
                                    currentRiwayat = currentRiwayat->prev;
                                }
                            } else if (menuRiwayat == 77) {
                                if (currentRiwayat->next != NULL) {
                                    currentRiwayat = currentRiwayat->next;
                                }
                            }
                        } else if (menuRiwayat == '1') {
                            clearScreen();
                            addRiwayat(currentRiwayat);
                            clearScreen();
                        } else if (menuRiwayat == '2') {
                            clearScreen();
                            modifyRiwayat(currentRiwayat);
                            clearScreen();
                        } else if (menuRiwayat == '3') {
                            deleteRiwayat(&currentRiwayat);
                            if(currentRiwayat == NULL) {
                                clearScreen();
                                goto noriwayat;
                            }
                        } else if (menuRiwayat == '4') {
                            clearScreen();
                            searchRiwayat(current);
                            clearScreen();
                        }
                        adariwayat:
                        printf("\033[H");
                        printf("%-15s: %-50s\n", "Nama", current->nama);
                        printf("%-15s: %02d-%02d-%-20d\n", "Tanggal", currentRiwayat->tanggal.day, currentRiwayat->tanggal.month, currentRiwayat->tanggal.year);
                        printf("%-15s: %-50s\n", "ID Pasien", current->id);
                        printf("%-15s: %-50s\n", "Diagnosis", currentRiwayat->diagnosis);
                        printf("%-15s: %-50s\n", "Tindakan", currentRiwayat->tindakan);
                        printf("%-15s: %02d-%02d-%-20d\n", "Kontrol", currentRiwayat->kontrol.day, currentRiwayat->kontrol.month, currentRiwayat->kontrol.year);
                        printf("%-15s: %.2f\n", "Biaya", currentRiwayat->biaya);
                        printf("(<-) Prev \t (->) Next \t (ESC) Back \n");
                        printf("( 1) Add \t ( 2) Change \t ( 3) Hapus \t ( 4) Search\n");
                    } else {
                        if (menuRiwayat == '1') {
                            clearScreen();
                            addRiwayat(currentRiwayat);
                            currentRiwayat = current->riwayat;
                            clearScreen();
                            goto adariwayat;
                        }
                        noriwayat:
                        printf("\033[H");
                        printf("Tidak ada riwayat.\n");
                        printf("( 1) Add \t (ESC) Back\n");
                    }
                } while ((menuRiwayat = getch()) != 27);
                clearScreen();
            } else if (menu == 49) { // Bianca Tambah pasien
                clearScreen();
                tambah(&head);
                clearScreen();
            } else if (menu == 50) {
                clearScreen();
                ubah(current);
                clearScreen();
            } else if (menu == 51) {
                clearScreen();
                hapus(&current);
                clearScreen();
                if (current == NULL) {
                    goto nodata;
                }
            } else if (menu == 52) {
                clearScreen();
                cari(head, &current);
                clearScreen();
            }
            adadata:
            mainMenu(current);
        } else {
            if (menu == '1') {
                clearScreen();
                tambah(&current);
                clearScreen();
                goto adadata;
            }
            nodata:
            printf("Tidak ada data.\n");
            printf("( 1) Add \t (ESC) Exit\n");
        }
    } while ((menu = getch()) != 27);
}

int main(int argc, char *argv[]) {
    Pasien *head;
    initPasien(&head);

    Tindakan *tindakan = malloc(sizeof(Tindakan));
    tindakan->aktivitas = NULL; tindakan->count = 0; tindakan->biaya = NULL;
    if (read_xlsx("DataPMC20232024.xlsx", head, tindakan) == 1) {
        return 1;
    }

    clearScreen();

    menu(head);

    return 0;
}