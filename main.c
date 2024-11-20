#include "dsaproject.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    T_student* students = NULL;
    char name[30];
    long ID;
    float grade;
    int answer;
    do {
        printf("\n\tEXAM RESULTS\n");
        printf("<1> Enter students\n");
        printf("<2> Add a student\n");
        printf("<3> Display student list\n");
        printf("<4> Search for a student\n");
        printf("<5> Sort the list of students by grade\n");
        printf("<6> Split the list into two sub-lists according to grades(<65 and >=65)\n");
        printf("<7> Calculate the exam average\n");
        printf("<8> Free lists\n");
        printf("<9> Exit\n");
        printf("Which operation you want to execute? -> ");
        scanf("%d", &answer);
        switch(answer){
            case 1:
                students = createstudent();
                break;
            case 2:
                printf("Enter student name: ");
                scanf("%s",name);
                printf("Enter the student's ID: ");
                scanf("%ld",&ID);
                printf("Enter the student's grade: ");
                scanf("%f", &grade);
                students = addstudent(students, name, ID, grade);
                break;
            case 3:
                displaylist(students);
                break;
            case 4:
                printf("Enter the student's ID to search:  ");
                scanf("%ld", &ID);
                int index=findstudent(students, ID);
                if(index == -1) printf("Student not found!\n");
                else printf("Student found at index: %d\n", index);
                break;
            case 5:
                sortlist(&students);
                displaylist(students);
                break;
            case 6:
                T_student* good_grades = NULL;
                T_student* bad_grades = NULL;
                splitlist(students,&good_grades, &bad_grades);
                sortlist(&good_grades);
                sortlist(&bad_grades);
                printf("\n\tStudents with good grades\n");
                displaylist(good_grades);
                printf("\n\tStudents with bad grades\n");
                displaylist(bad_grades);
                T_student *temp = mergelists(good_grades, bad_grades);
                displaylist(temp);
                freelist(&temp);
                free(bad_grades);
                free(good_grades);
                temp=NULL;
                good_grades = NULL;
                bad_grades = NULL;
                break;
            case 7:
                float average = averageexam(students);
                printf("Average: %.2f\n",average);
                break;
            case 8:
                freelist(&students);
                students= NULL;
                break;
            case 9:
                printf("\nSee you again!\n");
                break;
            default:
                printf("Please try again with a valid choice!\n");
                break;
        }
    }while(true);
    return 0;
}