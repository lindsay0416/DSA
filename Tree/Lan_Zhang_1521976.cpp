// ConsoleApplication1.cpp : Defines the entry point for the console application.


#include <iostream>
#include <stdlib.h>

typedef struct Node {
	long int data;
	Node *left;
	Node *right;
}node;

typedef struct BSThead{
	long int count;
	node *root;
};

BSThead *CreateBST() {
	BSThead *B = new BSThead;
	B->count = 0;
	B->root = NULL;
	return B;
}

void AddNodeR(node *root, node *pNew) {
	if (pNew->data < root->data) {
		if (root->left == NULL) {
			root->left = pNew;
		}
		else {
			AddNodeR(root->left, pNew);
		}
	}
	else {
		if (root->right == NULL) {
			root->right = pNew;
		}
		else {
			AddNodeR(root->right, pNew);
		}
	}
}

void AddNode(BSThead *B, long int d) {
	node *pNew = new node;
	pNew->data = d;
	pNew->left = NULL;
	pNew->right = NULL;
	if (B->count == 0) {
		B->root = pNew;
	}
	else {
		AddNodeR(B->root, pNew);
	}
	B->count++;
}

void printBST(node *root) {
	if (root != NULL) {
		printBST(root->left);
		printf("%d \n", root->data);
		printBST(root->right);
	}
}

node *searchParent(node *root, node *child)
{
	//rv: return value 
	node *rv = NULL;
	if(root !=NULL)
	{
		if(root->left == child || root->right == child)
		{
			rv = root;
		}
		else{
			rv = searchParent(root->left, child);
			if(rv == NULL)
			{
				rv = searchParent(root->right, child);
			}
		}
	}
	return rv;
}


node *findLargest(node *root)
{
	node *rv =NULL;
	if(root !=NULL)
	{
		if (root->right == NULL) 
		{
			rv = root;
		}
		else {
			rv = findLargest(root->right);
		}
	}
	return rv;
}

node *findSmallest(node *root) {
	node *rv = NULL;
	if(root !=NULL){
		if(root->left == NULL){
		rv = root;
		}
		else{
			rv = findSmallest(root->left);
		}
	}
	return rv;
}


node *searchBST(node *root, long int data) {
	node *rv;
	if (root != NULL) {
		if (data == root->data) {
			rv = root;
		}
		else {
			if (data > root->data) {
				rv = searchBST(root->right, data);
			}
			else {
				rv = searchBST(root->left, data);
			}
		}
	}
	else {
		rv = NULL;
	}
	return rv;
}

int deleteNode(BSThead *B, int data){
    //function will return 1 if value was found and deleted
    //return 0 if value is not found
    node *pCur = searchBST(B->root,data), *pLar = NULL, *pDel=NULL;  
	int rv = 0; // rv: returnning value
	
	if(pCur != NULL){
        pLar = findLargest(pCur->left);
        int value = 0;     
        if(pLar !=NULL){
            if(pLar->left !=NULL){       //take out the largest value to be the pCur(root), then Move the left tree up 
                value = pLar->data;     // value of the largest, the value is saved,
                pDel = pLar->left;
                pLar ->data = pLar ->left->data;   
                pLar->left = pDel->left;   
                pLar->right = pDel->right;
                delete pDel;
            }
            else{
                // no child for pLar
                value = pLar->data;
                delete pLar;
            }
            pCur->data = value;
        }
        else
        {
            // there is no left subtree
			if(pCur->right !=NULL){
				pDel = pCur->right;
				value = pDel->data;    // 1. save the deleted data as value first
				pCur->left = pDel->left;
				pCur->right = pDel->right;
				delete pDel;
				pCur->data = value;   // 2. value = pDel->data, deleted data become the pCur->data
				}
				else{
					node *pPar = searchParent(B->root, pCur);
					if(pPar !=NULL){
						if(pPar->left == pCur){
							pPar->left = NULL;
							delete pCur;
						}
						else{
							pPar->right = NULL;
							delete pCur;
						}
					}				
					
				}
			}
			rv =1;
        	// decrease the node counter;
       	 	B->count--;
   	 }
    	return rv;
	}

//empty tree function 
void deleteTree(node *root){
	if(root == NULL) return;
	deleteTree(root->left);
	deleteTree(root->right);

	printf("\n Deleting node: %d\n", root->data);
	free(root);
}

// ** Pointer to pointer 
void deleteTree2(node** root_ref){
	deleteTree(*root_ref);
	*root_ref = NULL;
}

// Tree height
int max = 0;
int HeightTree(node *root, int level){
	if(root)
	{
		if(root->left)
		{
			HeightTree(root->left, level+1);
		}
		if(root->right)
		{
			HeightTree(root->right,level+1);
		}
	}
	if(level > max)
		max = level;
	return level;
}

void populate(BSThead *B){
	int n = rand() % 10000 + 1;

	for(int i = 0; i < n; i++){
		int m = rand() % 10000 + 1;
		AddNode(B, m);
	}
}


int main()
{
	BSThead *myBST;
	myBST = CreateBST();

	for (int k = 0; k < 10; k++) {
		AddNode(myBST, rand() % 1000);
	}
	
	// populate
	printBST(myBST->root);

	//delete Tree 
	// deleteTree2(&myBST->root);
	
	if(deleteNode(myBST, 73));
		printf("Value deleted\n");
	printBST(myBST->root);

	// tree height
	HeightTree(myBST->root,1);
	printf("Tree height is %d\n", max);


	// system("pause");
	return 0;
}