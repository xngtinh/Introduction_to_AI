#include <iostream>
#include <cstring>
#include <fstream>
 
#define MAX 20

using namespace std;

int n=0;
string a[MAX][MAX];
int total;
int v[MAX];

void readFile();
void printMatrix(string a[MAX][MAX], int n);

main(){
	readFile();
	printMatrix(a, n);
	return 0;
}

void readFile(){
	int col=0;
	int row=0;
	string x;
    ifstream fs ("input.txt");
    if (fs.is_open())
    {
        fs >> n;
        while (!fs.eof()) //Doc file cho den cuoi file
        {
        	while(getline(cin, fs>>x))
			{
            	a[row][col]= x;
            	col++;
			}
			row++;
        	
        }
        fs.close();
    }
    else cout << "Khong mo duoc file";
}
void printMatrix(string a[MAX][MAX], int n){
	for(int i=0;i<n;i++){ //In mang ra man hinh de theo doi
        for(int j=0;j<n;j++) cout << a[i][j] << "  ";
        cout << endl;
    }cout << endl;
}

