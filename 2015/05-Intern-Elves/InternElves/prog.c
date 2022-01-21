/*
    Advent of Code 2015 - Day 5
    author. michel billaud. 
    date-written. 2022/01/21.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

bool is_nice_1(const char *word)
{
    // we're going ascii
    static const int VOWEL[128] = {
        ['a'] = 1, ['e'] = 1, ['i'] = 1, ['o'] = 1, ['u'] = 1
    };
    int length = strlen(word);
    int count = 0;
    for (int i = 0; i < length; i++) {
        count += VOWEL[(int) word[i]];
    }
    if (count < 3) return false;

    bool twice = false;
    for (int i = 1; i < length; i++) {
        if (word[i] == word[i-1]) {
            twice = true;
            break;
        }
    }
    if (! twice) return false;

    char * forbidden[4] = {"ab", "cd", "pq", "xy"};
    for (int i = 0; i < length; i++) {
        for (int f = 0; f < 4; f++) {
            if (strncmp(word+i, forbidden[f], 2) == 0) {
                return false;
            }
        }
    }
    return true;
}


bool is_nice_2(const char *word)
{
    // we're going ascii
    // index of the second element of pair
    int index_of_pair[128][128] = { {0}};
    bool pair_found = false;
    int length = strlen(word);
    for (int i = 1; i < length; i++) {
        int *p = & (index_of_pair[(int) word[i-1]][(int) word[i]]);
        if (*p == 0) {
            *p = i;
        } else if (*p < i-1) {
            pair_found = true;
            break;
        }
    }
    if (! pair_found) return false;
    for (int i = 2; i < length; i ++) {
        if (word[i-2]== word[i]) return true;
    }
    return false;
}

void perform_tests()
{
    printf("# Tests for part 1\n");
    assert(is_nice_1("ugknbfddgicrmopn"));
    assert(is_nice_1("aaa"));
    assert(!is_nice_1("jchzalrnumimnmhp"));
    assert(!is_nice_1("haegwjzuvuyypxyu"));
    assert(!is_nice_1("dvszwmarrgswjxmb"));

    printf("# Tests for part 2\n");
    assert(is_nice_2("qjhvhtzxzqqjkmpb"));
    assert(is_nice_2("xxyxx"));

    assert(! is_nice_2("uurcxstgmygtbstg"));
    assert(! is_nice_2("ieodomkazucvgmuy"));
    printf("- all tests passed.\n");
}

void part(const char part_name[],
          const char filename[],
          bool is_nice(const char[]))
{
    printf("# %s (%s)\n", part_name, filename);
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("loading data file");
        exit(EXIT_FAILURE);
    }
    int count = 0;
    char word[100];
    while (fscanf(f, "%s", word) == 1) {
        if (is_nice(word)) count +=  1;
    }
    fclose(f);
    printf("- count: %d\n", count);
}

int main(int argc, char *argv[])
{

    if (argc == 1) {
        perform_tests();
    } else {
        for (int i = 1; i < argc; i++) {
            part("Part 1", argv[i], is_nice_1);
            part("Part 2", argv[i], is_nice_2);
            
        }
    }
    return EXIT_SUCCESS;
}
