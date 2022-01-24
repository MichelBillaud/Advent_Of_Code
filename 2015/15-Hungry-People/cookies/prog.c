#define PUZZLE  "Advent of code 2015 day 15"

/*
  michel billaud
  24 jan 2022
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

bool get_first_decomposition(int array[], int size, int value)
{
    if (value < 0) return false;
    for (int i = 0; i < size-1; i++) {
        array[i] = 0;
    }
    array[size-1] = value;
    return true;
}

bool get_next_decomposition(int array[], int size, int value)
{
    if (array[0] == value) return false;
    int index = size - 1;
    while (array[index] == 0) {
        index--;
    }
    // if (index == 0) return false;
    int v = array[index];
    array[index - 1] += 1;
    array[index] = 0;
    array[size - 1] = v -1;
    return true;
}

// ----------------------------------------------------

struct s_properties {
    int coeff[5];
};

struct s_ingredient {
    char name[20];
    struct s_properties properties;
};

int nb_ingredients;
struct s_ingredient ingredients[10];

struct s_properties cookie_properties(int quantities[])
{
    struct s_properties props = { 0};
    for (int i = 0; i < nb_ingredients; i++) {
        for (int p = 0; p < 5; p++) {
            props.coeff[p] += quantities[i] * ingredients[i].properties.coeff[p];
        }
    }
    return props;
}

long cookie_score(struct s_properties props)
{
    long product = 1;
    for (int p = 0; p < 4; p++) {  // IGNORE CALORIES
        product *= props.coeff[p];
        if (product < 0) product = 0;
    }
    return product;
}

long cookie_calories(struct s_properties props)
{
	return props.coeff[4];
}

void load_data(const char filename[])
{
    nb_ingredients = 0;
    printf("# Processing (%s)\n", filename);
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        perror("loading data file");
        exit(EXIT_FAILURE);
    }
    for (char line[100]; fgets(line, 100, f) != NULL; ) {
        struct s_ingredient s;
        int r = sscanf(line,
                       "%[^:]: capacity %d, durability %d, flavor %d, "
					   "texture %d, calories %d ",
                       s.name, & s.properties.coeff[0], & s.properties.coeff[1],
                       & s.properties.coeff[2], & s.properties.coeff[3],
					   & s.properties.coeff[4]);
        assert(r == 6);
        ingredients[nb_ingredients++] = s;
    }
    fclose(f);
    for (int i = 0; i < nb_ingredients; i++) {
        printf("%s ->", ingredients[i].name);
        for (int p = 0; p < 5; p++) {
            printf("%d ", ingredients[i].properties.coeff[p]);
        }
        printf("\n");
    }
    printf("\n");
}

void part1()
{
    const int spoons = 100;
    int quantities[nb_ingredients];
    long best_score = LONG_MIN;
    get_first_decomposition(quantities, nb_ingredients, spoons);
    do {
        struct s_properties props = cookie_properties(quantities);
        long score = cookie_score(props);
        // long calories = cookie_calories(props);
        if (score > best_score) {
            best_score = score;
            printf("best: %ld\t", score);
            for (int i = 0; i < nb_ingredients; i++) {
                printf("%d ", quantities[i]);
            }
            printf("\n");
        }

    } while (get_next_decomposition(quantities, nb_ingredients, spoons));
    printf("- best score for part 1: %ld\n", best_score);
}


void part2()
{
    const int spoons = 100;
    const int expected_calories = 500;
    int quantities[nb_ingredients];
    long best_score = LONG_MIN;
    get_first_decomposition(quantities, nb_ingredients, spoons);
    do {
        struct s_properties props = cookie_properties(quantities);
        if (cookie_calories(props) != 500) continue;
        long score = cookie_score(props);
        if (score <= best_score) continue;
        best_score = score;
        printf("best: %ld\t", score);
        for (int i = 0; i < nb_ingredients; i++) {
            printf("%d ", quantities[i]);
        }
        printf("\n");


    } while (get_next_decomposition(quantities, nb_ingredients, spoons));
    printf("- best score for part 2: %ld\n", best_score);
}

void process(const char filename[])
{
    load_data(filename);
    //int q[] = { 44, 56 };
    // printf("test -> %ld\n", coookie_score(q));
    part1();
	part2();
}

void tests()
{
    printf("# Tests\n");
    int array[3];
    for (int value = 0; value <= 3; value++) {
        printf("- decompositions of %d\n", value);
        get_first_decomposition(array, 3, value);
        do {
            for (int i = 0; i < 3; i++) {
                printf("%d ", array[i]);
            }
            printf("\n");
        } while (get_next_decomposition(array, 3, value));
    }
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
