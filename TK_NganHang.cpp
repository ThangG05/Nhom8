#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include <Windows.h>
#define MAX 20
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
struct tk {
    char  tendangnhap[MAX],
        tentaikhoan[MAX],
        mk[MAX],
        hoten[MAX],
        chucvu[MAX],
        cccd[MAX],
        sdt[MAX],
        stk[MAX],
        email[MAX];    
};
struct sdtk {
    char STK[MAX];
    char OTP[MAX];
    float sodu;
};
bool timstk(char stk[MAX]) {
    struct tk temp;
    FILE* f = fopen("41.bin", "rb");
    if (f == NULL) return false;
    while (fread(&temp, sizeof(struct tk), 1, f) == 1) {
        if (strcmp(temp.stk, stk) == 0) {
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}
bool timemail(char email[MAX]) {
    struct tk temp;
    FILE* f = fopen("41.bin", "rb");
    if (f == NULL) return false;
    while (fread(&temp, sizeof(struct tk), 1, f) == 1) {
        if (strcmp(temp.email, email) == 0) {
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}
bool timtendangnhapl(char ten[MAX]) {
    struct tk temp;
    FILE* f = fopen("41.bin", "rb");
    if (f == NULL) return false;
    while (fread(&temp, sizeof(struct tk), 1, f) == 1) {
        if (strcmp(temp.tendangnhap,ten) == 0) {
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}
bool timOTP(char otp[MAX]) {
    struct sdtk temp;
    FILE* f = fopen("42.bin", "rb");
    if (f == NULL) return false;
    while (fread(&temp, sizeof(struct sdtk), 1, f) == 1) {
        if (strcmp(temp.OTP, otp) == 0) {
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}
void chuanhoa(char ten[]) {
    int len = strlen(ten);
    while (ten[0] == ' ') {
        memmove(ten, ten + 1, len);
        len--;
    }
    while (ten[len - 1] == ' ') {
        ten[len - 1] = '\0';
        len--;
    }
    bool dauTu = true;
    for (int i = 0; i < len; i++) {
        if (ten[i] == ' ') {
            dauTu = true;
        }
        else if (dauTu) {
            ten[i] = toupper(ten[i]);
            dauTu = false;
        }
        else {
            ten[i] = tolower(ten[i]);
        }
    }
}
void luusd(struct sdtk* a) {
    FILE* f = fopen("42.bin", "ab+");
    if (f != NULL) {
        fwrite(a, sizeof(struct sdtk), 1, f);
        fclose(f);
    }
}
bool kiem_tra_so(char chuoi[]) {
    for (int i = 0; chuoi[i] != '\0'; i++) {
        if (!isdigit(chuoi[i])) {
            return false; 
        }
    }
    return true; 
}
bool ktramk(char a[]) {
    int d = 0;
    int d1 = 0;
    for (int i = 0; i < strlen(a); i++) {
        if (a[i] >= 'A' && a[i] <= 'Z') {
            d++;
        }
        if (a[i] >= '0' && a[i] <= '9') {
            d1++;
        }
    }
    if (d > 0 && d1 > 0) {
        return true;
    }
    return false;
}
void dangky(struct tk* a) {
    printf("-->Nhap chuc vu (nguoi dung/quan ly): ");
    scanf("%[^\n]", a->chucvu);
    getchar();
    while (strcmp(a->chucvu, "nguoi dung") != 0 && strcmp(a->chucvu, "quan ly") != 0) {
        printf("Ban da nhap sai chuc vu, hay nhap lai\n");
        printf("-->Nhap chuc vu: ");
        scanf("%[^\n]", a->chucvu);
        getchar();
    }
    printf("-->Nhap ho ten nguoi dung: ");
    scanf(" %[^\n]", a->hoten);
    chuanhoa(a->hoten);
    getchar();
    printf("-->Nhap ten dang nhap: ");
    scanf("%[^\n]", a->tendangnhap);
    getchar();
    printf("-->Nhap mat khau: ");
    scanf("%s", a->mk);
    while ((strlen(a->mk) < 8 || strlen(a->mk) > 16) || ktramk(a->mk) == false) {
        printf("mat khau khong du manh ( >=8 va <=16 ky tu), chua it nhat 1 ky tu in hoa va so va co the co ky tu dac biet");
        printf("\n-->Nhap lai mat khau:");
        scanf("%s", a->mk);
    }
    printf("-->Xac thuc mat khau: ");
    char kt[MAX];
    scanf("%s", kt);
    while (strcmp(a->mk, kt) != 0) {
        printf("Mat khau xac thuc sai:-->hay nhap lai: ");
        scanf("%s", kt);
    }
    getchar();
    strcpy(a->tentaikhoan,a->hoten);
    printf("-->Nhap so can cuoc cong dan: ");
    scanf("%s", a->cccd);
    while (strlen(a->cccd) != 12 || kiem_tra_so(a->cccd)==false) {
        printf("so cccd khong hop le (12 chu so) va khong duoc chua chu cai");
        printf("\n-->Nhap lai cccd:");
        scanf("%s", a->cccd);
    }
    printf("-->Nhap so dien thoai: ");
    scanf("%s", a->sdt);
    while (strlen(a->sdt) != 10 || kiem_tra_so(a->sdt) == false) {
        printf("so dien thoai khong hop le (10 chu so) va khong duoc chua chu cai");
        printf("\n-->Nhap lai sdt:");
        scanf("%s", a->sdt);
    }
    char duoi[11] = "@gmail.com";
    printf("-->Nhap email (Dang ky khong can nhap duoi @gmail.com ):");
    scanf("%s", a->email);
    strcat(a->email, duoi);
    while (timemail(a->email)) {
        printf("Email nay da duoc tao roi!!!");
        printf("\n-->Nhap lai email khac:");
        scanf("%s", a->email);
        strcat(a->email, duoi);
    }
    struct sdtk sd;
    if (strcmp(a->chucvu, "quan ly") == 0) {
        strcpy(a->stk, "empty");
    }
    else {
        printf("-->Nhap so tai khoan:");
        scanf("%s", a->stk);
        while (timstk(a->stk) || strlen(a->stk)!=10) {
            printf("So tai khoan nay da duoc tao , hoac khong dung 10 so");
            printf("\n-->Nhap lai stk:");
            scanf("%s", a->stk);
        }
        strcpy(sd.STK, a->stk);
        sd.sodu = 0;
        printf("Nhap ma OTP:");
        scanf("%s", &sd.OTP);
        while (kiem_tra_so(sd.OTP) == false || strlen(sd.OTP) != 6) {
            printf("ma OTP (6 chu so) va khong duoc chua chu cai");
            printf("\n-->Nhap lai ma OTP:");
            scanf("%s", sd.OTP);
        }
        luusd(&sd);
    }
}
void luutk(struct tk* a) {
    FILE* f = fopen("41.bin", "ab+");
    if (f != NULL) {
        fwrite(a, sizeof(struct tk), 1, f);
        fclose(f);
    }
}
bool dangnhap(char ten[20], char mk[20], struct tk* a) {
    FILE* f = fopen("41.bin", "rb");
    if (f == NULL) return false;
    while (fread(a, sizeof(struct tk), 1, f) == 1) {
        if (strcmp(a->tendangnhap, ten) == 0 && strcmp(a->mk, mk) == 0) {
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}
bool dangnhaptk(char ten[20], struct tk* a) {
    FILE* f = fopen("41.bin", "rb");
    if (f == NULL) return false;
    while (fread(a, sizeof(struct tk), 1, f) == 1) {
        if (strcmp(a->tendangnhap, ten) == 0) {
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}
struct tk* timkiem(struct tk* a, char so[]) {
    FILE* f = fopen("41.bin", "rb");
    struct tk temp;
    while (fread(&temp, sizeof(struct tk), 1, f) == 1) {
        if (strcmp(temp.stk, so) == 0) {
            fclose(f);
            *a = temp;
            return a;
        }
    }
    fclose(f);
    return NULL;
}
struct sdtk* timkiemsdtk(struct sdtk* a, char so[]) {
    FILE* f = fopen("42.bin", "rb");
    struct sdtk temp;
    while (fread(&temp, sizeof(struct sdtk), 1, f) == 1) {
        if (strcmp(temp.STK, so) == 0) {
            fclose(f);
            *a = temp;
            return a;
        }
    }
    fclose(f);
    return NULL;
}
void hienthi(struct tk* t) {
    printf("|%-20s |%-12s |%-19s |%-18s |%-12s |%-13s |%-10s |%-20s |\n", t->hoten, t->chucvu, t->tendangnhap, t->tentaikhoan, t->stk, t->cccd, t->sdt, t->email);
}
void hienthi1(struct tk* t) {
    printf("+---------------------+-------------+--------------------+-------------------+-------------+--------------+-----------+---------------------+\n");
    printf("|  Ho ten nguoi dung  |   Vai tro   |    Ten dang nhap   |   Ten tai khoan   |     STK     |     CCCD     |    SDT    |          Email      |\n");
    printf("+---------------------+-------------+--------------------+-------------------+-------------+--------------+-----------+---------------------+\n");
    printf("|%-20s |%-12s |%-19s |%-18s |%-12s |%-13s |%-10s |%-20s |\n", t->hoten, t->chucvu, t->tendangnhap, t->tentaikhoan, t->stk, t->cccd, t->sdt, t->email);
    printf("+---------------------+-------------+--------------------+-------------------+-------------+--------------+-----------+---------------------+\n");
}
void hienthi_ds(struct tk t) {
    FILE* f = fopen("41.bin", "rb");
    if (f == NULL) return;
    printf("+---------------------+-------------+--------------------+-------------------+-------------+--------------+-----------+---------------------+\n");
    printf("|  Ho ten nguoi dung  |   Vai tro   |    Ten dang nhap   |   Ten tai khoan   |     STK     |     CCCD     |    SDT    |        Email        |\n");
    printf("+---------------------+-------------+--------------------+-------------------+-------------+--------------+-----------+---------------------+\n");
    while (fread(&t, sizeof(struct tk), 1, f) == 1) {
        if (strcmp(t.chucvu, "nguoi dung") == 0) {
            hienthi(&t);
        }
    }
    printf("+---------------------+-------------+--------------------+-------------------+-------------+--------------+-----------+---------------------+\n");
    fclose(f);
}
void sdu_lon_nho(struct tk* t, float x) {
    printf("+---------------------+-------------------+--------------+--------------+\n");
    printf("|  Ho ten nguoi dung  |   Ten tai khoan   |     STK      |    So du     |\n");
    printf("+---------------------+-------------------+--------------+--------------+\n");
    printf("|%-20s |%-18s |%-13s |%-13.3f |\n", t->hoten, t->tentaikhoan, t->stk, x);
    printf("+---------------------+-------------------+--------------+--------------+\n");
}
void capnhat_tai_khoan(struct tk* t) {
    FILE* f = fopen("41.bin", "rb+");
    if (f == NULL) return;
    struct tk temp;
    long pos;
    while (fread(&temp, sizeof(struct tk), 1, f) == 1) {
        if (strcmp(temp.tendangnhap, t->tendangnhap) == 0) {
            pos = ftell(f) - sizeof(struct tk);
            fseek(f, pos, SEEK_SET);
            fwrite(t, sizeof(struct tk), 1, f);
            fflush(f);
            break;
        }
    }
    fclose(f);
}
void capnhat_sodu(struct sdtk* t) {
    FILE* f = fopen("42.bin", "rb+");
    if (f == NULL) return;
    struct sdtk temp;
    long pos;
    while (fread(&temp, sizeof(struct sdtk), 1, f) == 1) {
        if (strcmp(temp.STK, t->STK) == 0) {
            pos = ftell(f) - sizeof(struct sdtk);
            fseek(f, pos, SEEK_SET);
            fwrite(t, sizeof(struct sdtk), 1, f);
            fflush(f);
            break;
        }
    }
    fclose(f);
}
void hienthisodu(struct sdtk* a) {
    printf("|%-15s |%-19.3f |\n", a->STK, a->sodu);
}
void hienthisodu_ds(struct sdtk a) {
    FILE* f = fopen("42.bin", "rb");
    if (f == NULL) return;
    printf("+----------------+--------------------+\n");
    printf("|       STK      |   SO DU HIEN TAI   |\n");
    printf("+----------------+--------------------+\n");
    while (fread(&a, sizeof(struct sdtk), 1, f) == 1) {
        hienthisodu(&a);
    }
    printf("+----------------+--------------------+\n");
    fclose(f);
}
struct sdtk* timsodumax(struct sdtk* a) {
    struct sdtk tien;
    float maxtien = 0;
    FILE* f = fopen("42.bin", "rb");
    if (f == NULL) return NULL;
    while (fread(&tien, sizeof(struct sdtk), 1, f) == 1) {
        if (tien.sodu > maxtien) {
            maxtien = tien.sodu;
            *a = tien;
        }
    }
    fclose(f);
    return a;
}
struct sdtk* timsodumin(struct sdtk* a) {
    struct sdtk tien;
    float mintien = 1e10;
    FILE* f = fopen("42.bin", "rb");
    if (f == NULL) return NULL;
    while (fread(&tien, sizeof(struct sdtk), 1, f) == 1) {
        if (tien.sodu < mintien) {
            mintien = tien.sodu;
            *a = tien;
        }
    }
    fclose(f);
    return a;
}
int main() {
    struct tk t;
    int tt = 1;
    struct sdtk sd = {};
    struct tk* check = NULL;
    struct tk* ktra = NULL;
    struct sdtk* ktra1 = NULL;
    struct tk* ktraa = NULL;
    struct sdtk* ktraa2 = NULL;
    struct sdtk* tientaikhoan = NULL;
    struct tk* suastk = NULL;
    struct sdtk* naprut = NULL;
    char cuoi[11] = "@gmail.com";
    while (tt) {
        printf("+----------------+\n");
        printf("|      MENU      |\n");
        printf("+----------------+\n");
        printf("| 1 |  Dang ky   |\n");
        printf("| 2 |  Dang nhap |\n");
        printf("| 3 |  Thoat     |\n");
        printf("+----------------+\n");
        printf("\n--->Nhap lua chon: ");
        int sql;
        scanf("%d", &sql);
        fflush(stdin);
        switch (sql) {
        case 1:
            system("cls");
            getchar();
            dangky(&t);
            luutk(&t);
            printf("Dang ky tai khoan thanh cong\n");
            printf("\nBAM PHIM BAT KY DE QUAY LAI\n");
            system("pause");
            continue;
            break;
        case 2:
            while (1) {
                system("cls");
                printf("+-----------------------+\n");
                printf("|       DANG NHAP       |\n");
                printf("+-----------------------+\n");
                printf("|  1 |Tiep tuc dang nhap|\n");
                printf("|  2 |       Thoat      |\n");
                printf("+-----------------------+\n");
                int nhap;
                printf("\n--->Chon: ");
                scanf("%d", &nhap);
                fflush(stdin);
                switch (nhap) {
                case 1:
                    char x[MAX], y[MAX];
                    system("cls");
                    getchar();
                    printf("---->Nhap ten dang nhap: ");
                    scanf("%[^\n]", x);
                    getchar();
                    printf("---->Nhap mat khau: ");
                    scanf("%[^\n]", y);
                    if (dangnhap(x, y, &t) == false) {
                        printf("Ten tai khoan hoac mat khau sai!!!\n");
                        if (dangnhaptk(x, &t) == true) {
                            int exitLoop = 0;
                            while (!exitLoop) {
                                printf("+---+--------------------+\n");
                                printf("| 1 | Quen mat khau      |\n");
                                printf("| 2 | Thoat              |\n");
                                printf("+---+--------------------+\n");
                                int pick;
                                printf("\n--->Chon:");
                                scanf("%d", &pick);
                                switch (pick) {
                                case 1: {
                                    char dienthoai[MAX];
                                    printf("-->Hay nhap so dien thoai dang ky: ");
                                    scanf("%s", dienthoai);
                                    if (strcmp(t.sdt, dienthoai) == 0) {
                                        char matkhau[MAX];
                                        printf("--->Nhap mat khau moi: ");
                                        scanf("%s", matkhau);
                                        while (ktramk(matkhau) == false) {
                                            printf("mat khau khong du manh (>=8 ky tu), chua it nhat 1 ky tu in hoa va so");
                                            printf("\n-->Nhap lai mat khau:");
                                            scanf("%s", matkhau);
                                        }
                                        strcpy(t.mk, matkhau);
                                        capnhat_tai_khoan(&t);
                                        printf("MAT KHAU DA DUOC DOI THANH CONG, VUI LONG DANG NHAP LAI!\n");
                                        printf("+---+--------------------+\n");
                                        printf("| 1 | Thoat              |\n");
                                        printf("+---+--------------------+\n");
                                        printf("--> Nhap(1):"); scanf("%d", &exitLoop);
                                    }
                                    else {
                                        printf("So dien thoai dang ky sai\n");
                                    }
                                    break;
                                }
                                case 2:
                                    exitLoop = 1;
                                    break;
                                default:
                                    printf("Lua chon khong hop le. Vui long chon lai.\n");
                                }
                            }
                        }
                        printf("\nBAM PHIM BAT KY DE QUAY LAI\n");
                        system("pause");
                        continue;
                    }
                    if (strcmp(t.chucvu, "quan ly") == 0) {
                        printf("Dang nhap voi vai tro: QUAN LY\n");
                        system("cls");
                        while (1) {
                            printf("+--------------------------------+\n");
                            printf("|   CHUC NANG CUA NGUOI QUAN LY  |\n");
                            printf("+--------------------------------+\n");
                            printf("| 1 |    Xem thong tin ca nhan   |\n");
                            printf("| 2 |    Xem danh sach tai khoan |\n");
                            printf("| 3 |    Sua thong tin           |\n");
                            printf("| 4 |    Quan ly so du           |\n");
                            printf("| 5 |    Tim kiem stk            |\n");
                            printf("| 6 |    Thong ke                |\n");
                            printf("| 7 |    Thoat                   |\n");
                            printf("+--------------------------------+");
                            int chon;
                            printf("\n--->Chon:");
                            scanf("%d", &chon);
                            switch (chon) {
                            case 1:
                                fflush(stdin);
                                system("cls");
                                printf("+--------------------------------------+\n");
                                printf("|         THONG TIN CA NHAN            |\n");
                                printf("+---------------+----------------------+\n");
                                printf("|Chuc vu        | %-21s|\n", t.chucvu);
                                printf("+--------------------------------------+\n");
                                printf("|Ten nguoi dung | %-21s|\n", t.hoten);
                                printf("+--------------------------------------+\n");
                                printf("Ten dang nhap   | %-21s|\n", t.tendangnhap);
                                printf("+---------------+----------------------+\n");
                                printf("|Ten tai khoan  | % -21s| \n", t.tentaikhoan);
                                printf("+---------------+----------------------+\n");
                                printf("|CCCD           | %-21s|\n", t.cccd);
                                printf("+---------------+----------------------+\n");
                                printf("|SDT            | %-21s|\n", t.sdt);
                                printf("+---------------+----------------------+\n");
                                printf("|Email          | %-21s|\n", t.email);
                                printf("+---------------+----------------------+\n");
                                break;
                            case 2:
                                fflush(stdin);
                                system("cls");
                                printf("       DANH SACH TAI KHOAN      \n");
                                hienthi_ds(t);
                                break;
                            case 3:
                                system("cls");
                                while (1) {
                                    printf("+--------------------------------+\n");
                                    printf("|           SUA THONG TIN        |\n");
                                    printf("+--------------------------------+\n");
                                    printf("| 1 |   Sua mat khau             |\n");
                                    printf("| 2 |   Sua ho va ten            |\n");
                                    printf("| 3 |   Sua so dien thoai        |\n");
                                    printf("| 4 |   Sua email                |\n");
                                    printf("| 5 |   Sua STK cho khach hang   |\n");
                                    printf("| 6 |   Thoat                    |\n");
                                    printf("+--------------------------------+\n");
                                    int Replace; printf("--> Chon:"); scanf("%d", &Replace);
                                    switch (Replace)
                                    {
                                    case 1:
                                        while (1) {
                                            printf("+---+-------------+\n");
                                            printf("| 1 |  Nhap mk cu |\n");
                                            printf("+---+-------------+\n");
                                            printf("| 2 |  Thoat      |\n");
                                            printf("+---+-------------+\n");
                                            int Nhap2;
                                            printf("--->Chon:");
                                            scanf("%d", &Nhap2);
                                            switch (Nhap2) {
                                            case 1:
                                                char Matkhau[MAX];
                                                printf("Hay nhap mat khau cu: ");
                                                scanf("%s", Matkhau);
                                                if (strcmp(t.mk, Matkhau) == 0) {
                                                    char Mknew[MAX];
                                                    printf("--->Nhap mat khau moi: ");
                                                    scanf("%s", Mknew);
                                                    while (ktramk(Mknew) == false) {
                                                        printf("mat khau khong du manh (>=8 ky tu), chua it nhat 1 ky tu in hoa va so");
                                                        printf("\n-->Nhap lai mat khau:");
                                                        scanf("%s", Mknew);
                                                    }
                                                    strcpy(t.mk, Mknew);
                                                    capnhat_tai_khoan(&t);
                                                    printf("MAT KHAU DA DUOC DOI THANH CONG!\n");
                                                    printf("+---+------------------+\n");
                                                    printf("| 1 | Tiep tuc thay doi|\n");
                                                    printf("+---+------------------+\n");
                                                    printf("| 2 | Tiep tuc su dung |\n");
                                                    printf("+---+------------------+\n");
                                                    printf("--->Chon:");
                                                    scanf("%d", &Nhap2);
                                                }
                                                else {
                                                    printf("Mat khau nhap sai\n");
                                                }
                                            }
                                            if (Nhap2 == 2) {
                                                break;
                                            }
                                        }
                                        break;
                                    case 2:
                                        char Fullname[MAX];
                                        printf("Hay nhap ho ten moi: ");
                                        scanf(" %[^\n]", Fullname);
                                        chuanhoa(Fullname);
                                        getchar();
                                        strcpy(t.hoten, Fullname);
                                        capnhat_tai_khoan(&t);
                                        printf("HO VA TEN DA DUOC DOI THANH CONG!\n");
                                        break;
                                    case 3:
                                        char Number[MAX];
                                        printf("Hay nhap so dien thoai moi: ");
                                        scanf("%s", Number);
                                        strcpy(t.sdt, Number);
                                        capnhat_tai_khoan(&t);
                                        printf("SDT DA DUOC DOI THANH CONG!\n");
                                        break;
                                    case 4:
                                        char Imeo[MAX];
                                        printf("-->Nhap email (Dang ky khong can nhap duoi @gmail.com ):");
                                        scanf("%s", Imeo);
                                        strcat(Imeo, cuoi);
                                        while (timemail(Imeo)) {
                                            printf("Email nay da duoc tao roi!!!");
                                            printf("\n-->Nhap lai email khac:");
                                            scanf("%s", Imeo);
                                            strcat(Imeo, cuoi);
                                        }
                                        strcpy(t.email, Imeo);
                                        capnhat_tai_khoan(&t);
                                        printf("Email DA DUOC DOI THANH CONG!\n");
                                        break;
                                    case 5:
                                        char Stk[MAX];
                                        char stknew[MAX];
                                        printf("-->Nhap so tai khoan khach hang can sua:");
                                        scanf("%s", Stk);
                                        suastk = timkiem(&t, Stk);
                                        if (suastk != NULL) {
                                            printf("-->Nhap so tai khoan can thay doi:");
                                            scanf("%s", stknew);
                                            while (timstk(stknew) || strlen(stknew)!=10) {
                                                printf("So tai khoan nay da duoc tao roi,hoac khong dung 10 ky tu so");
                                                printf("\n-->Nhap lai stk:");
                                                scanf("%s", stknew);
                                            }
                                            strcpy(t.stk, stknew);
                                            capnhat_tai_khoan(&t);
                                            printf("STK DA DUOC DOI THANH CONG!\n");
                                        }
                                        else {
                                            printf("Khong ton tai khach hang trong he thong tai khoan\n");
                                        }
                                        break;
                                    default:
                                        break;
                                    }
                                    if (Replace == 6) {
                                        break;
                                    }
                                }
                                break;
                            case 4:
                                fflush(stdin);
                                system("cls");
                                printf("       QUAN LY SO DU      \n");
                                hienthisodu_ds(sd);
                                break;
                            case 5:
                                system("cls");
                                char so[MAX];
                                printf("Nhap so tai khoan can tim:"); scanf("%s", &so);
                                check = timkiem(&t, so);
                                if (check != NULL) {
                                    printf("       THONG TIN SO TAI KHOAN      \n");
                                    hienthi1(check);
                                }
                                else {
                                    printf("Khong tim thay thong tin cua so tai khoan do\n");
                                }
                                break;
                            case 6:
                                while (1) {
                                    printf("+----------------------------------+\n");
                                    printf("|              THONG KE            | \n");
                                    printf("+---+------------------------------+\n");
                                    printf("| 1 | Khach hang co so du lon nhat |\n");
                                    printf("| 2 | Khach hang co so du nho nhat |\n");
                                    printf("| 3 | Thoat                        |\n");
                                    printf("+---+------------------------------+\n");
                                    int kh;
                                    printf("--> Lua chon:"); scanf("%d", &kh);
                                    FILE* f = fopen("42.bin", "rb");
                                    float x;
                                    float y;
                                    switch (kh)
                                    {
                                    case 1:
                                        system("cls");
                                        ktra1 = timsodumax(&sd);
                                        x = ktra1->sodu;
                                        printf("   KHACH HANG CO SO DU HIEN TAI LON NHAT     \n");
                                        while (fread(&sd, sizeof(struct sdtk), 1, f) == 1) {
                                            if (sd.sodu == x) {
                                                ktra = timkiem(&t, sd.STK);
                                                sdu_lon_nho(ktra, x);
                                                ktra = NULL;
                                            }
                                        }
                                        fclose(f);
                                        break;
                                    case 2:
                                        system("cls");
                                        ktraa2 = timsodumin(&sd);
                                        y = ktraa2->sodu;
                                        printf("   KHACH HANG CO SO DU HIEN TAI NHO NHAT     \n");
                                        while (fread(&sd, sizeof(struct sdtk), 1, f) == 1) {
                                            if (sd.sodu == y) {
                                                ktraa = timkiem(&t, sd.STK);
                                                sdu_lon_nho(ktraa, y);
                                                ktraa = NULL;
                                            }
                                        }
                                        fclose(f);
                                        break;
                                    default:
                                        break;
                                    }
                                    if (kh == 3) {
                                        break;
                                    }
                                }
                                break;
                            default:
                                printf("Thao tac khong hop le\n");
                                break;
                            }
                            if (chon == 7) {
                                break;
                            }
                        }
                    }
                    else if (strcmp(t.chucvu, "nguoi dung") == 0) {
                        printf("Dang nhap voi vai tro: NGUOI DUNG\n");
                        system("cls");
                        while (1) {
                            printf("+--------------------------------+\n");
                            printf("|     CHUC NANG CUA NGUOI DUNG   |\n");
                            printf("+--------------------------------+\n");
                            printf("| 1 |   Xem thong tin ca nhan    |\n");
                            printf("| 2 |   Xem so du                |\n");
                            printf("| 3 |   Sua thong tin            |\n");
                            printf("| 4 |   Nap tien                 |\n");
                            printf("| 5 |   Rut tien                 |\n");
                            printf("| 6 |   Thoat                    |\n");
                            printf("+--------------------------------|\n");
                            int chon1;
                            printf("\n--->Chon:");
                            scanf("%d", &chon1);
                            switch (chon1) {
                            case 1:
                                fflush(stdin);
                                system("cls");
                                printf("+--------------------------------------+\n");
                                printf("|         THONG TIN CA NHAN            |\n");
                                printf("+---------------+----------------------+\n");
                                printf("|Chuc vu        | %-21s|\n", t.chucvu);
                                printf("+--------------------------------------+\n");
                                printf("|Ten nguoi dung | %-21s|\n", t.hoten);
                                printf("+--------------------------------------+\n");
                                printf("Ten dang nhap   | %-21s|\n", t.tendangnhap);
                                printf("+---------------+----------------------+\n");
                                printf("|Ten tai khoan  | % -21s| \n", t.tentaikhoan);
                                printf("+---------------+----------------------+\n");
                                printf("|CCCD           | %-21s|\n", t.cccd);
                                printf("+---------------+----------------------+\n");
                                printf("|SDT            | %-21s|\n", t.sdt);
                                printf("+---------------+----------------------+\n");
                                printf("|STK            | %-21s|\n", t.stk);
                                printf("+---------------+----------------------+\n");
                                printf("|Email          | %-21s|\n", t.email);
                                printf("+---------------+----------------------+\n");
                                break;
                            case 2:
                                tientaikhoan = timkiemsdtk(&sd, t.stk);
                                fflush(stdin);
                                system("cls");
                                printf("+---------------+----------------------+\n");
                                printf("|So du hien tai | %-21.3f|\n", tientaikhoan->sodu);
                                printf("+---------------+----------------------+\n");
                                break;
                            case 3:
                                system("cls");
                                while (1) {
                                    printf("+--------------------------------+\n");
                                    printf("|           SUA THONG TIN        |\n");
                                    printf("+--------------------------------+\n");
                                    printf("| 1 |   Sua mat khau             |\n");
                                    printf("| 2 |   Sua ho va ten            |\n");
                                    printf("| 3 |   Sua so dien thoai        |\n");
                                    printf("| 4 |   Sua email                |\n");
                                    printf("| 5 |   Thoat                    |\n");
                                    printf("+--------------------------------|\n");
                                    int replace; printf("--> Chon:"); scanf("%d", &replace);
                                    switch (replace)
                                    {
                                    case 1:
                                        while (1) {
                                            printf("+---+-------------+\n");
                                            printf("| 1 |  Nhap mk cu |\n");
                                            printf("+---+-------------+\n");
                                            printf("| 2 |  Thoat      |\n");
                                            printf("+---+-------------+\n");
                                            int nhap2;
                                            printf("--->Chon:");
                                            scanf("%d", &nhap2);
                                            switch (nhap2) {
                                            case 1:
                                                char matkhau[MAX];
                                                printf("Hay nhap mat khau cu: ");
                                                scanf("%s", matkhau);
                                                if (strcmp(t.mk, matkhau) == 0) {
                                                    char mknew[MAX];
                                                    printf("--->Nhap mat khau moi: ");
                                                    scanf("%s", mknew);
                                                    while (ktramk(mknew) == false) {
                                                        printf("mat khau khong du manh (>=8 ky tu), chua it nhat 1 ky tu in hoa va so");
                                                        printf("\n-->Nhap lai mat khau:");
                                                        scanf("%s", mknew);
                                                    }
                                                    strcpy(t.mk, mknew);
                                                    capnhat_tai_khoan(&t);
                                                    printf("MAT KHAU DA DUOC DOI THANH CONG!\n");
                                                    printf("+---+------------------+\n");
                                                    printf("| 1 | Tiep tuc thay doi|\n");
                                                    printf("+---+------------------+\n");
                                                    printf("| 2 | Tiep tuc su dung |\n");
                                                    printf("+---+------------------+\n");
                                                    printf("--->Chon:");
                                                    scanf("%d", &nhap2);
                                                }
                                                else {
                                                    printf("Mat khau nhap sai\n");
                                                }
                                            }
                                            if (nhap2 == 2) {
                                                break;
                                            }
                                        }
                                        break;
                                    case 2:
                                        char fullname[MAX];
                                        printf("Hay nhap ho ten moi: ");
                                        scanf(" %[^\n]", fullname);
                                        chuanhoa(fullname);
                                        getchar();
                                        strcpy(t.hoten, fullname);
                                        capnhat_tai_khoan(&t);
                                        printf("HO VA TEN DA DUOC DOI THANH CONG!\n");
                                        break;
                                    case 3:
                                        char number[MAX];
                                        printf("Hay nhap so dien thoai moi: ");
                                        scanf("%s", number);
                                        strcpy(t.sdt, number);
                                        capnhat_tai_khoan(&t);
                                        printf("SDT DA DUOC DOI THANH CONG!\n");
                                        break;
                                    case 4:
                                        char imeo[MAX];
                                        printf("-->Nhap email (Dang ky khong can nhap duoi @gmail.com ):");
                                        scanf("%s", imeo);
                                        strcat(imeo, cuoi);
                                        while (timemail(imeo)) {
                                            printf("Email nay da duoc tao roi!!!");
                                            printf("\n-->Nhap lai email khac:");
                                            scanf("%s", imeo);
                                            strcat(imeo, cuoi);
                                        }
                                        strcpy(t.email, imeo);
                                        capnhat_tai_khoan(&t);
                                        printf("Email DA DUOC DOI THANH CONG!\n");
                                        break;
                                    default:
                                        break;
                                    }
                                    if (replace == 5) {
                                        break;
                                    }
                                }
                                break;
                            case 4:
                                float nap; printf("Nap them tien vao tai khoan :"); scanf("%f", &nap);
                                naprut = timkiemsdtk(&sd, t.stk);
                                char ma[MAX];
                                printf("Nha ma OTP:"); scanf("%s",ma);
                                if (timOTP(ma)==true) {
                                    naprut->sodu += nap;
                                    capnhat_sodu(&sd);
                                    printf("NAP TIEN  THANH CONG!\n");      
                                }
                                else {
                                    printf("Ma OTP sai!!!!!\n");
                                }
                                break;
                            case 5:
                                float rut; printf("Rut tien tu tai khoan :"); scanf("%f", &rut);
                                naprut = timkiemsdtk(&sd, t.stk);
                                while (rut > naprut->sodu) {
                                    printf("So du cua quy khach khong du.Hay nhap lai :"); scanf("%f", &rut);
                                }
                                char Ma[MAX];
                                printf("Nha ma OTP:"); scanf("%s", Ma);
                                if (timOTP(Ma)==true) {
                                    naprut->sodu -= rut;
                                    capnhat_sodu(&sd);
                                    printf("RUT TIEN  THANH CONG!\n");
                                }
                                else {
                                    printf("Ma OTP sai!!!!!\n");
                                }
                                break;
                            }
                            if (chon1 == 6) {
                                break;
                            }
                        }
                    }
                    break;
                }
                if (nhap == 2) {
                    break;
                }
            }
            break;
        }
        if (sql == 3) {
            break;
        }
    }
}