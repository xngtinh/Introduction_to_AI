#include <iostream>
#include<bits/stdc++.h>
using namespace std;

#define MAX 50 // So cong viec va so may toi da

// Struct cua 1 cong viec
struct CongViec
{
	// Thoi gian can de hoan thanh cong viec
	int thoiGian;
	// Chi so cong viec
	int chiSo;
};

// Struct cua 1 may
struct May
{
	// Tong thoi gian may da lam
	int tongThoiGian;
	// So cong viec may da lam
	int soCongViec;
	// Danh sach cac cong viec may da lam
	CongViec Cv[MAX];
};

//Prototype
void nhapCongViec(CongViec Cv[], int soCongViec);
void xuatCongViec(CongViec Cv[], int soCongViec);
void sapXepCongViec(CongViec Cv[], int soCongViec);
int mayLamItNhat(May may[], int soMay);
void khoiTaoMay(May may[], int soMay);
void chiaCongViec(May may[], int soMay, CongViec Cv[], int soCongViec);
void xuatKetQua(May may[], int soMay);
void hoanViCongViec(CongViec &Cv1, CongViec &Cv2);

//Ham main cua chuong trinh
int main()
{
	CongViec Cv[MAX];
	May may[MAX];
	int soMay, soCongViec;

	cout<<"Nhap so luong may: ";
	cin >> soMay;
	cout<<"Nhap so luong cong viec: ";
	cin >> soCongViec;


	khoiTaoMay(may, soMay);
	nhapCongViec(Cv, soCongViec);

	sapXepCongViec(Cv, soCongViec);
	cout << "Cac cong viec duoc sap theo thoi gian giam dan: " << endl;
	xuatCongViec(Cv, soCongViec);

	chiaCongViec(may, soMay, Cv, soCongViec);
	xuatKetQua(may, soMay);
	cout << endl;
	
	return 0;
}

// Nhap thoi gian cho cac cong viec
void nhapCongViec(CongViec Cv[], int soCongViec)
{
	int i;
	cout<<"Hay nhap thoi gian cho moi cong viec: ";
	for(i = 0; i < soCongViec; i++)
	{
		Cv[i].chiSo = i + 1;
		cin >> Cv[i].thoiGian;
	}
}

// Xuat thong tin cac cong viec
void xuatCongViec(CongViec Cv[], int soCongViec)
{
	int i;
	for(i = 0; i < soCongViec; i++)
	{
		cout << "   [" << Cv[i].chiSo << "] = " << Cv[i].thoiGian; 
	}
}

// Sap xep cac cong viec theo thoi gian giam dan
void sapXepCongViec(CongViec Cv[], int soCongViec)
{
	int i, j;
	for(i = 0; i < soCongViec - 1; i++)
		for(j = i + 1; j < soCongViec; j++)
			if(Cv[i].thoiGian < Cv[j].thoiGian)
				hoanViCongViec(Cv[i], Cv[j]);
}

// Khoi tao cho cac may
void khoiTaoMay(May may[], int soMay)
{
	int i;
	for(i = 0; i < soMay; i++)
	{
		may[i].tongThoiGian = 0;
		may[i].soCongViec = 0;
	}
}

// Tim may co thoi gian lam viec it nhat
int mayLamItNhat(May may[], int soMay)
{
	int i, f = 0;
	int min = may[0].tongThoiGian;
	for(i = 1; i < soMay; i++)
	{
		if(min > may[i].tongThoiGian)
		{
			min = may[i].tongThoiGian;
			f = i;
		}
	}
	return f;
}

// Chia cong viec cho cac may
void chiaCongViec(May may[], int soMay, CongViec Cv[], int soCongViec)
{
	int f, k, i;
	for(i = 0; i < soCongViec; i++)
	{
		// Chon may co thoi gian lam viec it nhat
		f = mayLamItNhat(may, soMay);
		// So viec may duoc chon da lam
		k = may[f].soCongViec;
		// Them cong viec tiep theo cho may da chon
		may[f].tongThoiGian += Cv[i].thoiGian;
		may[f].Cv[k].thoiGian = Cv[i].thoiGian;
		may[f].Cv[k].chiSo = Cv[i].chiSo;
		may[f].soCongViec ++;
	}
}

// Xuat ket qua ra man hinh
void xuatKetQua(May may[], int soMay)
{
	int i, j;
	int max = may[0].tongThoiGian;
	for(i = 0; i < soMay; i++)
	{
		if(max < may[i].tongThoiGian)
			max = may[i].tongThoiGian;
			
		cout << endl <<"-----------------------------"<< endl << "May" << i + 1 << ":";
		cout << endl << "Tong thoi gian thuc hien : " << may[i].tongThoiGian;
		cout << endl <<"Thuc hien cac cong viec : ";
		for(j = 0; j < may[i].soCongViec; j++)
		{
			cout << "[" << may[i].Cv[j].chiSo << "] ";
		}
	}
	cout << endl << "thoi gian de hoan thanh cac cong viec la : " << max << " h" << endl;
}

// Hoan vi hai cong viec
void hoanViCongViec(CongViec &Cv1, CongViec &Cv2)
{
	CongViec temp;

	//Hoan vi thoi gian cong viec
	temp.thoiGian = Cv1.thoiGian;
	Cv1.thoiGian = Cv2.thoiGian;
	Cv2.thoiGian = temp.thoiGian;

	// Hoan vi chi so cong viec
	temp.chiSo = Cv1.chiSo;
	Cv1.chiSo = Cv2.chiSo;
	Cv2.chiSo = temp.chiSo;
}
