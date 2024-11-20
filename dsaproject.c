#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dsaproject.h"

//1
T_student* createstudent(void) {
    T_student* newStudent = (T_student*)malloc(sizeof(T_student));
    if (newStudent == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    printf("Enter the name of the student: ");
    scanf("%s", newStudent->name);

    printf("Enter the student's ID: ");
    scanf("%ld", &newStudent->ID);

    printf("Enter the student's grade: ");
    scanf("%f", &newStudent->grade);

    newStudent->next = NULL;

    return newStudent;
}

//2
void displaylist(T_student* sentinel) {
    if (!sentinel->next) {
        printf("No students in the list.\n");
        return;
    }

    printf("List of students:\n");
    printf("--------------------------------------------------\n");
    printf("| %-30s | %-10s | %-5s |\n", "Name", "ID", "Grade");
    printf("--------------------------------------------------\n");

    T_student* current = sentinel->next;
    while (current) {
        printf("| %-30s | %-10ld | %-5.3f |\n", current->name, current->ID, current->grade);
        current = current->next;
    }
}

//3
T_student* addstudent(T_student* sentinel, char name[], long ID, float grade) {
    T_student* newStudent = (T_student*)malloc(sizeof(T_student));
    if (newStudent == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strcpy(newStudent->name, name);
    newStudent->ID = ID;
    newStudent->grade = grade;

    newStudent->next = sentinel->next;
    sentinel->next = newStudent;

    return sentinel;
}

//4
int studentcount(T_student* sentinel) {
    int count = 0;
    T_student* current = sentinel->next;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

//5
int findstudent(T_student* sentinel, long ID) {
    T_student* current = sentinel->next;
    while (current) {
        if (current->ID == ID) {
            printf("Student found:\n");
            printf("--------------------------------------------------\n");
            printf("| %-30s | %-10s | %-5s |\n", "Name", "ID", "Grade");
            printf("--------------------------------------------------\n");
            printf("| %-30s | %-10ld | %-5.3f |\n", current->name, current->ID, current->grade);
            return 1;
        }
        current = current->next;
    }
    printf("No student with ID %ld found.\n", ID);
    return 0;
}

//6
void deletelaststudent(T_student* sentinel) {
    if (!sentinel->next) {
        printf("No students to delete.\n");
        return;
    }

    T_student* current = sentinel->next;
    if (!current->next) {
        free(current);
        sentinel->next = NULL;
        return;
    }

    while (current->next->next) {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;
}

//7
void sortlist(T_student* sentinel) {
    T_student* sorted = NULL;
    T_student* current = sentinel->next;

    while (current) {
        T_student* next = current->next;
        if (!sorted || sorted->grade >= current->grade) {
            current->next = sorted;
            sorted = current;
        } else {
            T_student* temp = sorted;
            while (temp->next && temp->next->grade < current->grade) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }

    sentinel->next = sorted;
}

//8
float averageexam(T_student* sentinel) {
    T_student* current = sentinel->next;
    float sum = 0;
    int count = 0;

    while (current) {
        sum += current->grade;
        count++;
        current = current->next;
    }

    if (count == 0) {
        printf("No students in the list.\n");
        return 0;
    }

    float average = sum / count;
    if (average > 65) {
        printf("Average is greater than 65.\n");
    } else if (average > 50) {
        printf("Average is between 50 and 65.\n");
    } else {
        printf("Average is less than 50.\n");
    }

    return average;
}

//9
void freelist(T_student* sentinel) {
    T_student* current = sentinel->next;
    while (current) {
        T_student* temp = current;
        current = current->next;
        free(temp);
    }
    free(sentinel);
}

//10
void splitlist(T_student* sentinel, T_student** highLevel, T_student** lowLevel) {
    *highLevel = (T_student*)malloc(sizeof(T_student));
    *lowLevel = (T_student*)malloc(sizeof(T_student));

    if (!*highLevel || !*lowLevel) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    (*highLevel)->next = NULL;
    (*lowLevel)->next = NULL;

    T_student* current = sentinel->next;
    while (current) {
        T_student* newStudent = (T_student*)malloc(sizeof(T_student));
        if (!newStudent) {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        strcpy(newStudent->name, current->name);
        newStudent->ID = current->ID;
        newStudent->grade = current->grade;
        newStudent->next = NULL;

        if (current->grade >= 65) {
            newStudent->next = (*highLevel)->next;
            (*highLevel)->next = newStudent;
        } else {
            newStudent->next = (*lowLevel)->next;
            (*lowLevel)->next = newStudent;
        }

        current = current->next;
    }
}

//11
T_student* mergelists(T_student* firstSentinel, T_student* secondSentinel) {
    if (!firstSentinel || !secondSentinel) {
        printf("Error: One or both sentinels are NULL.\n");
        return NULL;
    }

    if (!firstSentinel->next) {
        free(firstSentinel);
        return secondSentinel;
    }

    if (!secondSentinel->next) {
        free(secondSentinel);
        return firstSentinel;
    }

    T_student* current = firstSentinel;
    while (current->next) {
        current = current->next;
    }

    current->next = secondSentinel->next;
    free(secondSentinel);

    return firstSentinel;
}
