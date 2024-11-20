#ifndef dsaproject_h
#define dsaporject_h
typedef struct student{
    char name[30];
    long ID;
    float grade;
    struct student* next;
}T_student;
//1
T_student* createstudent(void);
//2
void displaylist(T_student*);
//3
T_student* addstudent(T_student* , char[], long, float);
//4
int studentcount(T_student*);
//5
int findstudent(T_student*,long);
//6
void deletelaststudent(T_student*);
//7
void sortlist(T_student*);
//8
float averageexam(T_student*);
//9
void freelist(T_student*);
//10
void splitlist(T_student*, T_student**, T_student**);
//11
T_student* mergelists( T_student*, T_student*);

#endif // dsaproject_h