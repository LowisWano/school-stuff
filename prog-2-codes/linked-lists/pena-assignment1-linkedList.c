#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    char val;
    struct node *link;
}*LIST;

void insertLast(LIST *L, char elem);
void displayElements(LIST L);
void deleteAllElements(LIST *L, char elem);

int main(void){
    char elem;
    LIST head=NULL;
    insertLast(&head, 'A');
    insertLast(&head, 'B');
    insertLast(&head, 'B');
    insertLast(&head, 'A');
    insertLast(&head, 'A');
    insertLast(&head, 'B');
    insertLast(&head, 'A');
    
    deleteAllElements(&head, 'B');

    displayElements(head);
}

void displayElements(LIST L){
    LIST trav;
    for(trav=L;trav!=NULL;trav=trav->link){
        printf("%c", trav->val);
    }
}

// insert element at the last position
void insertLast(LIST *L, char elem){
    LIST *trav;
    LIST new = malloc(sizeof(struct node));
    new->val = elem;
    new->link = NULL;
    if(*L == NULL){
        *L = new;
    }else{ // I still can't visualize the process instinctly so remind future me to draw and visualize this shit
       for(trav=L;*trav!=NULL;trav=&(*trav)->link){}
        *trav = new; 
    }
}

void deleteAllElements(LIST *L, char elem){
    LIST *trav;
    LIST temp=NULL;
    for(trav=L;*trav!=NULL;){
        if((*trav)->val == elem){
            temp = *trav;
            *trav=(*trav)->link; //change the current node's link to point to the next node
            free(temp);
            temp = NULL;
        }else{
            trav=&(*trav)->link; // set trav to point to the next node
        }
    }
    free(temp);
}



