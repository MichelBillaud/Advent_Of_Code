#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Advent of Code 2020, day 1
// Michel Billaud, 12/12/2021

void part1(char filename[]);
void part2(char filename[]);

int main()
{
    printf("AOC 2020, Day 1\n");

    part1("../small.txt");
    part1("../large.txt");
    part2("../small.txt");
    part2("../large.txt");
}

int int_comparator( const void *p1, const void *p2)
{
    const int *i1 = p1, *i2 = p2;
    return *i1 - *i2;
}

size_t read_numbers(char filename[], int *numbers)
{
    FILE *datafile = fopen(filename, "r");
    if (datafile == NULL) {
        perror("reading data file");
        exit(EXIT_FAILURE);
    }
    size_t size = 0;

    for (int n; fscanf(datafile, "%d", &n) == 1; ) {
        numbers[size++] = n;
    }
    fclose(datafile);
    return size;
}

void print_array(char message[], int numbers[], size_t size) {
    printf("%s ", message);
	for (size_t i=0; i < size; i++) {
    	printf("%d ", numbers[i]);
    }
    printf("\n");
}

void part1(char filename[])
{
    // 1. read numbers from data file
    int numbers[500];
    size_t size = read_numbers(filename, numbers);

    // 2. Sort numbers
    qsort(numbers, size, sizeof (numbers[0]), int_comparator);

    // check order
	// print_array("data read:", numbers, size);

    // looking for 2020

    int *first = numbers, *last = numbers + size - 1;
    for (int sum; (sum = *first + *last) != 2020; ) {
        if (sum < 2020) {
            first++;
        } else {
            last--;
        }
    }
    printf("Part 1 File %s : %d * %d = %d\n",
           filename,
           *first, *last,
           *first * *last);

}

//
bool sorted_array_contains(int array[], size_t size, int value)
{
    // printf("searching for %d \n", value);
    int l = 0, r = size;
    while (l < r) {
        int m = (l+r)/2;
        if (value < array[m]) r = m;
        else if (value > array[m]) l = m+1;
        else return true;
    }
    return false;
}

void part2(char filename[])
{
    // 1. read numbers from data file
    int numbers[500];
    size_t size = read_numbers(filename, numbers);

    // 2. Sort numbers
    qsort(numbers, size, sizeof (numbers[0]), int_comparator);

 	// check order
	// print_array("data read:", numbers, size);
    // 3. search
    for (size_t i = 0; (i < size) && numbers[i] <= 2020; i++ ) {
        for (size_t j = i + 1; j < size && numbers[i] + numbers[j] <= 2020; j ++ ) {
            int last = 2020- numbers[i] -numbers[j];
			long product = numbers[i] * numbers[j] * last;
            if (sorted_array_contains(numbers, size, last)) {
                printf("Part 2 File %s : %d * %d * %d = %ld\n",
                       filename, numbers[i], numbers[j], last,
                       product);

                return;
            }
        }
    }
    printf("solution not found in %s\n", filename);
}
