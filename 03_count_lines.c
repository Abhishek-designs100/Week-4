#include <stdio.h>

int main(void) {
    char filename[256];
    FILE *fp;
    int ch, lines = 0, has_char = 0, last_char = '\n';

    printf("Enter filename to count lines: ");
    if (scanf("%255s", filename) != 1) {
        printf("Invalid filename.\n");
        return 1;
    }

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Could not open file");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        has_char = 1;
        if (ch == '\n') {
            lines++;
        }
        last_char = ch;
    }

    /* Count a final non-empty line even if it lacks a trailing newline. */
    if (has_char && last_char != '\n') {
        lines++;
    }

    if (ferror(fp)) {
        perror("Error while reading file");
        fclose(fp);
        return 1;
    }

    fclose(fp);
    printf("Number of lines: %d\n", lines);
    return 0;
}
