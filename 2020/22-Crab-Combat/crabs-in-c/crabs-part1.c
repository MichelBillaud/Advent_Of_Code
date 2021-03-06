/* 
    Advent of Code 2021 - Day 22 - Crab Combat - part 1
    Michel Billaud 13 jan 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DECK_MAX_SIZE 128
#define LINE_SIZE 80

typedef struct deck {
    int player;
    int top;
    int size;
    int data[DECK_MAX_SIZE];
} deck;

void deck_display(const deck *d)
{
    printf("Player %d's deck:", d->player);
    char sep = ' ';
    for (int i = 0; i < d->size; i++) {
        int index = (d->top + i) % DECK_MAX_SIZE;
        printf("%c %d", sep, d->data[index]);
        sep = ',';
    }
    printf("\n");
}

void deck_add(deck *d, int number)
{
    int index = (d->top + d->size) % DECK_MAX_SIZE;
    d->data[index] = number;
    d->size += 1;
}

bool deck_is_empty(const deck *d)
{
    return d->size == 0;
}

int deck_get_top(deck *d)
{
    int value = d->data[d->top];
    d->top = (d->top + 1) % DECK_MAX_SIZE;
    d->size += -1;
    return value;
}

int deck_score(const deck * d)
{
    int score = 0;
    int weight = d->size;
    for (int i = 0; i < d->size; i++) {
        int index = (d->top + i) % DECK_MAX_SIZE;
        score += d->data[index] * weight;
        weight += -1;
    }
    return score;

}


void read_deck(FILE *f, deck *d)
{
    char line[LINE_SIZE];
    // ignore first
    fgets(line, LINE_SIZE, f);
    // read numbers for deck 1
    while (true) {
        if (NULL == fgets(line, LINE_SIZE, f)) break;
        int number;
        if (1 != sscanf(line, "%d", &number)) break;
        deck_add(d, number);
    }
}

void part1(const char *filename)
{
    deck deck1 = { .player = 1 },
         deck2 = { .player = 2 };
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        perror("Loading data file");
        exit(EXIT_FAILURE);
    }
    read_deck(f, &deck1);
    read_deck(f, &deck2);
    fclose(f);

    int game_winner = 0;
    int game_winner_score = 0;
    for (int round = 1; ; round++) {
        printf("-- Round %d ---\n", round);
        deck_display( &deck1);
        deck_display( &deck2);

        if (deck_is_empty(& deck2)) {
            game_winner = 1;
            game_winner_score = deck_score(& deck1);
            break;
        }
        if (deck_is_empty(& deck1)) {
            game_winner = 2;
            game_winner_score = deck_score(& deck2);
            break;
        }
        int top1 = deck_get_top(&deck1);
        int top2 = deck_get_top(&deck2);
        printf("Player 1 plays: %d\n", top1);
        printf("Player 2 plays: %d\n", top2);

        int round_winner = 0;
        if (top1 > top2) {
            round_winner = 1;
            deck_add(& deck1, top1);
            deck_add(& deck1, top2);
        } else {
            round_winner = 2;
            deck_add(& deck2, top2);
            deck_add(& deck2, top1);
        }
        printf("Player %d wins the round!\n\n", round_winner);
    }


    printf("\nPlayer %d wins the game (%s) with %d points!\n",
           game_winner, filename, game_winner_score);
}


int main()
{
    printf("Hello, crabs!\n");
    part1("../small.txt");
part1("../large.txt");

    return EXIT_SUCCESS;
}
