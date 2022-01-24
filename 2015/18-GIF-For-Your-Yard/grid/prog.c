#define PUZZLE  "Advent of code 2015 day 18"

/*
  michel billaud
  24 jan 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define SIZE 100
#define STEPS 100

bool grid[SIZE][SIZE];


bool occupied(int r, int c)
{
    return (0 <= r) && (r < SIZE)
           && (0 <= c) && (c < SIZE)
           && grid[r][c];
}

int nb_neighbours(int r, int c)
{
    int count = 0;
    for (int rr = r-1; rr <= r+1; rr++) {
        for (int cc = c-1; cc <= c+1; cc++) {
            if (((r != rr) || (c != cc)) && occupied(rr, cc)) {
                count += 1;
            }
        }
    }
    return count;
}

bool new_state(bool on, int nb)
{
    return (nb == 3) || ((nb == 2) && on);
}

void execute_step()
{
    int n[SIZE][SIZE];
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            n[r][c] = nb_neighbours(r, c);
        }
    }
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            grid[r][c] = new_state(grid[r][c], n[r][c]);
        }
    }
}


void load_data(const char filename[])
{
    printf("# Processing (%s)\n", filename);
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        perror("loading data file");
        exit(EXIT_FAILURE);
    }
    int row = 0;
    for (char line[200]; fgets(line, 200, f) != NULL; ) {
        for (int col = 0; col < SIZE; col++) {
            grid[row][col] = (line[col] == '#');
        }
        row++;
    }
    fclose(f);
}

void part1(const char filename[])
{
    load_data(filename);
    for (int step = 1; step <= STEPS; step++) {
        execute_step();
    }
    int count = 0;
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (grid[r][c]) count += 1;
        }
    }
    printf("- part 1 : %d lights on\n", count);
}

void part2(const char filename[])
{
    load_data(filename);
    grid[0][0] = true;
    grid[SIZE-1][0] = true;
    grid[SIZE-1][SIZE-1] = true;
    grid[0][SIZE-1] = true;

    for (int step = 1; step <= STEPS; step++) {
        execute_step();
        grid[0][0] = true;
        grid[SIZE-1][0] = true;
        grid[SIZE-1][SIZE-1] = true;
        grid[0][SIZE-1] = true;
    }
    int count = 0;
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (grid[r][c]) count += 1;
        }
    }
    printf("- part 2 : %d lights on\n", count);
}

int main(int argc, char *argv[])
{
    printf(PUZZLE "\n");

    for (int i = 1; i < argc; i++) {
        part1(argv[i]);
        part2(argv[i]);
    }
    return EXIT_SUCCESS;
}
