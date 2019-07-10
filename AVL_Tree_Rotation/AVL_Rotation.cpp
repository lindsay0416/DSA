#include <iostream>
#include <stdlib.h>

typedef struct Node
{
    int data;      //data of the node
    Node *left;    //left child
    Node *right;   //right child
    // Node *parent; //parent pointer
    // bool isRoot;   //check wether it is a root node
}node;

typedef struct AVLhead
{
    int count;  //count of all the tree nodes
    node *root; //root node
} AVL;

AVLhead *CreateBST() {
	AVLhead *B = new AVLhead;
	B->count = 0;     // set the AVL tree to NULL, create a empty tree
	B->root = NULL;	  // Set the root to NULL
	return B;
}

// Add node function is used to test wheather the rotation function is working or not
//-----------recursive function,the rule of add node, to be the left child or right child---------
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

// starting add node 
void AddNode(AVLhead *B, long int d) 
{
	node *pNew = new node;
	pNew->data = d;
	pNew->left = NULL;
	pNew->right = NULL;
	if (B->count == 0) 
	{
		B->root = pNew;
	}
	else 
	{
		AddNodeR(B->root, pNew);
	}
	B->count++;
}

// print the tree 
void printBST(node *root) 
{
	if (root != NULL) 
	{
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
// ---------------AVL--------------
void populate(AVLhead *B){
	int n = rand() % 10000 + 1;

	for(int i = 0; i < n; i++){
		int m = rand() % 10000 + 1;
		AddNode(B, m);
		printf("\nTree Counter: %d", B->count);
	}
	printf("\nDEBUG: Tree populated with %d new nodes.", n);
}

//check the tree height
int heightAVLTree(node *root)
{
	int height = 0;

	if (root == NULL)
	{
		return height;
	}
	else
	{
		int leftheight = heightAVLTree(root->left);
		int rightheight = heightAVLTree(root->right);
		//Compare returns of left and right, add +1 to account for the current node
		if (leftheight > rightheight)
		{
			height = leftheight + 1;
		}
		else
		{
			height = rightheight + 1;
		}

		return height;
	}
}

// ----------------the first function in assignment2 :: isBalance ----------------
int isBalanced(node *root)
{
	// left is larger return -1
	// right is larger return 1
	// balanced return 0
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		int height = heightAVLTree(root->left) - heightAVLTree(root->right);
		int checkHeight;
		if (height > 1)
		{
			//left subtree is higher than right subtree
			checkHeight = -1;
		}
		else if (height < -1)
		{
			//right subtree is higher than left subtree
			checkHeight = 1;
		}
		else
		{
			//is balanced
			checkHeight = 0;
		}

		if ((isBalanced(root->left) == 0) && (isBalanced(root->right) == 0) && checkHeight == 0)
		{
			
			return 0;
		}

		else if (checkHeight == -1)
		{
			return -1;
		}

		else if (checkHeight == 1)
		{
			return 1;
		}
	}
}
// right rotation 
void rotateRight(AVLhead *H, node *pCur)
{
	// check avoid segmentation
	//AVLHead *H, we can regenerate the BST tree after rotation, only after we get the tree,
	 if (pCur -> right == NULL)
    {
        return;
    }
	else
	{
		node *parent = searchParent(H->root, pCur);
		
		node *target = pCur -> left;

		if (parent != NULL)
		{
			if(parent -> left == pCur)
			{
				parent -> left = target;
			}
			else
			{
				parent -> right = target;
			}
		}
			else
			{
				// rotate node is root node 
				H -> root = target;
			}

		pCur -> left = target->right;
		target -> right =pCur;
	}
}


// left rotation 
// target is the node that be targeted to rotation 
void rotateLeft(AVLhead *H, node *pCur)
{
	// check avoid segmentation
	//AVLHead *H, we can regenerate the BST tree after rotation, only after we get the tree,
	 if (pCur -> left == NULL)
    {
        return;
    }
	else
	{
		node *parent = searchParent(H->root, pCur);
		
		node *target = pCur -> right;

		if (parent != NULL)
		{
			if(parent -> left == pCur)
			{
				parent -> left = target;
			}
			else
			{
				parent -> right = target;
			}
		}
			else
			{
				// rotate node is root node 
				H -> root = target;
			}

		pCur -> right = target->left;
		target -> left =pCur;
	}
}


// double rotation functions 
// double rotation right --- left
void rotate_Right_Left(AVLhead *H, node *g)
{
	// rotate right
	node *p = g -> right;
	node *v = p -> left;
	node *w = v -> right;
	
	// swap
	v -> right = p;
	p -> left = w;

	//realign parent
	g -> right = v;

	// rotate left with g
	node *top = searchParent(H->root, g);
	w = v -> left;

	//swap
	g -> right = w;
	v -> left = g;

	//realign parent node
	if (top == NULL)
	{
		//g == root
		H->root = v;
	}

	else
	{
		//reconnect the tree node
		if (top->left == g)
		{
			top->left = v;
		}
		else
		{
			top->right = v;
		}
	}
    
}

// double rotation left --- right
void rotate_Left_Right(AVLhead *H, node *g)
{
	// rotate right
	node *p = g -> left;
	node *v = p -> right;
	node *w = v -> left;
	
	// swap
	v -> left = p;
	p -> right = w;

	//realign parent
	g -> left = v;

	// rotate left with g
	node *top = searchParent(H->root, g);
	w = v -> right;

	//swap
	g -> left = w;
	v -> right = g;

	//realign parent node
	if (top == NULL)
	{
		//g == root
		H->root = v;
	}

	else
	{
		//reconnect the tree node
		if (top->left == g)
		{
			top->left = v;
		}
		else
		{
			top->right = v;
		}
	}
    
}


int main()
{
	// AVLhead *myBST;
	// myBST = CreateBST();

	// // for (int k = 0; k < 10; k++) {
	// // 	AddNode(myBST, rand() % 1000);
	// // }
	
    // AddNode(myBST, 7);
    // AddNode(myBST, 6);
    // AddNode(myBST, 9);

    // rotateLeft(myBST -> root -> right);
	// // populate
	// printBST(myBST -> root);



	system("PAUSE");

    return 0; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// can use visual studio and vscode to run the code 
// visual studio need to install C++, in windows operation system Ctrl + R, in macOS command + R
