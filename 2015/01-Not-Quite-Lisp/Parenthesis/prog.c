#include <stdio.h>
#include <stdlib.h>

void part1(const char filename[])
{
    printf("# Part 1 (%s)\n", filename);
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("Loading data file");
        exit(EXIT_FAILURE);
    }
    int level = 0;
    for (int c;  (c = fgetc(f))!= EOF; ) {
        switch(c) {
        case '(':
            level += 1;
            break;
        case ')':
            level += -1;
            break;
        }
    }
    fclose(f);
    printf ("- level = %d\n", level);
}

void part2(const char filename[])
{
    printf("# Part 2 (%s)\n", filename);
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("Loading data file");
        exit(EXIT_FAILURE);
    }
    int level = 0;
    int position = 0;
    for (int c;  (c = fgetc(f))!= EOF;) {
        position += 1;
        switch(c) {
        case '(':
            level += 1;
            break;
        case ')':
            level += -1;
            if (level == -1) {
                goto position_found;
            }
            break;
        }
    }
position_found:
    printf("- position = %d\n", position);
    fclose(f);
}

int main()
{
    // part1("../test3.txt");
    part1("../puzzle.txt");
    // part2("../test5.txt");
    part2("../puzzle.txt");
}
