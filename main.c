#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#define FILENAME "students.dat"


int main() 
{
    int choice;

    do {
        printf("\n===== Student Grade Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Update Student Record\n");
        printf("5. Delete Student Record\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: 
                addStudent(); 
                break;
            case 2: 
                displayStudents(); 
                break;
            case 3: 
                searchStudent(); 
                break;
            case 4: 
                updateStudent(); 
                break;
            case 5: 
                deleteStudent(); 
                break;
            case 0: 
                printf("Exiting...\n"); 
                break;
            default: 
                printf("Invalid choice! Try again.\n");
        }
    } while(choice != 0);

    return 0;
}