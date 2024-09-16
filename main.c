#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h> // Include for using bool, true, and false

#define FACULTY_MAX_ACADEMIC_YEAR 5
typedef struct {
    char name[150];
    int id;
    char gender;
    int academicYear;
    float gpa;
} Student;

void addStudent(Student* students, int* numStudents) {

    int id;
   char firstName[50];
    char lastName[50];

    printf("Enter student first name: ");
    scanf("%s", firstName);

    printf("Enter student last name: ");
    scanf("%s", lastName);

    // Combine first and last name into a single string
    strcpy(students[*numStudents].name, firstName);
    strcat(students[*numStudents].name, " ");
    strcat(students[*numStudents].name, lastName);

    srand(time(NULL));  // Seed the random number generator with the current time

    bool isUnique;  // Use bool type for the isUnique variable
    do {
        isUnique = true;  // Assume the ID is unique initially
        id = rand() % 9000000 + 1000000;  // Generate a 7-digit number

        // Check for uniqueness
        for (int i = 0; i < *numStudents; i++) {
            if (students[*numStudents].id == id) {
                isUnique = false;  // If a match is found, the ID is not unique
                break;  // No need to continue checking, exit the loop
            }
        }
    } while (!isUnique);  // Repeat until a unique ID is found


    students[*numStudents].id = id;
    printf("Your student ID is :  %d\n", students[*numStudents].id);

    printf("Enter student gender (M/F): ");

    scanf(" %c", &students[*numStudents].gender);

    while (students[*numStudents].gender != 'M' && students[*numStudents].gender != 'F') {
        printf("Error Enter student gender (M/F): ");
        scanf(" %c", &students[*numStudents].gender);
    }

    printf("Enter student academic year (1-%d): ", FACULTY_MAX_ACADEMIC_YEAR);
    scanf("%d", &students[*numStudents].academicYear);
    while (students[*numStudents].academicYear < 1 || students[*numStudents].academicYear > FACULTY_MAX_ACADEMIC_YEAR)
    {
        printf("Invalid academic year. Please enter a value between 1 and %d.\n", FACULTY_MAX_ACADEMIC_YEAR);
        scanf("%d", &students[*numStudents].academicYear);
    };


    printf("Enter student GPA (0-4.0): ");
    scanf("%f", &students[*numStudents].gpa);
    while (students[*numStudents].gpa < 0.0 || students[*numStudents].gpa > 4.0)
    {
        printf("Invalid GPA. Please enter a value between 0.0 and 4.0.\n");
        scanf("%f", &students[*numStudents].gpa);
    };

    (*numStudents)++;
    printf("Student added successfully.\n");
}

void removeStudent(Student* students, int* numStudents, int id) {
    int i, j;
    for (i = 0; i < *numStudents; i++) {
        if (students[i].id == id) {
            for (j = i; j < *numStudents - 1; j++) {
                students[j] = students[j + 1];
            }
            (*numStudents)--;
            printf("Student removed successfully.\n");
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

void searchStudent(Student* students, int numStudents) {
    int choice;
    char name[100];
    int id;
    char firstName[50];
    char lastName[50];
    int i, j;


    printf("Choose search method:\n");
    printf("1. Search by name\n");
    printf("2. Search by ID\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    bool found = false;

    switch (choice) {
        case 1:
            printf("Enter student name: ");
            scanf("%s", name);

            // Split the name into first and last name
            for (int i = 0; name[i] != '\0'; i++) {
                if (name[i] == ' ') {
                    break;
                }
            }

            strncpy(firstName, name, i);
            firstName[i] = '\0';
            strcpy(lastName, name + i + 1);

            // Search by first or last name
            for (i = 0; i < numStudents; i++) {
                if (strcmp(students[i].name, name) == 0 ||
                    strstr(students[i].name, firstName) != NULL ||
                    strstr(students[i].name, lastName) != NULL) {
                    printf("Student found:\n");
                    printf("%-20s %-10d %-10c %-15d %-10.2f\n", students[i].name, students[i].id, students[i].gender, students[i].academicYear, students[i].gpa);
                }
            }
            break;

        case 2:
            printf("Enter student ID: ");
            scanf("%d", &id);

            // Search by ID
            for (int i = 0; i < numStudents; i++) {
                if (students[i].id == id) {
                    printf("Student found:\n");
                    printf("%-20s %-10d %-10c %-15d %-10.2f\n", students[i].name, students[i].id, students[i].gender, students[i].academicYear, students[i].gpa);
                    return; // Found a match, exit the loop
                }
            }

            printf("Student not found.\n");
            break;

        default:
            printf("Invalid choice.\n");
    }
}
Student* getStudentById(Student* students, int numStudents, int id) {
    int i;
    for (i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            return &students[i];
        }
    }
    return NULL;
}

void updateStudent(Student* students, int* numStudents, int id) {
    Student* student = getStudentById(students, *numStudents, id);
    if (student != NULL) {
        printf("Enter new academic year (1-%d): ", FACULTY_MAX_ACADEMIC_YEAR);
        scanf("%d", &student->academicYear);
        while (student->academicYear < 1 || student->academicYear > 5) {
            printf("Invalid academicYear. Please enter a value between 1 and 5.\n");
            scanf("%d", &student->academicYear);
        }

        printf("Enter new GPA (0-4.0): ");
        scanf("%f", &student->gpa);
        while (student->gpa < 0.0 || student->gpa > 4.0) {
            printf("Invalid GPA. Please enter a value between 0.0 and 4.0.\n");
            scanf("%f", &student->gpa);
        }

        printf("Student updated successfully.\n");
    }
    else {
        printf("Student with ID %d not found.\n", id);
    }
}

void intro()
{
    printf("Choose the desired operation: \n");
    printf("/");
    int x = 67;
    for (int i = 0; i < x; i++)
        printf("*");
    printf("/\n");
    printf("\t\t\tStudent Management System\n");
    printf("/");
    for (int i = 0; i < x; i++)
        printf("*");
    printf("/\n");
    printf("1- Add a new student\n");
    printf("2- Remove a student\n");
    printf("3- Retrieve student's data\n");
    printf("4- Update student's data\n");
}

int main() {
    Student students[100];
    int numStudents = 0;
    int choice;
    int id;

    while (1) {
        intro();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid integer.\n");
            continue;
        }

        switch (choice) {
        case 1:
            addStudent(students, &numStudents);
            break;
        case 2:
            printf("Enter student ID to remove: ");
            scanf("%d", &id);
            removeStudent(students, &numStudents, id);
            break;
        case 3:
            searchStudent(students, numStudents);
            break;
        case 4:
            printf("Enter student ID to update: ");
            scanf("%d", &id);
            updateStudent(students, &numStudents, id);
            break;

        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

return 0;
}
