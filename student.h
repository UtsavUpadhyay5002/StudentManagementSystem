#ifndef STUDENT_H
#define STUDENT_H

#include <stdlib.h>

typedef struct {
    int rollNumber;
    char name[50];
    float marks;
} Student;

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();


#endif