#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_PATIENTS 100
#define MAX_RECORDS 500
#include <stdlib.h>

// Dinh nghia cau truc Benh nhan
struct Patient {
    char cardId[10];       // Ma the benh nhan
    char name[50];         // Ten benh nhan
    char phone[15];        // So dien thoai
    double debt;           // Cong no
    int visitDays;         // So ngay da kham
};

// Dinh nghia cau truc Ho so kham benh
struct Record {
    int recId;             // ID ho so
    char cardId[10];       // Ma the benh nhan (lien ket voi Patient)
    char date[11];         // Ngay kham (dinh dang dd/mm/yyyy)
    char status[20];       // Tinh trang benh
};

// Mang toan cuc cho benh nhan va ho so
struct Patient patients[MAX_PATIENTS];
struct Record records[MAX_RECORDS];
int patientCount = 0;      // So benh nhan hien tai
int recordCount = 0;       // So ho so hien tai
int nextRecId = 1;         // ID ho so tiep theo (tu dong tang)

// Khai bao ham
void clearScreen();
void waitForEnter();
void displayMainMenu();
void showPage(const char* title);
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

// Ham xoa man hinh
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Ham cho nhan Enter
void waitForEnter() {
    printf("\nNhan Enter de tiep tuc...");
    while (getchar() != '\n');
}

// Ham hien thi tieu de trang
void showPage(const char* title) {
    clearScreen();
    printf("========================================================\n");
    printf("= %-50s =\n", title);
    printf("========================================================\n");
}

// Ham chuyen ky tu thanh chu thuong
char my_tolower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

// Ham kiem tra ho so trung lap
int isRecordDuplicate(const char* cardId, const char* date) {
    for (int i = 0; i < recordCount; i++) {
        // So sanh cardId va ngay kham
        if (strcmp(records[i].cardId, cardId) == 0 && strcmp(records[i].date, date) == 0) {
            return 1; // Trung lap
        }
    }
    return 0; // Khong trung lap
}

// Them du lieu mau de kiem tra
void addSamplePatients() {
    // Them 8 benh nhan mau nhu da co
    if (patientCount < MAX_PATIENTS) {
        strcpy(patients[patientCount].cardId, "A001");
        strcpy(patients[patientCount].name, "Nguyen Van A");
        strcpy(patients[patientCount].phone, "0912345678");
        patients[patientCount].debt = 500.00;
        patients[patientCount].visitDays = 2;
        patientCount++;
    }
    if (patientCount < MAX_PATIENTS) {
        strcpy(patients[patientCount].cardId, "B002");
        strcpy(patients[patientCount].name, "Le Thi B");
        strcpy(patients[patientCount].phone, "0987654321");
        patients[patientCount].debt = 1200.50;
        patients[patientCount].visitDays = 5;
        patientCount++;
    }
    if (patientCount < MAX_PATIENTS) {
        strcpy(patients[patientCount].cardId, "C003");
        strcpy(patients[patientCount].name, "Tran Van C");
        strcpy(patients[patientCount].phone, "0909090909");
        patients[patientCount].debt = 0.00;
        patients[patientCount].visitDays = 1;
        patientCount++;
    }
    if (patientCount < MAX_PATIENTS) {
        strcpy(patients[patientCount].cardId, "D004");
        strcpy(patients[patientCount].name, "Pham Thi D");
        strcpy(patients[patientCount].phone, "0812345678");
        patients[patientCount].debt = 250.75;
        patients[patientCount].visitDays = 3;
        patientCount++;
    }
    if (patientCount < MAX_PATIENTS) {
        strcpy(patients[patientCount].cardId, "E005");
        strcpy(patients[patientCount].name, "Vu Van E");
        strcpy(patients[patientCount].phone, "0365478912");
        patients[patientCount].debt = 1500.00;
        patients[patientCount].visitDays = 8;
        patientCount++;
    }
    if (patientCount < MAX_PATIENTS) {
        strcpy(patients[patientCount].cardId, "F006");
        strcpy(patients[patientCount].name, "Hoang Le F");
        strcpy(patients[patientCount].phone, "0778945612");
        patients[patientCount].debt = 75.50;
        patients[patientCount].visitDays = 1;
        patientCount++;
    }
    if (patientCount < MAX_PATIENTS) {
        strcpy(patients[patientCount].cardId, "G007");
        strcpy(patients[patientCount].name, "Nguyen Huu G");
        strcpy(patients[patientCount].phone, "0923456789");
        patients[patientCount].debt = 3200.00;
        patients[patientCount].visitDays = 15;
        patientCount++;
    }
    if (patientCount < MAX_PATIENTS) {
        strcpy(patients[patientCount].cardId, "H008");
        strcpy(patients[patientCount].name, "Tran Thi H");
        strcpy(patients[patientCount].phone, "0889123456");
        patients[patientCount].debt = 600.25;
        patients[patientCount].visitDays = 4;
        patientCount++;
    }
    if (patientCount < MAX_PATIENTS) {
        strcpy(patients[patientCount].cardId, "I009");
        strcpy(patients[patientCount].name, "Le Van I");
        strcpy(patients[patientCount].phone, "0934567890");
        patients[patientCount].debt = 400.00;
        patients[patientCount].visitDays = 2;
        patientCount++;
    }
    if (patientCount < MAX_PATIENTS) {
        strcpy(patients[patientCount].cardId, "K010");
        strcpy(patients[patientCount].name, "Cao Thi K");
        strcpy(patients[patientCount].phone, "0798765432");
        patients[patientCount].debt = 950.00;
        patients[patientCount].visitDays = 6;
        patientCount++;
    }
    printf("Da them %d benh nhan mau vao danh sach.\n", patientCount);
}

// Ham hien thi menu chinh
void displayMainMenu() {
    showPage("HE THONG QUAN LY BENH NHAN");
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
    printf("Nhap lua chon cua ban: ");
}

// Ham main
int main() {
    int choice;
    addSamplePatients(); // Them du lieu mau
    
    do {
        displayMainMenu();
        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        while (getchar() != '\n');
        
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
                showPage("THOAT CHUONG TRINH");
                printf("Cam on ban da su dung dich vu!\n");
                printf("Tam biet!\n");
                break;
            default: 
                printf("Lua chon khong hop le. Vui long chon lai.\n");
                waitForEnter();
        }
    } while (choice != 9);

    return 0;
}

// Ham kiem tra ma the co duy nhat khong
int isCardIdUnique(char cardId[]) {
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].cardId, cardId) == 0) {
            return 0; // Khong duy nhat
        }
    }
    return 1; // Duy nhat
}

// Ham tim vi tri benh nhan trong mang
int findPatientIndex(char cardId[]) {
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].cardId, cardId) == 0) {
            return i; // Tra ve vi tri
        }
    }
    return -1; // Khong tim thay
}

// Ham them benh nhan moi (F01)
void F01_addPatient() {
    char choice;
    do {
        showPage("TIEP NHAN BENH NHAN MOI");
        
        // Kiem tra danh sach day
        if (patientCount >= MAX_PATIENTS) {
            printf("Loi: Danh sach benh nhan da day.\n");
            printf("\n1. Quay lai menu chinh\n");
            printf("Lua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            return;
        }
        
        struct Patient newPatient;
        
        // Nhap ma the (cardId)
        do {
            printf("Nhap ma ho so (cardId) (9 ky tu): ");
            fgets(newPatient.cardId, sizeof(newPatient.cardId), stdin);
            newPatient.cardId[strcspn(newPatient.cardId, "\n")] = '\0';
            if (strlen(newPatient.cardId) == 0 || !isCardIdUnique(newPatient.cardId)) {
                printf("Loi: Ma ho so khong duoc rong va phai la duy nhat.\n");
            }
        } while (strlen(newPatient.cardId) == 0 || !isCardIdUnique(newPatient.cardId));
        
        // Nhap ten benh nhan
        do {
            printf("Nhap ten benh nhan: ");
            fgets(newPatient.name, sizeof(newPatient.name), stdin);
            newPatient.name[strcspn(newPatient.name, "\n")] = '\0';
            if (strlen(newPatient.name) == 0) {
                printf("Loi: Ten khong duoc rong.\n");
            }
        } while (strlen(newPatient.name) == 0);
        
        // Nhap so dien thoai
        do {
            printf("Nhap so dien thoai: ");
            fgets(newPatient.phone, sizeof(newPatient.phone), stdin);
            newPatient.phone[strcspn(newPatient.phone, "\n")] = '\0';
            if (strlen(newPatient.phone) < 10) {
                printf("Loi: So dien thoai phai co it nhat 10 ky tu.\n");
            }
        } while (strlen(newPatient.phone) < 10);
        
        // Nhap cong no
        do {
            printf("Nhap cong no ban dau: ");
            if (scanf("%lf", &newPatient.debt) != 1 || newPatient.debt < 0) {
                printf("Loi: Cong no phai la mot so khong am.\n");
                while (getchar() != '\n');
            } else {
                while (getchar() != '\n');
                break;
            }
        } while (1);
        
        // Gan gia tri mac dinh
        newPatient.visitDays = 0;
        
        // Them benh nhan vao mang
        patients[patientCount++] = newPatient;
        
        // Hien thi ket qua
        showPage("TIEP NHAN BENH NHAN MOI");
        printf("=== TIEP NHAN THANH CONG ===\n");
        printf("Ma ho so: %s\n", newPatient.cardId);
        printf("Ten benh nhan: %s\n", newPatient.name);
        printf("So dien thoai: %s\n", newPatient.phone);
        printf("Cong no: %.2lf\n", newPatient.debt);
        
        // Lua chon tiep tuc
        printf("\n1. Tiep tuc them benh nhan\n");
        printf("2. Quay lai menu chinh\n");
        printf("Lua chon: ");
        scanf(" %c", &choice);
        while (getchar() != '\n');
        
    } while (choice == '1');
}

// Ham cap nhat thong tin benh nhan (F02)
void F02_updatePatient() {
    char choice;
    do {
        showPage("CAP NHAT THONG TIN BENH NHAN");
        
        // Kiem tra danh sach rong
        if (patientCount == 0) {
            printf("Khong co benh nhan nao trong danh sach.\n");
            printf("\n1. Quay lai menu chinh\n");
            printf("Lua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            return;
        }
        
        char cardId[10];
        printf("Nhap ma ho so (cardId) cua benh nhan can cap nhat: ");
        fgets(cardId, sizeof(cardId), stdin);
        cardId[strcspn(cardId, "\n")] = '\0';

        // Tim benh nhan
        int index = findPatientIndex(cardId);
        if (index == -1) {
            showPage("CAP NHAT THONG TIN BENH NHAN");
            printf("Loi: Khong tim thay benh nhan voi ma ho so '%s'\n", cardId);
            printf("\n1. Thu lai\n");
            printf("2. Quay lai menu chinh\n");
            printf("Lua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            if (choice == '2') return;
            continue;
        }
        
        // Hien thi thong tin hien tai
        showPage("CAP NHAT THONG TIN BENH NHAN");
        printf("Tim thay benh nhan: %s\n", patients[index].name);
        printf("So dien thoai hien tai: %s\n", patients[index].phone);
        printf("Cong no hien tai: %.2lf\n", patients[index].debt);
        printf("----------------------------------------\n");
        
        // Cap nhat ten (neu co)
        printf("Nhap ten moi (de trong neu khong doi): ");
        char newName[50];
        fgets(newName, sizeof(newName), stdin);
        newName[strcspn(newName, "\n")] = '\0';
        if (strlen(newName) > 0) {
            strcpy(patients[index].name, newName);
        }
        
        // Cap nhat so dien thoai (neu co)
        printf("Nhap so dien thoai moi (de trong neu khong doi): ");
        char newPhone[15];
        fgets(newPhone, sizeof(newPhone), stdin);
        newPhone[strcspn(newPhone, "\n")] = '\0';
        if (strlen(newPhone) > 0) {
            strcpy(patients[index].phone, newPhone);
        }
        
        // Cap nhat cong no (neu co)
        printf("Nhap cong no moi (-1 de giu nguyen): ");
        double newDebt;
        if (scanf("%lf", &newDebt) == 1 && newDebt >= 0) {
            patients[index].debt = newDebt;
        }
        while (getchar() != '\n');
        
        // Hien thi ket qua
        showPage("CAP NHAT THONG TIN BENH NHAN");
        printf("=== CAP NHAT THANH CONG ===\n");
        printf("Ma ho so: %s\n", patients[index].cardId);
        printf("Ten benh nhan: %s\n", patients[index].name);
        printf("So dien thoai: %s\n", patients[index].phone);
        printf("Cong no: %.2lf\n", patients[index].debt);
        
        // Lua chon tiep tuc
        printf("\n1. Cap nhat benh nhan khac\n");
        printf("2. Quay lai menu chinh\n");
        printf("Lua chon: ");
        scanf(" %c", &choice);
        while (getchar() != '\n');
        
    } while (choice == '1');
}

// Ham xuat vien (xoa benh nhan) (F03)
void F03_dischargePatient(){
    char choice;
    do {
        showPage("XUAT VIEN (XOA BENH NHAN)");
        
        // Kiem tra danh sach rong
        if (patientCount == 0) {
            printf("Khong co benh nhan nao trong danh sach.\n");
            printf("\n1. Quay lai menu chinh\n");
            printf("Lua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            return;
        }
        
        char cardId[10];
        printf("Nhap ma ho so (cardId) cua benh nhan can xuat vien: ");
        fgets(cardId, sizeof(cardId), stdin);
        cardId[strcspn(cardId, "\n")] = '\0';
        
        // Tim benh nhan
        int index = findPatientIndex(cardId);
        if (index == -1){
            showPage("XUAT VIEN (XOA BENH NHAN)");
            printf("Loi: Khong tim thay benh nhan voi ma ho so '%s'\n", cardId);
            printf("\n1. Thu lai\n");
            printf("2. Quay lai menu chinh\n");
            printf("Lua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            if (choice == '2') return;
            continue;
        }
        
        // Hien thi thong tin can xoa
        showPage("XAC NHAN XUAT VIEN");
        printf("THONG TIN BENH NHAN CAN XOA:\n");
        printf("Ma ho so: %s\n", patients[index].cardId);
        printf("Ten benh nhan: %s\n", patients[index].name);
        printf("So dien thoai: %s\n", patients[index].phone);
        printf("Cong no: %.2lf\n", patients[index].debt);
        printf("So ngay kham: %d\n", patients[index].visitDays);
        printf("----------------------------------------\n");
        
        // Xac nhan xoa
        printf("Ban co chac chan muon xoa benh nhan nay? (y/n): ");
        char confirm;
        scanf(" %c", &confirm);
        while (getchar() != '\n');
        
        if (confirm != 'y' && confirm != 'Y') {
            showPage("XUAT VIEN (XOA BENH NHAN)");
            printf("Da huy thao tac xoa benh nhan.\n");
        } else {
            // Dich chuyen cac phan tu de xoa
            for (int i = index; i < patientCount - 1; i++){
                patients[i] = patients[i + 1];
            }
            patientCount--;
            showPage("XUAT VIEN (XOA BENH NHAN)");
            printf("=== XUAT VIEN THANH CONG ===\n");
        }
        
        // Lua chon tiep tuc
        printf("\n1. Xuat vien benh nhan khac\n");
        printf("2. Quay lai menu chinh\n");
        printf("Lua chon: ");
        scanf(" %c", &choice);
        while (getchar() != '\n');
        
    } while (choice == '1');
}

// Ham hien thi tat ca benh nhan (F04)
void F04_displayAllPatients() {
    char choice;
    do {
        showPage("DANH SACH BENH NHAN");
        
        // Kiem tra danh sach rong
        if (patientCount == 0) {
            printf("Khong co benh nhan nao trong danh sach.\n");
            printf("\n1. Quay lai menu chinh\n");
            printf("Lua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            return;
        }
        
        // Nhap so benh nhan moi trang
        int pageSize;
        printf("Nhap so benh nhan muon hien thi tren moi trang: ");
        while (scanf("%d", &pageSize) != 1 || pageSize <= 0) {
            while (getchar() != '\n');
            printf("Gia tri khong hop le. Vui long nhap mot so nguyen duong: ");
        }
        while (getchar() != '\n');
        
        int totalPages = (patientCount + pageSize - 1) / pageSize;
        int currentPage = 1;
        
        // Vong lap phan trang
        while (1) {
            showPage("DANH SACH BENH NHAN");
            printf("Trang %d/%d (Hien thi %d benh nhan moi trang)\n", currentPage, totalPages, pageSize);
            printf("----------------------------------------\n");
            
            // Tinh chi so bat dau va ket thuc
            int startIndex = (currentPage - 1) * pageSize;
            int endIndex = startIndex + pageSize;
            if (endIndex > patientCount) {
                endIndex = patientCount;
            }
            
            // Hien thi tieu de bang
            printf("---------------------------------------------------------------------------------------------------\n");
            printf("| %-4s | %-15s | %-25s | %-12s | %-10s | %-7s |\n","STT", "cardId", "name", "phone", "debt", "visitDays");
            printf("---------------------------------------------------------------------------------------------------\n");
            
            // Hien thi du lieu trang hien tai
            for (int i = startIndex; i < endIndex; i++) {
                printf("| %-4d | %-15s | %-25s | %-12s | %-10.2lf | %-9d |\n", 
                       i + 1, patients[i].cardId, patients[i].name, patients[i].phone, 
                       patients[i].debt, patients[i].visitDays);
            }
            
            if (endIndex > startIndex) {
                printf("---------------------------------------------------------------------------------------------------\n");
            }
            
            printf("DANG HIEN THI TRANG %d/%d\n", currentPage, totalPages);
            
            // Hien thi menu phan trang
            printf("\n=== CHON TUY CHON ===\n");
            printf("1. Trang tiep theo\n");
            if (totalPages > 1) {
                printf("2. Trang truoc\n");
                printf("3. Trang cu the\n");
            } else {
                printf("2. Trang cu the\n");
            }
            printf("0. Quay lai\n");
            printf("Lua chon cua ban: ");

            char choice_str[10];
            fgets(choice_str, sizeof(choice_str), stdin);
            int pageChoice = atoi(choice_str);
            
            // Xu ly lua chon phan trang
            switch (pageChoice) {
                case 0:
                    goto end_pagination;
                case 1:
                    if (currentPage < totalPages) {
                        currentPage++;
                    } else {
                        printf("Ban dang o trang cuoi cung!\n");
                        waitForEnter();
                    }
                    break;
                case 2:
                    if (totalPages > 1) {
                        if (currentPage > 1) {
                            currentPage--;
                        } else {
                            printf("Ban dang o trang dau tien!\n");
                            waitForEnter();
                        }
                    } else {
                        printf("Nhap so trang muon xem (1-%d): ", totalPages);
                        int targetPage;
                        if (scanf("%d", &targetPage) == 1 && targetPage >= 1 && targetPage <= totalPages) {
                            currentPage = targetPage;
                        } else {
                            printf("So trang khong hop le!\n");
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
                            printf("So trang khong hop le!\n");
                        }
                        while (getchar() != '\n');
                    } else {
                        printf("Chi co 1 trang!\n");
                        waitForEnter();
                    }
                    break;
                default:
                    printf("Lua chon khong hop le!\n");
                    waitForEnter();
                    break;
            }
        }
        
        end_pagination:
        showPage("DANH SACH BENH NHAN");
        printf("\n1. Xem lai danh sach\n");
        printf("2. Quay lai menu chinh\n");
        printf("Lua chon: ");
        scanf(" %c", &choice);
        while (getchar() != '\n');
        
    } while (choice == '1');
}

// Ham tim kiem benh nhan theo ten (F05)
void F05_searchPatient() {
    char choice;
    do {
        showPage("TIM KIEM BENH NHAN THEO TEN");
        
        // Kiem tra danh sach rong
        if (patientCount == 0) {
            printf("Khong co benh nhan nao trong danh sach.\n");
            printf("\n1. Quay lai menu chinh\n");
            printf("Lua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            return;
        }
        
        // Nhap ten can tim
        char searchName[50];
        printf("Nhap ten benh nhan can tim: ");
        fgets(searchName, sizeof(searchName), stdin);
        searchName[strcspn(searchName, "\n")] = '\0';
        
        if (strlen(searchName) == 0) {
            showPage("TIM KIEM BENH NHAN THEO TEN");
            printf("Loi: Ten tim kiem khong duoc rong.\n");
            printf("\n1. Thu lai\n");
            printf("2. Quay lai menu chinh\n");
            printf("Lua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            if (choice == '2') return;
            continue;
        }
        
        // Tim kiem khong phan biet hoa thuong
        struct Patient searchResults[MAX_PATIENTS];
        int resultCount = 0;
        
        for (int i = 0; i < patientCount; i++) {
            char patientNameLower[50];
            char searchNameLower[50];
            
            // Chuyen ten benh nhan thanh chu thuong
            for (int j = 0; patients[i].name[j] != '\0'; j++) {
                patientNameLower[j] = my_tolower(patients[i].name[j]);
            }
            patientNameLower[strlen(patients[i].name)] = '\0';
            
            // Chuyen ten tim kiem thanh chu thuong
            for (int j = 0; searchName[j] != '\0'; j++) {
                searchNameLower[j] = my_tolower(searchName[j]);
            }
            searchNameLower[strlen(searchName)] = '\0';
            
            // Kiem tra ten co chua chuoi tim kiem khong
            if (strstr(patientNameLower, searchNameLower) != NULL) {
                searchResults[resultCount] = patients[i];
                resultCount++;
            }
        }
        
        // Kiem tra ket qua tim kiem
        if (resultCount == 0) {
            showPage("TIM KIEM BENH NHAN THEO TEN");
            printf("Khong tim thay benh nhan nao co ten chua: '%s'\n", searchName);
            printf("\n1. Tim kiem lai\n");
            printf("2. Quay lai menu chinh\n");
            printf("Lua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            if (choice == '2') return;
            continue;
        }
        
        // Hien thi ket qua bang phan trang
        char title[100];
        snprintf(title, sizeof(title), "KET QUA TIM KIEM: '%s' (%d ket qua)", searchName, resultCount);
        startNewPaginationSession(searchResults, resultCount, title);
        
        showPage("TIM KIEM BENH NHAN THEO TEN");
        printf("\n1. Tim kiem benh nhan khac\n");
        printf("2. Quay lai menu chinh\n");
        printf("Lua chon: ");
        scanf(" %c", &choice);
        while (getchar() != '\n');
        
    } while (choice == '1');
}

// Ham sap xep benh nhan theo cong no (F06)
void F06_sortPatients() {
    char choice;
    do {
        showPage("SAP XEP DANH SACH BENH NHAN THEO CONG NO");
        
        // Kiem tra danh sach rong
        if (patientCount == 0) {
            printf("Khong co benh nhan nao trong danh sach.\n");
            printf("\n1. Quay lai menu chinh\n");
            printf("Lua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            return;
        }
        
        // Chon kieu sap xep
        printf("Chon kieu sap xep:\n");
        printf("1. Tang dan (tu cong no thap den cao)\n");
        printf("2. Giam dan (tu cong no cao den thap)\n");
        printf("Lua chon cua ban: ");
        
        int sortChoice;
        if (scanf("%d", &sortChoice) != 1) {
            while (getchar() != '\n');
            showPage("SAP XEP DANH SACH BENH NHAN THEO CONG NO");
            printf("Loi: Lua chon khong hop le.\n");
            printf("\n1. Thu lai\n");
            printf("2. Quay lai menu chinh\n");
            printf("Lua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            if (choice == '2') return;
            continue;
        }
        while (getchar() != '\n');
        
        // Tao ban sao cua mang de sap xep
        struct Patient sortedPatients[MAX_PATIENTS];
        for (int i = 0; i < patientCount; i++) {
            sortedPatients[i] = patients[i];
        }
        
        char title[100];
        switch (sortChoice) {
            case 1:
                qsort(sortedPatients, patientCount, sizeof(struct Patient), comparePatientsAscending);
                strcpy(title, "DANH SACH BENH NHAN SAP XEP TANG DAN THEO CONG NO");
                break;
            case 2:
                qsort(sortedPatients, patientCount, sizeof(struct Patient), comparePatientsDescending);
                strcpy(title, "DANH SACH BENH NHAN SAP XEP GIAM DAN THEO CONG NO");
                break;
            default:
                showPage("SAP XEP DANH SACH BENH NHAN THEO CONG NO");
                printf("Loi: Lua chon khong hop le.\n");
                printf("\n1. Thu lai\n");
                printf("2. Quay lai menu chinh\n");
                printf("Lua chon: ");
                scanf(" %c", &choice);
                while (getchar() != '\n');
                if (choice == '2') return;
                continue;
        }
        
        // Hien thi ket qua sap xep bang phan trang
        startNewPaginationSession(sortedPatients, patientCount, title);
        
        showPage("SAP XEP DANH SACH BENH NHAN THEO CONG NO");
        printf("=== SAP XEP THANH CONG ===\n");
        printf("\n1. Sap xep lai\n");
        printf("2. Quay lai menu chinh\n");
        printf("Lua chon: ");
        scanf(" %c", &choice);
        while (getchar() != '\n');
        
    } while (choice == '1');
}

// Ham xoa ky tu newline
void trimNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Ham kiem tra ngay hop le
int isValidDate(const char *date) {
    int day, month, year;
    if (sscanf(date, "%2d/%2d/%4d", &day, &month, &year) != 3) return 0;

    // Kiem tra nam
    if (year < 1900 || year >= 2100) return 0;
    
    // Kiem tra thang
    if (month < 1 || month > 12) return 0;

    // Kiem tra ngay
    int maxDays = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) maxDays = 30;
    else if (month == 2) {
        // Kiem tra nam nhuan
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            maxDays = 29;
        else
            maxDays = 28;
    }

    if (day < 1 || day > maxDays) return 0;
    return 1;
}

// Ham ghi nhan kham benh (F07)
void F07_addRecord() {
    char choice;

    do {
        showPage("GHI NHAN KHAM BENH");

        // Kiem tra danh sach rong
        if (patientCount == 0) {
            printf("Khong co benh nhan nao trong danh sach.\n");
            printf("\n1. Quay lai menu chinh\nLua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            return;
        }

        // Kiem tra danh sach ho so day
        if (recordCount >= MAX_RECORDS) {
            printf("Danh sach kham benh da day.\n");
            printf("\n1. Quay lai menu chinh\nLua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            return;
        }

        char cardId[10];
        printf("Nhap ma ho so (cardId) cua benh nhan: ");
        fgets(cardId, sizeof(cardId), stdin);
        trimNewline(cardId);

        // Tim benh nhan
        int patientIndex = findPatientIndex(cardId);

        if (patientIndex == -1) {
            printf("Loi: Khong tim thay benh nhan voi ma '%s'\n", cardId);
            printf("\n1. Thu lai\n2. Quay lai menu chinh\nLua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            if (choice == '2') return;
            continue;
        }

        // Hien thi thong tin benh nhan
        showPage("GHI NHAN KHAM BENH");
        printf("Thong tin benh nhan:\n");
        printf("Ma ho so: %s\n", patients[patientIndex].cardId);
        printf("Ten benh nhan: %s\n", patients[patientIndex].name);
        printf("So dien thoai: %s\n", patients[patientIndex].phone);
        printf("So lan kham truoc: %d\n", patients[patientIndex].visitDays);
        printf("----------------------------------------\n");

        struct Record newRecord;
        newRecord.recId = nextRecId++;
        strcpy(newRecord.cardId, cardId);
        
        // Nhap ngay kham va kiem tra
        do {
            printf("Nhap ngay kham (dd/mm/yyyy): ");
            fgets(newRecord.date, sizeof(newRecord.date), stdin);
            trimNewline(newRecord.date);

            if (strlen(newRecord.date) == 0) {
                printf("Loi: Ngay kham khong duoc rong.\n");
                continue;
            }

            if (!isValidDate(newRecord.date)) {
                printf("Loi: Ngay kham khong hop le.\n");
                continue;
            }
            
            // Kiem tra trung lap ngay kham
            if (isRecordDuplicate(newRecord.cardId, newRecord.date)) {
                printf("Loi: Benh nhan %s da co ho so kham benh vao ngay %s roi.\n",
                       patients[patientIndex].name, newRecord.date);
                printf("Vui long nhap ngay kham khac.\n");
                continue;
            }

            break;
        } while (1);
        
        // Nhap tinh trang benh
        do {
            printf("Nhap tinh trang benh: ");
            fgets(newRecord.status, sizeof(newRecord.status), stdin);
            trimNewline(newRecord.status);

            if (strlen(newRecord.status) == 0) {
                printf("Loi: Tinh trang khong duoc rong.\n");
            }
        } while (strlen(newRecord.status) == 0);

        // Luu ho so
        records[recordCount++] = newRecord;
        patients[patientIndex].visitDays++;

        // Hien thi ket qua
        printf("\n=== GHI NHAN THANH CONG ===\n");
        printf("Ma kham benh: %d\n", newRecord.recId);
        printf("Benh nhan: %s\n", patients[patientIndex].name);
        printf("Ngay kham: %s\n", newRecord.date);
        printf("Tinh trang: %s\n", newRecord.status);
        printf("So lan kham: %d\n", patients[patientIndex].visitDays);

        // Lua chon tiep tuc
        printf("\n1. Ghi tiep\n2. Quay lai menu chinh\nLua chon: ");
        scanf(" %c", &choice);
        while (getchar() != '\n');

    } while (choice == '1');
}

// Ham xem lich su kham benh (F08)
void F08_viewMedicalHistory() {
    char choice;
    do {
        showPage("LICH SU KHAM BENH");
        
        // Kiem tra danh sach ho so rong
        if (recordCount == 0) {
            printf("Khong co lich su kham benh nao.\n");
            printf("\n1. Quay lai menu chinh\n");
            printf("Lua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            return;
        }
        
        char cardId[10];
        printf("Nhap ma ho so (cardId) cua benh nhan: ");
        fgets(cardId, sizeof(cardId), stdin);
        cardId[strcspn(cardId, "\n")] = '\0';
        
        // Tim benh nhan
        int patientIndex = findPatientIndex(cardId);
        if (patientIndex == -1) {
            showPage("LICH SU KHAM BENH");
            printf("Loi: Khong tim thay benh nhan voi ma ho so '%s'\n", cardId);
            printf("\n1. Thu lai\n");
            printf("2. Quay lai menu chinh\n");
            printf("Lua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            if (choice == '2') return;
            continue;
        }
        
        // Lay tat ca ho so cua benh nhan
        struct Record patientRecords[MAX_RECORDS];
        int patientRecordCount = 0;
        
        for (int i = 0; i < recordCount; i++) {
            if (strcmp(records[i].cardId, cardId) == 0) {
                patientRecords[patientRecordCount] = records[i];
                patientRecordCount++;
            }
        }
        
        // Kiem tra co ho so nao khong
        if (patientRecordCount == 0) {
            showPage("LICH SU KHAM BENH");
            printf("Benh nhan %s chua co lich su kham benh.\n", patients[patientIndex].name);
            printf("\n1. Xem benh nhan khac\n");
            printf("2. Quay lai menu chinh\n");
            printf("Lua chon: ");
            scanf(" %c", &choice);
            while (getchar() != '\n');
            if (choice == '2') return;
            continue;
        }
        
        // Nhap so ho so moi trang
        int pageSize;
        printf("Nhap so lan kham muon hien thi tren moi trang: ");
        if (scanf("%d", &pageSize) != 1 || pageSize <= 0) {
            printf("Gia tri khong hop le. Su dung mac dinh 5.\n");
            pageSize = 5;
        }
        while (getchar() != '\n');
        
        int totalPages = (patientRecordCount + pageSize - 1) / pageSize;
        int currentPage = 1;
        
        // Vong lap phan trang
        while (1) {
            showPage("LICH SU KHAM BENH");
            printf("Benh nhan: %s (Ma: %s)\n", patients[patientIndex].name, patients[patientIndex].cardId);
            printf("So dien thoai: %s\n", patients[patientIndex].phone);
            printf("Tong so lan kham: %d\n", patientRecordCount);
            printf("Trang %d/%d (Hien thi %d lan kham moi trang)\n", currentPage, totalPages, pageSize);
            printf("------------------------------------------------------------\n");
            
            // Tinh chi so bat dau va ket thuc
            int startIndex = (currentPage - 1) * pageSize;
            int endIndex = startIndex + pageSize;
            if (endIndex > patientRecordCount) {
                endIndex = patientRecordCount;
            }
            
            // Hien thi tieu de bang
            printf("--------------------------------------------------------------------\n");
            printf("| %-4s | %-8s | %-10s | %-30s |\n", "STT", "Ma KB", "Ngay kham", "Tinh trang benh");
            printf("--------------------------------------------------------------------\n");
            
            // Hien thi du lieu trang hien tai
            for (int i = startIndex; i < endIndex; i++) {
                printf("| %-4d | %-8d | %-10s | %-30s |\n", 
                       i + 1, patientRecords[i].recId, patientRecords[i].date, patientRecords[i].status);
            }
            
            printf("--------------------------------------------------------------------\n");
            printf("DANG HIEN THI TRANG %d/%d - Tu lan kham %d den %d\n", 
                   currentPage, totalPages, startIndex + 1, endIndex);
            
            // Hien thi menu phan trang
            printf("\n=== CHON TUY CHON ===\n");
            printf("1. Trang tiep theo\n");
            
            if (totalPages > 1) {
                printf("2. Trang truoc\n");
                printf("3. Chuyen den trang\n");
            } else {
                printf("2. Thoat\n");
            }
            
            printf("0. Quay lai\n");
            printf("Lua chon cua ban: ");

            char choice_str[10];
            fgets(choice_str, sizeof(choice_str), stdin);
            int pageChoice = atoi(choice_str);
            
            // Xu ly lua chon phan trang
            switch (pageChoice) {
                case 0:
                    goto end_history;
                case 1:
                    if (currentPage < totalPages) {
                        currentPage++;
                    } else {
                        printf("Ban dang o trang cuoi cung!\n");
                        waitForEnter();
                    }
                    break;
                case 2:
                    if (totalPages > 1) {
                        if (currentPage > 1) {
                            currentPage--;
                        } else {
                            printf("Ban dang o trang dau tien!\n");
                            waitForEnter();
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
                        while (getchar() != '\n');
                    } else {
                        printf("Chi co 1 trang!\n");
                        waitForEnter();
                    }
                    break;
                default:
                    printf("Lua chon khong hop le!\n");
                    waitForEnter();
                    break;
            }
        }
        
        end_history:
        showPage("LICH SU KHAM BENH");
        printf("\n1. Xem lich su benh nhan khac\n");
        printf("2. Quay lai menu chinh\n");
        printf("Lua chon: ");
        scanf(" %c", &choice);
        while (getchar() != '\n');
        
    } while (choice == '1');
}

// Ham hien thi ket qua tim kiem
void displaySearchResults(struct Patient results[], int resultCount, const char* title) {
    printf("\n%s\n", title);
    printf("----------------------------------------\n");
    
    if (resultCount == 0) {
        printf("Khong co ket qua nao.\n");
        return;
    }
    
    // Hien thi bang ket qua
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

// Ham bat dau phan trang moi
void startNewPaginationSession(struct Patient list[], int count, char* title) {
    if (count == 0) {
        printf("Khong co du lieu de hien thi.\n");
        return;
    }
    
    // Nhap so benh nhan moi trang
    int pageSize;
    printf("Nhap so benh nhan muon hien thi tren moi trang: ");
    while (scanf("%d", &pageSize) != 1 || pageSize <= 0) {
        while (getchar() != '\n');
        printf("Gia tri khong hop le. Vui long nhap mot so nguyen duong: ");
    }
    while (getchar() != '\n');
    
    int totalPages = (count + pageSize - 1) / pageSize;
    int currentPage = 1;
    
    // Vong lap phan trang
    while (1) {
        showPage(title);
        printf("Trang %d/%d (Hien thi %d benh nhan moi trang)\n", currentPage, totalPages, pageSize);
        printf("----------------------------------------\n");
        
        // Tinh chi so bat dau va ket thuc
        int startIndex = (currentPage - 1) * pageSize;
        int endIndex = startIndex + pageSize;
        if (endIndex > count) {
            endIndex = count;
        }
        
        // Hien thi tieu de bang
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("| %-4s | %-15s | %-25s | %-12s | %-10s | %-7s |\n", "STT", "cardId", "name", "phone", "debt", "visitDays");
        printf("---------------------------------------------------------------------------------------------------\n");
        
        // Hien thi du lieu trang hien tai
        for (int i = startIndex; i < endIndex; i++) {
            printf("| %-4d | %-15s | %-25s | %-12s | %-10.2lf | %-9d |\n", 
                   i + 1, list[i].cardId, list[i].name, list[i].phone, 
                   list[i].debt, list[i].visitDays);
        }
        
        if (endIndex > startIndex) {
            printf("---------------------------------------------------------------------------------------------------\n");
        }
        
        printf("DANG HIEN THI TRANG %d/%d\n", currentPage, totalPages);
        
        // Hien thi menu phan trang
        printf("\n=== CHON TUY CHON ===\n");
        printf("1. Trang tiep theo\n");
        
        if (totalPages > 1) {
            printf("2. Trang truoc\n");
            printf("3. Trang cu the\n");
        } else {
            printf("2. Trang cu the\n");
        }
        
        printf("0. Quay lai\n");
        printf("Lua chon cua ban: ");

        char choice_str[10];
        fgets(choice_str, sizeof(choice_str), stdin);
        int pageChoice = atoi(choice_str);
        
        // Xu ly lua chon phan trang
        switch (pageChoice) {
            case 0:
                return;
            case 1:
                if (currentPage < totalPages) {
                    currentPage++;
                } else {
                    printf("Ban dang o trang cuoi cung!\n");
                    waitForEnter();
                }
                break;
            case 2:
                if (totalPages > 1) {
                    if (currentPage > 1) {
                        currentPage--;
                    } else {
                        printf("Ban dang o trang dau tien!\n");
                        waitForEnter();
                    }
                } else {
                    printf("Nhap so trang muon xem (1-%d): ", totalPages);
                    int targetPage;
                    if (scanf("%d", &targetPage) == 1 && targetPage >= 1 && targetPage <= totalPages) {
                        currentPage = targetPage;
                    } else {
                        printf("So trang khong hop le!\n");
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
                        printf("So trang khong hop le!\n");
                    }
                    while (getchar() != '\n');
                } else {
                    printf("Chi co 1 trang!\n");
                    waitForEnter();
                }
                break;
            default:
                printf("Lua chon khong hop le!\n");
                waitForEnter();
                break;
        }
    }
}

// Ham so sanh tang dan (cho qsort)
int comparePatientsAscending(const void *a, const void *b) {
    const struct Patient *patientA = (const struct Patient *)a;
    const struct Patient *patientB = (const struct Patient *)b;
    
    if (patientA->debt < patientB->debt) return -1;
    if (patientA->debt > patientB->debt) return 1;
    return 0;
}

// Ham so sanh giam dan (cho qsort)
int comparePatientsDescending(const void *a, const void *b) {
    const struct Patient *patientA = (const struct Patient *)a;
    const struct Patient *patientB = (const struct Patient *)b;
    
    if (patientA->debt > patientB->debt) return -1;
    if (patientA->debt < patientB->debt) return 1;
    return 0;
}

