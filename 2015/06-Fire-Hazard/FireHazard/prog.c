/*
	Advent of Code 2015 - day 6
    author. michel billaud.
    date-written. 2022-01-21
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

// Part 1 primitives

void toggle(bool *b)
{
    *b = ! *b;
}

void turn_on(bool *b)
{
    *b = true;
}
void turn_off(bool *b)
{
    *b = false;
}

void part1(const char filename[])
{
    printf("# Part 1 (%s)\n", filename);
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("Loading data file");
        exit(EXIT_FAILURE);
    }
    char word[10];
    bool grid[1000][1000] = { { false }};
    while (fscanf(f, "%s", word) == 1) {
        void (*action) (bool *);
        if (strcmp(word, "toggle") == 0) {
            action = toggle;
        } else {
            assert(strcmp(word, "turn") == 0);
            fscanf(f, "%s", word);
            if (strcmp(word, "on") == 0) {
                action = turn_on;
            } else {
                assert(strcmp(word, "off") == 0);
                action = turn_off;
            }
        }
        int x1, y1, x2, y2;
        int r = fscanf(f, "%d,%d through %d,%d",
                       &x1, &y1, &x2, &y2);
        assert(r == 4);
        for (int x = x1 ; x <= x2; x++) {
            for (int y = y1 ; y <= y2; y++) {
                action(& grid[x][y]);
            }
        }
    }
    int count = 0;
    for (int x = 0; x < 1000; x++) {
        for (int y = 0; y < 1000; y++) {
            if (grid[x][y]) count += 1;
        }
    }
    printf("- count = %d\n", count);
}

//
// Part 2
//

void increase(int *brightness)
{
    *brightness += 1;
}

void decrease(int *brightness)
{
    if (*brightness > 0) *brightness += -1;
}

void increase_twice(int *brightness)
{
    *brightness += 2;
}

void part2(const char filename[])
{
    printf("# Part 2 (%s)\n", filename);
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("Loading data file");
        exit(EXIT_FAILURE);
    }
    char word[10];
    int grid[1000][1000] = { { 0 }};
    while (fscanf(f, "%s", word) == 1) {
        void (*action) (int *);
        if (strcmp(word, "toggle") == 0) {
            action = increase_twice;
        } else {
            assert(strcmp(word, "turn") == 0);
            fscanf(f, "%s", word);
            if (strcmp(word, "on") == 0) {
                action = increase;
            } else {
                assert(strcmp(word, "off") == 0);
                action = decrease;
            }
        }
        int x1, y1, x2, y2;
        int r = fscanf(f, "%d,%d through %d,%d",
                       &x1, &y1, &x2, &y2);
        assert(r == 4);
        for (int x = x1 ; x <= x2; x++) {
            for (int y = y1 ; y <= y2; y++) {
                action(& grid[x][y]);
            }
        }
    }
    int count = 0;
    for (int x = 0; x < 1000; x++) {
        for (int y = 0; y < 1000; y++) {
            count += grid[x][y];
        }
    }
    printf("- total = %d\n", count);
}

int main(int argc, char* argv[])
{
    printf("AOC 2015 - Day 6\n");
    for (int i = 1; i < argc; i++) {
        part1(argv[i]);
        part2(argv[i]);
    }
    return EXIT_SUCCESS;
}
