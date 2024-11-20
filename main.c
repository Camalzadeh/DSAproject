#include <stdio.h>
#include <stdlib.h>
#include "dsaproject.h" // Include your header file

int main() {
    T_student* sentinel = (T_student*)malloc(sizeof(T_student));
    if (!sentinel) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    sentinel->next = NULL;

    int choice;
    char name[30];
    long id;
    float grade;
    T_student *highLevel = NULL, *lowLevel = NULL;

    do {
        printf("\n*** Student Exam Management System ***\n");
        printf("1. Enter a new student\n");
        printf("2. Add a new student (directly)\n");
        printf("3. Search for a student by ID\n");
        printf("4. Display the list of students\n");
        printf("5. Sort the list of students by grade\n");
        printf("6. Split the list into high-level and low-level students\n");
        printf("   a. Sort sub-lists by grade\n");
        printf("   b. Merge the two sub-lists\n");
        printf("7. Calculate the exam average\n");
        printf("8. Free all student data\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: { // Create and add a student
                T_student* newStudent = createstudent();
                sentinel = addstudent(sentinel, newStudent->name, newStudent->ID, newStudent->grade);
                free(newStudent); // Free temporary object
                break;
            }
            case 2: { // Add a student directly
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter ID: ");
                scanf("%ld", &id);
                printf("Enter grade: ");
                scanf("%f", &grade);
                sentinel = addstudent(sentinel, name, id, grade);
                break;
            }
            case 3: { // Search for a student
                printf("Enter ID to search: ");
                scanf("%ld", &id);
                if (!findstudent(sentinel, id)) {
                    printf("No student with ID %ld found.\n", id);
                }
                break;
            }
            case 4: { // Display all students
                displaylist(sentinel);
                break;
            }
            case 5: { // Sort students by grade
                sortlist(sentinel);
                printf("The list has been sorted by grades.\n");
                displaylist(sentinel);
                break;
            }
            case 6: { // Split list and handle sub-lists
                splitlist(sentinel, &highLevel, &lowLevel);
                printf("The list has been split into high-level and low-level students.\n");

                printf("\nHigh-level Students:\n");
                displaylist(highLevel);

                printf("\nLow-level Students:\n");
                displaylist(lowLevel);

                printf("\nSorting both sub-lists by grades...\n");
                sortlist(highLevel);
                sortlist(lowLevel);

                printf("\nSorted High-level Students:\n");
                displaylist(highLevel);

                printf("\nSorted Low-level Students:\n");
                displaylist(lowLevel);

                printf("\nMerging both sub-lists back into one sorted list...\n");
                sentinel = mergelists(highLevel, lowLevel);
                highLevel = NULL;
                lowLevel = NULL;
                displaylist(sentinel);
                break;
            }
            case 7: { // Calculate average grade
                float avg = averageexam(sentinel);
                printf("The exam average is: %.2f\n", avg);
                break;
            }
            case 8: { // Free all student data
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
            case 9: { // Exit
                printf("Exiting the program. Goodbye!\n");
                break;
            }
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 9);

    freelist(sentinel);
    return 0;
}
