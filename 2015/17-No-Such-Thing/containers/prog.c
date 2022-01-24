#define PUZZLE  "Advent of code 2015 day 17"

/*
  michel billaud
  24 jan 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define MAX_NB_CONTAINERS 50

int nb_containers;
int capacity[MAX_NB_CONTAINERS];
int total_capacity;

void process(const char filename[])
{
    printf("# Processing (%s)\n", filename);
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        perror("loading data file");
        exit(EXIT_FAILURE);
    }
    nb_containers = 0;
    total_capacity = 0;
    int c;
    while (fscanf(f, "%d", &c) == 1) {
        capacity[nb_containers++] = c;
        total_capacity += c;
    }
    fclose(f);
    printf("- %d containers\n- total capacity = %d\n",
           nb_containers, total_capacity);
}

// stupid brute force
void add_nb_ways(int quantity, int next, int *total)
{
    //printf("add_nb_ways(%d, %d, %d)\n", quantity, next, *total);
    if (quantity == 0) {
        *total += 1;
        return;
    }
    if (next == nb_containers) {
        return;
    }
    if (capacity[next] <= quantity) {
        add_nb_ways(quantity - capacity[next], next + 1, total);
    }
    add_nb_ways(quantity, next+1, total);
}

void part1(int quantity)
{
    int nb_ways = 0;
    add_nb_ways(quantity, 0, &nb_ways);
    printf("- part 1 : %d ways found\n", nb_ways);
}

void count_ways(int quantity, int containers_used, int next, int count[]) 
{
	// printf("count_ways(%d, %d, %d, ...)\n", quantity, containers_used, next);
	 if (quantity == 0) {
        count[containers_used] += 1;
        return;
    }
    if (next == nb_containers) {
        return;
    }
    if (capacity[next] <= quantity) {
        count_ways(quantity - capacity[next], containers_used + 1, next + 1, count);
    }
    count_ways(quantity, containers_used, next+1, count);
}

void part2(int quantity)
{
    // count by number of containers
    int count[MAX_NB_CONTAINERS + 1] = {0};
    count_ways(quantity, 0, 0, count);
    for (int i = 0; i <= MAX_NB_CONTAINERS; i++) {
        if (count[i] != 0) {
            printf("- part 2 : %d ways to use only %d containers\n",
                   count[i], i);
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    printf(PUZZLE "\n");
    process("../test.txt");
    part1(25);
    part2(25);
    printf("\n");
    process("../puzzle.txt");
    part1(150);
    part2(150);
    printf("\n");
    return EXIT_SUCCESS;
}
