/*
  Advent of Code 2020 - Day 9 - Encoding Error
  Parts 1 and 2.
  Michel Billaud, 27 dec 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef VERBOSE
#define VERBOSE false
#endif

#define MAX_DATA_SIZE 2000


bool isValid(long number, const long window[], int window_size)
{
    for (int i = 1; i < window_size; i++) {
        for (int j = 0; j < i; j++) {
            if (window[i] + window[j] == number) return true;
        }
    }
    return false;
}

long first_invalid_number(const long data[], int nb_data, int preamble_size)
{
    for (int i = preamble_size; i < nb_data; i++) {
        if (! isValid(data[i], & data[i - preamble_size], preamble_size)) {
            return (data[i]);
        }
    }
    return -1L;
}


long  encryption_weakness( long number, const long data[], int nb_data)
{
    for (int start = 0; start < nb_data-1; start ++) {
        long sum = data[start], min = sum, max = sum;
        int i = start + 1;
        do {
            if (data[i] < min) min = data[i];
            if (data[i] > max) max = data[i];
            sum += data[i];
            if (sum > number) break;
            if (sum == number) {
                if (VERBOSE) {
                    printf("Numbers are:`\n");
                    for (int j = start; j <= i; j++) {
                        printf("\t%15ld\n", data[j]);
                    }
                    printf("min\t%15ld\n", min);
                    printf("max\t%15ld\n", max);
                }

                return min + max;
            }
            i += 1;
        } while (i < nb_data);
    }
    return -1L;
}

void solve_puzzle(const char filename[], int preamble_size)
{
    (void) preamble_size;
    printf("# Part 1 (refactored), data file is %s\n", filename);
    long data[MAX_DATA_SIZE];
    int nb_data = 0;
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("Loading data");
        exit(EXIT_FAILURE);
    }
    while (1 == fscanf(f, "%ld", &data[nb_data])) {
        nb_data += 1;
    };
    fclose(f);
    printf("- %d numbers read\n", nb_data);

    long invalid = first_invalid_number(data, nb_data, preamble_size);
    printf("- invalid number %ld found.\n", invalid);

    printf("# Part 2\n");
    printf("- weakness is %ld\n", encryption_weakness(invalid, data, nb_data));
    printf("\n");

}


int main()
{
    solve_puzzle("../example.txt", 5);
    solve_puzzle("../large.txt", 25);
}
