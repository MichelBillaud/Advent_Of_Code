#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// AOC 2020 - day 02
// Michel Billaud, 12 dec 2021

void part1(char filename[]);
void part2(char filename[]);

int main()
{
    printf("AOC 2020 - day 2 - Password Philosophy\n");
    part1("../small.txt");
    part1("../large.txt");
    part2("../small.txt");
    part2("../large.txt");
}

/*
	the "part 1" version had only the file name as parameter.
	The functional parameter was introduced during refactoring when 
	it was clear the second part was similar: count the 
	valid passwords in a file according to a given policy.
*/

int nb_valid_passwords(char filename[], bool (*policy)(char *, char, int, int))
{
    FILE *datafile = fopen(filename, "r");
    if (datafile == NULL) {
        perror("reading data file");
        exit(EXIT_FAILURE);
    }
    int nb_valid_passwords = 0;
    while (true) {
        char line[100];
        if (fgets(line, 100, datafile) == NULL) break;
        int n1, n2;
        char letter;
        char password[50];
        int n = sscanf(line, "%d-%d %c: %s\n", &n1, &n2, &letter, password);
        if (policy(password, letter, n1, n2)) {
            nb_valid_passwords += 1;
        }
    }
    fclose(datafile);
    return nb_valid_passwords;
}

// PART 1 SPECIFIC CODE

int str_count(char string[], char c)
{
    int count = 0;
    for (char *p = string; *p; p++) {
        if (c == *p) {
            count++;
        }
    }
    return count;
}

bool is_valid_1(char password[], char letter, int min, int max)
{
    int n = str_count(password, letter);
    return (min <= n) && (n <= max);
}

void part1(char filename[])
{
    int nb = nb_valid_passwords(filename, is_valid_1);
    printf("Part 1: file %s contains %d valid passwords\n",
           filename, nb
          );
}

// PART 2 SPECIFIC CODE

bool is_valid_2(char password[], char letter, int a, int b)
{
    return (password[a-1]==letter) != (password[b-1]==letter);
}

void part2(char filename[])
{
    int nb = nb_valid_passwords(filename, is_valid_2);
    printf("Part 2: file %s contains %d valid passwords\n",
           filename, nb
          );
}
