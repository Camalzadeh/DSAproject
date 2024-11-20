#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "dsaproject.h"

// Yunis`s work 1,2,3,4,6,8
//1
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
//2
void displaylist(T_student* head) {
    if(head == NULL){
        printf("No students in the list.\n");
        return;
    }
    static bool isFirstCall = true;
    if(isFirstCall){
        isFirstCall = false;
        printf("List of students: \n");
        printf("=======================================================\n");
        printf("| %-30s | %-10s | %-5s |\n", "Name", "ID", "Grade");
        printf("=======================================================\n");
    }
    if(head->next != NULL) {
        displaylist(head->next);
    }
    printf("| %-30s | %-10ld | %-5.2f |\n", head->name, head->ID, head->grade);
    printf("-------------------------------------------------------\n");
    if(head->next == NULL) isFirstCall = true;
}

//3
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
//4
int studentcount(T_student* head){
    int num = 0;
    T_student* current = head;
    while(current){
        num++;
        current = current->next;
    }
    return num;
}
//6
void deletelaststudent(T_student** head){
    if(*head == NULL){
        printf("The list is empty. Nothing to delete.\n");
        return;
    }
    T_student* temp = *head;
    *head = (*head)->next;
    free(temp);
    printf("Last added student deleted.\n");
}
//8
float averageexam(T_student* head){
    long n = studentcount(head);
    float sum = 0;
    T_student* current = head;
    while(current){
        sum+= current->grade;
        current = current->next;
    }
    return sum/n;
}



//Humbat`s work 5,7,9,10,11

//5
int findstudent(T_student* head, long id){
    T_student* current = head;
    int index = 0;
    while(current){
        if(id == current->ID){
            printf("=======================================================\n");
            printf("| %-30s | %-10s | %-5s |\n", "Name", "ID", "Grade");
            printf("=======================================================\n");
            printf("| %-30s | %-10ld | %-5.2f |\n", current->name, current->ID, current->grade);
            printf("-------------------------------------------------------\n");
            return index;
        }
        current = current->next;
        index++;
    }
    printf("Student not found!\n");
    return -1;
}


//7
void insertionSort(T_student** head) {
    T_student* sorted = NULL;
    T_student* current = *head;
    while (current != NULL) {
        T_student* next = current->next;
        if (sorted == NULL || sorted->grade >= current->grade) {
            current->next = sorted;
            sorted = current;
        } else {
            T_student* temp = sorted;
            while (temp->next != NULL && temp->next->grade < current->grade) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
}
void sortlist(T_student** head) {
    //Bucket Sort
    if (*head == NULL) return;

    float minGrade = (*head)->grade;
    float maxGrade = (*head)->grade;
    T_student* current = *head;
    while (current != NULL) {
        if (current->grade < minGrade) minGrade = current->grade;
        if (current->grade > maxGrade) maxGrade = current->grade;
        current = current->next;
    }
    const int numBuckets = 10;
    T_student* buckets[numBuckets];
    for (int i = 0; i < numBuckets; i++) {
        buckets[i] = NULL;
    }
    current = *head;
    while (current != NULL) {
        int bucketIndex = (int)((current->grade - minGrade) / (maxGrade - minGrade + 0.0001) * (numBuckets - 1));
        T_student* nextStudent = current->next;
        current->next = buckets[bucketIndex];
        buckets[bucketIndex] = current;
        current = nextStudent;
    }
    *head = NULL;
    for (int i = 0; i < numBuckets; i++) {
        insertionSort(&buckets[i]);
        T_student* bucket = buckets[i];
        while (bucket != NULL) {
            T_student* nextBucket = bucket->next;
            bucket->next = *head;
            *head = bucket;
            bucket = nextBucket;
        }
    }
}

//9
void freelist(T_student** head) {
    T_student* current = *head;
    T_student* next = NULL;

    while (current != NULL) {
        next = current->next;
        printf("Freeing student: %s\n", current->name);
        free(current);
        current = next;
    }
    *head = NULL;
    printf("All students freed.\n");
}

//10
void splitlist(T_student* head, T_student** highLevel, T_student** lowLevel) {
    *highLevel = NULL;
    *lowLevel = NULL;
    T_student* current = head;
    while (current != NULL) {
        T_student* nextStudent = current->next;
        current->next = NULL;

        if (current->grade >= 65.0) {
            current->next = *highLevel;
            *highLevel = current;
        } else {
            current->next = *lowLevel;
            *lowLevel = current;
        }
        current = nextStudent;
    }
}

//11
struct student* mergelists(struct student* list1, struct student* list2) {
    T_student dummy;
    T_student* tail = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->grade <= list2->grade) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    if (list1 != NULL) {
        tail->next = list1;
    } else if (list2 != NULL) {
        tail->next = list2;
    }
    return dummy.next;
}


