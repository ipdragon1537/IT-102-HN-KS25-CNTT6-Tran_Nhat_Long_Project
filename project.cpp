#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_PATIENTS 100
#define MAX_RECORDS 500
#include <stdlib.h>

struct Patient {
    char cardId[10];       
    char name[50];       
    char phone[15];       
    double debt;
    int visitDays;
};
struct Record {
    int recId;          
    char cardId[10];    
    char date[11];     
    char status[20];    
};
struct Patient patients[MAX_PATIENTS];
struct Record records[MAX_RECORDS];
int patientCount = 0;
int recordCount = 0;
int nextRecId = 1;
void xoaEnter();
void displayMenu();
void F01_addPatient();
void F02_updatePatient();
void F03_dischargePatient();
void F04_displayAllPatients();
void F05_searchPatient();
void F06_sortPatients();
void F07_addRecord();
void F08_viewMedicalHistory();
void displaySearchResults(struct Patient results[], int resultCount, const char* title);
void startNewPaginationSession(struct Patient list[], int count, char* title);
int findPatientIndex(char cardId[]);
int isCardIdUnique(char cardId[]);
char my_tolower(char c);
int comparePatientsAscending(const void *a, const void *b);
int comparePatientsDescending(const void *a, const void *b);
char my_tolower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}
int main() {
    int choice;
    do {
        displayMenu();
        printf("Nhap lua chon cua ban: ");
        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        xoaEnter();
        switch (choice) {
            case 1: 
                F01_addPatient(); 
                break;
            case 2: 
                F02_updatePatient(); 
                break;
            case 3: 
                F03_dischargePatient(); 
                break;
            case 4: 
                F04_displayAllPatients(); 
                break;
            case 5: 
                F05_searchPatient();
                break;
            case 6:
                F06_sortPatients();
                break;
            case 7:
                F07_addRecord();
                break;
            case 8: 
                F08_viewMedicalHistory();
                break;
            case 9: 
                printf("Thoat chuong trinh. Tam biet!\n"); 
                break;
            default: 
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
        if (choice != 9) {
            printf("\nNhan Enter de tiep tuc...");
            getchar();
        }
    } while (choice != 9);

    return 0;
}

void xoaEnter() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void displayMenu() {
    printf("========================================================\n");
    printf("= HE THONG QUAN LY BENH NHAN =\n");
    printf("========================================================\n");
    printf("1. Tiep nhan benh nhan moi\n");
    printf("2. Cap nhat thong tin benh nhan\n");
    printf("3. Xuat vien (Xoa benh nhan)\n");
    printf("4. Hien thi danh sach benh nhan\n");
    printf("5. Tim kiem benh nhan theo ten\n");
    printf("6. Sap xep danh sach benh nhan theo cong no\n");
    printf("7. Ghi nhan kham benh\n");
    printf("8. Xem lich su kham benh\n");
    printf("9. Thoat\n");
    printf("========================================================\n");
}
int isCardIdUnique(char cardId[]) {
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].cardId, cardId) == 0) {
            return 0;
        }
    }
    return 1;
}

int findPatientIndex(char cardId[]) {
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].cardId, cardId) == 0) {
            return i;
        }
    }
    return -1;
}

// Them benh nhan moi
void F01_addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("Loi: Danh sach benh nhan da day.\n");
        return;
    }
    struct Patient newPatient;
    printf("--- TIEP NHAN BENH NHAN MOI ---\n");
    do {
        printf("Nhap ma ho so (cardId) (9 ky tu): ");
        fgets(newPatient.cardId, sizeof(newPatient.cardId), stdin);
        newPatient.cardId[strcspn(newPatient.cardId, "\n")] = '\0';
        if (strlen(newPatient.cardId) == 0 || !isCardIdUnique(newPatient.cardId)) {
            printf("Loi: Ma ho so khong duoc rong va phai la duy nhat.\n");
        }
    } while (strlen(newPatient.cardId) == 0 || !isCardIdUnique(newPatient.cardId));
    
    do {
        printf("Nhap ten benh nhan: ");
        fgets(newPatient.name, sizeof(newPatient.name), stdin);
        newPatient.name[strcspn(newPatient.name, "\n")] = '\0';
        if (strlen(newPatient.name) == 0) {
            printf("Loi: Ten khong duoc rong.\n");
        }
    } while (strlen(newPatient.name) == 0);
    
    do {
        printf("Nhap so dien thoai: ");
        fgets(newPatient.phone, sizeof(newPatient.phone), stdin);
        newPatient.phone[strcspn(newPatient.phone, "\n")] = '\0';
        size_t phoneLength = strlen(newPatient.phone);
        if (strlen(newPatient.phone) == 0) {
            printf("Loi: So dien thoai khong duoc rong.\n");
        } else if (phoneLength < 10){
            printf("Loi: So dien thoai phai co it nhat 10 ky tu.\n");
        }
    } while (strlen(newPatient.phone) < 10);
    
    do {
        printf("Nhap cong no ban dau: ");
        if (scanf("%lf", &newPatient.debt) != 1 || newPatient.debt < 0) {
            printf("Loi: Cong no phai la mot so khong am.\n");
            xoaEnter();
        }
    } while (newPatient.debt < 0);
    xoaEnter();
    
    newPatient.visitDays = 0;
    patients[patientCount++] = newPatient;
    printf("Tiep nhan benh nhan thanh cong!\n");
}

// Cap nhat benh nhan
void F02_updatePatient() {
    char cardId[10];
    printf("--- CAP NHAT THONG TIN BENH NHAN ---\n");
    printf("Nhap ma ho so (cardId) cua benh nhan can cap nhat: ");
    fgets(cardId, sizeof(cardId), stdin);
    cardId[strcspn(cardId, "\n")] = '\0';

    int index = findPatientIndex(cardId);
    if (index == -1) {
        printf("Loi: Khong tim thay benh nhan voi ma ho so da nhap.\n");
        return;
    }
    
    printf("Tim thay benh nhan: %s\n", patients[index].name);
    
    printf("Nhap ten moi (de trong neu khong doi): ");
    char newName[50];
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = '\0';
    if (strlen(newName) > 0) {
        strcpy(patients[index].name, newName);
    }
    
    printf("Nhap so dien thoai moi (de trong neu khong doi): ");
    char newPhone[15];
    fgets(newPhone, sizeof(newPhone), stdin);
    newPhone[strcspn(newPhone, "\n")] = '\0';
    if (strlen(newPhone) > 0) {
        strcpy(patients[index].phone, newPhone);
    }
    
    printf("Nhap cong no moi (-1 de giu nguyen): ");
    double newDebt;
    if (scanf("%lf", &newDebt) == 1 && newDebt >= 0) {
        patients[index].debt = newDebt;
    }
    xoaEnter();
    
    printf("Cap nhat thong tin benh nhan thanh cong!\n");
}

// Xuat vien(xoa benh nhan)
void F03_dischargePatient(){
    char cardId[10];
    printf ("---XUAT VIEN(XOA BENH NHAN)---\n");
    printf ("Nhap ma ho so (cardId) cua benh nhan can xuat vien: ");
    fgets(cardId,sizeof(cardId), stdin);
    cardId[strcspn(cardId, "\n")] = '\0';
    
    int index = findPatientIndex(cardId);
    if (index == -1){
        printf ("Loi:Khong tim thay ma benh nhan\n");
        return;
    }
    
    // xac nhan xoa benh nhan
    printf("Ban co chac chan muon xoa benh nhan %s (ma: %s)? (y/n): ", 
           patients[index].name, patients[index].cardId);
    char confirm;
    scanf("%c", &confirm);
    xoaEnter();
    
    if (confirm != 'y' && confirm != 'Y') {
        printf("Huy thao tac xoa benh nhan.\n");
        return;
    }
    
    for (int i = index; i < patientCount - 1; i++){
        patients[i] = patients[i + 1];
    }
    patientCount--;
    printf ("Xuat vien benh nhan thanh cong!\n");
}
void F04_displayAllPatients() {
    printf("---DANH SACH BENH NHAN---\n");
    if (patientCount == 0) {
        printf("Khong co benh nhan nao trong danh sach.\n");
        printf("Nhan phim bat ky de tiep tuc...");
        while (getchar() != '\n');
        getchar();
        return;
    }
    int pageSize;
    printf("Nhap so benh nhan muon hien thi tren moi trang: ");
    while (scanf("%d", &pageSize) != 1 || pageSize <= 0) {
        while (getchar() != '\n');
        printf("Gia tri khong hop le. Vui long nhap mot so nguyen duong: ");
    }
    while (getchar() != '\n');
    
    int totalPages = (patientCount + pageSize - 1) / pageSize;
    int currentPage = 1;
    while (1) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        printf("---DANH SACH BENH NHAN---\n");
        printf("Trang %d/%d (Hien thi %d benh nhan moi trang)\n", currentPage, totalPages, pageSize);
        printf("----------------------------------------\n");
        
        int startIndex = (currentPage - 1) * pageSize;
        int endIndex = startIndex + pageSize;
        if (endIndex > patientCount) {
            endIndex = patientCount;
        }
        printf("---------------------------------------------------------------------------------------------------\n");
	    printf("| %-4s | %-15s | %-25s | %-12s | %-10s | %-7s |\n","STT", "cardId", "name", "phone", "debt", "visitDays");
	    printf("---------------------------------------------------------------------------------------------------\n");
        for (int i = startIndex; i < endIndex; i++) {
	        printf("| %-4d | %-15s | %-25s | %-12s | %-10.2lf | %-9d |\n", i + 1,patients[i].cardId,patients[i].name,patients[i].phone,patients[i].debt,patients[i].visitDays);
	    }
        if (endIndex > startIndex) {
            printf("---------------------------------------------------------------------------------------------------\n");
        }
        printf("DANG HIEN THI TRANG %d/%d\n", currentPage, totalPages);
        printf("\n=== CHON TUY CHON ===\n");
        printf("1. Trang tiep theo\n");
        if (totalPages > 1) {
            printf("2. Trang truoc\n");
            printf("3. Trang cu the\n");
        } else {
            printf("2. Trang cu the\n");
        }
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");

        char choice_str[10];
        fgets(choice_str, sizeof(choice_str), stdin);
        int choice = atoi(choice_str);
        switch (choice) {
            case 0:
                return;
            case 1:
                if (currentPage < totalPages) {
                    currentPage++;
                } else {
                    printf("Ban dang o trang cuoi cung! Nhan phim bat ky de tiep tuc...");
                    getchar();
                }
                break;
            case 2:
                if (totalPages > 1) {
                    if (currentPage > 1) {
                        currentPage--;
                    } else {
                        printf("Ban dang o trang dau tien! Nhan phim bat ky de tiep tuc...");
                        getchar();
                    }
                } else {
                    printf("Nhap so trang muon xem (1-%d): ", totalPages);
                    int targetPage;
                    if (scanf("%d", &targetPage) == 1 && targetPage >= 1 && targetPage <= totalPages) {
                        currentPage = targetPage;
                    } else {
                        printf("So trang khong hop le! Van giu nguyen trang hien tai.\n");
                        while (getchar() != '\n');
                        printf("Nhan phim bat ky de tiep tuc...");
                        getchar();
                    }
                    while (getchar() != '\n');
                }
                break;
            case 3:
                if (totalPages > 1) {
                    printf("Nhap so trang muon xem (1-%d): ", totalPages);
                    int targetPage;
                    if (scanf("%d", &targetPage) == 1 && targetPage >= 1 && targetPage <= totalPages) {
                        currentPage = targetPage;
                    } else {
                        printf("So trang khong hop le! Van giu nguyen trang hien tai.\n");
                        while (getchar() != '\n');
                        printf("Nhan phim bat ky de tiep tuc...");
                        getchar();
                    }
                    while (getchar() != '\n');
                } else {
                    printf("Chuc nang khong ton tai! Nhan phim bat ky de tiep tuc...");
                    getchar();
                }
                break;
            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
                printf("Nhan phim bat ky de tiep tuc...");
                getchar();
                break;
        }
    }
}
void F05_searchPatient() {
    printf("--- TIM KIEM BENH NHAN THEO TEN ---\n");
    if (patientCount == 0) {
        printf("Khong co benh nhan nao trong danh sach.\n");
        return;
    }
    char searchName[50];
    printf("Nhap ten benh nhan can tim: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    if (strlen(searchName) == 0) {
        printf("Ten tim kiem khong duoc rong.\n");
        return;
    } 
    struct Patient searchResults[MAX_PATIENTS];
    int resultCount = 0;
    for (int i = 0; i < patientCount; i++) {
        char patientNameLower[50];
        char searchNameLower[50];
        for (int j = 0; patients[i].name[j] != '\0'; j++) {
            patientNameLower[j] = my_tolower(patients[i].name[j]);
        }
        patientNameLower[strlen(patients[i].name)] = '\0';
        
        for (int j = 0; searchName[j] != '\0'; j++) {
            searchNameLower[j] = my_tolower(searchName[j]);
        }
        searchNameLower[strlen(searchName)] = '\0';
        if (strstr(patientNameLower, searchNameLower) != NULL) {
            searchResults[resultCount] = patients[i];
            resultCount++;
        }
    }
    
    if (resultCount == 0) {
        printf("Khong tim thay benh nhan nao co ten chua: %s\n", searchName);
        return;
    }
    char title[100];
    snprintf(title, sizeof(title), "KET QUA TIM KIEM: '%s' (%d ket qua)", searchName, resultCount);
    startNewPaginationSession(searchResults, resultCount, title);
}
void F06_sortPatients() {
    printf("--- SAP XEP DANH SACH BENH NHAN THEO CONG NO ---\n");
    
    if (patientCount == 0) {
        printf("Khong co benh nhan nao trong danh sach.\n");
        return;
    }
    
    printf("Chon kieu sap xep:\n");
    printf("1. Tang dan (tu cong no thap den cao)\n");
    printf("2. Giam dan (tu cong no cao den thap)\n");
    printf("Lua chon cua ban: ");
    
    int choice;
    if (scanf("%d", &choice) != 1) {
        xoaEnter();
        printf("Lua chon khong hop le.\n");
        return;
    }
    xoaEnter();
    struct Patient sortedPatients[MAX_PATIENTS];
    for (int i = 0; i < patientCount; i++) {
        sortedPatients[i] = patients[i];
    }
    
    switch (choice) {
        case 1:
            qsort(sortedPatients, patientCount, sizeof(struct Patient), comparePatientsAscending);
            startNewPaginationSession(sortedPatients, patientCount, "DANH SACH BENH NHAN SAP XEP TANG DAN THEO CONG NO");
            break;
        case 2:
            qsort(sortedPatients, patientCount, sizeof(struct Patient), comparePatientsDescending);
            startNewPaginationSession(sortedPatients, patientCount, "DANH SACH BENH NHAN SAP XEP GIAM DAN THEO CONG NO");
            break;
        default:
            printf("Lua chon khong hop le.\n");
            return;
    }
    
    printf("Sap xep thanh cong!\n");
}
int comparePatientsAscending(const void *a, const void *b) {
    const struct Patient *patientA = (const struct Patient *)a;
    const struct Patient *patientB = (const struct Patient *)b;
    
    if (patientA->debt < patientB->debt) return -1;
    if (patientA->debt > patientB->debt) return 1;
    return 0;
}
int comparePatientsDescending(const void *a, const void *b) {
    const struct Patient *patientA = (const struct Patient *)a;
    const struct Patient *patientB = (const struct Patient *)b;
    
    if (patientA->debt > patientB->debt) return -1;
    if (patientA->debt < patientB->debt) return 1;
    return 0;
}
void displaySearchResults(struct Patient results[], int resultCount, const char* title) {
    printf("\n%s\n", title);
    printf("----------------------------------------\n");
    
    if (resultCount == 0) {
        printf("Khong co ket qua nao.\n");
        return;
    }
    
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("| %-4s | %-15s | %-25s | %-12s | %-10s | %-7s |\n", "STT", "cardId", "name", "phone", "debt", "visitDays");
    printf("---------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < resultCount; i++) {
        printf("| %-4d | %-15s | %-25s | %-12s | %-10.2lf | %-9d |\n", 
               i + 1, results[i].cardId, results[i].name, results[i].phone, 
               results[i].debt, results[i].visitDays);
    }
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("Tong so: %d benh nhan\n", resultCount);
}
void startNewPaginationSession(struct Patient list[], int count, char* title) {
    if (count == 0) {
        printf("Khong co du lieu de hien thi.\n");
        return;
    }
    
    int pageSize;
    printf("Nhap so benh nhan muon hien thi tren moi trang: ");
    while (scanf("%d", &pageSize) != 1 || pageSize <= 0) {
        while (getchar() != '\n');
        printf("Gia tri khong hop le. Vui long nhap mot so nguyen duong: ");
    }
    while (getchar() != '\n');
    
    int totalPages = (count + pageSize - 1) / pageSize;
    int currentPage = 1;
    
    while (1) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        printf("%s\n", title);
        printf("Trang %d/%d (Hien thi %d benh nhan moi trang)\n", currentPage, totalPages, pageSize);
        printf("----------------------------------------\n");
        
        int startIndex = (currentPage - 1) * pageSize;
        int endIndex = startIndex + pageSize;
        if (endIndex > count) {
            endIndex = count;
        }
        
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("| %-4s | %-15s | %-25s | %-12s | %-10s | %-7s |\n", "STT", "cardId", "name", "phone", "debt", "visitDays");
        printf("---------------------------------------------------------------------------------------------------\n");
        
        for (int i = startIndex; i < endIndex; i++) {
            printf("| %-4d | %-15s | %-25s | %-12s | %-10.2lf | %-9d |\n", 
                   i + 1, list[i].cardId, list[i].name, list[i].phone, 
                   list[i].debt, list[i].visitDays);
        }
        
        if (endIndex > startIndex) {
            printf("---------------------------------------------------------------------------------------------------\n");
        }
        
        printf("DANG HIEN THI TRANG %d/%d\n", currentPage, totalPages);
        printf("\n=== CHON TUY CHON ===\n");
        printf("1. Trang tiep theo\n");
        
        if (totalPages > 1) {
            printf("2. Trang truoc\n");
            printf("3. Trang cu the\n");
        } else {
            printf("2. Trang cu the\n");
        }
        
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");

        char choice_str[10];
        fgets(choice_str, sizeof(choice_str), stdin);
        int choice = atoi(choice_str);
        
        switch (choice) {
            case 0:
                return;
            case 1:
                if (currentPage < totalPages) {
                    currentPage++;
                } else {
                    printf("Ban dang o trang cuoi cung! Nhan phim bat ky de tiep tuc...");
                    getchar();
                }
                break;
            case 2:
                if (totalPages > 1) {
                    if (currentPage > 1) {
                        currentPage--;
                    } else {
                        printf("Ban dang o trang dau tien! Nhan phim bat ky de tiep tuc...");
                        getchar();
                    }
                } else {
                    printf("Nhap so trang muon xem (1-%d): ", totalPages);
                    int targetPage;
                    if (scanf("%d", &targetPage) == 1 && targetPage >= 1 && targetPage <= totalPages) {
                        currentPage = targetPage;
                    } else {
                        printf("So trang khong hop le! Van giu nguyen trang hien tai.\n");
                        while (getchar() != '\n');
                        printf("Nhan phim bat ky de tiep tuc...");
                        getchar();
                    }
                    while (getchar() != '\n');
                }
                break;
            case 3:
                if (totalPages > 1) {
                    printf("Nhap so trang muon xem (1-%d): ", totalPages);
                    int targetPage;
                    if (scanf("%d", &targetPage) == 1 && targetPage >= 1 && targetPage <= totalPages) {
                        currentPage = targetPage;
                    } else {
                        printf("So trang khong hop le! Van giu nguyen trang hien tai.\n");
                        while (getchar() != '\n');
                        printf("Nhan phim bat ky de tiep tuc...");
                        getchar();
                    }
                    while (getchar() != '\n');
                } else {
                    printf("Chuc nang khong ton tai! Nhan phim bat ky de tiep tuc...");
                    getchar();
                }
                break;
            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
                printf("Nhan phim bat ky de tiep tuc...");
                getchar();
                break;
        }
    }
}
void F07_addRecord() {
    printf("--- GHI NHAN KHAM BENH ---\n");
    
    if (patientCount == 0) {
        printf("Khong co benh nhan nao trong danh sach.\n");
        return;
    }
    if (recordCount >= MAX_RECORDS) {
        printf("Loi: Danh sach kham benh da day.\n");
        return;
    }
    char cardId[10];
    printf("Nhap ma ho so (cardId) cua benh nhan: ");
    fgets(cardId, sizeof(cardId), stdin);
    cardId[strcspn(cardId, "\n")] = '\0';
    
    int patientIndex = findPatientIndex(cardId);
    if (patientIndex == -1) {
        printf("Loi: Khong tim thay benh nhan voi ma ho so da nhap.\n");
        return;
    }
    
    struct Record newRecord;
    newRecord.recId = nextRecId++;
    strcpy(newRecord.cardId, cardId);
    do {
        printf("Nhap ngay kham (dd/mm/yyyy): ");
        fgets(newRecord.date, sizeof(newRecord.date), stdin);
        newRecord.date[strcspn(newRecord.date, "\n")] = '\0';
        if (strlen(newRecord.date) == 0) {
            printf("Loi: Ngay kham khong duoc rong.\n");
        }
    } while (strlen(newRecord.date) == 0);
    
    // Nh?p tình tr?ng
    do {
        printf("Nhap tinh trang benh: ");
        fgets(newRecord.status, sizeof(newRecord.status), stdin);
        newRecord.status[strcspn(newRecord.status, "\n")] = '\0';
        if (strlen(newRecord.status) == 0) {
            printf("Loi: Tinh trang khong duoc rong.\n");
        }
    } while (strlen(newRecord.status) == 0);
    records[recordCount++] = newRecord;
    patients[patientIndex].visitDays++;
    
    printf("Ghi nhan kham benh thanh cong!\n");
    printf("Ma kham benh: %d\n", newRecord.recId);
    printf("Benh nhan: %s\n", patients[patientIndex].name);
    printf("Ngay kham: %s\n", newRecord.date);
    printf("Tinh trang: %s\n", newRecord.status);
}
void F08_viewMedicalHistory() {
    printf("--- LICH SU KHAM BENH ---\n");
    
    if (recordCount == 0) {
        printf("Khong co lich su kham benh nao.\n");
        return;
    }
    
    char cardId[10];
    printf("Nhap ma ho so (cardId) cua benh nhan: ");
    fgets(cardId, sizeof(cardId), stdin);
    cardId[strcspn(cardId, "\n")] = '\0';
    
    int patientIndex = findPatientIndex(cardId);
    if (patientIndex == -1) {
        printf("Loi: Khong tim thay benh nhan voi ma ho so da nhap.\n");
        return;
    }
    struct Record patientRecords[MAX_RECORDS];
    int patientRecordCount = 0;
    
    for (int i = 0; i < recordCount; i++) {
        if (strcmp(records[i].cardId, cardId) == 0) {
            patientRecords[patientRecordCount] = records[i];
            patientRecordCount++;
        }
    }
    
    if (patientRecordCount == 0) {
        printf("Benh nhan %s chua co lich su kham benh.\n", patients[patientIndex].name);
        return;
    }
    int pageSize;
    printf("Nhap so lan kham muon hien thi tren moi trang: ");
    if (scanf("%d", &pageSize) != 1 || pageSize <= 0) {
        printf("Gia tri khong hop le. Su dung mac dinh 5.\n");
        pageSize = 5;
    }
    xoaEnter();
    
    int totalPages = (patientRecordCount + pageSize - 1) / pageSize;
    int currentPage = 1;
    
    while (1) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        printf("--- LICH SU KHAM BENH ---\n");
        printf("Benh nhan: %s (Ma: %s)\n", patients[patientIndex].name, patients[patientIndex].cardId);
        printf("So dien thoai: %s\n", patients[patientIndex].phone);
        printf("Tong so lan kham: %d\n", patientRecordCount);
        printf("Trang %d/%d (Hien thi %d lan kham moi trang)\n", currentPage, totalPages, pageSize);
        printf("------------------------------------------------------------\n");
        
        int startIndex = (currentPage - 1) * pageSize;
        int endIndex = startIndex + pageSize;
        if (endIndex > patientRecordCount) {
            endIndex = patientRecordCount;
        }
        
        printf("--------------------------------------------------------------------\n");
        printf("| %-4s | %-8s | %-10s | %-30s |\n", "STT", "Ma KB", "Ngay kham", "Tinh trang benh");
        printf("--------------------------------------------------------------------\n");
        
        for (int i = startIndex; i < endIndex; i++) {
            printf("| %-4d | %-8d | %-10s | %-30s |\n", 
                   i + 1, patientRecords[i].recId, patientRecords[i].date, patientRecords[i].status);
        }
        
        printf("--------------------------------------------------------------------\n");
        printf("DANG HIEN THI TRANG %d/%d - Tu lan kham %d den %d\n", 
               currentPage, totalPages, startIndex + 1, endIndex);
        
        printf("\n=== CHON TUY CHON ===\n");
        printf("1. Trang tiep theo\n");
        
        if (totalPages > 1) {
            printf("2. Trang truoc\n");
            printf("3. Chuyen den trang\n");
        } else {
            printf("2. Thoat\n");
        }
        
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");

        char choice_str[10];
        fgets(choice_str, sizeof(choice_str), stdin);
        int choice = atoi(choice_str);
        
        switch (choice) {
            case 0:
                return;
            case 1:
                if (currentPage < totalPages) {
                    currentPage++;
                } else {
                    printf("Ban dang o trang cuoi cung!\n");
                    printf("Nhan Enter de tiep tuc...");
                    getchar();
                }
                break;
            case 2:
                if (totalPages > 1) {
                    if (currentPage > 1) {
                        currentPage--;
                    } else {
                        printf("Ban dang o trang dau tien!\n");
                        printf("Nhan Enter de tiep tuc...");
                        getchar();
                    }
                } else {
                    return;
                }
                break;
            case 3:
                if (totalPages > 1) {
                    printf("Nhap so trang muon xem (1-%d): ", totalPages);
                    int targetPage;
                    if (scanf("%d", &targetPage) == 1 && targetPage >= 1 && targetPage <= totalPages) {
                        currentPage = targetPage;
                    } else {
                        printf("So trang khong hop le!\n");
                    }
                    xoaEnter();
                } else {
                    printf("Chi co 1 trang!\n");
                    printf("Nhan Enter de tiep tuc...");
                    getchar();
                }
                break;
            default:
                printf("Lua chon khong hop le!\n");
                printf("Nhan Enter de tiep tuc...");
                getchar();
                break;
        }
    }
}

