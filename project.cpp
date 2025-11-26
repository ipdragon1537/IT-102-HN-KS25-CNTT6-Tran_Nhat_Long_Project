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
int mySystemVariable;
int main() {
	const char* system("cls");
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
			    
			    break;
            case 6:
			    
				break;
            case 7:
			    
				break;
            case 8: 
			     
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
	}
	for (int i = index;i<patientCount-1;i++){
		patients[i]=patients[i+1];
	}
	patientCount--;
	printf ("Xuat vien benh nhan thanh cong");
}
void F04_displayAllPatients() {
    printf("---DANH SACH BENH NHAN---\n");
    
    if (patientCount == 0) {
        printf("Khong co benh nhan nao trong danh sach.\n");
        printf("Nhan phim bat ky de tiep tuc...");
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
        for (int i = startIndex; i < endIndex; i++) {
            printf("%d. Ma ho so: %s, Ten: %s, SDT: %s, Cong no: %.2lf, So ngay kham: %d\n",
                   i + 1, patients[i].cardId, patients[i].name, 
                   patients[i].phone, patients[i].debt, patients[i].visitDays);
        }

        printf("----------------------------------------\n");
        printf("DANG HIEN THI TRANG %d/%d\n", currentPage, totalPages);
        if (currentPage < totalPages) {
            printf("\n=== TU DONG CHUYEN TRANG ===\n");
            printf("1. Trang tiep theo (trang %d)\n", currentPage + 1);
            printf("2. Trang cu the\n");
            printf("0. Thoat\n");
            printf("Lua chon cua ban: ");
        } else {
            printf("\n=== DANG O TRANG CUOI ===\n");
            printf("1. Ve trang dau\n");
            printf("2. Trang cu the\n");
            printf("0. Thoat\n");
            printf("Lua chon cua ban: ");
        }
        int choice;
        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        while (getchar() != '\n');
        switch (choice) {
            case 0:
                return;
                
            case 1:
                if (currentPage < totalPages) {
                    currentPage++; 
                } else {
                    currentPage --;
                }
                break;
            case 2:
                printf("Nhap so trang muon xem (1-%d): ", totalPages);
                int targetPage;
                if (scanf("%d", &targetPage) == 1 && targetPage >= 1 && targetPage <= totalPages) {
                    currentPage = targetPage;
                } else {
                    printf("So trang khong hop le! Van giu nguyen trang hien tai.\n");
                    printf("Nhan phim bat ky de tiep tuc...");
                    getchar();
                }
                while (getchar() != '\n');
                break;
            default:
                printf("Lua chon khong hop le! Vui long chon 0, 1 hoac 2.\n");
                printf("Nhan phim bat ky de tiep tuc...");
                getchar();
                break;
        }
    }
}
