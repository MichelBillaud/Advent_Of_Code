#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// AOC 2020 Custom Customs - parts 1 and 2
// Michel Billaud, 2021/12/14

typedef unsigned long long mask;

/*
ANALYSIS.
     In part 1, we add the points for every group, 
    which were the number of questions answered positively
    for the members of the group. That is the union of
    the set of questions by each member of the group.

    In part 2, we consider the intersection instead of a union.

REFACTORING.
    This suggests the file processing routine to be parameterized by
    - the operation to be applied (union for part1, intersection for part 2)
    - the initial value of the set (empty for part1, all questions for part 2)

*/

#define EMPTY_MASK 0LL

mask questions(char string[])
{
    mask m = 0;
    for (int i = 0; string[i] != '\n'; i++) {
        m |= (1LL << (string[i] - 'a'));
    }
    return m;
}

// "Kernighan's method", actually by Peter Wegner 1960
// https://dl.acm.org/doi/10.1145/367236.367286

int bitcount(mask m)  {
    int c = 0; 
    while (m) {
        c++;
        m &= (m-1);
    }
    return c;
}

mask mask_or(mask m1, mask m2)
{
    return m1 | m2;
}

mask mask_and(mask m1, mask m2)
{
    return m1 & m2;
}

int total_points(const char filename[],
                 mask initial_mask,
                 mask (*combiner)(mask, mask))
{
    FILE *datafile = fopen(filename, "r");
    if (datafile == NULL) {
        perror("reading data file");
        exit(EXIT_FAILURE);
    }
    mask group_questions = initial_mask; // binary mask
    char line[100];
    int total = 0;
    while (fgets(line, 100, datafile) != NULL) {

        if (isalpha(line[0])) {
            group_questions = combiner(questions(line), group_questions);
        } else {
            total += bitcount(group_questions);
            group_questions = initial_mask;
        }
    }
    total += bitcount(group_questions);  // last group
    fclose(datafile);
    return total;
}

void part1(const char filename[])
{
    printf("Part 1 file '%s' total %d questions\n",
           filename, total_points(filename, EMPTY_MASK, mask_or));
}

void part2(const char filename[])
{
    printf("Part 2 file '%s' total %d questions\n",
           filename, total_points(filename, ~EMPTY_MASK, mask_and));
}


int main()
{
    printf("AOC 2020 Day 6 Custom Customs - parts 1 & 2\n");

    part1("../small.txt");
    part1("../large.txt");

    part2("../small.txt");
    part2("../large.txt");

    return EXIT_SUCCESS;
}
