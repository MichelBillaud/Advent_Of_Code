/*
	AOC 2015 Day 11 part 1 (cheating!)
	michel billaud
	23 jan 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

// [!!!]
//  we're cheating (supposing no strings or identifiers
// contain digits or minus)
// [!!!]

void process(const char filename[])
{
    printf("# Processing (%s)\n", filename);
    int total = 0;
    int signum = 1;
    int number = 0;
    bool inside_number = false;
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        perror("loading data file");
        exit(EXIT_FAILURE);
    }
    for (int c; (c = fgetc(f)) != EOF; ) {
        if (inside_number) {
            if (isdigit(c)) {
                number = 10 * number + c - '0';
            } else {
                total += signum * number;
                signum = 1;
                number = 0;
                inside_number = false;
            }
            // no adjacent sign or digit, ignore
        } else {
            if (c == '-') {
                signum = -1;
                inside_number = true;
            } else if (isdigit(c)) {
                number = c - '0';
                inside_number = true;
            }
        }
    }
    // should not happen
    if (inside_number) {
        total += signum * number;
    }
    fclose(f);
    printf("- total %d\n", total);
}




int main(int argc, char *argv[])
{
    printf("AOC 105 - day 11\n");

    for (int i = 1; i < argc; i++) {
        process(argv[i]);
    }
    return EXIT_SUCCESS;
}
