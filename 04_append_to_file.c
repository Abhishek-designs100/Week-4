#include <stdio.h>

int main(void) {
    char filename[256];
    char text[1000];
    FILE *fp;

    printf("Enter filename to append to: ");
    if (scanf("%255s", filename) != 1) {
        printf("Invalid filename.\n");
        return 1;
    }

    /* Consume the newline left by scanf before using fgets. */
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* discard remainder of filename line */
    }

    printf("Enter text to append: ");
    if (fgets(text, sizeof(text), stdin) == NULL) {
        printf("Input error.\n");
        return 1;
    }

    fp = fopen(filename, "a");
    if (fp == NULL) {
        perror("Could not open file for appending");
        return 1;
    }

    if (fprintf(fp, "%s", text) < 0) {
        perror("Append failed");
        fclose(fp);
        return 1;
    }

    if (fclose(fp) != 0) {
        perror("Closing file failed");
        return 1;
    }

    printf("Data appended successfully to %s\n", filename);
    return 0;
}
