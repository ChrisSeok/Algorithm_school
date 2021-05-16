#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
int min(int a,int b,int c){
    if(a<=b &&a<=c) return a;
    else if(b<=a && b<=c) return b;
    else return c;
}
void SequenceAlign(string x1,string y1,int m,int n){
    int Pgap= 3;
    int Pmismatch;
    string x2,y2 = ""; 
 
    int **M = new int*[m+1]; 
    for(int i=0;i<=m;++i){
        M[i] = new int[n+1];
    }

    for(int i=0;i<=n;i++){
        M[0][i] = Pgap*i;
    }
    for(int j=0;j<=m;j++){
        M[j][0] = Pgap*j;
    }
    
 
     for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(x1[i-1]==y1[j-1])Pmismatch = 0;
            else Pmismatch = 2;
            M[i][j] =min(M[i-1][j-1]+Pmismatch,M[i-1][j]+Pgap ,M[i][j-1]+Pgap);
        }
     }

     int i = m;
     int j = n;
     while((i>=1)&&(j>=1)){ 

        Pmismatch = 2;
        if(x1[i-1]==y1[j-1])Pmismatch = 0;
        
      
        if(M[i][j] == M[i-1][j-1] + Pmismatch){
            x2 = x1[i-1] + x2; 
            y2 = y1[j-1] + y2;
            i--;
            j--;
        }
        else if(M[i][j] == M[i-1][j] + Pgap){
            x2 = x1[i-1] + x2; 
            y2 = '-' + y2;
            i--;
        }
        else{
            x2 = '-' + x2; 
            y2 = y1[j-1] + y2;
            j--;
        }
     }

     while(i >= 1 && j < 1){ 
        x2 = x1[i-1] + x2;
        y2 = '-' + y2;
        i--;
        }

        while(j >= 1 && i < 1){
            x2 = '-' + x2;
            y2 = y1[j-1] + y2;
            j--;
        }

        cout<<x2<<endl;
        cout<<y2<<endl;

    for(int i=0;i<=m;i++){
        for(int j=0;j<=n;j++){
            cout<<M[i][j]<<' ';
        }
        cout<<endl;
    }


    for(int i=0;i<m;++i){
        delete[] M[i];
    }
    delete[] M;
}

int main(){
    ifstream fin;
	fin.open("input.txt");
	if(fin.fail()){
		cout<<"This program cannot open input file.";
		return 0;
	}
    int times;
    fin>>times;
    for(int i=0;i<times;i++){
        int m,n;
        string x1,y1;
        fin>>m;
        fin>>x1;
        fin>>n;
        fin>>y1;
        SequenceAlign(x1,y1,m,n);
    
    }

}