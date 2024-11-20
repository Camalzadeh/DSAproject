#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dsaproject.h"

//1 Yunis work
bool isIDUnique(T_student* sentinel, long ID) {
    T_student* current = sentinel->next;
    while (current) {
        if (current->ID == ID) {
            return false;
        }
        current = current->next;
    }
    return true;
}

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


//2 Yunis work
void displaylist_recursive(T_student* current) {
    if (current == NULL) {
        return;
    }
    displaylist_recursive(current->next);
    printf("| %-30s | %-10ld | %-5.3f |\n", current->name, current->ID, current->grade);
}

void displaylist(T_student* sentinel) {
    if (!sentinel->next) {
        printf("No students in the list.\n");
        return;
    }
    printf("List of students:\n");
    printf("--------------------------------------------------\n");
    printf("| %-30s | %-10s | %-5s |\n", "Name", "ID", "Grade");
    printf("--------------------------------------------------\n");

    displaylist_recursive(sentinel->next);
}

//3 Yunis work
T_student* addstudent(T_student* sentinel, char name[], long ID, float grade) {
    if (!isIDUnique(sentinel, ID)) {
        printf("Error: ID %ld is already in use. Cannot add student.\n", ID);
        return sentinel;
    }
    T_student* new = newStudent(name, ID, grade);
    new->next = sentinel->next;
    sentinel->next = new;

    return sentinel;
}


//4 Yunis work
int studentcount(T_student* sentinel) {
    int count = 0;
    T_student* current = sentinel->next;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

//5 Humbat work
int findstudent(T_student* sentinel, long ID) {
    T_student* current = sentinel->next;
    int index=0;
    while (current) {

        if (current->ID == ID) {
            printf("Student found:\n");
            printf("--------------------------------------------------\n");
            printf("| %-30s | %-10s | %-5s |\n", "Name", "ID", "Grade");
            printf("--------------------------------------------------\n");
            printf("| %-30s | %-10ld | %-5.3f |\n", current->name, current->ID, current->grade);
            return index;
        }
        current = current->next;
        index++;
    }
    printf("No student with ID %ld found.\n", ID);
    return -1;
}

//6 Huseyn work
void deletelaststudent(T_student* sentinel) {
    if (!sentinel->next) {
        printf("No students to delete.\n");
        return;
    }
    T_student* temp = sentinel->next;
    sentinel->next = temp->next;
    printf("Deleted student: %s (ID: %ld)\n", temp->name, temp->ID);
    free(temp);
}


//Humbat work
T_student* split(T_student* head) {
    T_student* fast = head;
    T_student* slow = head;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        if (fast != NULL) {
            slow = slow->next;
        }
    }

    T_student* temp = slow->next;
    slow->next = NULL;
    return temp;
}

T_student* merge(T_student* first, T_student* second) {
    T_student* sentinel = newStudent("",0,0);
    T_student* current = sentinel;

    while (first != NULL && second != NULL) {
        if (first->grade < second->grade) {
            current->next = first;
            first = first->next;
        } else {
            current->next = second;
            second = second->next;
        }
        current = current->next;
    }

    if (first != NULL) {
        current->next = first;
    } else {
        current->next = second;
    }

    T_student* mergedListHead = sentinel->next;
    free(sentinel);
    return mergedListHead;
}

T_student* mergesort(T_student* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    T_student* second = split(head);

    head = mergesort(head);
    second = mergesort(second);

    return merge(head, second);
}

void sortlist(T_student* sentinel) {
    sentinel->next=mergesort(sentinel->next);
}

//8 Shabnam work
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

//9 Huseyn work
void freelist(T_student* sentinel) {
    T_student* current = sentinel->next;
    while (current) {
        T_student* temp = current;
        current = current->next;
        free(temp);
    }
    free(sentinel);
}

//10 Shabnam work
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

//11 Huseyn work
T_student* mergelists(T_student* firstSentinel, T_student* secondSentinel) {
    return merge(firstSentinel->next,secondSentinel);
}
//additional Humbat works
T_student* newStudent(const char* name, long ID, float grade) {
    T_student* temp = (T_student*)malloc(sizeof(T_student));
    strcpy(temp->name, name);
    temp->ID = ID;
    temp->grade = grade;
    temp->next = NULL;
    return temp;
}