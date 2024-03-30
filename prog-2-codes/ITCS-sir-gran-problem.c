#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef char String[20];

typedef struct{
    int month, day, year;
}Date;

typedef struct name{
    String fname, mname, lname;
}Name;

typedef struct stud{
    String id;
    Name stud_name;
    int age;
    bool gender;
    Date birth_date;
}StudInfo;

typedef struct{
    StudInfo *class;
    int ctr;
    int max;
}ClassList, *ClassListPtr;

int getChoice(int choice);
int chooseClass();
void addStudent(ClassListPtr chosenClass);
StudInfo getStudDetails();
void displayStudents(ClassListPtr class);
void displayStudentsByYear(ClassListPtr C);
void printStudDetails(StudInfo s);

int main(void){
    ClassListPtr IT;
    ClassList CS;
    ClassListPtr chosenClass;
    int classChoice, back;

    // initialize all the structures
    CS.ctr = 0;
    CS.max = 2;
    CS.class = malloc(sizeof(StudInfo)*CS.max);
    
    
    IT = malloc(sizeof(ClassList));
    IT->ctr = 0;
    IT->max = 10;
    IT->class = malloc(sizeof(StudInfo)*IT->max);

    while(1){
        back=1;
        classChoice = chooseClass();
        switch(classChoice){
            case 1:
                chosenClass = &CS;
                break;
            case 2:
                chosenClass = IT;
                break;
            case 3:
                printf("Exiting...");
                exit(0);
        }

        while(back){
            switch(getChoice(classChoice)){
                case 1:
                    addStudent(chosenClass);
                    break;
                case 2:
                    displayStudents(chosenClass);
                    break;
                case 3:
                    displayStudentsByYear(chosenClass);
                    break;
                case 4:
                    printf("abc");
                case 5:
                    back = 0;
                    break;
                    
            }
            printf("\n");
        }
        printf("\n");
    }

    
    return 0;
}

void displayStudentsByYear(ClassListPtr C) {
    int i, year;
    printf("Enter a year: "); 
    scanf("%d", &year);
    for (i = 0; i < C->ctr; i++) {
        if (C->class[i].birth_date.year == year) {
            printStudDetails(C->class[i]);
        }
    }
}

void displayStudents(ClassListPtr C){
    int i;
    if(C->ctr > 0){
        for(i=0;i<C->ctr;i++){
            printStudDetails(C->class[i]);
        }
    }else{
        printf("No students are found.\n");
    }
    
}

void printStudDetails(StudInfo s){
	printf("%s\n", s.id);
    printf("%s\n", s.stud_name.fname);
    printf("%s\n", (s.gender == 1)?"Male":"Female");
    printf("\n");
}

StudInfo getStudDetails(){
    StudInfo stud;
    int tempgender;
    
    printf("Enter ID: ");
    scanf("%s", &stud.id);
    getchar();
    
    printf("Enter first name: ");
    scanf("%[^\n]s", &stud.stud_name.fname);
    getchar();
    
    // printf("Enter middle name: ");
    // scanf("%s", &stud.stud_name.mname);
    // getchar();
    
    // printf("Enter last name: ");
    // scanf("%s", &stud.stud_name.lname);
    // getchar();
    
    // printf("Enter age: ");
    // scanf("%d", &stud.age);

    printf("Enter gender(1 for male, 0 for female): ");
    scanf("%d", &tempgender);
    stud.gender = tempgender;

    // printf("Enter birth month: ");
    // scanf("%d", &stud.birth_date.month);

    // printf("Enter birth day: ");
    // scanf("%d", &stud.birth_date.day);

    printf("Enter birth year: ");
    scanf("%d", &stud.birth_date.year);
    return stud;
}

void addStudent(ClassListPtr chosenClass){
    if(chosenClass->ctr < chosenClass->max ){
        chosenClass->class[chosenClass->ctr++] = getStudDetails();
    }else{
        printf("Maximum students is 10.\n");
    }
    
}

int getChoice(int classChoice){
    int choice;
    printf("Hello, welcome to the %s Classlist! What would you like to do?\n", (classChoice == 1)? "CS": "IT");
        
    printf("1. Add a student\n");
    printf("2. Display students normally\n");
    printf("3. Display students born on a specified birth year.\n");
    printf("4. Display all students alphabetically\n");
    printf("5. Go back\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    return choice;
}

int chooseClass(){
    int classChoice;
    printf("Hello teacher, Welcome to the DCISM Student Database! What would you like to do?\n");
    printf("1. Navigate to CS Class\n");
    printf("2. Navigate to IT Class\n");
    printf("3. Exit\n");
    printf("Enter class: ");
    scanf("%d", &classChoice);
    printf("\n");
    return classChoice;
}

