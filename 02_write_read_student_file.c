#include <stdio.h>
#include <string.h>

struct Student {
    char name[100];
    int age;
    float marks;
};

int main(void) {
    struct Student student, loaded;
    FILE *fp;

    printf("Enter student name: ");
    if (fgets(student.name, sizeof(student.name), stdin) == NULL) {
        printf("Input error.\n");
        return 1;
    }
    student.name[strcspn(student.name, "\n")] = '\0';

    printf("Enter age and marks: ");
    if (scanf("%d %f", &student.age, &student.marks) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    /* Text format is portable and easy to inspect. */
    fp = fopen("student.txt", "w");
    if (fp == NULL) {
        perror("Could not open student.txt for writing");
        return 1;
    }

    if (fprintf(fp, "%s\n%d\n%.2f\n", student.name,
                student.age, student.marks) < 0) {
        perror("Writing failed");
        fclose(fp);
        return 1;
    }
    if (fclose(fp) != 0) {
        perror("Closing file failed");
        return 1;
    }

    fp = fopen("student.txt", "r");
    if (fp == NULL) {
        perror("Could not open student.txt for reading");
        return 1;
    }

    if (fgets(loaded.name, sizeof(loaded.name), fp) == NULL ||
        fscanf(fp, "%d", &loaded.age) != 1 ||
        fscanf(fp, "%f", &loaded.marks) != 1) {
        printf("Could not read complete student record.\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);
    loaded.name[strcspn(loaded.name, "\n")] = '\0';

    printf("\nData read back from student.txt\n");
    printf("Name : %s\nAge  : %d\nMarks: %.2f\n",
           loaded.name, loaded.age, loaded.marks);
    return 0;
}
