#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define max 100
void nhap(int a[],int n)
{
srand(time(NULL));
for(int i=1;i<=n;i++)
a[i]=rand()%50+1;//tao cac cong viec ngau nhien
}
void xuatfile(int a[],int n,int m)
{
printf("Cac cong viec can thuc hien: ");
for (int i=1;i<=n;i++)
printf("%d ",a[i]);
printf("\n");
}
void hoanvi(int &a,int &b)
{
int tam=a;
a=b;
b=tam;
}
void sapxepgiam(int a[],int n)
{
for(int i=1;i<n;i++)
for(int j=i+1;j<=n;j++)
if(a[j]>a[i])
hoanvi(a[i],a[j]);
}
int maymin(int a[][max],int m) //tim kiem xem hien tai may nao dang lam it viec nhat
{
int vt=1,min=a[1][-1];// a[1][-1] la tong thoi gian may 1 can de thuc hien cong viec
for(int i=1;i<=m;i++)
if(min>a[i][-1]) { min=a[i][-1]; vt=i; }
return vt;
}
void chiacv(int a[],int may[][max],int n,int m)
{
int k=n;
int t;
for(int i=1;i<=m;i++)
{
may[i][-1]=a[i];
may[i][1]=a[i];
may[i][0]=1;
}
while(k>m)
{
t=maymin(may,m);
may[t][-1]=may[t][-1]+a[k];
may[t][0]=may[t][0]+1;
may[t][may[t][0]]=a[k--];
}
}
void xuat(int may[][max],int m,int n)
{
printf("==================\n");
for (int i=1;i<=(n<m?n:m);i++)
{
printf("May thu %d: ",i);
for(int j=1;j<=may[i][0];j++)
printf("%d ",may[i][j]);
printf("\nTong thoi gian: %d\n==================",may[i][-1]);
printf("\n");
}
}
main()
{
int a[max],n,m,may[max][max];
printf("Nhap so cong viec: ");
scanf("%d",&n);
printf("Nhap so may: ");
scanf("%d",&m);
nhap(a,n);
xuatfile(a,n,m);
sapxepgiam(a,n);
chiacv(a,may,n,m);
xuat(may,m,n);
}
