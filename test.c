#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//including the necessary definitions from the main program
#define STUDENT_FILE "students.csv"
#define GRADES_FILE "grades.csv"

#define MIN_MARKS 0
#define MAX_MARKS 100

#define MIN_STUDENT_ID 1000
#define MAX_STUDENT_ID 10000

//NOTE: Because of the consistent linking ERRORs (screenshots attached), we are not able to distribute our main.c
//Therefore, to carry out the test we had to include the definetions which we were testing from main.c
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

typedef struct StudentNode {
    Student data;
    struct StudentNode* next;
} StudentNode;

typedef struct GradeNode {
    Grade data;
    struct GradeNode* next;
} GradeNode;

// Function prototypes from main.c 
int validateStudentID(int studentID);
int validateName(const char *name);
int validateMarks(float marks);
int validateCourseName(const char *courseName);
int studentIDExists(StudentNode* head, int studentID);

char* avgToLetter(float average);
float getGPAPoint(const char* letterGrade);

StudentNode* createStudentNode(Student data);
GradeNode* createGradeNode(Grade data);
void insertStudentNode(StudentNode** head, Student data);
void insertGradeNode(GradeNode** head, Grade data);
StudentNode* findStudentByID(StudentNode* head, int studentID);
float getAverage(GradeNode* head, int studentID);

//function implementations
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
    for (int i = 0; name[i] != '\0'; i++) {
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
    
    //inserting in the end
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

int studentIDExists(StudentNode* head, int studentID) 
{
    return findStudentByID(head, studentID) != NULL;
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

void freeStudentList(StudentNode** head) 
{
    StudentNode* current = *head;
    StudentNode* next;
    
    while (current != NULL) 
    {
        next = current->next;
        free(current);
        current = next;
    }
    
    *head = NULL;
}

void freeGradeList(GradeNode** head) 
{
    GradeNode* current = *head;
    GradeNode* next;
    
    while (current != NULL) 
    {
        next = current->next;
        free(current);
        current = next;
    }
    
    *head = NULL;
}

//=========================Unit tests==========================
void test_validateStudentID() 
{
    printf("Testing validateStudentID...\n");
    
    //testing Valid IDs
    assert(validateStudentID(1000) == 0);  // Min boundary
    assert(validateStudentID(5000) == 0);  // Middle value
    assert(validateStudentID(10000) == 0); // Max boundary
    
    //testing Invalid IDs
    assert(validateStudentID(999) != 0);   // Below min
    assert(validateStudentID(10001) != 0); // Above max
    assert(validateStudentID(-5) != 0);    // Negative value
    
    printf("validateStudentID tests passed!\n\n");
}

void test_validateName() 
{
    printf("Testing validateName...\n");
    
    //testing Valid names
    assert(validateName("John") == 1);
    assert(validateName("Mary Smith") == 1);
    assert(validateName("JohnDoe") == 1);
    
    //testing Invalid names
    assert(validateName("") == 0);         // Empty string
    assert(validateName("John123") == 0);  // Contains numbers
    assert(validateName("John!") == 0);    // Contains special characters
    
    printf("validateName tests passed!\n\n");
}

void test_validateCourseName() 
{
    printf("Testing validateCourseName...\n");
    
    //testing Valid course names (should be >0 and <7 characters)
    assert(validateCourseName("CS1073") == 0);
    assert(validateCourseName("TM2001") == 0);
    
    //testing Invalid course names
    assert(validateCourseName("") != 0);                 // Empty string
    assert(validateCourseName("Biology") != 0);          // Too long (7+ chars)
    assert(validateCourseName("Computer Science") != 0); // Way too long
    
    printf("validateCourseName tests passed!\n\n");
}

void test_validateMarks() 
{
    printf("Testing validateMarks...\n");
    
    //testing Valid marks
    assert(validateMarks(0) == 0);     // Min boundary
    assert(validateMarks(50) == 0);    // Middle value
    assert(validateMarks(100) == 0);   // Max boundary
    
    //testing Invalid marks
    assert(validateMarks(-1) != 0);    // Below min
    assert(validateMarks(101) != 0);   // Above max
    assert(validateMarks(150) != 0);   // Way above max
    
    printf("validateMarks tests passed!\n\n");
}

void test_avgToLetter() 
{
    printf("Testing avgToLetter...\n");
    
    //testing each grade boundary
    assert(strcmp(avgToLetter(95), "A+") == 0);
    assert(strcmp(avgToLetter(90), "A+") == 0);
    assert(strcmp(avgToLetter(85), "A") == 0);
    assert(strcmp(avgToLetter(80), "A-") == 0);
    assert(strcmp(avgToLetter(75), "B+") == 0);
    assert(strcmp(avgToLetter(70), "B") == 0);
    assert(strcmp(avgToLetter(65), "B-") == 0);
    assert(strcmp(avgToLetter(60), "C") == 0);
    assert(strcmp(avgToLetter(55), "C") == 0);
    assert(strcmp(avgToLetter(50), "D") == 0);
    assert(strcmp(avgToLetter(49), "F") == 0);
    assert(strcmp(avgToLetter(0), "F") == 0);
    
    printf("avgToLetter tests passed!\n\n");
}

//helper function for float comparison
int float_equals(float a, float b) 
{
    const float EPSILON = 0.0001;
    return (a > b - EPSILON) && (a < b + EPSILON);
}

void test_getGPAPoint() 
{
    printf("Testing getGPAPoint...\n");
    
    //testing each grade's GPA conversion using our own comparison function
    assert(float_equals(getGPAPoint("A+"), 4.3));
    assert(float_equals(getGPAPoint("A"), 4.0));
    assert(float_equals(getGPAPoint("A-"), 3.7));
    assert(float_equals(getGPAPoint("B+"), 3.3));
    assert(float_equals(getGPAPoint("B"), 3.0));
    assert(float_equals(getGPAPoint("B-"), 2.7));
    assert(float_equals(getGPAPoint("C"), 2.3));
    assert(float_equals(getGPAPoint("D"), 1.0));
    assert(float_equals(getGPAPoint("F"), 0.0));
    assert(float_equals(getGPAPoint("Unknown"), 0.0));
    
    printf("getGPAPoint tests passed!\n\n");
}

void test_studentNodeOperations() 
{
    printf("Testing student node operations...\n");
    
    StudentNode* head = NULL;
    
    //testing creation and insertion of student nodes
    Student s1 = {1001, "John Smith", 0.0, ""};
    Student s2 = {1002, "Jane Doe", 0.0, ""};
    Student s3 = {1003, "Bob Johnson", 0.0, ""};
    
    insertStudentNode(&head, s1);
    insertStudentNode(&head, s2);
    insertStudentNode(&head, s3);
    
    //testing finding students
    StudentNode* found = findStudentByID(head, 1002);
    assert(found != NULL);
    assert(found->data.studentID == 1002);
    assert(strcmp(found->data.name, "Jane Doe") == 0);
    
    //testing student exists function
    assert(studentIDExists(head, 1001) == 1);
    assert(studentIDExists(head, 1002) == 1);
    assert(studentIDExists(head, 1003) == 1);
    assert(studentIDExists(head, 1004) == 0); // Doesn't exist
    
    //clean up
    freeStudentList(&head);
    assert(head == NULL);
    
    printf("Student node operations tests passed!\n\n");
}

void test_gradeNodeOperations() 
{
    printf("Testing grade node operations...\n");
    
    GradeNode* head = NULL;
    
    Grade g1 = {1001, "CS101", 85.5};
    Grade g2 = {1001, "Math", 90.0};
    Grade g3 = {1002, "CS101", 75.5};
    
    insertGradeNode(&head, g1);
    insertGradeNode(&head, g2);
    insertGradeNode(&head, g3);
    
    //testing getAverage function
    //two courses for ID 1001 : (85.5 + 90.0) / 2
    float avg = getAverage(head, 1001);
    assert(avg == 87.75); // (85.5 + 90.0) / 2
    
    //only one course for ID 1002
    avg = getAverage(head, 1002);
    assert(avg == 75.5); 
    
    //No courses
    avg = getAverage(head, 1003);
    assert(avg == 0);
    
    //clean up
    freeGradeList(&head);
    assert(head == NULL);
    
    printf("Grade node operations tests passed!\n\n");
}

int main() 
{
    printf("Running unit tests for Student Grade Management System\n");
    printf("====================================================\n\n");

    test_validateStudentID();
    test_validateName();
    test_validateCourseName();
    test_validateMarks();
    
    test_avgToLetter();
    test_getGPAPoint();
    
    test_studentNodeOperations();
    test_gradeNodeOperations();
    
    printf("\nAll tests passed successfully!\n");
    return 0;
}