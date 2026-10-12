#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "employees.txt"
#define NAME_SIZE 100

struct Department {
    char name[60];
};

struct Employee {
    int id;
    char name[NAME_SIZE];
    float salary;
    struct Department department; /* Nested structure */
};

static void read_line(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
}

static int read_int(const char *prompt, int *value) {
    char line[100], extra;
    printf("%s", prompt);
    if (fgets(line, sizeof(line), stdin) == NULL) return 0;
    return sscanf(line, "%d %c", value, &extra) == 1;
}

static int read_float(const char *prompt, float *value) {
    char line[100], extra;
    printf("%s", prompt);
    if (fgets(line, sizeof(line), stdin) == NULL) return 0;
    return sscanf(line, "%f %c", value, &extra) == 1;
}

static void add_employee(void) {
    struct Employee e;
    FILE *fp;

    if (!read_int("Employee ID: ", &e.id)) {
        printf("Invalid ID.\n");
        return;
    }
    read_line("Employee name: ", e.name, sizeof(e.name));
    read_line("Department: ", e.department.name, sizeof(e.department.name));
    if (!read_float("Salary: ", &e.salary)) {
        printf("Invalid salary.\n");
        return;
    }

    /* Pipe-delimited text storage; reject delimiters/newlines in fields. */
    if (strchr(e.name, '|') || strchr(e.department.name, '|')) {
        printf("Please do not use the '|' character in names or department.\n");
        return;
    }

    fp = fopen(DATA_FILE, "a");
    if (fp == NULL) {
        perror("Could not open employee file");
        return;
    }
    if (fprintf(fp, "%d|%s|%s|%.2f\n", e.id, e.name,
                e.department.name, e.salary) < 0) {
        perror("Writing employee failed");
        fclose(fp);
        return;
    }
    fclose(fp);
    printf("Employee saved to %s.\n", DATA_FILE);
}

static void list_employees(void) {
    FILE *fp = fopen(DATA_FILE, "r");
    char line[400];
    int found = 0;

    if (fp == NULL) {
        printf("No employee records yet.\n");
        return;
    }

    printf("\n%-8s %-24s %-20s %s\n", "ID", "NAME", "DEPARTMENT", "SALARY");
    printf("----------------------------------------------------------------\n");
    while (fgets(line, sizeof(line), fp) != NULL) {
        struct Employee e;
        char *id = strtok(line, "|");
        char *name = strtok(NULL, "|");
        char *department = strtok(NULL, "|");
        char *salary = strtok(NULL, "|\r\n");

        if (!id || !name || !department || !salary) continue;
        e.id = atoi(id);
        snprintf(e.name, sizeof(e.name), "%s", name);
        snprintf(e.department.name, sizeof(e.department.name), "%s", department);
        e.salary = (float)atof(salary);

        printf("%-8d %-24s %-20s %.2f\n", e.id, e.name,
               e.department.name, e.salary);
        found = 1;
    }
    if (ferror(fp)) perror("Error reading employee file");
    if (!found) printf("No valid employee records found.\n");
    fclose(fp);
}

int main(void) {
    char choice_line[32];
    int choice;

    for (;;) {
        printf("\n=== Employee Management System ===\n");
        printf("1. Add employee\n");
        printf("2. List employees\n");
        printf("3. Exit\n");
        printf("Choose an option: ");

        if (fgets(choice_line, sizeof(choice_line), stdin) == NULL) break;
        if (sscanf(choice_line, "%d", &choice) != 1) {
            printf("Please enter 1, 2, or 3.\n");
            continue;
        }

        switch (choice) {
            case 1:
                add_employee();
                break;
            case 2:
                list_employees();
                break;
            case 3:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    }
    return 0;
}
