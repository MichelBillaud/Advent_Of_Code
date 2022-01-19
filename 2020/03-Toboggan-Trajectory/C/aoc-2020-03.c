#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// AOC 2020 day 3
// michel billaud 12 dec 2021

/*
	In part #2, the file has to be processed wrt. 5 different slopes descriptions
	instead of 1.

    Design decision : As file operations are slow, we read the file only once, 
    and we manage an array of slopes.
*/

struct slope {
    int right, down;
    int nb_trees;
};

/*
    Refactoring
    - former part 1 is generalized to count tree for an array of slopes. 
    - Part 1 now uses an array of only 1 slope, et displays its tree number.
    - Part 5 uses an array of 5 slopes, et displays the product of tree numbers.
*/

void process(const char filename[], struct slope slopes[], int nb_slopes);
void part1(const char filename[]);
void part2(const char filename[]);


int main()
{
    printf("AOC 2020 day 2 - Toboggan-Trajectory\n");
    part1("../small.txt");
    part1("../large.txt");

    part2("../small.txt");
    part2("../large.txt");

    return EXIT_SUCCESS;
}

// --------------------------------------------------
void process(const char filename[],
             struct slope slopes[], int nb_slopes )
{
    FILE * datafile = fopen(filename, "r");
    if (datafile == NULL) {
        perror("reading datafile");
        exit(EXIT_FAILURE);
    }
    int line_number = 0;
    char line[100];
    int position = 0;
    int nb_trees = 0;
    while (fgets(line, 100, datafile) != NULL) {
        int len = strchr(line, '\n') - line;
        for (int s = 0; s < nb_slopes; s++) {
            // a slope is processed every "down" lines
            if (line_number % slopes[s].down == 0) {
                int position = (line_number / slopes[s].down)
                               * slopes[s].right;
                if (line[position % len] == '#') {
                    slopes[s].nb_trees += 1;
                }
            }
        }
        line_number += 1;
    }
    fclose(datafile);
}

// --------------------------------------------------------

void part1(const char filename[])
{
    struct slope slopes[] = {{ .right = 3, .down = 1 }};
    process(filename, slopes, 1);
    printf("Part 1, file '%s', encountered %d trees\n",
           filename, slopes[0].nb_trees);
}

void part2(const char filename[])
{
    struct slope slopes[] = {
        { .right = 1, .down = 1 },
        { .right = 3, .down = 1 },
        { .right = 5, .down = 1 },
        { .right = 7, .down = 1 },
        { .right = 1, .down = 2 },
    };
    process(filename, slopes, 5);
    int product = 1;
    printf("Part 2, file '%s' [", filename);
    for (int s = 0; s < 5; s++) {
        product *= slopes[s].nb_trees;
        printf("%d ", slopes[s].nb_trees);
    }
    printf("] => %d\n", product);
}
