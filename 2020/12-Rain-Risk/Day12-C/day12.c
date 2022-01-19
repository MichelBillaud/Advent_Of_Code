/*
	Advent Of Code 2020 - Day 12 -  Rain Risk
	*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int D[] = {0, -1, 0, 1, 0}; // N W S E

typedef enum dir_t { NORTH, WEST, SOUTH, EAST} dir_t;

typedef struct state_t {
    long x, y, wx, wy;
    dir_t dir;
} state_t;

//
// utilities for part 1
//
void move_ship_forward(state_t *s, int v)
{
    s->x += v * D[s->dir];
    s->y += v * D[s->dir + 1];
}

void turn_ship_left(state_t *s, int quarters)
{
    s->dir = (s->dir + quarters) % 4;
}

void move_ship_to_direction(state_t *s, dir_t dir, int v)
{
    s->x += v * D[dir];
    s->y += v * D[dir+1];
}

long manhattan_distance(state_t *s)
{
    return labs(s->x) + labs(s->y);
}

//
// part 1
//

void part1(const char filename[])
{
    printf("# Part 1 refactored (%s)\n", filename);
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("reading data");
        exit (EXIT_FAILURE);
    }
    char command;
    int value;
    state_t state = {.x = 0, .y = 0, .dir = EAST };

    while(fscanf(f, "%c%d ", &command, &value) == 2) {
        // printf("c = %c, v = %d\n", command, value);
        switch (command) {
        case 'F' :
            move_ship_forward(&state, value);
            break;
        case 'B' :
            move_ship_forward(&state, -value);
            break;

        case 'L' :
            turn_ship_left(&state, value/90);
            break;
        case 'R' :
            turn_ship_left(&state, 4 - value/90);
            break;

        case 'N' :
            move_ship_to_direction(&state, NORTH, value);
            break;
        case 'W' :
            move_ship_to_direction(&state, WEST, value);
            break;
        case 'S' :
            move_ship_to_direction(&state, SOUTH, value);
            break;
        case 'E' :
            move_ship_to_direction(&state, EAST, value);
            break;
        default:
            printf("UNKNOWN COMMAND %c", command);
            exit(EXIT_FAILURE);
        }
        // printf("- position %d,%d dir %c\n", x, y, "NWSE"[d]);

    }

    printf("- final position %ld,%ld\n", state.x, state.y);
    printf("- manhattan distance = %ld\n", manhattan_distance(& state));
    printf("\n");
    fclose(f);
}

//
// Utilities for part 2

const int R[] = {1,0,0,1,-1,0,0,-1,1,0};

void move_ship_to_waypoint(state_t *s, int steps)
{
    s->x += steps * s->wx;
    s->y += steps * s->wy;
}

void move_waypoint(state_t *s, dir_t dir, int distance)
{
    s->wx += distance * D[dir];
    s->wy += distance * D[dir+1];
}

void turn_waypoint_left(state_t *s, dir_t dir)
{

    long wx =  R[2*dir + 0] * s->wx + R[2*dir + 1] * s->wy;
    long wy =  R[2*dir + 2] * s->wx + R[2*dir + 3] * s->wy;
    s->wx = wx;
    s->wy = wy;
    
}

void part2(const char filename[])
{
    printf("# Part 2 (%s)\n", filename);
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("reading data");
        exit (EXIT_FAILURE);
    }
    state_t state = { .x = 0, .y = 0, .wx = 10, .wy = -1 };
    char command;
    int value;

    while(fscanf(f, "%c%d ", &command, &value) == 2) {
        // printf("c = %c, v = %d\n", command, value);
        switch (command) {
        case 'F' :
            move_ship_to_waypoint(&state, value);
            break;
        case 'B' :
            move_ship_to_waypoint(&state, -value);
            break;

        case 'L' :
            turn_waypoint_left(&state, value/90);
            break;

        case 'R' :
            turn_waypoint_left(&state,  4 - value/90);
            break;

        case 'N' :
            move_waypoint(&state, NORTH, value);
            break;
        case 'W' :
            move_waypoint(&state, WEST, value);
            break;
        case 'S' :
            move_waypoint(&state, SOUTH, value);
            break;
        case 'E' :
            move_waypoint(&state, EAST, value);
            break;
        default:
            printf("UNKNOWN COMMAND %c", command);
            exit(EXIT_FAILURE);
        }
        /*
        printf("-%c%d\tposition %ld,%ld\t waypoint %ld,%ld \n",
            command, value,
            state.x, state.y, state.wx, state.wy);
            */
    }
  
    printf("- final position %ld,%ld\n", state.x, state.y);
    printf("- manhattan distance = %ld\n", manhattan_distance(&state));
    printf("\n");
    fclose(f);
}


int main()
{
    printf("AOC 2020 - Day 12\n");
    part1("../small.txt");
    part1("../large.txt");

    part2("../small.txt");
    part2("../large.txt");

    return EXIT_SUCCESS;
}
