#include<stdio.h>
#include<stdlib.h>

struct node{
    struct node *prev;
    float data;
    struct node *next;
};

void insert_beg(struct node **ptrnode1ptr, float new_value);
void insert_end(struct node **ptrnode1ptr, float new_value);  // useful when number of nodes in linked list unknown but want to add a node at the last
int insert_afterpos(struct node **ptrnode1ptr, int pos, float new_value);   // pos starts from 1
int delete_beg(struct node **ptrnode1ptr, float *del_value);
int delete_end(struct node **ptrnode1ptr, float *del_value);
int delete_atpos(struct node **ptrnode1ptr, int pos, float *del_value);

int find_size(struct node *node1ptr);
//int search(struct node *node1ptr, float elem);        // do after learning search algorithms
//int sort(struct node *node1ptr);        // do after learning sort algorithms
int display(struct node *node1ptr);

void main(){

    struct node *node1ptr;
    node1ptr = NULL;

    printf("--------Linear Doubly-Linked List---------\n");

    float new_elem;
    printf("\nEnter the value of the first node: ");
    scanf("%f", &new_elem);
    insert_beg(&node1ptr, new_elem);
    printf("Doubly-Linked list with given value in first node created successfully.\n");

    printf("\nOperations:\n");
    printf("1. Insert node at the beginning of the linked list\n2. Insert node at the end of the linked list\n3. Insert node after the node at specified position\n");
    printf("4. Delete the node at the beginning of the linked list\n5. Delete the node at the end of the linked list\n6. Delete the node at specified position\n");
    printf("7. Obtain the number of nodes in the linked list.\n8. Display the doubly-linked list\n(Enter -1 to exit)\n\n");

    int op;
    for( ; ; ){
        printf("\nEnter the operation to be performed on the doubly-linked list: ");
        scanf("%d", &op);
        switch(op){
            case 1:{
                float new_elem;
                printf("Enter the value of the new first node: ");
                scanf("%f", &new_elem);
                insert_beg(&node1ptr, new_elem);
                printf("Node with given value inserted at the beginning of the linked list successfully.\n");
                break;
            }

            case 2:{
                float new_elem;
                printf("Enter the value of the new last node: ");
                scanf("%f", &new_elem);
                insert_end(&node1ptr, new_elem);
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
                if(insert_afterpos(&node1ptr, priornode, new_elem)==1){
                    printf("Node with given value inserted at position %d successfully.\n", priornode+1);
                }
                else{
                        printf("Invalid position entered. Entered position exceeds the number of nodes in the linked list.\n");
                }
                break;
            }

            case 4:{
                float del_elem;
                if(delete_beg(&node1ptr, &del_elem)==1){
                    printf("Node at the beginning of the linked list deleted successfully.\nValue contained in it: %f\n", del_elem);
                }
                else{
                    printf("Linked list already empty\n");
                }
                break;
            }

            case 5:{
                float del_elem;
                if(delete_end(&node1ptr, &del_elem)==1){
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
                if(delete_atpos(&node1ptr, pos, &del_elem)==1){
                    printf("Node at position %d deleted successfully.\nValue contained in it: %f\n", pos, del_elem);
                }
                else{
                    printf("Invalid position entered. Entered position exceeds the number of nodes in the linked list.\n");
                }
                break;
            }

            case 7:
                printf("Number of nodes in linked list = %d\n", find_size(node1ptr));
                break;

            case 8:
                display(node1ptr);
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


void insert_beg(struct node **ptrnode1ptr, float new_value){
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->prev = NULL;
    newnode->data = new_value;
    newnode->next = *ptrnode1ptr;
    if( (*ptrnode1ptr) != NULL ){(*ptrnode1ptr)->prev = newnode; }
    *ptrnode1ptr = newnode;
}

void insert_end(struct node **ptrnode1ptr, float new_value){
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = new_value;
    newnode->next = NULL;

    if(*ptrnode1ptr==NULL){ insert_beg(ptrnode1ptr, new_value); }
    else{
        struct node *p = *ptrnode1ptr;
        while(p->next!=NULL){
            p = p->next;
        }
        newnode->prev = p;
        p->next = newnode;
    }
}

int insert_afterpos(struct node **ptrnode1ptr, int pos, float new_value){
    if(pos==0){ insert_beg(ptrnode1ptr, new_value); return 1; }
    else{
        struct node *p = *ptrnode1ptr;
        for(int i=1; i<=pos-1; i++){
            if(i<pos-1 && p->next==NULL){ return -1; }
            p = p->next;
        }
        struct node *newnode = (struct node *)malloc(sizeof(struct node));
        newnode->prev = p;
        newnode->data = new_value;
        newnode->next = p->next;
        p->next = newnode;
        return 1;
    }
}

int delete_beg(struct node **ptrnode1ptr, float *del_value){
    if(*ptrnode1ptr==NULL){ return -1 ; }
    else{
        *del_value = (*ptrnode1ptr)->data ;
        struct node *newfirstnode = (*ptrnode1ptr)->next ;
        free(*ptrnode1ptr) ;
        *ptrnode1ptr = newfirstnode ;
        (*ptrnode1ptr)->prev = NULL ;
        return 1;
    }
}

int delete_end(struct node **ptrnode1ptr, float *del_value){
    struct node *p = *ptrnode1ptr;
    if(*ptrnode1ptr!=NULL && (*ptrnode1ptr)->next!=NULL){ // i.e. linked list not having 0 or 1 node only
        while(p->next->next!=NULL){                             // relying on complicated conditions because assuming find_size() is not available
            p = p->next;
        }
        *del_value = p->next->data;
        free(p->next);
        p->next = NULL;
        return 1;
    }
    else{
        delete_beg(ptrnode1ptr, del_value);
    }
}

// ****** incorrect code, does not account for all cases ********
int delete_atpos(struct node **ptrnode1ptr, int pos, float *del_value){
    struct node *p = *ptrnode1ptr;
    for(int i=1; i<=pos-2; i++){
        if(p->next==NULL){ return -1; }
        else{ p = p->next; }
    }
    // now p points to pos-1 node.  to delete: pos node
    if(p->next==NULL){ return -1; }
    else{
        *del_value = p->next->data;
        struct node *q = p->next->next;
        free(p->next);
        p->next = q;
        if(p->next!=NULL){ p->next->prev = p ; } // if condition accommodates del_end operation. can instead also call del_end separately.
        return 1;
    }
}


int find_size(struct node *node1ptr){
    if(node1ptr==NULL){ return 0; }               // at least 1 node present in linked list (if not so, p->next not defined
    else{
        int count=1;
        struct node *p = node1ptr;
        while(p->next!=NULL){
            ++count;
            p = p->next;
        }
        return count;
    }
}

int display(struct node *node1ptr){
    printf("\n&node1ptr = %u     node1ptr = %u\n", &node1ptr, node1ptr);
    printf("Doubly-Linked List Contents:\n");
    printf("%7s %7s    %7s   %7s   %7s  %8s  %8s  %8s\n", "&p", "p",  "&(p->prev)", "&(p->data)", "&(p->next)",  "p->prev", "p->data", "p->next");
    struct node *p = node1ptr;
    if(p==NULL){ printf("NULL"); return -1; }
    else{
        for(;;){
            printf("%7u %7u   %10u  %10u  %10u  %10u %12f %10u\n", &p, p,  &(p->prev), &(p->data), &(p->next),  p->prev, p->data, p->next);
            if(p->next==NULL){ printf("\n\n"); break; }
            else{ p = p->next; }
        }
    }

    printf("Doubly-Linked List Contents:\n");
    //struct node *p = node1ptr;
    p = node1ptr;
    if(p==NULL){ printf("NULL"); return -1; }
    else{
        for(;;){
            if(p->next==NULL){
                printf("%f\n\n", p->data);
                return 1;
            }
            else{
                printf("%f <-> ", p->data);
            }
            p = p->next;
        }
    }
}
