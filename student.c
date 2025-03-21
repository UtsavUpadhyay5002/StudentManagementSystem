#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#define FILENAME "students.dat"

void addStudent() 
{
    FILE *fp = fopen(FILENAME, "ab");
    Student s;
    printf("Enter Roll Number: ");
    scanf("%d", &s.rollNumber);
    printf("Enter Name: ");
    getchar(); // clear newline
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Student record added successfully.\n");
}

void displayStudents() 
{
    FILE *fp = fopen(FILENAME, "rb");
    Student s;

    printf("\n%-10s %-30s %-10s\n", "Roll No", "Name", "Marks");
    printf("----------------------------------------------\n");
    while(fread(&s, sizeof(Student), 1, fp)) {
        printf("%-10d %-30s %-10.2f\n", s.rollNumber, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent() 
{
    int roll;
    int found = 0;
    Student s;
    FILE *fp = fopen(FILENAME, "rb");

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(Student), 1, fp)) {
        if(s.rollNumber == roll) {
            printf("\nRecord Found:\nRoll: %d\nName: %s\nMarks: %.2f\n", s.rollNumber, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if(!found)
        printf("No student found with Roll Number %d\n", roll);

    fclose(fp);
}

void updateStudent() 
{
    int roll;
    int found = 0;
    Student s;
    FILE *fp = fopen(FILENAME, "rb+");

    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(Student), 1, fp)) {
        if(s.rollNumber == roll) {
            printf("Enter new name: ");
            getchar();
            fgets(s.name, 50, stdin);
            s.name[strcspn(s.name, "\n")] = '\0';
            printf("Enter new marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            found = 1;
            printf("Record updated successfully.\n");
            break;
        }
    }

    if(!found)
        printf("Student with Roll Number %d not found.\n", roll);

    fclose(fp);
}

void deleteStudent() 
{
    int roll, found = 0;
    Student s;
    FILE *fp = fopen(FILENAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(Student), 1, fp)) {
        if(s.rollNumber == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if(found)
        printf("Record deleted successfully.\n");
    else
        printf("Student with Roll Number %d not found.\n", roll);
}