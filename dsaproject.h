#ifndef dsaproject_h
#define dsaporject_h
typedef struct student{
    char name[30];
    long ID;
    float grade;
    struct student* next;
}T_student;

T_student* createstudent(void);
void displaylist(T_student*);
T_student* addstudent(T_student* , char[], long, float);
int studentcount(T_student*);
int findstudent(T_student*);
void deletelaststudent(T_student*);
void sortlist(T_student*);
float averageexam(T_student*);
void freelist(T_student*);
void splitlist(T_student*, T_student**, T_student**);
T_student* mergelists( T_student*, T_student*);

#endif // dsaproject_h
