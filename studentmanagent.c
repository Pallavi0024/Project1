#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Define Employee structure
struct Employee {
    int id;
    char name[50];
    char department[30];
    char designation[30];
    float salary;
    char contact[20];
};
// Function prototypes
void addEmployee();
void viewAllEmployees();
void searchEmployee();
void updateEmployeeDetails();
void deleteEmployee();
void manageSalary();
void generateReports();
void sortEmployees();
void exitProgram();

int main() {
    int choice;
    
    do {
        printf("\n--- Employee Management System ---\n");
        printf("1. Add Employee\n");
        printf("2. View All Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee Details\n");
        printf("5. Delete Employee\n");
        printf("6. Manage Salary\n");
        printf("7. Generate Reports\n");
        printf("8. Sort Employees\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addEmployee(); break;
            case 2: viewAllEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: updateEmployeeDetails(); break;
            case 5: deleteEmployee(); break;
            case 6: manageSalary(); break;
            case 7: generateReports(); break;
            case 8: sortEmployees(); break;
            case 9: exitProgram(); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 9);
    
    return 0;
}
// Function to add an employee
void addEmployee() {
    FILE *file = fopen("employees.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    struct Employee emp;
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    getchar();  // To consume the newline character after the previous input
    printf("Enter Name: ");
    fgets(emp.name, sizeof(emp.name), stdin);
    printf("Enter Department: ");
    fgets(emp.department, sizeof(emp.department), stdin);
    printf("Enter Designation: ");
    fgets(emp.designation, sizeof(emp.designation), stdin);
    printf("Enter Salary: ");
    scanf("%f", &emp.salary);
    getchar();  // To consume the newline character after the previous input
    printf("Enter Contact: ");
    fgets(emp.contact, sizeof(emp.contact), stdin);

    fwrite(&emp, sizeof(struct Employee), 1, file);
    fclose(file);
    printf("Employee added successfully!\n");
}

// Function to view all employees
void viewAllEmployees() {
    FILE *file = fopen("employees.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Employee emp;
    printf("\n--- Employee Records ---\n");
    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        printf("ID: %d, Name: %s, Department: %s, Designation: %s, Salary: %.2f, Contact: %s\n", 
               emp.id, emp.name, emp.department, emp.designation, emp.salary, emp.contact);
    }
    fclose(file);
}
// Function to search for an employee by ID, name, or department
void searchEmployee() {
    FILE *file = fopen("employees.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int choice;
    printf("\nSearch by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Department\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    struct Employee emp;
    int found = 0;
    switch(choice) {
        case 1: {
            int id;
            printf("Enter Employee ID to search: ");
            scanf("%d", &id);
            while (fread(&emp, sizeof(struct Employee), 1, file)) {
                if (emp.id == id) {
                    printf("Employee Found: ID: %d, Name: %s, Department: %s, Salary: %.2f\n", 
                           emp.id, emp.name, emp.department, emp.salary);
                    found = 1;
                    break;
                }
            }
            break;
        }
        case 2: {
            char name[50];
            printf("Enter Name to search: ");
            getchar();  // To consume the newline character left by the previous input
            fgets(name, sizeof(name), stdin);
            while (fread(&emp, sizeof(struct Employee), 1, file)) {
                if (strstr(emp.name, name)) {
                    printf("Employee Found: ID: %d, Name: %s, Department: %s, Salary: %.2f\n", 
                           emp.id, emp.name, emp.department, emp.salary);
                    found = 1;
                }
            }
            break;
        }
        case 3: {
            char dept[30];
            printf("Enter Department to search: ");
            getchar();  // To consume the newline character left by the previous input
            fgets(dept, sizeof(dept), stdin);
            while (fread(&emp, sizeof(struct Employee), 1, file)) {
                if (strstr(emp.department, dept)) {
                    printf("Employee Found: ID: %d, Name: %s, Department: %s, Salary: %.2f\n", 
                           emp.id, emp.name, emp.department, emp.salary);
                    found = 1;
                }
            }
            break;
        }
        default:
            printf("Invalid choice!\n");
    }

    if (!found) {
        printf("No employee found matching the search criteria.\n");
    }
    fclose(file);
}

// Function to update employee details
void updateEmployeeDetails() {
    FILE *file = fopen("employees.txt", "r+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int id;
    printf("Enter Employee ID to update: ");
    scanf("%d", &id);

    struct Employee emp;
    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        if (emp.id == id) {
            printf("Enter new Designation: ");
            getchar();  // To consume the newline character left by the previous input
            fgets(emp.designation, sizeof(emp.designation), stdin);
            printf("Enter new Salary: ");
            scanf("%f", &emp.salary);
            printf("Enter new Contact: ");
            getchar();  // To consume the newline character left by the previous input
            fgets(emp.contact, sizeof(emp.contact), stdin);
            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            fwrite(&emp, sizeof(struct Employee), 1, file);
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Employee details updated successfully!\n");
    } else {
        printf("Employee with ID %d not found.\n", id);
    }
    fclose(file);
}
// Function to delete an employee by ID
void deleteEmployee() {
    FILE *file = fopen("employees.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    struct Employee emp;
    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        if (emp.id != id) {
            fwrite(&emp, sizeof(struct Employee), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("employees.txt");
    rename("temp.txt", "employees.txt");

    if (found) {
        printf("Employee with ID %d deleted successfully!\n", id);
    } else {
        printf("Employee with ID %d not found.\n", id);
    }
}
// Function to manage salary (view and update)
void manageSalary() {
    FILE *file = fopen("employees.txt", "r+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int id;
    printf("Enter Employee ID to manage salary: ");
    scanf("%d", &id);

    struct Employee emp;
    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        if (emp.id == id) {
            printf("Current Salary: %.2f\n", emp.salary);
            printf("Enter new Salary: ");
            scanf("%f", &emp.salary);
            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            fwrite(&emp, sizeof(struct Employee), 1, file);
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Salary updated successfully!\n");
    } else {
        printf("Employee with ID %d not found.\n", id);
    }
    fclose(file);
}

// Function to generate reports (e.g., by department)
void generateReports() {
    FILE *file = fopen("employees.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char dept[30];
    printf("Enter Department for report: ");
    getchar();  // To consume the newline character left by the previous input
    fgets(dept, sizeof(dept), stdin);

    struct Employee emp;
    int found = 0;
    printf("\n--- Report for Department: %s ---\n", dept);
    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        if (strstr(emp.department, dept)) {
            printf("ID: %d, Name: %s, Designation: %s, Salary: %.2f\n", 
                   emp.id, emp.name, emp.designation, emp.salary);
            found = 1;
        }
    }

    if (!found) {
        printf("No employees found in this department.\n");
    }

    fclose(file);
}
// Function to sort employees by name (simple bubble sort)
void sortEmployees() {
    FILE *file = fopen("employees.txt", "r+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Employee employees[100];
    int count = 0;
    while (fread(&employees[count], sizeof(struct Employee), 1, file)) {
        count++;
    }
    // Bubble sort by name
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(employees[i].name, employees[j].name) > 0) {
                struct Employee temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }
    // Print sorted employees
    printf("\n--- Sorted Employees ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Name: %s, Department: %s, Designation: %s, Salary: %.2f, Contact: %s\n", 
               employees[i].id, employees[i].name, employees[i].department, employees[i].designation, employees[i].salary, employees[i].contact);
    }
    fclose(file);
}
// Function to exit the program
void exitProgram() {
    printf("Exiting the program.\n");
}