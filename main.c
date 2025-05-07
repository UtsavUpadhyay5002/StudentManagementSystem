#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_FILE "students.csv"
#define GRADES_FILE "grades.csv"

#define MIN_MARKS 0
#define MAX_MARKS 100

#define MIN_STUDENT_ID 1000
#define MAX_STUDENT_ID 10000

//structure for student basic info
typedef struct {
    int studentID;
    char name[50];
    float gpa;
    char letterGrade[5];
} Student;

typedef struct {
    int studentID;
    char courseName[50];
    float courseMarks;
} Grade;

//student linked list
typedef struct StudentNode {
    Student data;
    struct StudentNode* next;
} StudentNode;

//grades linked list
typedef struct GradeNode {
    Grade data;
    struct GradeNode* next;
} GradeNode;

//function prototypes
void addStudent(StudentNode** head);
void removeStudent(StudentNode** head, int id);
void addGrade(GradeNode** head, StudentNode* studentHead);
void displayStudents(StudentNode* head, GradeNode* gradeHead);
void displayGrades(GradeNode* head, int studentID);
void searchStudentByName(StudentNode* head, GradeNode* gradeHead);
void sortStudents(StudentNode** head, GradeNode* gradeHead, int criteria);
void printBarChart(GradeNode* head);

void loadStudentsFromFile(StudentNode** head);
void loadGradesFromFile(GradeNode** head);
void saveStudentsToFile(StudentNode* head);
void saveGradesToFile(GradeNode* head);
void freeStudentList(StudentNode** head);
void freeGradeList(GradeNode** head);

int validateStudentID(int studentID);
int validateName(const char *name);
int validateMarks(float marks);
int validateCourseName(const char *courseName);
int studentIDExists(StudentNode* head, int studentID);

float getAverage(GradeNode* head, int studentID);
char* avgToLetter(float average);
char* getLetterGrade(GradeNode* head, int studentID);
float getGPAPoint(const char* letterGrade);

//functions for linked list operations
StudentNode* createStudentNode(Student data);
GradeNode* createGradeNode(Grade data);
void insertStudentNode(StudentNode** head, Student data);
void insertGradeNode(GradeNode** head, Grade data);
StudentNode* findStudentByID(StudentNode* head, int studentID);

int main() 
{
    StudentNode* studentHead = NULL;
    GradeNode* gradeHead = NULL;
    
    //Loading existing data from files
    loadStudentsFromFile(&studentHead);
    loadGradesFromFile(&gradeHead);
    
    int choice;
    do {
        printf("\n===== Student Grade Management System =====\n");
        printf("1. Display All Students\n");
        printf("2. Add Student\n");
        printf("3. Add Grade\n");
        printf("4. View Student Profile\n");
        printf("5. Search Student By Name\n");
        printf("6. Sort and Display Students\n");
        printf("7. Print Student Bar Chart\n");
        printf("8. Remove Student\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if(choice == 1)
        {
            displayStudents(studentHead, gradeHead); 
        }
        else if(choice == 2)
        {
            addStudent(&studentHead); 
        }
        else if(choice == 3) 
        {
            addGrade(&gradeHead, studentHead); 
        }
        else if(choice == 4)
        {
            printf("Enter Student ID: ");
            int id;
            scanf("%d", &id);
            displayGrades(gradeHead, id); 
        }
        else if(choice == 5) 
        {
            searchStudentByName(studentHead, gradeHead); 
        }
        else if(choice == 6)
        { 
            printf("\nSort by:\n1. ID\n2. Name\n3. GPA\nEnter choice: ");
            int sortChoice;
            scanf("%d", &sortChoice);
            sortStudents(&studentHead, gradeHead, sortChoice);
            displayStudents(studentHead, gradeHead);
        }
        else if(choice == 7)
        {
            printBarChart(gradeHead); 
        }
        else if(choice == 8)
        {
            printf("Enter Student ID to remove: ");
            int removeID;
            scanf("%d", &removeID);
            removeStudent(&studentHead, removeID);
        }
        else if(choice == 0)
        {
            printf("Saving data and exiting...\n");
            saveStudentsToFile(studentHead);
            saveGradesToFile(gradeHead);
        }
        else
        {
            printf("Invalid choice! Try again.\n");
        }
    } while(choice != 0);

    //freeing allocated memory before exiting
    freeStudentList(&studentHead);
    freeGradeList(&gradeHead);

    return 0;
}

StudentNode* createStudentNode(Student data) 
{
    StudentNode* newNode = (StudentNode*)malloc(sizeof(StudentNode));
    if (newNode == NULL) 
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

GradeNode* createGradeNode(Grade data) 
{
    GradeNode* newNode = (GradeNode*)malloc(sizeof(GradeNode));
    if (newNode == NULL) 
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertStudentNode(StudentNode** head, Student data) 
{
    StudentNode* newNode = createStudentNode(data);
    if (*head == NULL) 
    {
        *head = newNode;
        return;
    }
    
    StudentNode* current = *head;
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = newNode;
}

void insertGradeNode(GradeNode** head, Grade data) 
{
    GradeNode* newNode = createGradeNode(data);
    if (*head == NULL) 
    {
        *head = newNode;
        return;
    }
    
    GradeNode* current = *head;
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = newNode;
}

StudentNode* findStudentByID(StudentNode* head, int studentID) 
{
    StudentNode* current = head;
    while (current != NULL) 
    {
        if (current->data.studentID == studentID) 
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int validateStudentID(int studentID) 
{
    return !(studentID >= MIN_STUDENT_ID && studentID <= MAX_STUDENT_ID);
}

int validateName(const char *name) 
{
    if (strlen(name) == 0) 
    {
        return 0;
    }
    for (int i = 0; name[i] != '\0'; i++) 
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' ')) 
        {
            return 0;
        }
    }

    return 1;
}

int validateCourseName(const char *courseName) 
{
    return !(strlen(courseName) > 0 && strlen(courseName) < 7);
}

int validateMarks(float marks) 
{
    return !(marks >= MIN_MARKS && marks <= MAX_MARKS);
}

int studentIDExists(StudentNode* head, int studentID) 
{
    return findStudentByID(head, studentID) != NULL;
}

void loadStudentsFromFile(StudentNode** head) 
{
    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) return;  // File doesn't exist yet
    
    char line[100];
    Student s;
    
    while (fgets(line, sizeof(line), fp)) 
    {
        sscanf(line, "%d,%49[^\n]", &s.studentID, s.name);
        insertStudentNode(head, s);
    }
    
    fclose(fp);
}

void loadGradesFromFile(GradeNode** head) 
{
    FILE *fp = fopen(GRADES_FILE, "r");
    if (!fp) return;  // File doesn't exist yet
    
    char line[100];
    Grade g;
    
    while (fgets(line, sizeof(line), fp)) 
    {
        sscanf(line, "%d,%49[^,],%f", &g.studentID, g.courseName, &g.courseMarks);
        insertGradeNode(head, g);
    }
    
    fclose(fp);
}

void saveStudentsToFile(StudentNode* head) 
{
    FILE *fp = fopen(STUDENT_FILE, "w");
    if (!fp) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    StudentNode* current = head;
    while (current != NULL) 
    {
        fprintf(fp, "%d,%s\n", current->data.studentID, current->data.name);
        current = current->next;
    }
    
    fclose(fp);
}

void saveGradesToFile(GradeNode* head) 
{
    FILE *fp = fopen(GRADES_FILE, "w");
    if (!fp) 
    {
        printf("Error opening file for writing.\n");
        return;
    }
    
    GradeNode* current = head;
    while (current != NULL) 
    {
        fprintf(fp, "%d,%s,%.2f\n", current->data.studentID, current->data.courseName, current->data.courseMarks);
        current = current->next;
    }
    
    fclose(fp);
}

void addStudent(StudentNode** head) 
{
    Student s;
    
    printf("Enter Student ID (1000-10000): ");
    scanf("%d", &s.studentID);
    if (validateStudentID(s.studentID)) 
    {
        printf("Invalid Student ID.\n");
        return;
    }
    
    if (studentIDExists(*head, s.studentID)) 
    {
        printf("ERROR: Student ID already exists!!\n");
        return;
    }
    
    printf("Enter Name: ");
    getchar();
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';
    if (!validateName(s.name)) 
    {
        printf("Invalid name.\n");
        return;
    }
    
    insertStudentNode(head, s);
    printf("Student added successfully.\n");

    saveStudentsToFile(*head);
}

void removeStudent(StudentNode** head, int id) 
{
    if (*head == NULL) 
    {
        printf("No students in the system.\n");
        return;
    }
    
    //if the student to remove is the head
    if ((*head)->data.studentID == id) 
    {
        StudentNode* temp = *head;
        *head = (*head)->next;
        free(temp);
        printf("Student with ID %d removed successfully.\n", id);
        saveStudentsToFile(*head);
        return;
    }
    
    //looking for the student in the rest of the list
    StudentNode* current = *head;
    while (current->next != NULL && current->next->data.studentID != id) 
    {
        current = current->next;
    }
    
    //if found
    if (current->next != NULL) 
    {
        StudentNode* temp = current->next;
        current->next = temp->next;
        free(temp);
        printf("Student with ID %d removed successfully.\n", id);
        saveStudentsToFile(*head);
    } 
    else 
    {
        printf("Student with ID %d not found.\n", id);
    }
}

void addGrade(GradeNode** head, StudentNode* studentHead) 
{
    Grade g;
    
    printf("Enter Student ID: ");
    scanf("%d", &g.studentID);
    if (validateStudentID(g.studentID)) 
    {
        printf("Invalid Student ID.\n");
        return;
    }
    
    if (!studentIDExists(studentHead, g.studentID)) 
    {
        printf("ERROR: Student ID does not exist!!\n");
        return;
    }
    
    printf("Enter Course Name: ");
    getchar();
    fgets(g.courseName, 50, stdin);
    g.courseName[strcspn(g.courseName, "\n")] = '\0';
    if (validateCourseName(g.courseName)) 
    {
        printf("Invalid Course Name.\n");
        return;
    }
    
    printf("Enter Marks (0-100): ");
    scanf("%f", &g.courseMarks);
    if (validateMarks(g.courseMarks)) 
    {
        printf("Invalid Marks.\n");
        return;
    }
    
    insertGradeNode(head, g);
    printf("Grade added successfully.\n");
    
    saveGradesToFile(*head);
}

float getAverage(GradeNode* head, int studentID) 
{
    GradeNode* current = head;
    float total = 0;
    int count = 0;
    
    while (current != NULL) 
    {
        if (current->data.studentID == studentID) 
        {
            total += current->data.courseMarks;
            count++;
        }
        current = current->next;
    }
    
    if(count > 0)
    {
        return total / count;
    }
    else
    {
        return 0;
    }
}

char* avgToLetter(float average) 
{
    static char grade[5];
    
    if (average >= 90) 
    {
        strcpy(grade, "A+");
    }
    else if (average >= 85) 
    {
        strcpy(grade, "A");
    }
    else if (average >= 80) 
    {
        strcpy(grade, "A-");
    }
    else if (average >= 75) 
    {
        strcpy(grade, "B+");
    }
    else if (average >= 70)
    { 
        strcpy(grade, "B");
    }
    else if (average >= 65) 
    {
        strcpy(grade, "B-");
    }
    else if (average >= 55) 
    {
        strcpy(grade, "C");
    }
    else if (average >= 50) 
    {
        strcpy(grade, "D");
    }
    else 
    {
        strcpy(grade, "F");
    }
    
    return grade;
}

char* getLetterGrade(GradeNode* head, int studentID) 
{
    return avgToLetter(getAverage(head, studentID));
}

float getGPAPoint(const char* letterGrade) 
{
    if (strcmp(letterGrade, "A+") == 0) 
    {
        return 4.3;
    }
    else if (strcmp(letterGrade, "A") == 0) 
    {
        return 4.0;
    }
    else if (strcmp(letterGrade, "A-") == 0) 
    {
        return 3.7;
    }
    else if (strcmp(letterGrade, "B+") == 0)
    {
        return 3.3;
    }
    else if (strcmp(letterGrade, "B") == 0) 
    {
        return 3.0;
    }
    else if (strcmp(letterGrade, "B-") == 0) 
    {
        return 2.7;
    }
    else if (strcmp(letterGrade, "C") == 0) 
    {
        return 2.3;
    }
    else if (strcmp(letterGrade, "D") == 0) 
    {
        return 1.0;
    }
    else 
    {
        return 0.0;
    }
}

void displayStudents(StudentNode* head, GradeNode* gradeHead) 
{
    if (head == NULL) 
    {
        printf("No students in the system.\n");
        return;
    }
    
    printf("\n%-10s %-30s %-5s  %-5s\n", "StudentID", "Name", "Grade", "CGPA");
    printf("-----------------------------------------------------\n");
    
    StudentNode* current = head;
    while (current != NULL) 
    {
        // Get the letter grade and GPA for the current student
        strcpy(current->data.letterGrade, getLetterGrade(gradeHead, current->data.studentID));
        current->data.gpa = getGPAPoint(current->data.letterGrade);
        
        printf("%-10d %-30s %-5s  %-.2f\n", 
               current->data.studentID, 
               current->data.name, 
               current->data.letterGrade, 
               current->data.gpa);
        
        current = current->next;
    }
}

void displayGrades(GradeNode* head, int studentID) 
{
    GradeNode* current = head;
    int found = 0;
    
    printf("\nGrades for Student ID: %d\n", studentID);
    printf("%-30s %-10s %-5s  %-5s\n", "Course", "Marks", "Grade", "CGPA");
    printf("-----------------------------------------------------\n");
    
    while (current != NULL) 
    {
        if (current->data.studentID == studentID) 
        {
            char* letterGrade = avgToLetter(current->data.courseMarks);
            float gpa = getGPAPoint(letterGrade);
            
            printf("%-30s %-10.2f %-5s  %-.2f\n", 
                   current->data.courseName, 
                   current->data.courseMarks, 
                   letterGrade,
                   gpa);
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) 
    {
        printf("No grades found for Student ID %d\n", studentID);
    }
}

void searchStudentByName(StudentNode* head, GradeNode* gradeHead) 
{
    if (head == NULL) 
    {
        printf("No students in the system.\n");
        return;
    }
    
    char searchTerm[50];
    printf("Enter name to search: ");
    getchar();
    fgets(searchTerm, 50, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = '\0';
    
    StudentNode* current = head;
    int found = 0;
    
    printf("\n%-10s %-30s %-5s  %-5s\n", "StudentID", "Name", "Grade", "CGPA");
    printf("-----------------------------------------------------\n");
    
    while (current != NULL) 
    {
        if (strstr(current->data.name, searchTerm)) 
        {
            strcpy(current->data.letterGrade, getLetterGrade(gradeHead, current->data.studentID));
            current->data.gpa = getGPAPoint(current->data.letterGrade);
            
            printf("%-10d %-30s %-5s  %-.2f\n", 
                   current->data.studentID, 
                   current->data.name, 
                   current->data.letterGrade, 
                   current->data.gpa);
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) 
    {
        printf("No students found matching '%s'.\n", searchTerm);
    }
}

//function to sort the linked list using the bubble sort approach - simpler than quicksort for linked lists
void sortStudents(StudentNode** head, GradeNode* gradeHead, int criteria) 
{
    if (*head == NULL || (*head)->next == NULL) 
    {
        return; 
    }
    
    int swapped;
    StudentNode* ptr1;
    StudentNode* lptr = NULL;
    
    do {
        swapped = 0;
        ptr1 = *head;
        
        while (ptr1->next != lptr) 
        {
            //calculating grades and GPAs for comparison
            strcpy(ptr1->data.letterGrade, getLetterGrade(gradeHead, ptr1->data.studentID));
            ptr1->data.gpa = getGPAPoint(ptr1->data.letterGrade);
            
            strcpy(ptr1->next->data.letterGrade, getLetterGrade(gradeHead, ptr1->next->data.studentID));
            ptr1->next->data.gpa = getGPAPoint(ptr1->next->data.letterGrade);
            
            int shouldSwap = 0;
            
            //comparing based on criteria
            if (criteria == 1) 
            { // ID
                shouldSwap = (ptr1->data.studentID > ptr1->next->data.studentID);
            } else if (criteria == 2) 
            { // Name
                shouldSwap = (strcmp(ptr1->data.name, ptr1->next->data.name) > 0);
            } else if (criteria == 3) 
            { // GPA
                shouldSwap = (ptr1->data.gpa < ptr1->next->data.gpa);
            }
            
            if (shouldSwap) 
            {
                // Swap the nodes data
                Student temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void printBarChart(GradeNode* head) 
{
    int studentID;
    printf("Enter Student ID: ");
    scanf("%d", &studentID);
    
    GradeNode* current = head;
    int found = 0;
    
    //ANSI Color codes - REFERENCE: https://c-for-dummies.com/blog/?p=5270
    #define RESET   "\x1b[0m"
    #define RED     "\x1b[31m"
    #define YELLOW  "\x1b[33m"
    #define GREEN   "\x1b[32m"
    #define CYAN    "\x1b[36m"
    
    printf("\nGrade Bar Chart for Student ID: %d\n", studentID);
    printf("---------------------------------------\n");
    
    while (current != NULL) 
    {
        if (current->data.studentID == studentID) 
        {
            found = 1;
            float marks = current->data.courseMarks;
            int barLength = (int)(marks / 5);           //scale to 20 characters
            
            //colour selection
            const char* color;
            if (marks >= 85) 
            {
                color = GREEN;
            }
            else if (marks >= 70) 
            {
                color = YELLOW;
            }
            else 
            {
                color = RED;
            }
            
            printf("%-10s | ", current->data.courseName);
            printf("%s", color);
            for (int i = 0; i < barLength; i++) 
            {
                printf("#");
            }
            printf(RESET); 
            printf(" (%.0f)\n", marks);
        }
        current = current->next;
    }
    
    if (!found) 
    {
        printf("No grades found for this student.\n");
    }
}

void freeStudentList(StudentNode** head) 
{
    //Base case
    if (*head == NULL) 
    {
        return;
    }
    
    //saving the next pointer
    StudentNode* next = (*head)->next;
    
    //freeing the current node
    free(*head);
    
    //setting head to next and recursively free the rest
    *head = next;
    freeStudentList(head);
}

void freeGradeList(GradeNode** head) 
{
    if (*head == NULL) 
    {
        return;
    }
    
    GradeNode* next = (*head)->next;
    
    free(*head);
    
    *head = next;
    freeGradeList(head);
}