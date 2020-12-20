#include <iostream>
using namespace std;
#include <windows.h>
#include <conio.h>


#define  cprintf printf
#define  getch _getch

enum COLORS {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};
void gotoxy(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x,y };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void clrscr()
{
    CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
    HANDLE  hConsoleOut;
    COORD   Home = { 0,0 };
    DWORD   dummy;

    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

    FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
    csbiInfo.dwCursorPosition.X = 0;
    csbiInfo.dwCursorPosition.Y = 0;
    SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}
void gotoxy(short x, short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x,y };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void textcolor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void ancontro()
{
    HANDLE hOut;
    CONSOLE_CURSOR_INFO ConCurInf;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &ConCurInf);
}
void hiencontro()
{
    HANDLE hOut;
    CONSOLE_CURSOR_INFO ConCurInf;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = TRUE;
    SetConsoleCursorInfo(hOut, &ConCurInf);
}
void delay(int n)
{
    Sleep(n);
}

class test
{
public:
    static void anscii();
    static void mau();
};
void test::anscii()
{
    //clrscr();
    int i;
    for (i = 1; i <= 255; i++) { printf("%4d%c   ", i, i); }
    //
    /*
    for (i=1 ;i<=6; i++ ){gotoxy(1,i*2);cprintf(" %d %c",i,i);}
    for (i=11 ;i<=12; i++ ){gotoxy(1,12+(i-10)*2);cprintf("%d %c",i,i);}
    for (i=14 ;i<=25; i++ ){gotoxy(1,16+(i-13)*2);cprintf("%d %c",i,i);}
    for (i=27 ;i<=31; i++ ){gotoxy(1,40+(i-26)*2);cprintf("%d %c",i,i);}
    for (i=127 ;i<=151; i++ ){gotoxy(15,(i-126)*2);cprintf("%d %c",i,i);}
    for (i=152 ;i<=176; i++ ){gotoxy(30,(i-151)*2);cprintf("%d %c",i,i);}
    for (i=177 ;i<=201; i++ ){gotoxy(45,(i-176)*2);cprintf("%d %c",i,i);}
    for (i=202 ;i<=226; i++ ){gotoxy(60,(i-201)*2);cprintf("%d %c",i,i);}
    for (i=227 ;i<=251; i++ ){gotoxy(75,(i-226)*2);cprintf("%d %c",i,i);}*/

    /*        getch();
    clrscr();
    for (i=251 ;i<=255; i++ ){gotoxy(1,(i-250)*2);cprintf(" %d %c",i,i);}
    cprintf("dau cach dac biet");
    */        _getch();
}
void test::mau()
{
    for (int i = 0; i < 16; i++)
    {
        textcolor(i);
        cout << endl << i << char(i + 'a');
    }
}
void textbackground(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}







//class menhde for VuongHao's Algorithms, coded by langman-Bui Tan Quang-25/12/2010 
class menhde
{
private:
    char* xau;
    int n; // length of xau, use as buffer that speed up the code before
    int number; // number of sub menhde in this menhde

    void update();
    static void xoakitu(char*, int);
    static int nguphap(char*);
    static void chuanhoa(char* str);
public:
    menhde();
    menhde(const char*);
    menhde(const menhde&);
    ~menhde();
    friend ostream& operator<<(ostream&, const menhde&);
    friend istream& operator>>(istream&, menhde&);
    menhde operator[](int) const;
    menhde chung(const menhde&);
    int  operator==(const menhde&) const;
    int  operator==(const char*)   const;
    void operator+=(const menhde&);
    void operator+=(const char*);
    void operator-=(const menhde&);
    void operator-=(const char*);
    void operator -(); //navigator
    void operator =(const menhde&);
    void operator -(menhde& x); //move navigator to x and vice versa
    int  cohoi();
    int  cotuyen();
    void tachhoi(); //split and ^
    void tachtuyen(); //split or U
    void chuyenve(menhde&);
    friend class bieuthuc;
};
menhde::menhde() :n(0), number(0)
{
    xau = new char[100];
}
menhde::menhde(const char* str) //unsafe for this class, exception can be made by this function
{
    xau = new char[100];
    for (int i = 0, temp1 = strlen(str); i <= temp1; i++)
        xau[i] = str[i];
    chuanhoa(xau);
    update();
}
menhde::menhde(const menhde& x)
{
    xau = new char[100];
    for (int i = 0; i <= x.n; i++)
        xau[i] = x.xau[i];
    n = x.n;
    number = x.number;
}
menhde::~menhde()
{
    delete xau;
}
ostream& operator<<(ostream& os, const menhde& x)
{
    for (int i = 0; i < x.n; i++)
    {
        switch (x.xau[i])
        {
        case 'a':textcolor(9); break;
        case 'b':textcolor(10); break;
        case 'c':textcolor(11); break;
        case 'd':textcolor(12); break;
        case 'e':textcolor(13); break;
        case 'p':textcolor(14); break;
        case 'q':textcolor(15); break;
        default:textcolor(8);
        }
        cprintf("%c", x.xau[i]);
    }
    textcolor(7);
    return os;
}
istream& operator>>(istream& is, menhde& x)
{
    hiencontro();
    int i = 0;
    char ch = 'a';
    int max = 99;
    int nopenscope = 0;
    int addflag = 1;

    while (ch != 13)
    {
        ch = _getch();
        addflag = 1;
        if (ch == 13 && i > 0 && strchr("abcdepq,)", x.xau[i - 1]) == 0) ch = 'z';
        if (ch == 8 && i)
        {
            cprintf("\b \b"), i--;
            if (x.xau[i] == '(') nopenscope--;
            else if (x.xau[i] == ')') nopenscope++;
        }
        ch = tolower(ch);
        if (strchr("abcdepq,~!&|()^vu", ch) == 0 || i == max) continue;
        if (strchr(",~!&|()^vu", ch)) textcolor(8);
        switch (ch)
        {
        case 'a':textcolor(9); break;
        case 'b':textcolor(10); break;
        case 'c':textcolor(11); break;
        case 'd':textcolor(12); break;
        case 'e':textcolor(13); break;
        case 'p':textcolor(14); break;
        case 'q':textcolor(15); break;
            //case '-':case '>':ch=26;break;                //condition
        case '!':case '~':ch = -86; break;                // not
        case '&':case '^':ch = -17; break;                // and
        case '|':case 'v':case 'u':ch = 'U'; break;    // or
        }
        // filler
        // case for ",," "U,"  // the end of a sub menhde can't is "->" "U" ....
        if (i > 0 && ch == ',' && (x.xau[i - 1] == ',' || x.xau[i - 1] == -86 || x.xau[i - 1] == -17 || x.xau[i - 1] == 'U')) continue;

        //case for "aa" ,"ab"  // 2 sub of menhde can not stand together
        if (i > 0 && strchr("abcdepq", ch) && strchr("abcdepq", x.xau[i - 1])) continue;

        //case for ! operator and '(' , not operator can't stand before a,b,c,d,e,p,q
        if (i > 0 && strchr("abcdepq", x.xau[i - 1]) && ch == -86) continue;

        //case for double operator stand together //! operator can stand together
        if ((i == 0 || x.xau[i - 1] == ',' || x.xau[i - 1] == -86 || x.xau[i - 1] == -17 || x.xau[i - 1] == 'U') && (ch == ',' || ch == -17 || ch == 'U')) continue;

        //case for ','
        if (i == '0' && ch == ',') continue;
        if (i > 0 && ch == ',' && (x.xau[i - 1] == ',' || x.xau[i - 1] == -86 || x.xau[i - 1] == -17 || x.xau[i - 1] == 'U')) continue;

        //case for ')'
        if (nopenscope == 0 && ch == ')') continue;
        if (ch == ')' && strchr("abcdepq()", x.xau[i - 1]) == 0) continue;
        if (ch == ')' && x.xau[i - 1] == '(') { cprintf("\b \b"), i--, nopenscope--; continue; }

        //case for '('
        if (i > 0 && strchr("abcdepq", x.xau[i - 1]) && ch == '(') continue;

        //count for ()
        if (ch == '(') nopenscope++;
        else if (ch == ')') nopenscope--;


        //case for multi operator not stand together
        if (strchr("abcdepq", ch) && i > 1 && x.xau[i - 1] == -86 && x.xau[i - 2] == -86)
            while (i > 1 && x.xau[i - 1] == -86 && x.xau[i - 2] == -86) cprintf("\b\b  \b\b"), i -= 2;

        //when input ',' close all open scope those are open
        if (ch == ',')
        {
            //process the excess scope
            char temp[100];
            int itemp = 0, j;
            char* p = x.xau + i - 1;
            while (p != x.xau && *p != ',') p--;
            for (char* q = p + (p != x.xau); q < x.xau + i; q++)
                temp[itemp++] = *q;
            for (j = 0; j < itemp; j++) cprintf("\b \b"), i--;
            while (nopenscope > 0)    temp[itemp++] = ')', nopenscope--;
            temp[itemp] = NULL;
            menhde::chuanhoa(temp);
            if (menhde::nguphap(temp))
            {
                //remove duplicate
                x.xau[i] = NULL;
                x.update();
                for (j = 0; j < x.number; j++)
                    if (x[j] == temp) temp[0] = NULL, addflag = 0;

                cout << menhde(temp);
                for (j = 0; j<int(strlen(temp)); j++)
                    x.xau[i++] = temp[j];
                textcolor(8);
            }
            else addflag = 0;
            delete temp;
        }
        if (addflag == 1)
        {
            x.xau[i++] = ch;
            cprintf("%c", ch);
        }
    }

    //remove final ',' if that to be
    if (ch == 13 && x.xau[i - 1] == ',') cprintf("\b \b"), i--;

    if (ch == 13)
    {
        //process the excess scope
        char* temp = new char[100];
        int itemp = 0, j;
        char* p = x.xau + i - 1;
        while (p != x.xau && *p != ',') p--;
        for (char* q = p + (p != x.xau); q < x.xau + i; q++)
            temp[itemp++] = *q;
        for (j = 0; j < itemp; j++) cprintf("\b \b"), i--;
        while (nopenscope > 0)    temp[itemp++] = ')', nopenscope--;
        temp[itemp] = NULL;
        menhde::chuanhoa(temp);
        if (menhde::nguphap(temp))
        {
            //remove duplicate
            x.xau[i] = NULL;
            x.update();
            for (j = 0; j < x.number; j++)
                if (x[j] == temp) temp[0] = NULL, addflag = 0;

            cout << menhde(temp);
            for (j = 0; j<int(strlen(temp)); j++)
                x.xau[i++] = temp[j];
            textcolor(8);
        }
        else addflag = 0;
        delete temp;
    }


    x.xau[i] = NULL;
    printf("\n");
    textcolor(7);
    x.update();
    ancontro();
    return is;
}
menhde menhde::operator[](int index) const
{
    menhde x;
    int i = 0, io = 0, ix = 0;
    for (i = 0; i < n && io < index && io < number; i++)
        if (xau[i] == ',') io++;
    for (; i < n && xau[i] != ','; i++)
        x.xau[ix++] = xau[i];
    x.xau[ix] = NULL;
    x.update();
    return x;
}
int  menhde::operator==(const menhde& x) const
{
    if (n != x.n || number != x.number) return 0;
    for (int i = 0; i < n; i++)
        if (xau[i] != x.xau[i]) return 0;
    return 1;
}
int  menhde::operator==(const char* str) const
{
    return *this == menhde(str);
}
void menhde::operator+=(const menhde& x)
{
    char* temp = new char[100];
    for (int i = 0, k; i < x.number; i++)
    {
        strcpy(temp, x[i].xau);
        int len = strlen(temp);
        char* p = strstr(xau, temp);
        if (p != NULL && (p == xau || *(p - 1) == ',') && (p[len] == NULL || p[len] == ',')) continue;
        if (number > 0) xau[n++] = ',';
        for (k = 0; k <= len; k++)
            xau[n++] = temp[k];
        number++;
        update();
        while (xau[n - 1] == ',' || xau[n - 1] == ' ') xau[--n] = NULL;
    }
    delete temp;
}
void menhde::operator+=(const char* str)
{
    (*this) += menhde(str);
}
void menhde::operator-=(const menhde& x)
{
    char* temp = new char[100];
    for (int i = 0; i < x.number; i++)
    {
        strcpy(temp, x[i].xau);
        int len = strlen(temp);
        char* p = strstr(xau, temp);
        if (p == NULL) continue;
        if (!(p == xau || *(p - 1) == ',')) continue;
        if (!(p[len] == NULL || p[len] == ',')) continue;
        while (*p != NULL && *p != ',') xoakitu(p, 0);
        if (*p == ',') xoakitu(p, 0);
        i--;
        update();
        while (xau[n - 1] == ',' || xau[n - 1] == ' ') xau[--n] = NULL;
    }
    delete temp;
}
void menhde::operator-=(const char* str)
{
    (*this) -= menhde(str);
}
void menhde::operator -() //only for sub menhde, fist sub menhde
{
    if (number == 1 && ((xau[0] == -86 && n == 2) || (n > 0 && xau[0] == -86 && xau[1] == '(' && xau[n - 1] == ')'))) menhde::xoakitu(xau, 0), chuanhoa(xau);
}
void menhde::operator =(const menhde& x)
{
    for (int i = 0; i <= x.n; i++)
        xau[i] = x.xau[i];
    n = x.n;
    number = x.number;
}
void menhde::operator -(menhde& x)
{
    (*this).chuyenve(x);
    x.chuyenve(*this);
}
void menhde::update()
{
    n = strlen(xau);
    number = 0;
    for (int i = 0; i < n; i++)
        if (xau[i] == ',') number++;
    number += (n != 0);
}
int  menhde::cohoi()
{
    int i, j, isubscope, flag, re = 0;
    for (i = 0; i < n; i++)
        if (i == 0 || xau[i - 1] == ',')
        {
            re++;
            isubscope = 0;
            flag = 1; //duoc quyen tach hoi hay ko
            for (j = i; j < n && xau[j] != ','; j++)
            {
                if (xau[j] == ')' && isubscope == 0) break;
                else if (xau[j] == '(') isubscope++;
                else if (xau[j] == ')') isubscope--;
                if (isubscope == 0 && xau[j] == 'U') flag = 0;
            }

            if (flag == 1)
            {
                for (j = i; j < n && xau[j] != ','; j++)
                {
                    if (xau[j] == ')' && isubscope == 0) break;
                    else if (xau[j] == '(') isubscope++;
                    else if (xau[j] == ')') isubscope--;
                    if (xau[j] == -17 && isubscope == 0) return re;
                }
            }
        }
    return 0;
}
void menhde::tachhoi() //split and ^
{
    int i, j, isubscope, flag;
    for (i = 0; i < n; i++)
        if (i == 0 || xau[i - 1] == ',')
        {
            isubscope = 0;
            flag = 1; //duoc quyen tach hoi hay ko
            for (j = i; j < n && xau[j] != ','; j++)
            {
                if (xau[j] == ')' && isubscope == 0) break;
                else if (xau[j] == '(') isubscope++;
                else if (xau[j] == ')') isubscope--;
                if (isubscope == 0 && xau[j] == 'U') flag = 0;
            }

            if (flag == 1)
            {
                for (j = i; j < n && xau[j] != ','; j++)
                {
                    if (xau[j] == ')' && isubscope == 0) break;
                    else if (xau[j] == '(') isubscope++;
                    else if (xau[j] == ')') isubscope--;
                    if (xau[j] == -17 && isubscope == 0) xau[j] = ',';
                }
            }
        }
    //xoa trung
    update();
    menhde temp(*this);
    xau[0] = NULL;
    n = 0;
    number = 0;
    *this += temp;
}
int  menhde::cotuyen()
{
    int i, j, isubscope, re = 0;
    for (i = 0; i < n; i++)
        if (i == 0 || xau[i - 1] == ',')
        {
            re++;
            isubscope = 0;
            for (j = i; j < n && xau[j] != ','; j++)
            {
                if (xau[j] == ')' && isubscope == 0) break;
                else if (xau[j] == '(') isubscope++;
                else if (xau[j] == ')') isubscope--;
                if (xau[j] == 'U' && isubscope == 0) return re;
            }
        }
    return 0;
}
void menhde::tachtuyen() //split or U
{
    int i, j, isubscope;
    for (i = 0; i < n; i++)
        if (i == 0 || xau[i - 1] == ',')
        {
            isubscope = 0;
            for (j = i; j < n && xau[j] != ','; j++)
            {
                if (xau[j] == ')' && isubscope == 0) break;
                else if (xau[j] == '(') isubscope++;
                else if (xau[j] == ')') isubscope--;
                if (xau[j] == 'U' && isubscope == 0) xau[j] = ',';
            }
        }
    //xoa trung
    update();
    menhde temp(*this);
    xau[0] = NULL;
    n = 0;
    number = 0;
    *this += temp;
}
void menhde::xoakitu(char* str, int i)
{
    for (int temp = strlen(str); i < temp; i++)
        str[i] = str[i + 1];
}
int  menhde::nguphap(char* str)
{
    //check for scope
    int nopenscope = 0, i, len = strlen(str);
    for (i = 0; i < len; i++)
        if (str[i] == '(') nopenscope++;
        else if (str[i] == ')') nopenscope--;
    if (nopenscope) return 0;

    //check for : endless with -> U ^ !
    if (str[len - 1] == -86 || str[len - 1] == -17 || str[len - 1] == 'U') return 0;

    //

    return 1;
}
void menhde::chuanhoa(char* str)
{
    int i;
    //cout<<endl<<"start : "<<str;

    //remove not operator
    for (i = 0; i<int(strlen(str)) - 1; i++)
    {
        if (str[i] == -86 && str[i + 1] == -86)
        {
            xoakitu(str, i);
            xoakitu(str, i);
            i -= 2;
        }
    }

    //remove scope
    for (i = 0; i<int(strlen(str)) - 1; i++)
        if (str[i] == '(')
        {
            int isempty = 1, isubscope = 0, j, ishoi = 1, istuyen = 1;
            //tim cai dong cua no la cai gan nhat va kiem tra luon xem co duoc quyen ton tai hay ko
            for (j = i + 1; j<int(strlen(str)); j++)
            {
                if (str[j] == ')' && isubscope == 0) break;
                else if (str[j] == '(') isubscope++;
                else if (str[j] == ')') isubscope--;
                else if (str[j] == 'U') ishoi = 0;
                else if (str[j] == -17) istuyen = 0;
                if (str[j] == 'U' || str[j] == -17) isempty = 0;
            }
            if (isempty == 1 || j - i == strlen(str) - 1 || ((ishoi == 1 || istuyen == 1) && str[i - 1] != -86))
            {
                //remove scope
                xoakitu(str, i--);
                xoakitu(str, j - 1);
            }

        }
    //remove not operator
    for (i = 0; i<int(strlen(str)) - 1; i++)
    {
        if (str[i] == -86 && str[i + 1] == -86)
        {
            xoakitu(str, i);
            xoakitu(str, i);
            i -= 2;
        }
    }

    //change ,, to ,
    for (i = 0; i<int(strlen(str)) - 1; i++)
        if ((str[i] == ',' && str[i + 1] == ',') || (str[i] == ' ')) xoakitu(str, i--);

    //cout<<endl<<"end : "<<str;
}
void menhde::chuyenve(menhde& x)
{
    for (int i = 0; i < number; i++)
    {
        menhde temp = (*this)[i];
        if ((temp.xau[0] == -86 && temp.n == 2) || (temp.n > 0 && temp.xau[0] == -86 && temp.xau[1] == '(' && temp.xau[temp.n - 1] == ')'))
        {
            i--;
            (*this) -= temp;
            -temp;
            x += temp;
        }
    }
}
menhde menhde::chung(const menhde& x)
{
    menhde temp, result;
    for (int i = 0; i < x.number; i++)
    {
        temp = x[i];
        int len = temp.n;
        char* p = strstr(xau, temp.xau);
        if (p != NULL && (p == xau || *(p - 1) == ',') && (p[len] == NULL || p[len] == ',')) result += temp;
    }
    return result;
}



//class bieuthuc for VuongHao's Algorithms, coded by langman-Bui Tan Quang-27/12/2010 
class bieuthuc
{
private:
    menhde  giathiet;
    menhde  giathietcon[50];
    int     ngiathietcon;
    menhde  ketluan;
    menhde  ketluancon[50];
    int     nketluancon;
    int        kq;
public:
    bieuthuc();
    bieuthuc(const char*, const char*);
    bieuthuc(const menhde&, const menhde&);
    friend ostream& operator<<(ostream&, const bieuthuc&);
    void phgtc(int); //"phan hoach gia thiet con"
    void phklc(int);
    void phanhoach();
    void cach() const;
    void buoc1();
    void buoc2();
    void buoc3();
    void buoc4();
    void buoc5();
    void buoc6();
    int  giai();
    void nhapgiathiet() { cin >> giathiet; }
    void nhapketluan() { cin >> ketluan; }
};
bieuthuc::bieuthuc() :giathiet(), ketluan() { ngiathietcon = 0; nketluancon = 0; kq = 1; }
bieuthuc::bieuthuc(const char* a, const char* b) : giathiet(a), ketluan(b) { ngiathietcon = 0; nketluancon = 0; kq = 1; }
bieuthuc::bieuthuc(const menhde& a, const menhde& b) : giathiet(a), ketluan(b) { ngiathietcon = 0; nketluancon = 0; kq = 1; }
ostream& operator<<(ostream& os, const bieuthuc& x)
{
    cout << x.giathiet;
    textcolor(7); cprintf(" %c ", 26);
    cout << x.ketluan;
    return os;
}
void bieuthuc::phgtc(int i)
{
    int k, j;
    menhde temp;
    menhde* a = &giathietcon[i];
    int x = a->cotuyen() - 1;
    temp = a->operator[](x);
    temp.tachtuyen();
    int soluong = temp.number; // tao ra "soluong" mau moi, add vao duoi cua giathietcon[]
    for (k = 0; k < soluong; k++)
    {
        //tao mau moi
        menhde* moi = new menhde;
        for (j = 0; j < a->number; j++)
            if (j != x) moi->operator+=(a->operator[](j));
            else moi->operator+=(temp[k]);
        //add
        giathietcon[ngiathietcon++] = *moi;
    }
    //xoa mau tai i
    for (k = i; k < ngiathietcon - 1; k++)
        giathietcon[k] = giathietcon[k + 1];
    ngiathietcon--;
}
void bieuthuc::phklc(int i)
{
    int k, j;
    menhde temp;
    menhde* a = &ketluancon[i];
    int x = a->cohoi() - 1;
    temp = a->operator[](x);
    temp.tachhoi();
    int soluong = temp.number; // tao ra "soluong" mau moi, add vao duoi cua giathietcon[]
    for (k = 0; k < soluong; k++)
    {
        //tao mau moi
        menhde* moi = new menhde;
        for (j = 0; j < a->number; j++)
            if (j != x) moi->operator+=(a->operator[](j));
            else moi->operator+=(temp[k]);
        //add
        ketluancon[nketluancon++] = *moi;
    }
    //xoa mau tai i
    for (k = i; k < nketluancon - 1; k++)
        ketluancon[k] = ketluancon[k + 1];
    nketluancon--;
}
void bieuthuc::phanhoach()
{
    ngiathietcon = 1;
    giathietcon[0] = giathiet;
    for (int i = 0; i < ngiathietcon; i++)
        if (giathietcon[i].cotuyen()) phgtc(i--);
    nketluancon = 1;
    ketluancon[0] = ketluan;
    for (int i = 0; i < nketluancon; i++)
        if (ketluancon[i].cohoi()) phklc(i--);
}
void bieuthuc::buoc1()
{
    cout << "     Buoc 1: Phat bieu lai bieu thuc\n";
    cout << "\t" << (*this) << endl;
}
void bieuthuc::buoc2()
{
    giathiet - ketluan;
    cout << "     Buoc 2: Chuyen ve cac phu dinh\n";
    cout << "\t" << (*this) << endl;
}
void bieuthuc::buoc3()
{
    giathiet.tachhoi();
    ketluan.tachtuyen();
    cout << "     Buoc 3: Tach hoi tai gia thiet, tach tuyen tai ket luan\n";
    cout << "\t" << (*this) << endl;
}
void bieuthuc::buoc4()
{
    cout << "     Buoc 4: Phan hoach gia thiet - tuyen, ket luan - hoi\n";
    //show gia thiet
    phanhoach();
    int i, j;
    for (i = 0; i < ngiathietcon; i++)
        for (j = 0; j < nketluancon; j++)
        {
            cout << "\t" << giathietcon[i];
            textcolor(7); cprintf(" %c ", 26);
            cout << ketluancon[j] << endl;
        }
}
void bieuthuc::buoc5()
{
    cout << "     Buoc 5: Kiem tra tinh dung dan cua tung menh de con\n";
    int i, j;
    menhde temp;
    kq = 1;
    for (i = 0; i < ngiathietcon; i++)
        for (j = 0; j < nketluancon; j++)
        {
            cout << "\t" << giathietcon[i];
            textcolor(7); cprintf(" %c ", 26);
            cout << ketluancon[j] << "    ";
            temp = giathietcon[i].chung(ketluancon[j]);
            if (temp.n == 0)
            {
                cout << "Khong duoc chung minh";
                kq = 0;
            }
            else
            {
                cout << "Duoc chung minh vi chung " << temp;
            }


            cout << endl;
        }
}
void bieuthuc::buoc6()
{
    cout << "     Buoc 6: Ket luan\n\t";
    if (kq == 1) cout << "Da duoc chung minh";
    cout << "Khong duoc chung minh";
}
int bieuthuc::giai()
{
    kq = 1;
    buoc1();
    buoc2();
    buoc3();
    buoc4();
    buoc5();
    buoc6();
    return kq;
}

class ungdung
{
public:
    ungdung();
    ~ungdung();
};
ungdung::ungdung()
{
    bieuthuc x;
    clrscr();
    gotoxy(18, 1); cout << "Chuong trinh mo phong giai thuat Vuong Hao";
    gotoxy(1, 2); cout << "I. Quy dinh chung" << endl;
    gotoxy(5, 3); cout << "+ Tap hop ki tu dung cho menh de  : "; textcolor(14); cout << "abcdepq,"; textcolor(7);
    gotoxy(5, 4); cout << "+ Phep gom nhom (thu tu uu tien 1): "; textcolor(14); cout << "()"; textcolor(7);
    gotoxy(5, 5); cout << "+ Phep phu dinh (thu tu uu tien 2): "; textcolor(14); cout << "!~"; textcolor(7);
    gotoxy(5, 6); cout << "+ Phep hoi      (thu tu uu tien 3): "; textcolor(14); cout << "&&"; textcolor(7);
    gotoxy(5, 7); cout << "+ Phep tuyen    (thu tu uu tien 4): "; textcolor(14); cout << "||"; textcolor(7);
    gotoxy(1, 9); cout << "II. Nhap vao menh de logic";
    gotoxy(5, 10); cout << "Nhap gia thiet :"; x.nhapgiathiet();
    gotoxy(5, 11); cout << "Nhap ket luan  :"; x.nhapketluan();
    gotoxy(1, 13); cout << "III. Trinh bay loi giai" << endl;
    x.giai();
}
ungdung::~ungdung()
{
   
}

int main()
{
    ungdung a;
    getch();
}
