#include "kania.h"

// Add
void addRiwayat(Riwayat *current){ 
    Riwayat* newRiwayat = (Riwayat*)malloc(sizeof(Riwayat));
    char buffer[100];
    printf("%-15s : ","Tanggal");
    scanf("%d%d%d", &newRiwayat->tanggal.day, &newRiwayat->tanggal.month, &newRiwayat->tanggal.year);
    printf("%-15s : ", "Diagnosis");
    scanf(" %[^\n]%*c", buffer);
    newRiwayat->diagnosis = strdup(buffer);
    printf("%-15s : ", "Tindakan");
    scanf(" %[^\n]%*c", buffer);
    newRiwayat->tindakan = strdup(buffer);
    printf("%-15s : ", "Tanggal Kontrol");
    scanf("%d%d%d", &newRiwayat->kontrol.day, &newRiwayat->kontrol.month, &newRiwayat->kontrol.year);
    printf("%-15s : ", "Biaya");
    scanf("%f", &newRiwayat->biaya);
    createRiwayat(&current, newRiwayat);
}

// Modify
void modifyRiwayat(Riwayat *current){
    int pilihan;
    char buffer[100];
    printf("( 1) Tanggal \t ( 2) Diagnosis \t ( 3) Tindakan\n");
    pilihan = getch();
    switch(pilihan){
        case '1' :
            printf("%-15s : ", "Tanggal");
            scanf("%d%d%d", &(current->tanggal.day), &(current->tanggal.month), &(current->tanggal.year));
            break; 
        case '2' : 
            printf("%-15s", "Diagnosis");
            scanf(" %[^\n]%*c", buffer);
            free(current->diagnosis);
            current->diagnosis = strdup(buffer);
            break;
        case '3' : 
            printf("%-15s : ", "Tindakan");
            scanf(" %[^\n]%*c", buffer);
            current->tindakan = strdup(buffer);
            printf("%-15s : ", "Tanggal Kontrol");
            scanf("%d%d%d", &(current->kontrol.day), &(current->kontrol.month), &(current->kontrol.year));
            printf("%-15s : ", "Biaya");
            scanf("%f", &current->biaya);
            break;
    }
}

// Delate
void deleteRiwayat(Riwayat **current){
    Riwayat *temp = *current;
    (*current) = (*current)->prev;
    if (temp->prev == NULL && temp->next == NULL) {
        free(temp->diagnosis);
        free(temp->tindakan);
        free(temp);
        (*current) = NULL;
        return;
    }
    if (temp->prev == NULL) {
        free(temp->next->prev);
        temp->next->prev = NULL;
        *current = temp->next;
    } else {
        temp->prev->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
    }
}

// Display
void display(Pasien *current){
    printf("Kedatangan    : %d-%d-%d\n", current->riwayat->tanggal.day, current->riwayat->tanggal.month, current->riwayat->tanggal.year);
    printf("Diagnosis     : %s\n", current->riwayat->diagnosis);
    printf("Tindakan      : %s\n", current->riwayat->tindakan);
    printf("Kontrol       : %d-%d-%d\n", current->riwayat->kontrol.day, current->riwayat->kontrol.month, current->riwayat->kontrol.year);
    printf("Biaya         : %f\n", current->riwayat->biaya);
}

// Search
void searchRiwayat(Pasien *current){
    int found = 0;
    Tanggal tanggal; 
    char buffer[100]; 
    int pilihan;
    printf("( 1) Tanggal \t (2) Diagnosis \t (3) Tindakan\n");
    pilihan = getch();
    switch(pilihan){
        case '1': 
            printf("%-15s : ", "Tanggal");
            scanf("%d%d%d", &tanggal.day, &tanggal.month, &tanggal.year);
            while(current != NULL){
                if(tanggal.day == current->riwayat->tanggal.day && tanggal.month == current->riwayat->tanggal.month && tanggal.year == current->riwayat->tanggal.year){
                    found = 1; 
                    display(current);
                }
                current = current->next;
            }
            break;
        case '2': 
            printf("%-15s : ", "Diagnosis");
            scanf(" %[^\n]%*c", buffer);
            while(current != NULL){
                if(strcmp(current->riwayat->diagnosis, buffer) == 0){
                    found = 1; 
                    display(current);
                }
                current = current->next;
            }
            break;
        case '3': 
            printf("%-15s : ", "Tindakan");
            scanf(" %[^\n]%*c", buffer);
            while(current != NULL){
                if(strcmp(current->riwayat->tindakan, buffer)==0){
                    found = 1;
                    display(current);
                }
            }
            break;
    }
    getch();
}   

// Laveinshtein Distance
/*
int calculateDistance(const char* inputWord, const char* checkWord) {
    int len1 = strlen(inputWord);
    int len2 = strlen(checkWord);
    int** wordMatrix = (int**)malloc((len1 + 1) * sizeof(int*));
    for (int i = 0; i <= len1; i++) {
        wordMatrix[i] = (int*)malloc((len2 + 1) * sizeof(int));
    }

    for (int i = 0; i <= len1; i++) {
        wordMatrix[i][0] = i;
    }

    for (int j = 0; j <= len2; j++) {
        wordMatrix[0][j] = j;
    }

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (inputWord[i - 1] == checkWord[j - 1]) {
                wordMatrix[i][j] = wordMatrix[i - 1][j - 1];
            } else {
                int min = wordMatrix[i - 1][j] + 1;
                if (wordMatrix[i][j - 1] + 1 < min) {
                    min = wordMatrix[i][j - 1] + 1;
                }
                if (wordMatrix[i - 1][j - 1] + 1 < min) {
                    min = wordMatrix[i - 1][j - 1] + 1;
                }
                wordMatrix[i][j] = min;
            }
        }
    }

    int distance = wordMatrix[len1][len2];

    for (int i = 0; i <= len1; i++) {
        free(wordMatrix[i]);
    }
    free(wordMatrix);

    return distance;
}

int startsWith(const char* str, const char* prefix) {
    while (*prefix) {
        if (*prefix++ != *str++) {
            return 0;
        }
    }
    return 1;
}

void similarExists(const char* inputSearch, Pasien* head, int pilihan) {
    Pasien* current = head;
    int maxDistance = strlen(inputSearch);

    // Assuming a maximum of 100 similar words
    Riwayat** fuzzyWordList = (Riwayat**)malloc(100 * sizeof(Riwayat*));
    int fuzzyWordCount = 0;

    while (current != NULL) {
        Riwayat* riwayat = current->riwayat;
        while (riwayat != NULL) {
            const char* checkWord = NULL;
            switch (pilihan) {
                case 1: {
                    char dateStr[11];
                    snprintf(dateStr, sizeof(dateStr), "%02d-%02d-%04d", riwayat->tanggal.day, riwayat->tanggal.month, riwayat->tanggal.year);
                    checkWord = dateStr;
                    break;
                }
                case 2:
                    checkWord = riwayat->diagnosis;
                    break;
                case 3:
                    checkWord = riwayat->tindakan;
                    break;
            }

            if (checkWord && startsWith(checkWord, inputSearch)) {
                // Check for uniqueness before adding
                int exists = 0;
                for (int j = 0; j < fuzzyWordCount; j++) {
                    const char* existingWord = NULL;
                    switch (pilihan) {
                        case 1: {
                            char existingDateStr[11];
                            snprintf(existingDateStr, sizeof(existingDateStr), "%02d-%02d-%04d",
                                     fuzzyWordList[j]->tanggal.day, fuzzyWordList[j]->tanggal.month, fuzzyWordList[j]->tanggal.year);
                            existingWord = existingDateStr;
                            break;
                        }
                        case 2:
                            existingWord = fuzzyWordList[j]->diagnosis;
                            break;
                        case 3:
                            existingWord = fuzzyWordList[j]->tindakan;
                            break;
                    }
                    if (strcmp(existingWord, checkWord) == 0) {
                        exists = 1;
                        break;
                    }
                }
                if (!exists) {
                    fuzzyWordList[fuzzyWordCount] = riwayat;
                    fuzzyWordCount++;
                }
            }

            riwayat = riwayat->next;
        }
        current = current->next;
    }

    for (int i = 0; i < fuzzyWordCount; i++) {
        switch (pilihan) {
            case 1:
                printf("%d. %02d-%02d-%04d\n", i + 1, fuzzyWordList[i]->tanggal.day, fuzzyWordList[i]->tanggal.month, fuzzyWordList[i]->tanggal.year);
                break;
            case 2:
                printf("%d. %s\n", i + 1, fuzzyWordList[i]->diagnosis);
                break;
            case 3:
                printf("%d. %s\n", i + 1, fuzzyWordList[i]->tindakan);
                break;
        }
    }

    int selection;
    printf("> ");
    scanf("%d", &selection);

    if (selection > 0 && selection <= fuzzyWordCount) {
        Riwayat* selectedRecord = fuzzyWordList[selection - 1];
        printf("ID Pasien: %s\n", head->id);  // Assuming you want the ID of the head patient
        printf("Tanggal: %02d-%02d-%04d\n", selectedRecord->tanggal.day, selectedRecord->tanggal.month, selectedRecord->tanggal.year);
        printf("Diagnosis: %s\n", selectedRecord->diagnosis);
        printf("Tindakan: %s\n", selectedRecord->tindakan);
        printf("Tanggal Kontrol: %02d-%02d-%04d\n", selectedRecord->kontrol.day, selectedRecord->kontrol.month, selectedRecord->kontrol.year);
        printf("Biaya: %.2f\n", selectedRecord->biaya);
    } else {
        printf("Invalid selection.\n");
    }

    free(fuzzyWordList);
}
*/

// void menu(Pasien* head){
//     int choice;
//     do{
//         printf("( 1) Add \t ( 2) Change\n");
//         printf("( 3) Delate \t ( 4) Search\n");
//         printf("> ");
//         scanf("%d", &choice);
//         switch(choice){
//             case 1 : 
//                 addRiwayat(head);
//                 break; 

//             case 2 :
//                 modifyRiwayat(head);
//                 break;
//             case 3 :
//                 deleteRiwayat(head);
//                 break;
//             case 4 :
//                 searchRiwayat(head);
//                 break;
//             case 5: 
//                 printf("Keluar dari program");
//                 printf("\n");
//                 break;
//             default :
//                 printf("Ulangi input");
//                 printf("\n");
//                 break;
//         }
//     }while (choice != 4);
//     printf("Program selesai");
// }