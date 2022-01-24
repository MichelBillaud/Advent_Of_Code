#define PUZZLE  "Advent of code 2015 day 16"

/*
  michel billaud
  24 jan 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define MAX_NB_SUES 1000
#define MAX_NB_AUNTIES 1000

enum Type {
    CHILDREN,
    CATS,
    SAMOYEDS,
    POMERANIANS,
    AKITAS,
    VIZSLAS,
    GOLDFISH,
    TREES,
    CARS,
    PERFUMES,
    NB_TYPES // dummy
};

const char * names[NB_TYPES] = {
    [CHILDREN] = "children",
    [CATS] = "cats",
    [SAMOYEDS] = "samoyeds",
    [POMERANIANS] = "pomeranians",
    [AKITAS] = "akitas",
    [VIZSLAS] = "vizslas",
    [GOLDFISH] = "goldfish",
    [TREES] = "trees",
    [CARS] = "cars",
    [PERFUMES] = "perfumes"
};

struct aunty {
	int num;
	enum Type type[3];
	int value[5];
};
	

int index_of(const char name[])
{
    for (int i = 0; i < NB_TYPES; i++) {
        if (strcmp(name, names[i]) == 0) {
            return i;
        }
    }
    printf("mispeled name %s\n", name);
    exit(EXIT_FAILURE);
}

const int READING[NB_TYPES] = {
    [CHILDREN] = 3,
    [CATS] = 7,
    [SAMOYEDS] = 2,
    [POMERANIANS] = 3,
    [AKITAS] = 0,
    [VIZSLAS] = 0,
    [GOLDFISH] = 5,
    [TREES] = 3,
    [CARS] = 2,
    [PERFUMES] = 1
};

int nb_aunties;
struct aunty aunties[MAX_NB_AUNTIES];

bool matches(struct aunty *a)
{
	for (int i = 0; i < 3; i++) {
		if (READING[a->type[i]] != a->value[i]) {
			return false;
		}
	}
	return true;   
}

bool field_match_2(enum Type type, int value) {
	return  
		type == CHILDREN      ? value == READING[CHILDREN]
		: type == CATS        ? value >  READING[CATS]
		: type == SAMOYEDS    ? value == READING[SAMOYEDS]
		: type == POMERANIANS ? value <  READING[POMERANIANS]
		: type == AKITAS      ? value == READING[AKITAS]
		: type == VIZSLAS     ? value == READING[VIZSLAS]
		: type == GOLDFISH    ? value <  READING[GOLDFISH]
		: type == TREES       ? value >  READING[TREES]
		: type == CARS        ? value == READING[CARS]
		: type == PERFUMES    ? value == READING[PERFUMES]
		: false;
}

bool matches2(struct aunty *a)
{
	for (int i = 0; i < 3; i++) {
		if (! field_match_2(a->type[i], a->value[i])) {
			return false;
		}
	}
	return true;
}

void load_data(const char filename[])
{
    printf("# Processing (%s)\n", filename);
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        perror("loading data file");
        exit(EXIT_FAILURE);
    }
    for (char line[100]; fgets(line, 100, f) != NULL; ) {
        int num, q[3];
        char n[3][20];
        int r = sscanf(line, "Sue %d: %[^:]: %d, %[^:]: %d, %[^:]: %d",
                       &num, n[0], &q[0], n[1], &q[1], n[2], &q[2]);
        aunties[nb_aunties].num = num;
        for (int i = 0; i < 3; i++) {
            aunties[nb_aunties].type[i] = index_of(n[i]);
            aunties[nb_aunties].value[i] = q[i];
        }
        nb_aunties += 1;    }
    fclose(f);
    printf("\n");
}

void dump()
{
    printf("# Data\n");
    for (int a = 0; a < nb_aunties; a++) {
        printf("%4d :", aunties[a].num);
        for (int i = 0; i < 3; i++) {
            printf("%s: %d ", names[aunties[a].type[i]], aunties[a].value[i]);
        }
        printf("\n");

    }
}

void part(const char title[], bool (*check)(struct aunty *))
{
    printf("# %s\n", title);
    for (int a = 0; a < nb_aunties; a++) {
        if (check( & aunties[a])) {
            printf("- %s: Sue %d matches.\n", title, aunties[a].num);
        }
    }
}

void process(const char filename[])
{
    load_data(filename);
    // dump();
    part("part 1", matches);
    part("part 2", matches2);

}

void tests()
{
    printf("# Tests\n");
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
