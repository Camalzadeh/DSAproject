#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dsaproject.h"
T_student* createstudent() {
    T_student* newStudent = (T_student*)malloc(sizeof(T_student));

    printf("Write the name of the student: ");
    fgets(newStudent->name, 30, stdin);
    newStudent->name[strcspn(newStudent->name, "\n")] = '\0';

    printf("Enter the student's ID: ");
    scanf("%ld", &newStudent->ID);

    printf("Enter the student's grade: ");
    scanf("%f", &newStudent->grade);

    newStudent->next = NULL;

    return newStudent;
}
void displaylist(T_student* first){
    if(first == NULL){
        printf("No students in the list.\n");
        return;
    }
    printf("List of students: \n");
    printf("--------------------------------------------------\n");
    printf("| %-30s | %-10s | %-5s |\n", "Name", "ID", "Grade");
    printf("--------------------------------------------------\n");

    T_student* current = first;
    while (current != NULL) {
        printf("| %-30s | %-10ld | %-5.3f |\n", current->name, current->ID, current->grade);
        current = current->next;
    }

}
T_student* addstudent(T_student* head, char name[], long id, float grade) {
    T_student* newStudent = (T_student*)malloc(sizeof(T_student));
    if (newStudent == NULL) {
        printf("Memory error!\n");
        return head;
    }

    strcpy(newStudent->name, name);
    newStudent->ID = id;
    newStudent->grade = grade;
    newStudent->next = head;

    return newStudent;
}


