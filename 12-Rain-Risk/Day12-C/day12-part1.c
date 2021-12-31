/*
	Advent Of Code 2020 - Day 12 -  Rain Risk
    part 1 only
	*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int D[] = {0, -1, 0, 1, 0}; // N W S E

void part1(const char filename[])
{
    printf("# Part 1 (%s)\n", filename);
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("reading data");
        exit (EXIT_FAILURE);
    }
    char command;
    int value;
    int x = 0, y = 0, d = 3;
    while(fscanf(f, "%c%d ", &command, &value) == 2) {
        // printf("c = %c, v = %d\n", command, value);
        switch (command) {
        case 'F' :
            x += value *D[d];
            y += value *D[d+1];
            break;
        case 'B' :
            x -= value *D[d];
            y -= value *D[d+1];
            break;

        case 'L' :
            d = (d + value/90) % 4;
            break;
        case 'R' :
            d = (d + 4 - value/90) % 4;
            break;

        case 'N' :
            x += value *D[0];
            y += value *D[1];
            break;
        case 'W' :
            x += value *D[1];
            y += value *D[2];
            break;
        case 'S' :
            x += value *D[2];
            y += value *D[3];
            break;
        case 'E' :
            x += value *D[3];
            y += value *D[4];
            break;
        default:
            printf("UNKNOWN COMMAND %c", command);
            exit(EXIT_FAILURE);
        }
        // printf("- position %d,%d dir %c\n", x, y, "NWSE"[d]);

    }

    printf("- final position %d,%d\n", x, y);
    printf("- manhattan distance = %d\n", abs(x) + abs(y));
    printf("\n");
    fclose(f);
}


int main()
{
    printf("AOC 2020 - Day 12 - part 1 only\n");

    part1("../small.txt");
    part1("../large.txt");

    return EXIT_SUCCESS;
}
