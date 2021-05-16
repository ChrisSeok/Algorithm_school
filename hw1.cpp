#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


    int num=0;


        struct Node{
        int index;
        Node *left;
        Node *right;
        Node(){
            index=-1;
            left=NULL;
            right=NULL;
            num=0;
        }
        Node(int i){
            this->index = i;
            left=NULL;
            right=NULL;
        }
    };


int Getindex(Node *n){
    return n->index;
}
void SetData(Node *n, int index){
    n->index = index;
}
Node *Getleftsubtree(Node *n){
    return n->left;
}
Node *Getrightsubtree(Node *n){
    return n->right;
}
void Makeleftsubtree(Node *main, Node *lsub){
    if(main->left!=NULL){
        delete main->left;
        }
    main->left = lsub;
}
void Makerightsubtree(Node *main, Node *rsub){
if(main->right!=NULL){
        delete main->right;
        }
    main->right = rsub;
}
void TreeInit(Node **root){ 
    *root = NULL;
}


Node *searchdata;

void preSearch(Node *n,int data){
if(n!=NULL){//if문을 들여쓰기 없이 평행하게 쓰면 첫 if에서 걸려도 다음 if에 또!! 걸림 
    if(n->index==data){
    	 searchdata = n;
    	 return;
    }
     if(searchdata==NULL && n->left!=NULL){ //else if 에서 if로 바꾸니 된다...why? //because, else if 이면 한경우 해당하면 다른건 못들어감 
    	preSearch(n->left,data);
	}
	if(searchdata==NULL && n->right!=NULL){
    	preSearch(n->right,data);
	}
}
	return;
}

void Insert(Node **root, int index,int left,int right){
	searchdata = NULL;

    Node *newnode = new Node(index);
    if(left!= -1) newnode->left = new Node(left);
    if(right!= -1) newnode->right = new Node(right);

    if(index==1){
        *root = newnode;
    }
    else{ //search place to insert
      preSearch(*root,index); 
      if(left!= -1) Makeleftsubtree(searchdata,newnode->left);//instead of changing K with newnode, just add newnode's children
      if(right!= -1) Makerightsubtree(searchdata,newnode->right);
    }
}
int count;
void Setcount(){
    count=0; //count is global
}
void traverse(Node *n){
if(n){
    traverse(n->left);
    count++;
    traverse(n->right);
    }
return; //necessary?
}

int HowmanyR(Node *node){
	if(node!=NULL){
        Setcount();
        traverse(node->left);
        int l = count;
        Setcount();
        traverse(node->right);
        int r = count;
        if(l<r) num++; 

        HowmanyR(node->left);
        HowmanyR(node->right);
}
}




void InorderTraverse(Node *bt){
    if(bt){
        InorderTraverse(bt->left);
       	cout<<bt->index<<",";
        InorderTraverse(bt->right);
    }
}


int main(){
	
	ifstream fin;
	fin.open("input.txt");
	if(fin.fail()){
		cout<<"This program cannot open input file.";
		return 0;
	}
	
	int numofTree;
	fin>>numofTree;
	int *arr = new int[numofTree]; 
	for(int i=0; i<numofTree; i++){
		Node *ROOT = new Node();
		int numofData;
		fin>>numofData;
		for(int j=0;j<numofData;j++){
			int index, l, r;
			fin>>index>>l>>r;
			Insert(&ROOT,index,l,r);
		} 
		HowmanyR(ROOT);
		arr[i]= num;
		
		delete ROOT;
	}

	for(int i=0; i<numofTree;i++){
		cout<<arr[i]<<endl;
	}

}

