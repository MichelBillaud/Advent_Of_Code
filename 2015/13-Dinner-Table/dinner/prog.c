/*
  michel billaud
  32 jan 2022
*/

#define PUZZLE  "Advent of code 2015 day 13"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

char names[20][20];
int nb_names;
int gain[20][20] = {{0}};

int index_of_name(const char name[])
{
    for (int i = 0; i < nb_names; i++) {
        if (strcmp(name, names[i]) == 0) return i;
    }
    strcpy(names[nb_names], name);
    return nb_names++;
}

bool get_first_cycle(int array[], int size)
{
    if (size <= 0) {
        return false;
    }
    for (int i = 0; i < size; i++) {
        array[i] =  i;
    }
    return true;
}

void swap(int *pa, int *pb)
{
    int tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}

bool get_next_cycle(int array[], int size)
{
    int suffix_start = size-1;
    while (suffix_start > 1
            &&  array[suffix_start - 1] >= array[suffix_start]) {
        suffix_start --;
    }
    if (suffix_start == 1) {
        return false;
    }
    int index = size -1;
    while (array[suffix_start - 1] > array[index]) {
        index --;
    }
    swap (& array[suffix_start - 1], & array[index]);
    for (int left = suffix_start, right = size - 1;
            left < right;
            left++, right-- ) {
        swap (& array[left], &array[right]);
    }

    return true;
}

int happiness(int cycle[], int nb)
{
    int first = cycle[0], last = cycle[nb-1];
    int h = gain[first][last] + gain[last][first];
    for (int i = 1; i < nb; i++) {
        int a = cycle[i-1], b = cycle[i];
        h += gain[a][b] + gain[b][a];
    }
    return h;
}


int optimal_happiness()
{
    int cycle[20];
    int best_happiness = INT_MIN;
    (void) get_first_cycle(cycle, nb_names);
    do {
        int h = happiness(cycle, nb_names);

        if (h > best_happiness) {
            best_happiness = h;
            printf("%4d : ", h);
            for (int i = 0; i < nb_names; i++) {
                printf("%s ", names[cycle[i]]);
            }
            printf("\n");
        } //  else  printf("%d,", h);
    } while(get_next_cycle(cycle, nb_names));
    return best_happiness;
}


void process(const char filename[])
{
    printf("# Processing (%s)\n", filename);
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        perror("loading data file");
        exit(EXIT_FAILURE);
    }
    for (char line[100]; fgets(line, 100, f) != NULL; ) {
        char name1[20], name2[20], action[20];
        int quantity;
        sscanf(line, "%s would %s %d happiness units by "
               "sitting next to %[^.]s.", name1, action, &quantity, name2);
        // printf ("- %s/%s %s %d\n", name1, name2, action, quantity);
        int n1 = index_of_name(name1);
        int n2 = index_of_name(name2);
        gain[n1][n2] = 	strcmp("gain", action) == 0
                        ? quantity
                        : -quantity;

    }
    /*
    printf("- gain matrix\n");
    for (int i=0; i < nb_names; i++) {
        for (int j=0; j <nb_names; j++) {
            printf("%4d", gain[i][j]);
        }
        printf("\n");
    }
    */
    fclose(f);

	int h1 = optimal_happiness();
	printf("- part 1 : %d\n", h1);
	(void) index_of_name("Me");
	int h2 = optimal_happiness();
	printf("- part 2 : %d\n", h2);
	
}


void tests()
{
    printf("# Tests\n");
    int cycle[5];
    get_first_cycle(cycle, 5);
    do {
        for (int i=0; i<5; i++) printf("%2d", cycle[i]);
        printf("\n");
    } while (get_next_cycle(cycle, 5));
    printf("- all tests passed\n");
}


int main(int argc, char *argv[])
{
    printf(PUZZLE "\n");

    if (argc == 1) {
        tests();
    } else {
        for (int i = 1; i < argc; i++) {
            process(argv[i]);
        }
    }

    return EXIT_SUCCESS;
}
