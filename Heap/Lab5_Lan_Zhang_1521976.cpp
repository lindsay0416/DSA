#include <iostream>
using namespace std;

// Defination of max heap is the root is the largest node in the heap, and each parent node is larger than its left child and right child
// Heap can be think as an array, for example, if the index of heap is "i", the left child should be heap[2i + 1], right child: heap[2i + 2] parent: heap[i]
// Create the left and right pointer in "typedef struct Node", 
// HBThead, head of the binary tree
// Find the maximum value in an array as the root
// Create the bnary heap
//HBT

typedef struct Node
{
    int data;      //data of the node
    Node *left;    //left child
    Node *right;   //right child
    Node *sibling; //right sibling
    bool isRoot;   //check wether it is a root node
} node;

typedef struct HBThead
{
    int count;  //count of all the nodes
    node *root; //root node
} HBT;

//start from tree root, compare with each sub node, determine witch position will the node to be placed
void compare_to_add(node *parent, node *pNew)
{
    if (parent->left == NULL)
    {
        parent->left = pNew;
        printf("parent: %d; ", parent->data);
        printf("left child added: %d\n", pNew->data);
        return;
    }
    else if (parent->right == NULL)
    {
        parent->right = pNew;
        parent->left->sibling = pNew;
        printf("parent: %d; ", parent->data);
        printf("right child added: %d\n", pNew->data);
        return;
    }
    else if (!parent->isRoot)
    {
        if (parent->sibling->left == NULL)
        {
            parent->sibling->left = pNew;
            printf("parent: %d; ", parent->sibling->data);
            printf("left child added: %d\n", parent->sibling->left->data);
            return;
        }
        if (parent->sibling->right == NULL)
        {
            parent->sibling->right = pNew;
            printf("parent: %d; ", parent->sibling->data);
            printf("right child added: %d\n", parent->sibling->right->data);
            return;
        }
    }
    compare_to_add(parent->left, pNew);
}

// add node to create a balanced binary tree
void add_node(HBT *tree, int data)
{
    node *pNew = new node;
    pNew->left = NULL;
    pNew->right = NULL;
    node *sibling = new node;
    sibling->left = NULL;
    pNew->right = NULL;
    pNew->sibling = sibling;
    pNew->data = data;
    if (tree->count == 0)
    {
        pNew->isRoot = true;
        tree->root = pNew;
    }
    else
    {
        compare_to_add(tree->root, pNew);
    }
    tree->count++;
}

// find the maximum value in the array
void max_heap(int *a, int k, int n)
{
    int j, t;
    t = a[k];
    j = 2 * k;
    while (j <= n)
    {
        if (j < n && a[j + 1] > a[j])
            j = j + 1;
        if (t > a[j])
            break;
        else if (t <= a[j])
        {
            a[j / 2] = a[j];
            j = 2 * j;
        }
    }
    a[j / 2] = t;
    return;
}
// 
HBT *create_binary_heap(int *heap, int n)
{
    int k;
    for (k = n / 2; k >= 1; k--)
    {
        max_heap(heap, k, n);
    }
    HBT *t = new HBT;
    t->root = NULL;
    t->count = 0;
    for (int index = 1; index <= n; index++)
    {
        // cout << heap[index] << endl;
        add_node(t, heap[index]);
    }
    return t;
}

int main()
{
    int n = 8;
    int a[30];
    a[1] = 3;
    a[2] = 1;
    a[3] = 6;
    a[4] = 5;
    a[5] = 2;
    a[6] = 4;
    a[7] = 7;
    a[8] = 8;

    HBT *tree = create_binary_heap(a, n);

    printf("count: %d\n", tree->count);
    cout << tree->root->data << endl;
    cout << tree->root->left->data << endl;
    cout << tree->root->right->data << endl;
    cout << tree->root->left->left->data << endl;
    cout << tree->root->left->right->data << endl;
    cout << tree->root->right->left->data << endl;
    cout << tree->root->right->right->data << endl;
    cout << tree->root->left->left->left->data << endl;
}
