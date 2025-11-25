#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_PATIENTS 100
#define MAX_RECORDS 500
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
void F08_viewPatientRecords();
int findPatientIndex(char cardId[]);
int isCardIdUnique(char cardId[]);
void sortPatientsByDebt(int order);
char my_tolower(char c);

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
			    F08_viewPatientRecords(); 
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
        if (strlen(newPatient.phone) == 0) {
            printf("Loi: So dien thoai khong duoc rong.\n");
        }
    } while (strlen(newPatient.phone) == 0);
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

