#include "bianca.h"

void tambah(Pasien **head) {
    Pasien* temp = (Pasien*)malloc(sizeof(Pasien));
    temp->nama = (char*)malloc(100 * sizeof(char));
    temp->alamat = (char*)malloc(100 * sizeof(char));
    temp->kota = (char*)malloc(100 * sizeof(char));
    temp->temp_lahir = (char*)malloc(100 * sizeof(char));
    temp->bpjs = (char*)malloc(100 * sizeof(char));
    temp->id = (char*)malloc(100 * sizeof(char));

    printf("Masukkan Nama Pasien   : ");
    fgets(temp->nama, 100, stdin);
    temp->nama[strcspn(temp->nama, "\n")] = 0; 

    printf("Masukkan Alamat        : ");
    fgets(temp->alamat, 100, stdin);
    temp->alamat[strcspn(temp->alamat, "\n")] = 0;

    printf("Masukkan Kota          : ");
    fgets(temp->kota, 100, stdin);
    temp->kota[strcspn(temp->kota, "\n")] = 0;

    printf("Masukkan Tempat Lahir  : ");
    fgets(temp->temp_lahir, 100, stdin);
    temp->temp_lahir[strcspn(temp->temp_lahir, "\n")] = 0;

    printf("Masukkan Tanggal Lahir : ");
    scanf("%d %d %d", &temp->tgl_lahir.day, &temp->tgl_lahir.month, &temp->tgl_lahir.year);

    printf("Masukkan Umur          : ");
    scanf("%d", &temp->umur);

    while (getchar() != '\n');

    printf("Masukkan No BPJS       : ");
    fgets(temp->bpjs, 100, stdin);
    temp->bpjs[strcspn(temp->bpjs, "\n")] = 0;

    printf("Masukkan ID Pasien     : ");
    fgets(temp->id, 100, stdin);
    temp->id[strcspn(temp->id, "\n")] = 0;

    temp->riwayat = NULL;
    temp->prev = NULL;
    temp->next = NULL;

    if (*head == NULL) {
        *head = temp;
    } else {
        Pasien* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = temp;
        temp->prev = current;
    }
    printf("Pasien berhasil didaftarkan\n");
}

int min(int a, int b) {
    return a < b ? a : b;
}

int calcmatch(const char* str1, const char* str2) {
    int l1, l2, l3;
    int a = 0;
    l1 = strlen(str1);
    l2 = strlen(str2);
    l3 = min(l1,l2);
    for(int i = 0;i<l3;i++){
        if(str1[i]==str2[i]){
            a = a+1;
        }
    }
    return a;

}

int searchbyCrit(Pasien *head, Pasien **matched, int criteria, char *search) {
    int matchlen;
    int count = 0;
    Pasien *temp = head;
    char *compare;
    Pasien *tempMatched = *matched;
    while (temp != NULL) {
        if (criteria == 1) {
            compare = strdup(temp->nama);
        } else if (criteria == 2) {
            compare = strdup(temp->alamat);
        } else if (criteria == 3) {
            compare = strdup(temp->kota);
        } else {
            compare = strdup(temp->temp_lahir);
        }
        matchlen = calcmatch(compare, search);
        if (matchlen == strlen(search)) {
            tempMatched->nama = strdup(temp->nama);
            tempMatched->alamat = strdup(temp->alamat);
            tempMatched->kota = strdup(temp->kota);
            tempMatched->temp_lahir = strdup(temp->temp_lahir);
            tempMatched->tgl_lahir.day = temp->tgl_lahir.day;
            tempMatched->tgl_lahir.month = temp->tgl_lahir.month;
            tempMatched->tgl_lahir.year = temp->tgl_lahir.year;
            tempMatched->umur = temp->umur;
            tempMatched->bpjs = strdup(temp->bpjs);
            tempMatched->id = strdup(temp->id);
            createPasien(tempMatched);
            tempMatched = tempMatched->next;
            count++;
        }
        temp = temp->next;
    }
    tempMatched = *matched;
    if (count > 1) {
        while (tempMatched->next->next != NULL) {
            tempMatched = tempMatched->next;
        }
        Pasien *to_delete = tempMatched->next;
        tempMatched->next = NULL;
        free(to_delete);
    } else if (count == 1) {
        free(tempMatched->next);
        tempMatched->next = NULL;
    }
    return count;
}

void cari(Pasien *head, Pasien **current){
    char search[100];
    char krit[100];
    int found = 0;
    int d, m, y, matchLen;
    int count = 0;

    if (head == NULL){
        printf("Belum ada data pasien\n");
        return;
    }

    printf("Kategori pasien yang ingin dicari\n");
    printf("( 1) Nama \t ( 2) Alamat\n");
    printf("( 3) Kota \t ( 4) Tempat Lahir\n");

    Pasien *matched = NULL;
    initPasien(&matched);
    int menu;
    switch ((menu = getch())) {
        case 27:
            return;
        case '1': // Nama
            printf("Masukkan nama pasien\n> ");
            scanf("%[^\n]%*c", search);
            count = searchbyCrit(head, &matched, 1, search);
            break;
        case '2': // Alamat
            printf("Masukkan alamat pasien\n> ");
            scanf("%[^\n]%*c", search);
            count = searchbyCrit(head, &matched, 2, search);
            break;
        case '3': // Kota
            printf("Masukkan kota pasien\n> ");
            scanf("%[^\n]%*c", search);
            count = searchbyCrit(head, &matched, 3, search);
            break;
        case '4': // Tempat Lahir
            printf("Masukkan tempat lahir pasien\n> ");
            scanf("%[^\n]%*c", search);
            count = searchbyCrit(head, &matched, 4, search);
            break;
    }

    if (count == 0) {
        printf("Tidak ada pasien yang cocok.\n");
        getch();
    } else if (count == 1) {
        (*current) = head;
        while (strcmp((*current)->nama, matched->nama) && (*current) != NULL) {
            (*current) = (*current)->next;
        }
    } else {
        int menu;
        do {
            if (menu == 0 || menu == 224) {
                menu = getch();
                if (menu == 75) {
                    if (matched->prev != NULL) {
                        matched = matched->prev;
                    }
                } else if (menu == 77) {
                    if (matched->next != NULL) {
                        matched = matched->next;
                    }
                }
            } else if (menu == 27) {
                return;
            }
            system("clear");
            printf("\033[H");
            printf("\033[H");
            printf("%-15s: %-50s\n", "Nama", matched->nama);
            printf("%-15s: %-50s\n", "Alamat", matched->alamat);
            printf("%-15s: %-50s\n", "Kota", matched->kota);
            printf("%-15s: %-50s\n", "Tempat Lahir", matched->temp_lahir);
            printf("%-15s: %02d-%02d-%-20d\n", "Tanggal Lahir", matched->tgl_lahir.day, matched->tgl_lahir.month, matched->tgl_lahir.year);
            printf("%-15s: %d\n", "Umur", matched->umur);
            printf("%-15s: %-50s\n", "No. BPJS", matched->bpjs);
            printf("%-15s: %-50s\n", "ID Pasien", matched->id);
            printf("(<-) Previous \t (ENTER) Choose \t (->) Next \t (ESC) Quit\n");
        } while ((menu = getch()) != '\r');
        (*current) = head;
        while (strcmp((*current)->nama, matched->nama) && (*current) != NULL) {
            (*current) = (*current)->next;
        }
    }
    Pasien *toFree = matched;
    Pasien *nexttoFree;
    while (toFree != NULL) {
        nexttoFree = toFree->next;
        free(toFree->nama);
        free(toFree->alamat);
        free(toFree->kota);
        free(toFree->temp_lahir);
        free(toFree->bpjs);
        free(toFree->id);
        free(toFree);
        toFree = nexttoFree;
    }
    // printf("Kategori pasien yang ingin dicari?\n");
    // scanf(" %s", krit);

    // if (head == NULL){
    //     printf("Belum ada data pasien\n");
    //     return;
    // }

    // while (found == 0) {
    //     Pasien *temp = head;
    //     if (strcmp(krit, "Nama") == 0){
    //         printf("Pasien dengan %s siapa yang ingin dicari?\n", krit);
    //         scanf("%s", search);
    //         while (temp != NULL) {
    //             matchLen = calcmatch(temp->nama, search);
    //             if (matchLen == strlen(search)) {
    //                 printf("\n");
    //                 printf("Nama Pasien     : %s\n", temp->nama);
    //                 printf("Alamat          : %s\n", temp->alamat);
    //                 printf("Kota            : %s\n", temp->kota);
    //                 printf("Tempat Lahir    : %s\n", temp->temp_lahir);
    //                 printf("Tanggal Lahir   : %d-%d-%d\n", temp->tgl_lahir.day, temp->tgl_lahir.month, temp->tgl_lahir.year);
    //                 printf("Umur            : %d\n", temp->umur);
    //                 printf("No BPJS         : %s\n", temp->bpjs);
    //                 printf("ID Pasien       : %s\n", temp->id);
    //                 count = count + 1;
    //             }
    //             temp = temp->next;
    //         }
    //         if (count > 1) {
    //             printf("Ditemukkan lebih dari 1 pasien yang memiliki %s tersebut, tolong pilih berdasarkan ID Pasien dari daftar di atas\n", krit);
    //             strcpy(krit, "ID Pasien");
    //         } 
    //         else if (count == 0) {
    //             printf("Tidak ada pasien dengan nama %s \n", search);
    //             return;
    //         } 
    //         else {
    //             found = 1;
    //         }
    //     }
    //     else if(strcmp(krit, "Alamat") == 0){
    //         printf("Pasien dengan %s mana yang ingin dicari?\n", krit);
    //         scanf(" %s", search);
    //         while (temp != NULL) {
    //             matchLen = calcmatch(temp->alamat, search);
    //             if (matchLen == strlen(search)) {
    //                 printf("\n");
    //                 printf("Nama Pasien     : %s\n", temp->nama);
    //                 printf("Alamat          : %s\n", temp->alamat);
    //                 printf("Kota            : %s\n", temp->kota);
    //                 printf("Tempat Lahir    : %s\n", temp->temp_lahir);
    //                 printf("Tanggal Lahir   : %d-%d-%d\n", temp->tgl_lahir.day, temp->tgl_lahir.month, temp->tgl_lahir.year);
    //                 printf("Umur            : %d\n", temp->umur);
    //                 printf("No BPJS         : %s\n", temp->bpjs);
    //                 printf("ID Pasien       : %s\n", temp->id);
    //                 count = count + 1;
    //             }
    //             temp = temp->next;
    //         }

    //         if (count > 1) {
    //             printf("Ditemukkan lebih dari 1 pasien yang memiliki %s tersebut, tolong pilih berdasarkan ID Pasien dari daftar di atas\n", krit);
    //             strcpy(krit, "ID Pasien");
    //         } 
    //         else if (count == 0) {
    //             printf("Tidak ada pasien dengan %s %s \n", krit, search);
    //             return;
    //         } 
    //         else {
    //             found = 1;
    //         }
    //     }
    //     else if(strcmp(krit, "Tempat Lahir") == 0){
    //         printf("Pasien dengan %s mana yang ingin dicari?\n", krit);
    //         scanf("%s", search);
    //         while (temp != NULL) {
    //             matchLen = calcmatch(temp->temp_lahir, search);
    //             if (matchLen == strlen(search)) {
    //                 printf("\n");
    //                 printf("Nama Pasien     : %s\n", temp->nama);
    //                 printf("Alamat          : %s\n", temp->alamat);
    //                 printf("Kota            : %s\n", temp->kota);
    //                 printf("Tempat Lahir    : %s\n", temp->temp_lahir);
    //                 printf("Tanggal Lahir   : %d-%d-%d\n", temp->tgl_lahir.day, temp->tgl_lahir.month, temp->tgl_lahir.year);
    //                 printf("Umur            : %d\n", temp->umur);
    //                 printf("No BPJS         : %s\n", temp->bpjs);
    //                 printf("ID Pasien       : %s\n", temp->id);
    //                 count = count + 1;
    //                 }
    //             temp = temp->next;
    //         }
    //         if (count > 1) {
    //             printf("Ditemukkan lebih dari 1 pasien yang memiliki %s tersebut, tolong pilih berdasarkan ID Pasien dari daftar di atas\n", krit);
    //             strcpy(krit, "ID Pasien");
    //         } 
    //         else if (count == 0) {
    //             printf("Tidak ada pasien dengan %s %s \n",krit, search);
    //             return;
    //         } 
    //         else {
    //             found = 1;
    //         }
    //     }        
    //     else if(strcmp(krit, "Kota") == 0){
    //         printf("Pasien dengan %s mana yang ingin dicari?\n", krit);
    //         scanf("%s", search);
    //         while (temp != NULL) {
    //             matchLen = calcmatch(temp->kota, search);
    //             if (matchLen == strlen(search)) {
    //                 printf("\n");
    //                 printf("Nama Pasien     : %s\n", temp->nama);
    //                 printf("Alamat          : %s\n", temp->alamat);
    //                 printf("Kota            : %s\n", temp->kota);
    //                 printf("Tempat Lahir    : %s\n", temp->temp_lahir);
    //                 printf("Tanggal Lahir   : %d-%d-%d\n", temp->tgl_lahir.day, temp->tgl_lahir.month, temp->tgl_lahir.year);
    //                 printf("Umur            : %d\n", temp->umur);
    //                 printf("No BPJS         : %s\n", temp->bpjs);
    //                 printf("ID Pasien       : %s\n", temp->id);
    //                 count=count+1;
    //                 }
    //             temp = temp->next;
    //         }

    //         if (count > 1) {
    //             printf("Ditemukkan lebih dari 1 pasien yang memiliki %s tersebut, tolong pilih berdasarkan ID Pasien dari daftar di atas\n", krit);
    //             strcpy(krit, "ID Pasien");
    //         } 
    //         else if (count == 0) {
    //             printf("Tidak ada pasien dengan %s %s \n",krit, search);
    //             return;
    //         } 
    //         else {
    //             found = 1;
    //         }
    //     }
    //     else if(strcmp(krit, "Tanggal Lahir")==0) {
    //         printf("Pasien dengan %s mana yang ingin dicari?\n", krit);
    //         scanf(" %d %d %d", &d, &m, &y);
    //         while ((temp->tgl_lahir.day!=d)&&(temp->tgl_lahir.month!=m)&&(temp->tgl_lahir.year!=y)&&(temp != NULL)){
    //             temp = temp->next;
    //         }
    //         if (temp == NULL) {
    //             printf("Tidak ada pasien dengan %s %d %d %d \n",krit, d, m, y);
    //             return;
    //         }
    //         else {
    //             found = found+1;
    //         }
    //     }
    //     else if(strcmp(krit, "Umur") == 0){
    //         printf("Pasien dengan %s mana yang ingin dicari?\n", krit);
    //         scanf("%d", &d);
    //         while (temp != NULL) {
    //             if (temp->umur==d) {
    //                 printf("\n");
    //                 printf("Nama Pasien     : %s\n", temp->nama);
    //                 printf("Alamat          : %s\n", temp->alamat);
    //                 printf("Kota            : %s\n", temp->kota);
    //                 printf("Tempat Lahir    : %s\n", temp->temp_lahir);
    //                 printf("Tanggal Lahir   : %d-%d-%d\n", temp->tgl_lahir.day, temp->tgl_lahir.month, temp->tgl_lahir.year);
    //                 printf("Umur            : %d\n", temp->umur);
    //                 printf("No BPJS         : %s\n", temp->bpjs);
    //                 printf("ID Pasien       : %s\n", temp->id);
    //                 count=count+1;
    //                 }
    //             temp = temp->next;
    //         }
    //         if (count > 1) {
    //             printf("Ditemukkan lebih dari 1 pasien yang memiliki %s tersebut, tolong pilih berdasarkan ID Pasien dari daftar di atas\n", krit);
    //             strcpy(krit, "ID Pasien");
    //         } 
    //         else if (count == 0) {
    //             printf("Tidak ada pasien dengan %s %d \n",krit, d);
    //             return;
    //         } 
    //         else {
    //             found = 1;
    //         }
    //     }
    //     else if(strcmp(krit, "No BPJS") == 0){
    //         printf("Pasien dengan %s mana yang ingin dicari?\n", krit);
    //         fgets(search, 100, stdin);
    //         search[strcspn(search, "\n")] = 0; 
    //         while ((strcmp(temp->bpjs, search)!= 0)&&(temp != NULL)){
    //             temp = temp->next;
    //         }
    //         if (temp == NULL){
    //             printf("Tidak ada pasien dengan %s %s \n",krit, search);
    //             return;
    //         }
    //         else{
    //             found = found+1;
    //         }
    //     }

    //     else if(strcmp(krit, "ID Pasien")==0){
    //         printf("Pasien dengan %s mana yang ingin dicari?\n", krit);
    //         scanf(" %[^\n]%*c", search);
    //         while ((strcmp(temp->id, search)!= 0)&&(temp != NULL)){
    //             temp = temp->next;
    //         }
    //         if (temp == NULL){
    //             printf("Tidak ada pasien dengan %s %s \n",krit, search);
    //             return;
    //         }
    //         else {
    //             found = found+1;
    //         }
    //     }
    //     else {
    //         printf("Kriteria yang dicari tidak ada, tolong masukkan ulang");
    //         scanf("%s", krit);
    //     }
    // }
    
    // If found
    // printf("\n");
    // printf("Nama Pasien     : %s\n", temp->nama);
    // printf("Alamat          : %s\n", temp->alamat);
    // printf("Kota            : %s\n", temp->kota);
    // printf("Tempat Lahir    : %s\n", temp->temp_lahir);
    // printf("Tanggal Lahir   : %d-%d-%d\n", temp->tgl_lahir.day, temp->tgl_lahir.month, temp->tgl_lahir.year);
    // printf("Umur            : %d\n", temp->umur);
    // printf("No BPJS         : %s\n", temp->bpjs);
    // printf("ID Pasien       : %s\n", temp->id);
}
void hapus(Pasien **current) {
    Pasien *temp = *current;
    *current = (*current)->prev;
    if (temp->prev == NULL && temp->next == NULL) {
        return;
    }
    if (temp->prev == NULL) {
        if (temp->next != NULL) {
            temp->next->prev = NULL;
        }
        *current = temp->next; 
    } else {
        temp->prev->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
    }
    free(temp->nama);
    free(temp->alamat);
    free(temp->kota);
    free(temp->temp_lahir);
    free(temp->bpjs);
    free(temp->id);
    free(temp);
}

void ubah(Pasien *current) {
    char buffer[100];
    int d, m, y;
    int umur;
    char *endptr;

    if (current == NULL) {
        printf("Current is NULL\n");
        return;
    }

    printf("Masukkan Nama Baru: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0; 
    if (strcmp(buffer, "") != 0) {
        free(current->nama);
        current->nama = strdup(buffer);
    }
    printf("Masukkan Alamat Baru: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strcmp(buffer, "") != 0) {
        free(current->alamat);
        current->alamat = strdup(buffer);
    }
    printf("Masukkan Kota Baru: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strcmp(buffer, "") != 0) {
        free(current->kota);
        current->kota = strdup(buffer);
    }
    printf("Masukkan Tempat Lahir Baru: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strcmp(buffer, "") != 0) {
        free(current->temp_lahir);
        current->temp_lahir = strdup(buffer);
    }
    printf("Masukkan Tanggal Lahir Baru (dd mm yyyy): ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strcmp(buffer, "") != 0) {
        if (sscanf(buffer, "%d %d %d", &d, &m, &y) == 3) {
            current->tgl_lahir.day = d;
            current->tgl_lahir.month = m;
            current->tgl_lahir.year = y;
        } else {
            printf("Input tanggal lahir tidak valid. Data lama dipertahankan.\n");
        }
    }

    printf("Masukkan Umur Baru: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strcmp(buffer, "") != 0) {
        umur = strtol(buffer, &endptr, 10);
        if (*endptr == '\0') {
            current->umur = umur;
        } else {
            printf("Input umur tidak valid. Data lama dipertahankan.\n");
        }
    }

    printf("Masukkan No BPJS Baru: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strcmp(buffer, "") != 0) {
        free(current->bpjs);
        current->bpjs = strdup(buffer);
    }

    printf("Masukkan ID Pasien Baru: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strcmp(buffer, "") != 0) {
        free(current->id);
        current->id = strdup(buffer);
    }

    printf("Data pasien berhasil diubah\n");
}

void print(Pasien *head) {
    Pasien *current = head;
    while (current != NULL) {
        printf("\n");
        printf("Nama Pasien     : %s\n", current->nama);
        printf("Alamat          : %s\n", current->alamat);
        printf("Kota            : %s\n", current->kota);
        printf("Tempat Lahir    : %s\n", current->temp_lahir);
        printf("Tanggal Lahir   : %d-%d-%d\n", current->tgl_lahir.day, current->tgl_lahir.month, current->tgl_lahir.year);
        printf("Umur            : %d\n", current->umur);
        printf("No BPJS         : %s\n", current->bpjs);
        printf("ID Pasien       : %s\n", current->id);
        current = current->next;
    }
}

void perintah(Pasien *head) {
    char perintah[10];
    int selesai = 0;
    Pasien* current = head;
    while (selesai == 0) {
        printf("Masukkan operasi> ");
        scanf("%s", perintah);
        if (strcmp(perintah, "keluar") == 0) {
            selesai = 1;}
        else if (strcmp(perintah, "tambah") == 0) {
            tambah(&head);}
        else if (strcmp(perintah, "hapus") == 0) {
            hapus(&head);}
        else if (strcmp(perintah, "print") == 0) {
            print(head);}
        else if (strcmp(perintah, "cari") == 0) {
            cari(head, &current);}
        else if (strcmp(perintah, "ubah") == 0) {
            ubah(head);}
        else {
            printf("Perintah tidak valid, masukan ulang\n");
        }
    }
    current = head;
    while (current != NULL) {
        Pasien* temp = current;
        current = current->next;
        free(temp->nama);
        free(temp->alamat);
        free(temp->kota);
        free(temp->temp_lahir);
        free(temp->bpjs);
        free(temp->id);
        free(temp);
    }
}
