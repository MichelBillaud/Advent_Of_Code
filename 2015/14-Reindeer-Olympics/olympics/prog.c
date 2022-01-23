#define PUZZLE  "Advent of code 2015 day 14"

/*
  michel billaud
  23 jan 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

typedef struct s_reindeer {
    char name[20];
    int speed;
    int fly_duration;
    int rest_duration;
} reindeer;

int min(int a, int b)
{
    return a < b ? a : b;
}

int distance(const reindeer *r, int duration)
{
    int nb_cycles = duration / (r->fly_duration + r->rest_duration);
    int extra =  duration % (r->fly_duration + r->rest_duration);

    int fly_duration = nb_cycles * r->fly_duration
                       + min(extra, r->fly_duration);
    return fly_duration * r->speed;
}

reindeer reindeers[20];
int nb_reindeers;

void load_data(const char filename[])
{
    nb_reindeers = 0;
    printf("# Processing (%s)\n", filename);
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        perror("loading data file");
        exit(EXIT_FAILURE);
    }

    for (char line[100]; fgets(line, 100, f) != NULL; ) {
        //
        reindeer r;
        sscanf(line, "%s can fly %d km/s for %d seconds, "
               "but then must rest for %d seconds.",
               r.name, & r.speed,
               &r.fly_duration, &r.rest_duration);
        reindeers[nb_reindeers++] = r;
    }
    fclose(f);

}

void part1(int limit)
{
    int best_distance = INT_MIN;
    int winner = -1;
    for (int i = 0; i < nb_reindeers; i++) {
        int d = distance(& reindeers[i], limit);
        if (d > best_distance) {
            best_distance = d;
            winner = i;
        }
    }
    printf("- Part 1 : After %d, winner is %s at distance %d\n",
           limit, reindeers[winner].name, best_distance);

}

void part2(int limit)
{
    int score[20] = {0};
    for (int time = 1; time <= limit; time++) {
        int best_distance = INT_MIN;
        int d[20];
        for (int i = 0; i < nb_reindeers; i++) {
            d[i]= distance(& reindeers[i], time);
            if (d[i] > best_distance) best_distance = d[i];
        }
        for (int i = 0; i < nb_reindeers; i++) {
            if (d[i] == best_distance) score[i] += 1;
        }
    }

    int best_score = 0;
    for (int i = 0; i < nb_reindeers; i++) {
        if (score[i] > best_score) best_score = score[i];
    }
    printf("- part 2 best score : %d\n", best_score);
}

void process(const char filename[], int limit)
{
    load_data(filename);
    part1(limit);
    part2(limit);
}


int main(int argc, char *argv[])
{
    printf(PUZZLE "\n");

    for (int i = 1; i < argc; i++) {
        process(argv[i], 2503);
    }

    return EXIT_SUCCESS;
}
