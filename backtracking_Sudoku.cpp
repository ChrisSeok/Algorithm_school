#include <iostream>
#include <fstream>
using namespace std;

int board[9][9];
int row, col;

bool isZero(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(board[i][j]==0){
                row = i; 
                col = j; 
                return true;
            }
        }
    }
    return false;
}

bool isAvailable(int r, int c, int num){ //가로,세로,subgrid에 num없어야
    for(int i=0;i<9;i++){//세로
        if(board[r][i]==num) return false;
    }
    for(int j=0;j<9;j++){//가로
        if(board[j][c]==num) return false;
    }
    int rstart = r-(r%3);
    int cstart = c-(c%3);
    for(int i=rstart;i<rstart+3;i++){ //subgrid
        for(int j=cstart;j<cstart+3;j++){
            if(board[i][j] == num) return false;
			}
    }
    return true;  
	 
}

bool Sudoku(){
    if(!isZero()) return true; //isZero함수 실행 후 row,col 값 바뀜

    //isZero가 참이고 row, col은 0인 원소의 인덱스로 바뀌어 있음
    int x = row;
    int y = col;
    for(int i=1;i<10;i++){//숫자 1에서9

        if(isAvailable(x,y,i)){

            board[x][y]=i;//assign 후 recursion

            if(Sudoku()) return true;
            else{
				board[x][y] = 0; //다음 i로 
			}	
        }
    }
    return false; //1~9 중available한 숫자가 하나도 없을 경우 
    
}


int main(){ 
    ifstream fin;
    fin.open("input.txt");
	
    int times;
    fin>>times;
	int element;
	
	for(int i=0;i<times;i++){
		row, col = 0;
		for(int r=0;r<9;r++){
			for(int c=0;c<9;c++){
				fin>>element;
				board[r][c] = element;
			}
		}
		cout<<"sudoku"<<i+1<<endl;
		Sudoku();
            for(int r=0;r<9;r++){
			    for(int c=0;c<9;c++){
				    cout<<board[r][c]<<' ';
			    }
			    cout<<endl;
		    }
	}
	
	return 0;
}

