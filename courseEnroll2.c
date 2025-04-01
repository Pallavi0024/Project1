#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "enrollments.txt"

struct Enrollment {
    int id;
    char name[50];
    char course[50];
};

void enrollStudent();
void viewEnrollments();
void editEnrollment();
void removeEnrollment();

int main() {
    int choice;
    do {
        printf("\nCourse Enrollment System\n");
        printf("1. Enroll Student\n");
        printf("2. View Enrollments\n");
        printf("3. Edit Enrollment\n");
        printf("4. Remove Enrollment\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: enrollStudent(); break;
            case 2: viewEnrollments(); break;
            case 3: editEnrollment(); break;
            case 4: removeEnrollment(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);
    return 0;
}

void enrollStudent() {
    FILE *file = fopen(FILE_NAME, "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    struct Enrollment e;
    printf("Enter Student ID: ");
    scanf("%d", &e.id);
    getchar();
    printf("Enter Student Name: ");
    fgets(e.name, sizeof(e.name), stdin);
    strtok(e.name, "\n");
    printf("Enter Course Name: ");
    fgets(e.course, sizeof(e.course), stdin);
    strtok(e.course, "\n");
    fprintf(file, "%d,%s,%s\n", e.id, e.name, e.course);
    fclose(file);
    printf("Student enrolled successfully!\n");
}

void viewEnrollments() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No enrollments found!\n");
        return;
    }
    struct Enrollment e;
    printf("\nID | Name | Course\n");
    while (fscanf(file, "%d,%49[^,],%49[^\n]\n", &e.id, e.name, e.course) != EOF) {
        printf("%d | %s | %s\n", e.id, e.name, e.course);
    }
    fclose(file);
}

void editEnrollment() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No enrollments found!\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    struct Enrollment e;
    int id, found = 0;
    printf("Enter Student ID to edit: ");
    scanf("%d", &id);
    getchar();
    while (fscanf(file, "%d,%49[^,],%49[^\n]\n", &e.id, e.name, e.course) != EOF) {
        if (e.id == id) {
            printf("Enter New Name: ");
            fgets(e.name, sizeof(e.name), stdin);
            strtok(e.name, "\n");
            printf("Enter New Course: ");
            fgets(e.course, sizeof(e.course), stdin);
            strtok(e.course, "\n");
            found = 1;
        }
        fprintf(temp, "%d,%s,%s\n", e.id, e.name, e.course);
    }
    fclose(file);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    if (found)
        printf("Enrollment updated successfully!\n");
    else
        printf("Student ID not found!\n");
}

void removeEnrollment() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No enrollments found!\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    struct Enrollment e;
    int id, found = 0;
    printf("Enter Student ID to remove: ");
    scanf("%d", &id);
    while (fscanf(file, "%d,%49[^,],%49[^\n]\n", &e.id, e.name, e.course) != EOF) {
        if (e.id == id) {
            found = 1;
            continue;
        }
        fprintf(temp, "%d,%s,%s\n", e.id, e.name, e.course);
    }
    fclose(file);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    if (found)
        printf("Enrollment removed successfully!\n");
    else
        printf("Student ID not found!\n");
}
