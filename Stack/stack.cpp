#include <iostream>
#include <string>

typedef struct Node {
    long int data;
    Node *Next; //next is a data name
    
    }node;
    
typedef struct{
    long int Count;
    node *Top;  // Top is a data name
    
    }StackHead;
    
StackHead *CreateStack(){
    StackHead*mS = new StackHead;
    mS->Count = 0;
    mS->Top = NULL;
    return mS;
}

//Pop
long int Pop(StackHead *mS){
    long int d = -1;
    if (mS->Count !=0){
        node *pCur;
        pCur = mS->Top;
        d = mS ->Top->data;
        mS->Top = mS->Top->Next;
        mS->Count--;
        delete pCur;
        }
        return d;
    }

//emptyStack 

void EmptyStack(StackHead *mS){
    if(mS->Count == 0){
    printf("True");
    }
    else{
        printf("False");
        while (mS->Count>0)
        {
        Pop(mS);
        }
        
        delete mS;
    }
}

//Push
void Push(StackHead *mS, long int d){
    node *pNew = new node;
    pNew->data =d;
    if  (mS -> Count == 0)
        pNew->Next =NULL;
    else 
        pNew->Next =mS->Top;
    mS->Top = pNew;
    mS->Count++;
    
}




//population function
void populate(StackHead *MS, int n ){
    for(int i = 0; i<n; i++){
        Push(MS, rand()%10000+1);
    }
}

 //Random Populating
void PopulateRandom(StackHead *mS, int k){
    for(int j=0; j<k; j++)
    {
        int RandomNum = rand()%10000;
        Push(mS, RandomNum);
        
    }
}




int main()
{
    StackHead *myStack = new StackHead; 
    myStack =CreateStack();
    
   //Push
    printf("Pushing values to our stack\n"); 
    for(int k = 0; k < 10; k++){
       int rv =rand()%10000+1;
       Push(myStack,rv);
       printf("%d\n",rv);
       }
       
    //Pop
    printf("\nPoping values from our stack\n");
    for(int k = 0; k < 10; k++){
        printf("%d\n",Pop(myStack));
        }	
   
   //Empty
    EmptyStack(myStack);
    
    //RandomPopulate
    int ranV = rand()%10000;
    PopulateRandom(myStack, ranV);
            
    long int D;
    D = Pop(myStack);
    
    system("pause");
    return 0;
}

