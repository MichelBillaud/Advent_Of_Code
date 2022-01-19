#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// AOC 2015 - Day 2 - No Math

int paper_needed(int x, int y, int z) {
	int max = x, little = y * z;
	if (y > max) { max = y; little = x * z; }
	if (z > max) { max = z; little = x * y; }
	return 2*(x*y + x*z + y*z) + little;
}

void part1(const char filename[])
{
    printf("# Part 1 (%s)\n", filename);
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("Cant open data file");
        exit (EXIT_FAILURE);
    }
	int total = 0;
    while (true) {
        int x, y, z;
		if (3 != fscanf(f, "%dx%dx%d", &x, &y, &z)) break;
		int paper = paper_needed(x, y, z);
		// printf ("-> %d %d %d = %d\n", x, y, z, paper);
		total += paper;
    }
	printf("- total paper= %d\n", total);
	fclose(f);
}

int ribbon_needed(int x, int y, int z) {
	int max = x, perimeter = 2*(y + z);
	if (y > max) { max = y; perimeter = 2*(x + z); }
	if (z > max) { max = z; perimeter = 2*(x + y); }
	return  x*y*z + perimeter;
}


void part2(const char filename[])
{
    printf("# Part 2 (%s)\n", filename);
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("Cant open data file");
        exit (EXIT_FAILURE);
    }
	int total = 0;
    while (true) {
        int x, y, z;
		if (3 != fscanf(f, "%dx%dx%d", &x, &y, &z)) break;
		int ribbon = ribbon_needed(x, y, z);
		// printf ("-> %d %d %d = %d\n", x, y, z, ribbon);
		total += ribbon;
    }
	printf("- total ribbon = %d\n", total);
	fclose(f);
}

int main()
{
    part1("../test43.txt");
	part1("../puzzle.txt");
	part2("../test43.txt");
	part2("../puzzle.txt");
}
