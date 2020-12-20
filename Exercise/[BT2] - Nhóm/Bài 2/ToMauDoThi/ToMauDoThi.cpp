#include <iostream>
#include <cstring>
#include <fstream>
 
#define MAX 20

using namespace std;

int n=0;
int a[MAX][MAX];
int total;
int v[MAX];

void readFile();
void printMatrix(int a[MAX][MAX], int n);
int color(int a[MAX][MAX], int n, int v[], int color);
int numColor(int a[MAX][MAX], int n, int v[]);
int result(int a[MAX][MAX], int n, int v[], int i, int c);

main(){
	readFile();
	printMatrix(a, n);
	total = numColor(a, n, v);
	cout<<"So mau da dung la "<<total<<endl;
	cout<<"Ket qua da to "<<endl;
	for (int i=0; i<n; i++){
		cout<<"Dinh "<<i<< " to mau "<<v[i]<<endl;
	}
	cout << endl;
	return 0;
}

void readFile(){
	int q,p;
    ifstream fs ("dothi.txt");
    if (fs.is_open())
    {
        fs >> n;
        while (!fs.eof()) //Doc file cho den cuoi file
        {
            fs >> q;
            fs >> p;
            a[q][p]=1;
            a[p][q]=1;
        }
        fs.close();
    }
    else cout << "Khong mo duoc file";
}
void printMatrix(int a[MAX][MAX], int n){
	for(int i=0;i<n;i++){ //In mang ra man hinh de theo doi
        for(int j=0;j<n;j++) cout << a[i][j] << "  ";
        cout << endl;
    }cout << endl;
}
int color(int a[MAX][MAX], int n, int v[], int color){
	int count = 0;
	for (int i=0; i<n; i++)
		if((v[i] == 0) && result(a, n, v, i, color)){
			v[i]=color;
			count++;
		}
	return count;
}
int numColor(int a[MAX][MAX], int n, int v[]){
	for (int i=0; i<n; i++){
		v[i]=0;
	}
	int count=0;
	int num=0;
	while(count<n){
		num++;
		count += color(a, n, v, num);
	}
	return num;
}
int result(int a[MAX][MAX], int n, int v[], int i, int c){
	for (int j=0; j<n; j++){
		if (a[i][j] && v[j] == c) return 0;
	}
	return 1;
}
