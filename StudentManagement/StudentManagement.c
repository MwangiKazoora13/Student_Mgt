#include <stdio.h>
#include <string.h>

typedef struct {
char name[50];
int roll_number;
float marks;
} Student;

//add students function
void add_student(FILE *file) {
    Student student;
    printf("Enter student name: ");
    scanf(" %[^\n]", student.name); // To include spaces
    printf("Enter roll number: ");
    scanf("%d", &student.roll_number);
    printf("Enter marks: ");
    scanf("%f", &student.marks);

    fwrite(&student, sizeof(Student), 1, file);
}

//display students function
void display_students(FILE *file) {
    Student student;
    rewind(file);
    while (fread(&student, sizeof(Student), 1, file)) {
            printf("Name: %s, Roll Number: %d, Marks: %.2f\n",
                   student.name, student.roll_number, student.marks);
    }
}

//search student function
void search_student(FILE *file, int roll_number) {
    Student student;
    rewind(file);
    while (fread(&student, sizeof(Student), 1, file)) {
            if (student.roll_number == roll_number) {
                printf("Student found: Name: %s, Roll Number: %d, Marks: %.2f\n", student.name, student.roll_number, student.marks);
                       return;
            }
    }
    printf("Student with roll number %d not found.\n", roll_number);
}

int main() {
    FILE *file = fopen("students.dat", "w+b");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

int choice, roll_number;
do {
        printf("\n1. Add Student\n2. Display All Students\n3. Search Student by Roll Number\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_student(file);
                break;
            case 2:
                display_students(file);
                break;
            case 3:
                printf("Enter roll number to search: ");
                scanf("%d", &roll_number);
                search_student(file, roll_number);
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
} while (choice != 4);

fclose(file);
return 0;
}
