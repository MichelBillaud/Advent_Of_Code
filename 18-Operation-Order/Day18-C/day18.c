/*
 * Advent of Code 2020 - Day 18 - Operation Order
 * Michel BIllaud, 2 jan 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

long get_expr1(const char **p);
long get_term1(const char **p);

void skip_spaces(const char **p)
{
    while(isspace(**p)) *p += 1;
}

bool is_operator(char c) {
	return c == '+' || c == '*';
}

// ----------------------------------

long get_term1(const char **p)
{
    long value = 0;
    skip_spaces(p);
    if (**p == '(') {
        *p += 1;
        value = get_expr1(p);
        assert(**p == ')');
    } else 	if (isdigit(**p)) {
        // numbers are single digits
        value = **p - '0';
    } else assert(1 == 0);
    *p += 1;
    return value;
}

long get_expr1(const char **p)
{
    long left = get_term1(p);
    while (true) {
        skip_spaces(p);
        if (! is_operator(**p) ) break;
        char op = **p;
        *p += 1;
        long right = get_term1(p);
        left = op == '+'
               ? left + right
               : left * right;
    }
    return left;
}

long value1(const char *string)
{
    const char **p = &string;
    return get_expr1(p);
	assert(**p == '\0');
}

void test1(const char string[], long expected)
{
    printf("# Test 1: %s\n", string);
    printf("- expected : %ld\n", expected);
    printf("- obtained : %ld\n", value1(string));
}


void tests_part1() {
	printf("# Tests part 1\n");

    test1("1 + 2 * 3 + 4 * 5 + 6", 71);
    test1("1 + (2 * 3) + (4 * (5 + 6))", 51);
    test1("2 * 3 + (4 * 5)", 26);
    test1("5 + (8 * 3 + 9 + 3 * 4 * 3)", 437);
    test1("5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))", 12240);
    test1("((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2", 13632);
}

// ---------------------------------------------------

long get_factor2(const char **p);
long get_term2(const char **p);
long get_expr2(const char **p);


long get_factor2(const char **p)
{
    long value = 0;
    skip_spaces(p);
    if (**p == '(') {
        *p += 1;
        value = get_expr2(p);
        assert(**p == ')');
    } else 	if (isdigit(**p)) {
        // numbers are single digits
        value = **p - '0';
    } else assert(1 == 0);
    *p += 1;
    return value;
}

long get_term2(const char **p)
{
    long left = get_factor2(p);
    while (true) {
        skip_spaces(p);
        if ( **p  != '+') break;
        char op = **p;
        *p += 1;
        long right = get_factor2(p);
        left =  left + right;
    }
    return left;
}


long get_expr2(const char **p)
{
    long left = get_term2(p);
    while (true) {
        skip_spaces(p);
        if ( **p  != '*') break;
        char op = **p;
        *p += 1;
        long right = get_term2(p);
        left =  left * right;
    }
    return left;
}

long value2(const char *string)
{
    const char **p = &string;
    return get_expr2(p);
	assert(**p == '\0');
}

void test2(const char string[], long expected)
{
    printf("# Test 2: %s\n", string);
    printf("- expected : %ld\n", expected);
    printf("- obtained : %ld\n", value2(string));
}

void tests_part2() {
	printf("# Tests part 2\n");

    test2 ("1 + 2 * 3 + 4 * 5 + 6", 231);
    test2("1 + (2 * 3) + (4 * (5 + 6))", 51);
    test2("2 * 3 + (4 * 5)", 46);
    test2("5 + (8 * 3 + 9 + 3 * 4 * 3)", 1445);
    test2("5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))", 669060);
    test2("((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2", 23340);
}

long sum_file(const char filename[], long (*evaluator)(const char *)) {
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		perror("reading data file");
		exit(EXIT_FAILURE);
	}
	char line[1000]; 
	long sum = 0;
	while (fgets(line, 1000, f) != NULL) {
		long v = evaluator(line);
		// printf("%16ld %s", v, line); 
		sum += v;
	}
	fclose(f);
	return sum;
}

void part1(const char filename[]) {
	printf("# Part 1, %s\n", filename);
	long sum = sum_file(filename, value1);
	printf("- Sum is %ld\n", sum);
}

void part2(const char filename[]) {
	printf("# Part 2, %s\n", filename);
	long sum = sum_file(filename, value2);
	printf("- Sum is %ld\n", sum);
}

int main()
{
    printf("# AOC 2020  - Day 18\n");
	// tests_part1();
	part1("../large.txt");

	// tests_part2();
	part2("../large.txt");
    return EXIT_SUCCESS;
}
