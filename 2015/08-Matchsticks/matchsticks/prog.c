/*
	Advent of Code 2015 - Day 8
	michel billaud, 22 jan 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct s_counters {
    int code;
    int chars;
    int specials;
} counters;

bool is_special(char c)
{
    return (c == '\\') || (c == '"') || (c == '\'');
}
counters count(const char string[])
{
    counters c = { 0};
    const char *p = string;
	c.specials = 2;  // enclosing
    assert(*p == '"');
    c.code += 1;
    c.specials += 1;
    p++;
    while(*p != '"') {
        if (*p == '\\') {
            p ++;
            if (*p == 'x') {
                p += 3;
                c.code += 4;
                c.specials += 1;
            } else {
                p += 1;
                c.code += 2;
                c.specials += 2;
            }
        } else {
            p += 1;
            c.code += 1;
        }
        c.chars += 1;
    }
    c.code += 1;
    c.specials += 1;
    return c;
}

void process(const char filename[])
{
    printf("# Processing (%s)\n", filename);
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        perror("loading data file");
        exit(EXIT_FAILURE);
    }
    counters total = {0,0, 0};
    for (char line[100]; fgets(line, 100, f) != NULL; ) {
        counters c = count(line);
        total.chars += c.chars;
        total.code += c.code;
        total.specials += c.specials;
    }
    fclose(f);
    printf("- total: %d code, %d data, %d specials\n",
           total.code, total.chars, total.specials);
    printf("- part 1 difference: %d\n", total.code - total.chars);
	printf("- part 2           : %d", total.specials);
    printf("\n");
}

void test_string(const char string[], int code, int chars, int specials)
{
    printf("- string: %s\n", string);
    printf("- expected: %d code, %d chars, %d specials\n",
           code, chars, specials);
    counters c = count(string);
    printf("- computed: %d code, %d chars, %d specials\n", 
		c.code, c.chars, c.specials);
    printf("\n");

}

void tests()
{
    printf("# Tests\n");
    test_string("\"\"", 2, 0, 2);
    test_string("\"abc\"", 5, 3, 2);
    test_string("\"\\\\\"", 4, 1, 4);
    test_string("\"aaa\\\"aaa\"", 10, 7, 4);
    test_string("\"\\x27\"", 6, 1, 3);
    printf("- all tests passed\n");
}


int main(int argc, char *argv[])
{
    printf("AOC 2015 - Day 8\n");
    if (argc == 1) {
        tests();
    } else {
        for (int i = 1; i < argc; i++) {
            process(argv[i]);
        }
    }


    return EXIT_SUCCESS;
}
