#include <stdio.h>

struct Student {
    char name[100];
    int age;
    float marks;
};

int main(void) {
    struct Student student;

    printf("Enter student name: ");
    if (fgets(student.name, sizeof(student.name), stdin) == NULL) {
        printf("Input error.\n");
        return 1;
    }
    for (char *p = student.name; *p != '\0'; p++) {
        if (*p == '\n') {
            *p = '\0';
            break;
        }
    }

    printf("Enter age: ");
    if (scanf("%d", &student.age) != 1 || student.age < 0) {
        printf("Invalid age.\n");
        return 1;
    }

    printf("Enter marks: ");
    if (scanf("%f", &student.marks) != 1) {
        printf("Invalid marks.\n");
        return 1;
    }

    printf("\nStudent Details\n");
    printf("Name : %s\n", student.name);
    printf("Age  : %d\n", student.age);
    printf("Marks: %.2f\n", student.marks);
    return 0;
}
