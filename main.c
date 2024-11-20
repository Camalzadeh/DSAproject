#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dsaproject.h" // Include your header file

int main() {
    T_student* sentinel = newStudent("",0,0);
    if (!sentinel) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    sentinel->next = NULL;


    long id;
    float grade;
    T_student *highLevel = NULL, *lowLevel = NULL;

    sentinel=addstudent(sentinel,"salam", 12,21);
    sentinel=addstudent(sentinel,"salam", 13,64);
    sentinel=addstudent(sentinel,"salam", 14,100);
    sentinel=addstudent(sentinel,"salam", 15,72);

    while(true) {
        printf("\n---- Student Exam Management System -----\n");
        printf("1. Enter a new student\n");
        printf("2. Add a new student (directly)\n");
        printf("3. Search for a student by ID\n");
        printf("4. Get the count of students\n");
        printf("5. Display the list of students\n");
        printf("6. Sort the list of students by grade\n");
        printf("7. Delete last added student\n");
        printf("8. Split the list into high-level and low-level students\n");
        printf("   a. Sort sub-lists by grade\n");
        printf("   b. Merge the two sub-lists\n");
        printf("9. Calculate the exam average\n");
        printf("10. Free all student data\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Please enter an integer.\n");
            while (getchar() != '\n') {}
            continue;
        }

        switch (choice) {
            case 1: {
                T_student* newStudent = createstudent();
                sentinel = addstudent(sentinel, newStudent->name, newStudent->ID, newStudent->grade);
                free(newStudent);
                break;
            }
            case 2: {
                char name[30];
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter ID: ");
                scanf("%ld", &id);
                printf("Enter grade: ");
                scanf("%f", &grade);
                sentinel = addstudent(sentinel, name, id, grade);
                break;
            }
            case 3: {
                printf("Enter ID to search: ");
                scanf("%ld", &id);
                int index = findstudent(sentinel, id);
                if(index!=-1) {
                    printf("Student found in index: %d \n",index);
                }
                else {
                    printf("No student found \n");
                }
                break;
            }
            case 4: {
                int count=studentcount(sentinel);
                printf("Count of students: %d \n",count);
                break;
            }
            case 5: {
                displaylist(sentinel);
                break;
            }
            case 6: {
                sortlist(sentinel);
                printf("The list has been sorted by grades.\n");
                displaylist(sentinel);
                break;
            }
            case 7: {
                deletelaststudent(sentinel);
                displaylist(sentinel);
                break;
            }
            case 8: {
                splitlist(sentinel, &highLevel, &lowLevel);
                printf("The list has been split into high-level and low-level students.\n");

                printf("\nHigh-level Students:\n");
                displaylist(highLevel);

                printf("\nLow-level Students:\n");
                displaylist(lowLevel);

                printf("\n Sorting both lists\n");
                sortlist(highLevel);
                sortlist(lowLevel);

                printf("\nMerging both sub-lists back into one sorted list...\n");
                sentinel = mergelists(lowLevel,highLevel);
                highLevel = NULL;
                lowLevel = NULL;
                displaylist(sentinel);
                break;
            }
            case 9: {
                float avg = averageexam(sentinel);
                printf("The exam average is: %.2f\n", avg);
                break;
            }
            case 10: {
                freelist(sentinel);
                sentinel = (T_student*)malloc(sizeof(T_student));
                if (!sentinel) {
                    printf("Memory allocation failed.\n");
                    return 1;
                }
                sentinel->next = NULL;
                printf("All data has been freed.\n");
                break;
            }
            case 11: {
                printf("Exiting the program. Goodbye!\n");
                break;
            }
            default: {
                printf("Please enter number between 1 and 11.\n");
                break;
            }
        }
    }

}
