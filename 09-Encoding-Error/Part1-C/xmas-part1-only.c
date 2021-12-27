/*
  Advent of Code 2020 - Day 9 - Encoding Error
  Part 1 only.
  Michel Billaud, 27 dec 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_DATA_SIZE 2000


bool isValid(long number, long window[], int window_size) {
	for (int i = 1; i < window_size; i++) {
		for (int j = 0; j < i; j++) {
			if (window[i] + window[j] == number) return true;
		}
	}
	return false;
}

void solve_puzzle(const char filename[], int preamble_size) {
	(void) preamble_size;
	printf("# Part 1, fichier %s\n", filename);
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
	printf("- %d nombres lus\n", nb_data);

	for (int i = preamble_size; i < nb_data; i++){
		if (! isValid(data[i], & data[i - preamble_size], preamble_size)) {
			printf("- invalid number %ld found at %d\n", data[i], i);
			break;
		}
	}
}

int main() {
   solve_puzzle("../example.txt", 5);
   solve_puzzle("../large.txt", 25);
}
