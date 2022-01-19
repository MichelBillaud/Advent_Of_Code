#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// AOC 2020 Custom Customs - part 1 only
// Michel Billaud, 2021/12/14

typedef unsigned long long mask;

mask questions(char string[]) {
	mask m = 0;
	for (int i = 0; string[i] != '\n'; i++) {
		m |= (1LL << (string[i] - 'a'));
	}
	// printf("%llx for %s", m, string);
	return m;
}

int bitcount(mask m)
{
    int c = 0;
    while (m) {
        c += m & 1;
        m >>= 1;
    }
    return c;
}

void part1(const char filename[])
{
    FILE *datafile = fopen(filename, "r");
    if (datafile == NULL) {
        perror("reading data file");
        exit(EXIT_FAILURE);
    }
    mask group_questions = 0; // binary mask
    char line[100];
    int total = 0;
    while (fgets(line, 100, datafile) != NULL) {

		if (isalpha(line[0])) {
            group_questions |= questions(line);
        } else {
            total += bitcount(group_questions);
            group_questions = 0;
        }
    }
    total += bitcount(group_questions);
    fclose(datafile);
    printf("Part 1 file '%s' total %d questions\n",
           filename, total);
}

int main()
{
    printf("AOC 2020 Day 6 Custom Customs - part 1\n");
	
    part1("../small.txt");
	part1("../large.txt");

    return EXIT_SUCCESS;
}
