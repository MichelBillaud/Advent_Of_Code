#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 2000


int int_natural_order(const void *p1, const void *p2)
{
    const int *i1 = p1, *i2 = p2;
    return *i1 - *i2;
}

int  get_sequence(const char filename[], int numbers[])
{
    int nb_numbers = 1;
    numbers[0] = 0;
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("reading data");
        exit(EXIT_FAILURE);
    }

    for (int n; fscanf(f, "%d", &n) == 1; ) {
        numbers[nb_numbers ++] = n;
    }
    fclose(f);

    qsort(numbers, nb_numbers, sizeof(numbers[0]), int_natural_order);
    int last = numbers[nb_numbers - 1];
    numbers[nb_numbers++] = last + 3;
    return nb_numbers;
}

void part1(const char filename[])
{
    printf("# Part 1 (%s)\n", filename);
    int numbers[MAX_SIZE];
    numbers[0] = 0;
    int nb_numbers = get_sequence(filename, numbers);

    int diff[3] = {0};
    for (int i = 1; i < nb_numbers; i++) {
        diff[numbers[i] - numbers[i-1]] += 1;
    }
    printf("- d1 = %d, d3 = %d, solution = %d\n",
           diff[1], diff[3], diff[1]*diff[3]);
}


void part2(const char filename[])
{
	  printf("# Part 1 (%s)\n", filename);
    int numbers[MAX_SIZE];
    numbers[0] = 0;
    int nb_numbers = get_sequence(filename, numbers);
    long count[MAX_SIZE];
    count[0] = 1;
    for (int i = 1; i < nb_numbers; i++) {
        count[i] = 0;
        for (int p = i-1; (p >= 0) && (numbers[i] - numbers[p] <= 3); p--) {
            count[i] += count[p];
        }
    }
    printf("- There are %ld distinct ways to connect the outlets\n", count[nb_numbers-1]);
}


int main()
{
    part1("../first.txt");
    part1("../second.txt");
    part1("../large.txt");

    part2("../first.txt");
    part2("../second.txt");
    part2("../large.txt");
}