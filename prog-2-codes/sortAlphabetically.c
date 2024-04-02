#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char String[20];

typedef struct {
    int month, day, year;
} Date;

typedef struct name {
    String fname, mname, lname;
} Name;

typedef struct stud {
    String id;
    Name stud_name;
} StudInfo;

typedef struct {
    StudInfo class[10];
    int ctr;
} ClassList, *ClassListPtr;
void displayList(ClassList c);
void sortAlphabetically(ClassListPtr c);

int main(void) {
    ClassList c;
    c.ctr = 5; // Set the count of students

    // Initialize each student's information
    strcpy(c.class[0].id, "23100371");
    strcpy(c.class[0].stud_name.fname, "Luis");
    strcpy(c.class[0].stud_name.mname, "E");
    strcpy(c.class[0].stud_name.lname, "Ouano");

    strcpy(c.class[1].id, "23100371");
    strcpy(c.class[1].stud_name.fname, "Paul");
    strcpy(c.class[1].stud_name.mname, "E");
    strcpy(c.class[1].stud_name.lname, "Ouano");

    strcpy(c.class[2].id, "23100371");
    strcpy(c.class[2].stud_name.fname, "Alec");
    strcpy(c.class[2].stud_name.mname, "E");
    strcpy(c.class[2].stud_name.lname, "Ouano");


    strcpy(c.class[3].id, "23100371");
    strcpy(c.class[3].stud_name.fname, "Justin");
    strcpy(c.class[3].stud_name.mname, "E");
    strcpy(c.class[3].stud_name.lname, "Ouano");

    strcpy(c.class[4].id, "23100371");
    strcpy(c.class[4].stud_name.fname, "Francis");
    strcpy(c.class[4].stud_name.mname, "E");
    strcpy(c.class[4].stud_name.lname, "Ouano");

    printf("Before sorting:\n");
    displayList(c);
    
    printf("\nAfter sorting:\n");
    sortAlphabetically(&c);
    displayList(c);
    
    return 0;
}

void sortAlphabetically(ClassListPtr c){
    int i, j, min;
    StudInfo temp;
    for(i=0;i<c->ctr-1;i++){
        min = i;
        for(j=i+1;j<c->ctr;j++){
            if(strcmp(c->class[j].stud_name.fname, c->class[min].stud_name.fname) < 0){
                // if first non matching char of str1 is greater = > 0
                // if first non matching char of str1 is lesser = < 0
                // if equal = 0
                printf("%d ", strcmp(c->class[j].stud_name.fname, c->class[min].stud_name.fname));
                min = j;
            }
        }
        printf("\n");
        temp = c->class[min];
        c->class[min] = c->class[i];
        c->class[i] = temp;
    }
}

void displayList(ClassList c) {
    int i;
    for (i = 0; i < c.ctr; i++) {
        printf("%s ", c.class[i].stud_name.fname);
    }
}

