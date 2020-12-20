#include "stdio.h"
#include "conio.h"
#include "string.h"
#include "stdlib.h"
#define FileNut "SDLNut.txt"
#define FileLuat "SDLLuat.txt"
#define MAX_NUT 200
#define MAX_LUAT 100
#define LEN_YNGHIA 26
#define LEN_NUT 4
#define LEN_VT 4
#define NODE_AND 1
#define NODE_OR 2
/*
Moi nut thuoc 1 trong 3 loai: NutLa, TrungGian, KetLuan
*/
typedef enum Loai {NutLa,TrungGian,KetLuan};
typedef struct tagLuat{
	char TenLuat[10];
	int VT[2*LEN_VT];
	int VP;
	tagLuat() // Ham khoi tao
		{
			for (int i=0; i<2*LEN_VT; i++)
				VT[i] = 0;
			VP = 0;
		}
}LUAT;
//////////////////////////////////////////////////////////////////////////
LUAT TapLuat[MAX_LUAT];
int SoLuat = 0;
char NutTen[MAX_NUT][LEN_NUT];
char NutYNghia[MAX_NUT][LEN_YNGHIA];
int SoNut = 0;
int GTNut[MAX_NUT]; // =0: Sai; =1: Dung ; =-1 : Chua biet
enum Loai NutLoai[MAX_NUT];
//////////////////////////////////////////////////////////////////////
// Dinh nghia cac ham
void DocNutTuFile(char* FileName){
	FILE *f;
	char Ten[LEN_NUT];
	int k;
	// Doc luat tu file vao mang tap luat
	f = fopen(FileName, "rt");
	if (f!= NULL){
		fscanf(f, "%d\n", &SoNut);
		for (int i=1; i<=SoNut; i++)
		{
			fscanf(f, "%s %s\n", &NutTen[i], &NutYNghia[i]);
		}
	}
	else
	{
		printf("\n Khong tim thay file : %s !!!", FileName);
		getch();
	}
	fclose(f);
}
// Ham tim vi tri cua nut co ten (Ten) trong mang NutTen[]
int TimVitriNut(char *Ten){
	for (int i=1; i<=SoNut; i++)
		if (strcmp(NutTen[i], Ten) == 0)
			return i;
	return 0;
}
// Ham doc danh sach cac luat tu file vao mang TapLuat[]
void DocLuatTuFile(char* FileName){
	FILE *f;
	int nCount, bNot;
	char stInput[1024];
	int nLen, iFnd, jFnd, j;
	char stTen[LEN_NUT];
	f = fopen(FileName, "rt");
	if (f!=NULL)
	{
		fscanf(f, "%d", &SoLuat);
		for (int i=0; i<SoLuat; i++)
		{
			fscanf(f, "%s", &stInput);
			nLen = strlen(stInput);
			jFnd = 0;
			iFnd = 0;
			while (jFnd<nLen && stInput[jFnd] != ':')
			TapLuat[i].TenLuat[iFnd++] = stInput[jFnd++];
			// Tim vi tri phan cach ve trai va ve phai
			jFnd ++;
			while (jFnd<nLen && stInput[jFnd] != '>')
			jFnd ++;
			// Xu ly ve trai
			bNot = 1; nCount = 0;
			iFnd ++; // Bo qua dau ':'
			while (iFnd<jFnd-1)
			{
				while (iFnd<jFnd-1 && stInput[iFnd] == ' ')
				iFnd++; // Bo qua cac khoang trang
				if (stInput[iFnd] == '^')
				{
					TapLuat[i].VT[2*nCount] = NODE_AND;
				}
				else
				if (stInput[iFnd] == '|')
				{
					TapLuat[i].VT[2*nCount] = NODE_OR;
				}
				else
				if (stInput[iFnd] == '~')
				bNot = -1;
				else
				{
					j = iFnd;
					while (j<jFnd && stInput[j] != ' ' && stInput[j] != '|'
					&& stInput[j] != '^' && stInput[j] != '~' && stInput[j] != '=')
					stTen[j-iFnd] = stInput[j++];
					stTen[j-iFnd] = '\0';
					TapLuat[i].VT[2*nCount+1] =
					bNot*TimVitriNut(stTen);
					bNot = 1;
					nCount ++;
					iFnd = j-1;
				}
				iFnd ++;
			}
			// Xu ly ve phai
			iFnd = jFnd+1;
			while (iFnd<nLen)
			stTen[iFnd-jFnd-1] = stInput[iFnd++];
			stTen[iFnd-jFnd-1] = '\0';
			TapLuat[i].VP = TimVitriNut(stTen);
		}
	}
	else
	{
		printf("\n Khong tim thay file: %s", FileName);
		getch();
	}
	fclose(f);
}
////////////////////////////////////////////////////////////////////
void PhanLoaiNut()
{
	int bNot; // =1 khi khang dinh, =-1 khi phu dinh
	int bFound;
	for (int i=0; i<SoLuat; i++) // Duyet tren ve phai cua tung luat
	{
		bFound = 0;
		for (int j=0; j<SoLuat && bFound == 0; j++)
		{
		// Duyet o ve trai cua tung luat
			for (int k=1; k<2*LEN_VT && bFound == 0; k+=2)
			{
			bNot = 1;
			if (TapLuat[j].VT[k]<0)
				bNot = -1; // Gan =-1 de khi nhan vao thanh so duong
			if (bNot*TapLuat[j].VT[k] == TapLuat[i].VP)
				bFound = 1;
			}
		}
		if (bFound == 0) // Neu tim khong gap o ve trai > Day la nut KetLuan
			NutLoai[TapLuat[i].VP] = KetLuan;
		else
			NutLoai[TapLuat[i].VP] = TrungGian;
	}
}
/////////////////////////////////////////////////////////////////////
// Hoi nguoi dung gia tri cua nut thu VitriNut.
void HoiNguoiDung(int VitriNut)
{
	int traloi;
	do
	{
		printf("\n Cho biet gia tri cua nut %s (%s) (1: Dung; 0: Sai)? ",
		NutTen[VitriNut], NutYNghia[VitriNut]);
		scanf("%d", &traloi);
		if (traloi == 0 || traloi == 1)
			break;
	}
	while(traloi != 0 && traloi != 1);
		GTNut[VitriNut] = traloi;
}
int NOT(int p)
{
	if (p == 0)
		return 1;
	else
		return 0;
}
int AND (int p, int q)
{
	if (p == 1 && q ==1)
		return 1;
	else
		return 0;
}
int OR (int p, int q)
{
	if (p == 1 || q == 1)
		return 1;
	else
		return 0;
}
/////////////////////////////////////////////////////////////////////
// Ham nay tinh gia tri cua 1 nut ket luan
void TinhGiaTriCuaNutKetLuan(int SoHieuNut)
{
	LUAT r;
	int bNot;
	int giatri, x;
	// Neu nut nay co gia tri roi > khong can tinh
	if (GTNut[SoHieuNut] >=0)
	return;
	// Tim luat co ket luan la SoHieuNut
	for (int i=0; i<SoLuat; i++)
	{
		r = TapLuat[i];
		if (r.VP == SoHieuNut || (-1)*r.VP == SoHieuNut) // Neu tim gap
		{
		// Duyet ve trai cua luat de tinh gia tri cac nut o ve trai
			for (int j=0; j<LEN_VT; j++)
			{
				bNot = 1;
				if (r.VT[2*j+1]<0)
					bNot = -1;
				if (GTNut[bNot*r.VT[2*j+1]]<0) // Neu nut nay chua co gia tri
				{
				// Neu nut chua co gia tri nay la NutLa > Hoi nguoi dung
					if (NutLoai[bNot*r.VT[2*j+1]] == NutLa)
						HoiNguoiDung(bNot*r.VT[2*j+1]);
					else // Day la nut TrungGian
						TinhGiaTriCuaNutKetLuan(bNot*r.VT[2*j+1]);
				}
			}
			// Den day, Cac nut o ve trai deu co gia tri > Tinh gia tri cua ve phai dua vao luat r
			if (r.VT[1]<0)
				giatri = NOT(GTNut[r.VT[1]]);
			else
				giatri = GTNut[r.VT[1]];
			for (int j=1; j<LEN_VT && r.VT[2*j+1]!=0; j++)
			{
				// x la gia tri cua nut phia sau
				if (r.VT[2*j+1]<0)
					x = NOT(GTNut[r.VT[2*j+1]]);
				else
					x = GTNut[r.VT[2*j+1]];
				if (r.VT[2*j] == NODE_AND)
					giatri = AND(giatri, x);
				else
					giatri = OR(giatri,x);
			}
			GTNut[r.VP] = giatri;
		}
	}
}
/////////////////////////////////////////////////////////////////////
void HienThiTapNut()
{
	system("cls");
	printf("\n DANH SACH CAC NUT \n");
	printf("\nTEN NUT Y NGHIA\n");
	for (int i=1; i<=SoNut; i++)
		printf("\n%4s %s", NutTen[i], NutYNghia[i]);
	printf("\n\n\n An ENTER de quay ve man hinh chinh");
	getch();
}
/////////////////////////////////////////////////////////////////////
// Tu luat > tao chuoi luat
void TaoChuoiLuat(int SoHieuLuat, char ChuoiLuat[])
{
	int bNot;
	ChuoiLuat[0] = '\0';
	for (int j=0; j<LEN_VT; j++)
		if (TapLuat[SoHieuLuat].VT[2*j+1] != 0)
		{
			bNot = 1;
			if (TapLuat[SoHieuLuat].VT[2*j] == NODE_AND)
				strcat(ChuoiLuat, " & ");
			else
				if (TapLuat[SoHieuLuat].VT[2*j] == NODE_OR)
					strcat(ChuoiLuat, " | ");
			if (TapLuat[SoHieuLuat].VT[2*j+1] < 0)
			{
				strcat(ChuoiLuat, "~");
				bNot = -1;
			}
			strcat(ChuoiLuat,
			NutTen[(bNot*TapLuat[SoHieuLuat].VT[2*j+1])]);
		}
	strcat(ChuoiLuat, " => ");
	strcat(ChuoiLuat, NutTen[TapLuat[SoHieuLuat].VP]);
	ChuoiLuat[strlen(ChuoiLuat)] = '\0';
}
/////////////////////////////////////////////////////////////////////
// Hien thi danh sach cac luat
void HienThiTapLuat()
{
	char stLuat[1024];
	system("cls");
	printf (" DANH SACH CAC LUAT\n");
	printf("\n STT LUAT\n");
	for (int i=0; i<SoLuat; i++)
	{
		TaoChuoiLuat(i, stLuat);
	printf("\n%2d %30s", i+1, stLuat);
}
printf("\n\n\n An ENTER de quay ve man hinh chinh");
getch();
}
// Xu ly qua trinh suy dien lui
void Xuly_SuyDienLui()
{
	system("cls");
	for (int i=1; i<=SoNut; i++)
	{
		GTNut[i] = -1;
	}
	for (int i=1; i<=SoNut; i++)
		if (NutLoai[i] == KetLuan)
		{
			TinhGiaTriCuaNutKetLuan(i);
		}
	printf("\n Ket qua qua trinh suy dien lui:\n");
	for (int i=1; i<=SoNut; i++)
		if (NutLoai[i] == KetLuan)
		{
			printf("\n Nut ket luan %s (%s) co gia tri la: %d", NutTen[i],
			NutYNghia[i], GTNut[i]);
		}
	printf("\n\n\n An ENTER de quay ve man hinh chinh");
	getch();
}
// Ham nay hien thi gia tri cua cac nut
void HienThiGTNut()
{
system("cls");
printf ("\n BANG GIA TRI CUA CAC NUT\n\n");
for (int i=1; i<=SoNut; i++)
{
printf("\n%s (%s): %d", NutTen[i], NutYNghia[i], GTNut[i]);
}
printf("\n\n\n An ENTER de quay ve man hinh chinh");
getch();
}
/////////////////////////////////////////////////////////////////////
// Trinh bay giao dien
void GiaoDien()
{
	char chon;
	do{
		system("cls");
		printf("\nCHUONG TRINH MINH HOA SUY DIEN LUI\n\n");
		printf("\n 1. XEM TAP NUT");
		printf("\n 2. XEM TAP LUAT");
		printf("\n 3. CHAY CHUONG TRINH");
		printf("\n 4. XEM GIA TRI CUA CAC NUT");
		printf("\n 5. THOAT");
		printf(" Chon (1, 2, 3, 4, 5): ");
		chon = getch();
		switch (chon)
			{
			case '1':
					HienThiTapNut();
					break;
			case '2':
					HienThiTapLuat();
					break;
			case '3':
					Xuly_SuyDienLui();
					break;
			case '4':
					HienThiGTNut();
					break;
			case '5':
				exit(0);
			}
	}
	while (1);
}
// Chuong trinh chinh
int main()
{
	DocNutTuFile(FileNut);
	DocLuatTuFile(FileLuat);
	PhanLoaiNut();
	// Khoi tao gia tri cua cac nut =-1 (Chua biet)
	for (int i=1; i<=SoNut; i++)
	{
		GTNut[i] = -1;
	}
	GiaoDien();
	return 0;
}
