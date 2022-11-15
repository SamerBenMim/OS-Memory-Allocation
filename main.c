#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
int pos = 0 ;
struct Node {
    char process ; // name of the process
    int size; // size of the process
    struct Node *next;
    struct Node *prev;

};

void insertStart(struct Node** head, int data, char process){

    // creating memory for newNode
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

    // assigning newNode's next as the current head
    // Assign data & and make newNode's prev as NULL
    newNode->size = data;
    newNode->process = process ;
    newNode->next = *head;
    newNode->prev = NULL;

    // if list already had item(s)
    // We need to make current head previous node as this new node
    if(*head != NULL)
        (*head)->prev = newNode;

    // change head to this newNode
    *head = newNode;

}

void insertLast(struct Node** head, int size, char process ){
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

    newNode->process = process;
    newNode->size = size;
    newNode->next = NULL;

    //need this if there is no node present in linked list at all
    if(*head==NULL){
        *head = newNode;
        newNode->prev = NULL;
        return;
    }

    struct Node* temp = *head;

    // traverse till the last node
    while(temp->next!=NULL)
        temp = temp->next;

    // assign last node's next to this new Node
    temp->next = newNode;
    // assign this new Node's previous to last node(temp)
    newNode->prev = temp;
}

int calcSize(struct Node* node){
    int size=0;

    while(node!=NULL){
        node = node->next;
        size++;
    }
    return size;
}

void insertPosition(int pos, int psize, char process , struct Node** head){
    int size = calcSize(*head);

    //If pos is 0 then should use insertStart method
    //If pos is less than 0 then can't enter at all
    //If pos is greater than size then bufferbound issue
    if(pos<1 || size < pos)
    {
        printf("Can't insert, %d is not a valid position\n",pos);
    }
    else{
        struct Node* temp = *head;
        struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

        newNode->size = psize;
        newNode->process = process;

        newNode->next = NULL;

        // traverse till pos
        while(--pos)
        {
            temp=temp->next;
        }

        // assign prev/next of this new node
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next = newNode;
        newNode->next->prev = newNode;

        // change next of temp nod//

        /*
       --      --
      P   TMP       N
       --      --
          --     --
       TMP   new    N
           --
         * */

        //A==Tmp==B
    }
}

void display(struct Node* node)
{
    struct Node* end;
    printf("\nIn Forward Direction :\n");
    while (node != NULL) {
        printf("%c(%d)  ",node->process ,node->size);
        end = node;
        node = node->next;
    }

}



void mergeFreeSpace(struct Node** head){
    struct Node* node = *head;
    while (node != NULL) {
        if(node->process =='_'){
           struct  Node * tmp = node->next;
           while(tmp&&tmp->process=='_'){
                node->size+= tmp->size;
                struct  Node * delete = tmp;
                tmp= tmp->next;
                delete->prev->next = tmp;
                if(tmp)
                tmp -> prev = delete->prev;
                free(delete);
            }
        }
        node = node->next;
    }

}

void firstFit_InsertProcess(struct Node** head,int size, char process){
    struct Node* node = *head;
    int index =0 ;
    while (node != NULL) {
        index++;
        if(node->process =='_'){ // vide
           if(node->size>=size){
               int remain = node->size - size ;
               node->process = process ;
               node->size = size ;
               if(!node->next)               insertLast(head,remain,  '_' );

               else insertPosition(index,  remain,  '_' , head);
               mergeFreeSpace(head) ;
               return;
           }
        }
        node = node->next;
    }

}
void nextFit_InsertProcess(struct Node** head,int size, char process){
    struct Node* node = *head;
    struct Node* tmp = *head;

    int l = 0 ;
    while (tmp != NULL) {
        l ++ ;
        tmp = tmp->next;
    }
    int index =pos ;
    int i = pos ;
    int longeur =l ;
    while(pos--) node = node->next;
    while (l--) {
        index= (index+1)%longeur; // CIRCULAR LINKED LIST !;
        if(node->process =='_'){ // vide
            if(node->size>=size){
                int remain = node->size - size ;
                node->process = process ;
                node->size = size ;
                if(!node->next) insertLast(head,remain,  '_' );
                else insertPosition(index,  remain,  '_' , head);
                pos= index;
                mergeFreeSpace(head) ;
                return;
            }
        }
        node = node->next;
    }
}


void bestFit_InsertProcess(struct Node** head,int size, char process){
    struct Node* node = *head;
    int index =0 ;
    int bestfit = INT_MAX;
    while (node != NULL) {
        index++;
        if(node->process =='_'){
            if(node->size>=size){
                if(node->size<bestfit){
                    bestfit = index ;
                }
            }
        }
        node = node->next;
    }
    node = *head;
    int tmp = bestfit-1;
    while(tmp--)node = node->next;
    printf("%c",node->process);
    int remain = node->size - size ;
    node->process = process ;
    node->size = size ;
    if(!node->next)insertLast(head,remain,  '_' );

    else insertPosition(bestfit,  remain,  '_' , head);
    mergeFreeSpace(head) ;
    return;

}
void removeProcess(struct Node** head, char process){
    struct Node* node = *head;
    while (node != NULL) {
        if(node->process == process ){
            node->process = '_';
        }
        node = node->next;
    }
    mergeFreeSpace(head) ;
    printf("\n%c is Removed",process);
}


int main()
{
    struct Node* head = NULL;
 // init list
    insertLast(&head,1,'_');
    insertLast(&head,4,'A');
    insertLast(&head,2,'_');
    insertLast(&head,1,'B');
    insertLast(&head,2,'_');
    insertLast(&head,5,'C');
    insertLast(&head,1,'_');
    insertLast(&head,8,'D');
    insertLast(&head,2,'_');
    insertLast(&head,2,'E');
    insertLast(&head,1,'_');
    insertLast(&head,4,'F');
    insertLast(&head,2,'_');
    insertLast(&head,3,'G');
    insertLast(&head,5,'_');
    /////////// FIRST FIT
    printf("************* FIRST FIT ***************** ");
    removeProcess(&head,'A');
    display(head);
    firstFit_InsertProcess(&head,5,'W');
    display(head);
    firstFit_InsertProcess(&head,2,'X');
    display(head);
    removeProcess(&head,'C');
    display(head);
    firstFit_InsertProcess(&head,6,'Y');
    display(head);
    firstFit_InsertProcess(&head,4,'Z');
    display(head);
    /////////// Best FIT
    head = NULL;
    // init list
    insertLast(&head,1,'_');
    insertLast(&head,4,'A');
    insertLast(&head,2,'_');
    insertLast(&head,1,'B');
    insertLast(&head,2,'_');
    insertLast(&head,5,'C');
    insertLast(&head,1,'_');
    insertLast(&head,8,'D');
    insertLast(&head,2,'_');
    insertLast(&head,2,'E');
    insertLast(&head,1,'_');
    insertLast(&head,4,'F');
    insertLast(&head,2,'_');
    insertLast(&head,3,'G');
    insertLast(&head,5,'_');
    printf("\n************* BEST FIT ***************** ");
    removeProcess(&head,'A');
    display(head);
    bestFit_InsertProcess(&head,5,'W');
    display(head);
    bestFit_InsertProcess(&head,2,'X');
    display(head);
    removeProcess(&head,'C');
    display(head);
    bestFit_InsertProcess(&head,6,'Y');
    display(head);
    bestFit_InsertProcess(&head,4,'Z');
    display(head);
    /////////// NEXT FIT
    head = NULL;
    // init list
    insertLast(&head,1,'_');
    insertLast(&head,4,'A');
    insertLast(&head,2,'_');
    insertLast(&head,1,'B');
    insertLast(&head,2,'_');
    insertLast(&head,5,'C');
    insertLast(&head,1,'_');
    insertLast(&head,8,'D');
    insertLast(&head,2,'_');
    insertLast(&head,2,'E');
    insertLast(&head,1,'_');
    insertLast(&head,4,'F');
    insertLast(&head,2,'_');
    insertLast(&head,3,'G');
    insertLast(&head,5,'_');
    printf("\n************* NEXT FIT ***************** ");
    removeProcess(&head,'A');
    display(head);
    nextFit_InsertProcess(&head,5,'W');
    display(head);
    nextFit_InsertProcess(&head,2,'X');
    display(head);
    removeProcess(&head,'C');
    display(head);
    nextFit_InsertProcess(&head,6,'Y');
    display(head);
    nextFit_InsertProcess(&head,4,'Z');
    display(head);

    return 0;
}
