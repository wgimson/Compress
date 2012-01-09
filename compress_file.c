/* Compresses a file by maintaining a pair of consecutive char variables, one
 * representing the current character in the file, and the other the previous
 * character. These are retrieved using the getc() function. For each previous 
 * character that is equivalent to the current character as characters are 
 * incremented through the file, a repetition count is increased by one. Once 
 * the current character and the previous character differ, the previous 
 * character and the repetition count are printed to an output file, ending
 * in ".rle". In this way the output file will eventually contain every character 
 * in the original and the number of consecutive repetitions of that character. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 13


int main(int argc, char *argv[])
{
    FILE *src, *dest;
    unsigned int next_char, prev_char;
    int i, rep_count = 1;
    char *dest_name;

    if (argc != 2) {
        printf("\nUsage: compress_file file.\n");
        exit(EXIT_FAILURE);
    }

    if ((src = fopen(argv[1], "rb")) == NULL) {
        printf("\nError: cannot open %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    dest_name = malloc(strlen(argv[1]) + 5);
    strcpy(dest_name, argv[1]);
    strcat(dest_name, ".rle");

    if ((dest = fopen(dest_name, "wb")) == NULL) {
        printf("\nError: cannot open %s.\n", dest_name);
        exit(EXIT_FAILURE);
    }

    next_char = getc(src);
    prev_char = 0;
    while (prev_char != EOF) {
        for (i = 0; i < LINE_LEN; i++) {
            prev_char = next_char;
            next_char = getc(src);

            if (next_char == prev_char)
                rep_count++;
            else if (prev_char != EOF) {
                fprintf(dest, "%02d %x ", rep_count, prev_char);
                rep_count = 1;
            }
        }
        fprintf(dest, "\n");
        i = 0;
    }
    
    fclose(src);
    fclose(dest);
    free(dest_name);

    return 0;
}
