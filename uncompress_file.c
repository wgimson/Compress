/* Decompresses a file using the fscanf() function, reading two decimal 
 * places, one or more spaces, and two hexidecimal places at a time. This 
 * represents a single character/repetition pair in the run-length encoded
 * file. If the decimal number is one, then the hexidecmal number is casted
 * to a char type and printed in the destination file. If the decimal number
 * is greater than one, the hexidecimal number is repeatedly cast to a char
 * type and printed to the source file as many times. This program illustrates
 * the power of the fscanf() function - implementation would have been much
 * more difficult using something like getc(). */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *src, *dest;
    unsigned int ch;
    int i, rep_count, num_begin_chars;
    char *dest_name, *src_ends, *passed_string;
    
    if (argc != 2) {
        printf("\nUsage: uncompress_file file.\n");
        exit(EXIT_FAILURE);
    }

    num_begin_chars = strlen(argv[1]) - 4;
    src_ends = malloc(4);
    passed_string = argv[1];
    strcpy(src_ends, passed_string + num_begin_chars);

    if (strcmp(src_ends, ".rle") != 0) {
        printf("\nError: file must end in \".rle\".\n");
        exit(EXIT_FAILURE);
    }
    
    free(src_ends);

    if ((src = fopen(argv[1], "rb")) == NULL) {
        printf("\nError: cannot open %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    passed_string = argv[1] + num_begin_chars;
    strcpy(passed_string, "\0");
    dest_name = malloc(num_begin_chars);
    strcpy(dest_name, argv[1]);
    if ((dest = fopen(dest_name, "wb")) == NULL) {
        printf("\nError: cannot open %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (fscanf(src, "%2d %2x", &rep_count, &ch) != EOF) {
        if (rep_count > 1) {
            for (i = 0; i < rep_count; i++) {
                putc((char) ch, dest);
            }
        } else {
            putc((char) ch, dest);
        }
    }

    free(dest_name);
    return 0;
}
