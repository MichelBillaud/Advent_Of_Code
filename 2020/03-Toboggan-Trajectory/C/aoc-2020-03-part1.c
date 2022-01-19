#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// AOC 2020 day 3 
// michel billaud 12 dec 2021

void process(const char filename[]);

int main()
{
    printf("AOC 2020 day 2 - Toboggan-Trajectory\n");
    process("../small.txt");
    process("../large.txt");
    return EXIT_SUCCESS;
}

void process(const char filename[])
{
    FILE * datafile = fopen(filename, "r");
    if (datafile == NULL) {
        perror("reading datafile");
        exit(EXIT_FAILURE);
    }
	char line[100]; 
	int position = 0;
	int nb_trees = 0;
	while (fgets(line, 100, datafile) != NULL) {
		// printf("-> %s", line);
		int len = strchr(line, '\n') - line;
		// printf("len = %d\n", len);
		if (line[position] == '#') {
			nb_trees += 1;
		}
		// line[position] = line[position] == '#' ? 'X' : 'O';
		// printf("%s", line);
		position = (position + 3) % len;
	}
	printf("Part 1, file '%s', encountered %d trees\n", filename, nb_trees);
	fclose(datafile);
}