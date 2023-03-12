// circular linked list
// 'beginning' and 'ending' are with respect to order of appearance when writing from left to right

#include<stdio.h>
#include<stdlib.h>

struct node{
    float data;
    struct node *next;
};

void insert_beg(struct node **ptrlastnodeptr, float new_value);
void insert_end(struct node **ptrlastnodeptr, float new_value);  // useful when number of nodes in linked list unknown but want to add a node at the last
int insert_afterpos(struct node **ptrlastnodeptr, int pos, float new_value);   // pos starts from 1
int delete_beg(struct node **ptrlastnodeptr, float *del_value);
int delete_end(struct node **ptrlastnodeptr, float *del_value);
int delete_atpos(struct node **ptrlastnodeptr, int pos, float *del_value);

int find_size(struct node *lastnodeptr);
//int search(struct node *lastnodeptr, float elem);        // do after learning search algorithms
//int sort(struct node *lastnodeptr);        // do after learning sort algorithms
int display(struct node *lastnodeptr);

void main(){

    struct node *lastnodeptr;
    lastnodeptr = NULL;

    printf("--------Circular Linked List---------\n");

    float new_elem;
    printf("\nEnter the value of the first node: ");
    scanf("%f", &new_elem);
    insert_beg(&lastnodeptr, new_elem);
    printf("Linked list with given value in first node created successfully.\n");

    printf("\nOperations:\n");
    printf("1. Insert node at the beginning of the linked list\n2. Insert node at the end of the linked list\n3. Insert node after the node at specified position\n");
    printf("4. Delete the node at the beginning of the linked list\n5. Delete the node at the end of the linked list\n6. Delete the node at specified position\n");
    printf("7. Obtain the number of nodes in the linked list.\n8. Display the linked list\n(Enter -1 to exit)\n\n");

    int op;
    for( ; ; ){
        printf("\nEnter the operation to be performed on the linked list: ");
        scanf("%d", &op);
        switch(op){
            case 1:{
                float new_elem;
                printf("Enter the value of the new first node: ");
                scanf("%f", &new_elem);
                insert_beg(&lastnodeptr, new_elem);
                printf("Node with given value inserted at the beginning of the linked list successfully.\n");
                break;
            }

            case 2:{
                float new_elem;
                printf("Enter the value of the new last node: ");
                scanf("%f", &new_elem);
                insert_end(&lastnodeptr, new_elem);
                printf("Node with given value inserted at the end of the linked list successfully.\n");
                break;
            }

            case 3:{
                float new_elem;
                int priornode;
                printf("Enter the value of the new node: ");
                scanf("%f", &new_elem);
                printf("Enter the position after which this node is to be inserted: ");
                scanf("%d", &priornode);
                if(insert_afterpos(&lastnodeptr, priornode, new_elem)==1){
                    printf("Node with given value inserted at position %d successfully.\n", priornode+1);
                }
                else{
                        printf("Invalid position entered. Entered position exceeds the number of nodes in the linked list.\n");
                }
                break;
            }

            case 4:{
                float del_elem;
                if(delete_beg(&lastnodeptr, &del_elem)==1){
                    printf("Node at the beginning of the linked list deleted successfully.\nValue contained in it: %f\n", del_elem);
                }
                else{
                    printf("Linked list already empty\n");
                }
                break;
            }

            case 5:{
                float del_elem;
                if(delete_end(&lastnodeptr, &del_elem)==1){
                printf("Node at the end of the linked list deleted successfully.\nValue contained in it: %f\n", del_elem);
                }
                else{
                    printf("Linked list already empty\n");
                }
                break;
            }

            case 6:{
                float del_elem;
                int pos;
                printf("Enter the position of the node which is to be deleted: ");
                scanf("%d", &pos);
                if(delete_atpos(&lastnodeptr, pos, &del_elem)==1){
                    printf("Node at position %d deleted successfully.\nValue contained in it: %f\n", pos, del_elem);
                }
                else{
                    printf("Entered position out of bounds of linked list.\n");
                }
                break;
            }

            case 7:
                printf("Number of nodes in linked list = %d\n", find_size(lastnodeptr));
                break;

            case 8:
                display(lastnodeptr);
                break;

            case -1:
                printf("Exiting...\n\n");
                exit(0);

            default:
                printf("Invalid operation.");
                break;
        }
    }
}





void insert_beg(struct node **ptrlastnodeptr, float new_value){ // need to include both cases : list initially empty, list initially non-empty
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = new_value;
    if( (*ptrlastnodeptr)==NULL ){ newnode->next = newnode; *ptrlastnodeptr = newnode; } // list initially empty
    else{ newnode->next = (*ptrlastnodeptr)->next; (*ptrlastnodeptr)->next = newnode; }  // list initially non-empty
}

void insert_end(struct node **ptrlastnodeptr, float new_value){
    insert_beg(ptrlastnodeptr, new_value);
    *ptrlastnodeptr = (*ptrlastnodeptr)->next;
                        // note, here second statement refers to ptrlastnodeptr which is modified after insert_beg()
}

int insert_afterpos(struct node **ptrlastnodeptr, int pos, float new_value){
    if(pos==0){ insert_beg(ptrlastnodeptr, new_value); }
    else{
        struct node *p = (*ptrlastnodeptr) -> next;
        for(int i=1; i<=pos-1; i++){
            if(i<pos-1 && p->next==*ptrlastnodeptr){
                return -1;
            }
            p = p->next;
        }
        struct node *newnode = (struct node *)malloc(sizeof(struct node));
        newnode->data = new_value;
        newnode->next = p->next;
        p->next = newnode;
        return 1;
    }
}

int delete_beg(struct node **ptrlastnodeptr, float *del_value){
    if(*ptrlastnodeptr==NULL){ return -1; }
    else{
        *del_value = (*ptrlastnodeptr)->next->data ;
        if( (*ptrlastnodeptr) == (*ptrlastnodeptr)->next ){ free(*ptrlastnodeptr); (*ptrlastnodeptr)=NULL; } // case where only 1 node in linked list
        else{
            struct node *temp = (*ptrlastnodeptr)->next->next;
            free((*ptrlastnodeptr)->next);
            (*ptrlastnodeptr)->next = temp ;
        }
        return 1;
    }
}

int delete_end(struct node **ptrlastnodeptr, float *del_value){
    if(*ptrlastnodeptr==NULL){ return -1; }
    else{
        *del_value = (*ptrlastnodeptr)->data ;
        if( *ptrlastnodeptr == (*ptrlastnodeptr)->next){ free(*ptrlastnodeptr); *ptrlastnodeptr=NULL; } // case where only 1 node in linked list
        else{
            struct node *p = (*ptrlastnodeptr) -> next;
            while(p->next != *ptrlastnodeptr){
                p = p->next;
            }
            // now p points to new last node
            p->next = (*ptrlastnodeptr)->next;
            free(*ptrlastnodeptr);
            *ptrlastnodeptr = p;
        }
        return 1;
    }
}

// ************** need to clean this code to make more compact and efficient *******************
int delete_atpos(struct node **ptrlastnodeptr, int pos, float *del_value){
    if(*ptrlastnodeptr==NULL){ return -1; }
    if(pos<=0){ return -1; }
    if(pos==1){ delete_beg(ptrlastnodeptr, del_value); }
    else{
        int read;
        struct node *p = *ptrlastnodeptr;
        for(read=0; read<pos-1; read++){      // does not execute for pos=1
            p = p->next;
            if(p == *ptrlastnodeptr){ return -1; }
        }
        // now p points to pos-1 node
        if(p->next==*ptrlastnodeptr){ delete_end(ptrlastnodeptr, del_value); }     // deleting last node
        else{
            *del_value = p->next->data ;
            struct node *temp = p->next->next ;
            free(p->next);
            p->next = temp ;
            return 1;
        }
    }
}


int find_size(struct node *lastnodeptr){
    if(lastnodeptr==NULL){ return 0; }               // no node
    else{
        int count=0;
        struct node *p = lastnodeptr;
        do{
            ++count;
            p = p->next;
        }
        while(p!=lastnodeptr);
        return count;
    }
}

int display(struct node *lastnodeptr){
    printf("\n&lastnodeptr = %u   lastnodeptr = %u\n", &lastnodeptr, lastnodeptr);
    printf("Circular Linked List Contents:\n");
    printf("%7s %7s     %10s   %10s   %12s  %7s\n",   "&p", "p", "&(p->data)", "&(p->next)", "p->data", "p->next");
    struct node *p = lastnodeptr;
    if(p==NULL){ printf("NULL"); return -1; }
    else{
        for(;;){
            p = p->next;
            printf("%7u %7u   %11u  %11u   %13f  %7u\n",  &p, p, &(p->data), &(p->next), p->data, p->next);
            if(p==lastnodeptr){ break; }
        }
    }

    printf("\nLinked List Contents:\n");
    //struct node *p = lastnodeptr;
    p = lastnodeptr;
    if(p==NULL){ printf("NULL"); return -1; }
    else{
        int count=1;
        for( ; ; count++){
            p = p->next;
            printf(" -> %7f", p->data);
            if(p==lastnodeptr){
                printf(" -\n");
                printf("|");
                for(int j=0; j<14*count; j++){ printf("_"); }
                printf("__|\n");
                return 1;
            }
        }
    }
}
