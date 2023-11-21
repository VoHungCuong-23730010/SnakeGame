#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>
#include <random>

using namespace std;

#define dotToiDa 500
#define doDaiMacDinh 5
#define tocDoThap 400
#define tocDoTrungBinh 300
#define tocDoCao 150
void diChuyenCotDong(int cot, int dong);
struct Point
{
    int cot, dong;
};

int capDo = 1;// 1- de, 2 - trung binh, 3 - kho
int diem = 0;
Point conMoi;
Point gocTraiTren;// góc trái trên
Point gocPhaiDuoi;// góc phải dưới

class CONRAN
{
public:
    struct Point dotRan[dotToiDa];
    int doDai = doDaiMacDinh;
    int tocDo = tocDoThap;
    bool lonLen = false;
    CONRAN()
    {
        gocTraiTren.cot = 10;// tọa độ cột góc trái trên của khung trong chơi
        gocTraiTren.dong = 04;// tọa độ dòng góc trái trên của khung trò chơi
        gocPhaiDuoi.cot = 92;// tọa độ cột góc phải dưới của khung trò chơi
        gocPhaiDuoi.dong = 24;// tọa độ dòng góc phải dưới của khung trò chơi

        khoiTaoThanRan();
    }

    /**
    * Khởi tạo thân rắn
    */
    void khoiTaoThanRan()
    {
        // điểm bắt đầu game
        Point diemBatDau;
        diemBatDau.cot = (gocTraiTren.cot + gocPhaiDuoi.cot)/2;
        diemBatDau.dong = (gocTraiTren.dong + gocPhaiDuoi.dong)/2;

        // khởi tạo tọa độ cho các đốt của thân rắn
        for(int i=0; i<doDai; i++)
        {
            dotRan[i].cot = diemBatDau.cot--;
            dotRan[i].dong = diemBatDau.dong;
        }
    }
    void veConRan()
    {
        diChuyenCotDong(dotRan[0].cot,dotRan[0].dong);
        cout << "O";
        for (int i = 1; i < doDai; i++)
        {
            diChuyenCotDong(dotRan[i].cot,dotRan[i].dong);
            cout<<"+";
        }
    }
    void diChuyen(int Huong)
    {
        for (int i = doDai-1; i>0; i--)
            dotRan[i] = dotRan[i-1];
        if (Huong==0) dotRan[0].cot = dotRan[0].cot + 1;
        if (Huong==1) dotRan[0].dong = dotRan[0].dong + 1;
        if (Huong==2) dotRan[0].cot = dotRan[0].dong - 1;
        if (Huong==3) dotRan[0].cot = dotRan[0].dong - 1;

    }
    // Khi ran di chuyen xoa anh ran cu tren man hinh (xoa dot cuoi cung)
    void xoaConRan()
    {
        gotoxy(dotRan[DoDai].cot, dotRan[DoDai].dong);
        cout<< " ";
    }

    void veConRanChet()
    {
        // Ve cai minh luc ran chet
        for (int i = 1; i < DoDai; i++)
        {
            gotoxy(dotRan[i].cot, dotRan[i].dong);
            cout<< ".";
        }
        // Ve cai dau khi ran chet
        gotoxy(dotRan[0].cot, dotRan[0].dong);
        cout<< "*";
    }    
    // Khi dau ran cham vao vien ham tra ve <true>
	bool ktDauChamVien()
    {
        if(dotRan[0].cot == gocTrenTrai.cot || dotRan[0].cot == gocDuoiPhai.cot || dotRan[0].dong == gocTrenTrai.dong || dotRan[0].dong == gocDuoiPhai.dong)
            return true;
        return false;
    }
    // Khi dau ran cham phai than cua no thi ham tra ve <true>
    bool ktDauChamThan()
    {
        for (int i = 1; i < doDai; i++)
        {
            if(dotRan[0].cot == dotRan[i].cot && dotRan[0].dong == dotRan[i].dong)
                return true;
        }
        return false;
    }
};

/**
* Di chuyển con trỏ tới vị trí dòng và cột
*/
void diChuyenCotDong(int cot, int dong)
{
    COORD coord;
    coord.X = cot;
    coord.Y = dong;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/**
* Chơi lại
* Làm mới các chỉ số của rắn tương ứng với loại trò chơi và độ khó
*/
void choiLai(CONRAN r) {
    // làm mới các chỉ số
    diem = 0;
    r.doDai = doDaiMacDinh;
    if (capDo == 1)
    {
        r.tocDo = tocDoThap;
    }
    if (capDo == 2)
    {
        r.tocDo = tocDoTrungBinh;
    }
    if (capDo == 3)
    {
        r.tocDo = tocDoCao;
    }

    r.khoiTaoThanRan();
}

/**
* Kiểm tra con mồi được tạo có bị trung với con rắn không
*/
bool ktConMoiTrungConRan(CONRAN r)
{
    for (int i = 0; i < r.doDai; i++)
    {
        if (conMoi.cot == r.dotRan[i].cot && conMoi.dong == r.dotRan[i].dong)
            return true;
    }
    return false;
}

/**
* Vẽ con mồi
*/
void veConMoi(CONRAN r)
{
    srand(time(0));
    while(true)
    {
        // random tọa độ của con mồi
        conMoi.cot = (rand() % (gocPhaiDuoi.cot - gocTraiTren.cot - 1)) + gocTraiTren.cot + 1;
        conMoi.dong = (rand() % (gocPhaiDuoi.dong - gocTraiTren.dong - 1)) + gocTraiTren.dong + 1;

        // kiểm tra nếu tạo độ con mồi trùng với con rắn thì tạo lại
        if (ktConMoiTrungConRan(r))
        {
            continue;
        }

        break;
    }

    // di chuyển con trỏ tới tọa độ của con mồi để vẽ con mồi
    diChuyenCotDong(conMoi.cot, conMoi.dong);
    cout << "x";
}

/**
* xóa con mồi
*/
void xoaConMoi()
{
    diChuyenCotDong(conMoi.cot, conMoi.dong);
    cout << " ";
}
int main()
{
    CONRAN r;
    int Huong = 0;
    char t;

    // xuất tiếng việt có dấu ra màn hình
    SetConsoleOutputCP(65001);
    veConMoi(r);
    while (1)
    {
        if (kbhit())
        {
            t = getch();
            if (t=='a') Huong = 2;
            if (t=='w') Huong = 3;
            if (t=='d') Huong = 0;
            if (t=='x') Huong = 1;
        }
        r.veConRan();
        r.diChuyen(Huong);
        Sleep(300);
    }

    return 0;
}
