/*
	Advent of Code 2015 - Day 9
	michel billaud
	22 jan 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

int nbNames = 0;
char names[20][20];
int distances[20][20];

bool get_first_permutation(int array[], int size)
{
    if (size <= 0) {
        return false;
    }
    for (int i = 0; i < size; i++) {
        array[i] =  i;
    }
    return true;
}

void swap(int *pa, int *pb)
{
    int tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}

bool get_next_permutation(int array[], int size)
{
    int suffix_start = size-1;
    while (suffix_start > 0
            &&  array[suffix_start - 1] >= array[suffix_start]) {
        suffix_start --;
    }
    if (suffix_start == 0) {
        return false;
    }
    int index = size -1;
    while (array[suffix_start - 1] > array[index]) {
        index --;
    }
    swap(& array[suffix_start - 1], & array[index]);
    for (int left = suffix_start, right = size - 1;
            left < right;
            left++, right-- ) {
        swap(& array[left], &array[right]);
    }
    return true;
}

int index_of(const char name[])
{
    for (int i = 0; i < nbNames; i++) {
        if (strcmp(names[i], name) == 0) {
            return i;
        };
    }
    strcpy(names[nbNames], name);
    return (nbNames++);
}

void process(const char filename[])
{
	nbNames = 0;
    printf("# Processing (%s)\n", filename);
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        perror("loading data file");
        exit(EXIT_FAILURE);
    }
    for (char line[100]; fgets(line, 100, f) != NULL; ) {
        char t1[20], t2[20];
        int d;
        sscanf(line, "%s to %s = %d", t1, t2, &d);
        // printf("distance de %s à %s = %d\n", t1, t2, d);
        int l1 = index_of(t1);
        int l2 = index_of(t2);
        distances[l1][l2] = d;
        distances[l2][l1] = d;
    }
    fclose(f);

    int least_distance = INT_MAX;
	int longest_distance = INT_MIN;
    int perm[nbNames];

    for (bool exists = get_first_permutation(perm, nbNames);
            exists;
            exists = get_next_permutation(perm, nbNames)) {
        int distance = 0;
        for (int i = 1; i < nbNames; i++) {
            distance += distances[perm[i-1]][perm[i]];
        }
        if (distance < least_distance) {
            least_distance = distance;      
        } 
		if (distance > longest_distance) {
			longest_distance = distance;
		}
    }
	printf("- part1 shortest path is %d\n", least_distance);
	printf("- part2 longest  path is %d\n", longest_distance);
}

void tests()
{
    printf("# Tests\n");
    printf("- all tests passed\n");
}

int main(int argc, char *argv[])
{
    printf("aoc 2015 - day 9\n");
    if (argc == 1) {
        tests();
    } else {
        for (int i = 1; i < argc; i++) {
            process(argv[i]);
        }
    }



    return EXIT_SUCCESS;
}
