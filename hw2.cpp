#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib> 
using namespace std;


void MergeTwoArea(int *arr,int left,int mid,int right){
	
	int *newArr = new int[right+1];
    int newidx = left;
    int start = left; 
    int mplus = mid+1;
    
    while((start<=mid)&&(mplus<=right)){
        if(arr[start]<=arr[mplus]){

        	newArr[newidx] = arr[start];
        	start++;
        }
        else{ 
			newArr[newidx] = arr[mplus]; 
	        mplus++;
    	}
    	newidx++;
    }
    
    if(start>mid){ 
        for (int i=mplus;i<=right;i++){
            newArr[newidx] = arr[i];
            newidx++;
        }
    }
    else{
        for(int i=start;i<=mid;i++){
            newArr[newidx] = arr[i];
            newidx++;
        }
    }
    
    for(int i=left;i<=right;i++){
        arr[i] = newArr[i];
    }

}
void Mergesort(int *arr,int left,int right){
	int mid;
    if(left<right){

        mid = (left+right)/2;
        Mergesort(arr,left,mid);
        Mergesort(arr,mid+1,right);
        MergeTwoArea(arr,left,mid,right);
        }
}

void Quicksort(int *arr, int start, int end){ 
	if(start >= end){ 
		return; 
	} 
	
	int pivot = start; 
	int i = pivot + 1; 
	int j = end; 
	
	int temp; 
	while(i <= j){ 
		while(i <= end && arr[i] <= arr[pivot]){  
			i++; 
		} 
		while(j > start && arr[j] >= arr[pivot]){ 
			j--; 
		} 
		
		if(i > j){ 
		temp = arr[j]; 
		arr[j] = arr[pivot]; 
		arr[pivot] = temp;
		}
		else{ 
		temp = arr[i]; 
		arr[i] = arr[j]; 
		arr[j] = temp; 
		} 
		
	}
	Quicksort(arr,start,j-1); 
	Quicksort(arr,j+1,end); 
} 


double randMresult[3][3];
double randQresult[3][3];
double Mavg[3]={0,0,0};
double Qavg[3]={0,0,0};

void FillRand(int R,int data){
		int *arr= new int[R];
	for(int i=0;i<3;i++){	
		for(int j=0;j<R;j++){
			arr[j]=rand();
		}
	    int len = R-1;
	    clock_t MstartTime = clock();
	      Mergesort(arr,0,len);
		clock_t MendTime = clock();
		randMresult[i][data] = (double)(MendTime-MstartTime)/CLOCKS_PER_SEC;
		Mavg[data] = Mavg[data]+randMresult[i][data];
	    clock_t QstartTime = clock();
	     Quicksort(arr,0,len);
	    clock_t QendTime = clock();
	    randQresult[i][data]=(double)(QendTime-QstartTime)/CLOCKS_PER_SEC;
	    Qavg[data] = Qavg[data]+randQresult[i][data];
	    
	    delete[] arr;
	}
}



int main(){
	std::srand(5323);	
	ifstream fin;
	fin.open("input.txt");
	if(fin.fail()){
		cout<<"This program cannot open input file.";
		return 0;
	}
	int N,R;
	double result[2][3];
	
	cout<<"sorted\t\t";
	
	for(int i=0;i<3;i++){
		fin>>N;
		int *arr= new int[N];
		cout<<"N="<<N<<"\t\t";
		
		for(int j=0;j<N;j++){
			arr[j]=j;
		}
		int len = N-1;
	    clock_t MstartTime = clock();
	      Mergesort(arr,0,len);
		clock_t MendTime = clock();
		result[0][i]=(double)(MendTime-MstartTime)/CLOCKS_PER_SEC;
	
	    clock_t QstartTime = clock();
	    Quicksort(arr,0,len);
	    clock_t QendTime = clock();
	    	result[1][i]=(double)(QendTime-QstartTime)/CLOCKS_PER_SEC;
	    
	     delete[] arr;
}
cout<<endl;
	
	printf("Merge sort\t");
	
	for(int i=0;i<3;i++){
		printf("%8f\t",result[0][i]);
	}
	
	printf("\nQuick sort\t");
	
	for(int i=0;i<3;i++){
		printf("%8f\t",result[1][i]);
	}
	cout<<endl<<endl;
	
	
	printf("random\t\t\t");

	for(int i=0;i<3;i++){
		fin>>R;
		FillRand(R,i);
		cout<<"N="<<R<<"\t\t";
	}
	
	cout<<endl;
	
	printf("Merge sort\n");
	for(int i=0;i<3;i++){
		printf("\t\t");
		cout<<"data"<<i+1;
		printf("\t");
		for(int j=0;j<3;j++){
		printf("%8f\t",randMresult[i][j]);
		}
		cout<<endl;
	}
	printf("\t\taverage\t");
	for(int i=0;i<3;i++){
		printf("%8f\t",Mavg[i]/3);
	}
		
	cout<<endl<<endl;
	
	printf("Quick sort\n");
	for(int i=0;i<3;i++){
		printf("\t\t");
		cout<<"data"<<i+1;
		printf("\t");
		for(int j=0;j<3;j++){
		printf("%8f\t",randQresult[i][j]);
		}
		cout<<endl;
	}
	printf("\t\taverage\t");
	for(int i=0;i<3;i++){
		printf("%8f\t",Qavg[i]/3);
	}
	
}
