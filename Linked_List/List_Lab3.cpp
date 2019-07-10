
    
#include <iostream>
#include <string>

typedef struct Node
{
    int data;
    Node *next;
    //Node *previous;
} node;

typedef struct List
{
    int count;
    node *head;
}list;

list *CreateList(void)
{
    list *lst = new list;
    lst->count = 0;
    lst->head = NULL;
    printf("list address: %p\n", &lst);
    return lst;
}

//Add node
void AddNode(list *lst, int data)
{
    node *pNew = new node;
    pNew->data = data;
    // Is the list empty?
    if (lst->count == 0)
    {
        pNew->next = NULL;
        lst->head = pNew;
        lst->count = 1;
        return;
    }
    if (lst->head->data > pNew->data)
    {
        //is the element to be added at the begining
        //of the list?
        pNew->next = lst->head;
        lst->head = pNew;
        lst->count++;
        return;
    }
    // General case
    node *pPre = lst->head;
    node *pCur = lst->head->next;
    while (pCur != NULL && pCur->data < pNew->data)
    {
        pPre = pCur;
        pCur = pCur->next;
    }
    pNew->next = pCur;
    pPre->next = pNew;
    //Add to the list index count
    lst->count++;
}

void PopulateList(list *lst)
{
    int n = rand() % 10000 + 1;
    for (int i = 0; i < n; i++)
    {
        int p = rand() % 100 + 1;
        AddNode(lst, p);
    }
    printf("Number of Elements Generated: %d\n", n);
}

void PrintList(list *lst)
{
    if (lst == NULL)
    {
        return;
    }
    printf("list size: %d\n", lst->count);
    node *pCur = lst->head;
    while (pCur != NULL)
    {
        printf("%d\n", pCur->data);
        pCur = pCur->next;
    }
}

//Delete Node
void DeleteNode(list *lst, int data)
{
    if (lst->count == 0)
    {
        printf("empty list!\n");
        return;
    }
    node *pPre;
    node *pCur = lst->head;
    while (pCur->data != data)
    {
        if (pCur->next == NULL)
        {
            printf("not found!\n");
            return;
        }
        pPre = pCur;
        pCur = pCur->next;
    }
    pPre->next = pCur->next;
    pCur = NULL;
    delete pCur;
    lst->count--;
    printf("data: %d found and deleted!\n", data);
}

//search Node
node *SearchNode(list *lst, int data)
{
    if (lst->count == 0)
    {
        printf("empty list!\n");
        return NULL;
    }
    node *pLoc = lst->head;
    while (pLoc->data != data)
    {
        if (pLoc->next == NULL)
        {
            printf("not found!\n");
            return NULL;
        }
        pLoc = pLoc->next;
    }
    return pLoc;
}

list *DeleteList(list *lst)
{
    if (lst->count == 0)
    {
        printf("empty list!\n");
        return NULL;
    }
    node *pCur = lst->head;
    node *pTmp;
    while (pCur != NULL)
    {
        pTmp = pCur->next;
        pCur = NULL;
        delete pCur;
        pCur = pTmp;
    }
    lst->head = NULL;
    lst->count = 0;
    delete lst->head;
    lst = NULL;
    delete lst;
    return lst;
}

int main()
{
    list *myList = CreateList();
    // PopulateList(myList);
    AddNode(myList, 3);
    AddNode(myList, 4);
    AddNode(myList, 2);
    AddNode(myList, 1);
    DeleteNode(myList, 4);
    PrintList(myList);
    node *n = SearchNode(myList, 2);
    printf("%d found!\n", n->data);
    list *lst = DeleteList(myList);
    return 0;
}

