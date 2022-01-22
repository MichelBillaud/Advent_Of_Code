/*
	Advent of Code 2015 - Day 10
	michel billaud
	22 jan 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// automatic allocation of arrays is limited to 1 or 2 MB.
// so dynamic allocation is required.

#define SIZE 10000000

void xform(char *dst, const char *src)
{
    const char *s = src;
    char *d = dst;
    while (*s != '\0') {
        char c = *s++;
        int rep = 1;
        while (*s == c) {
            rep += 1;
            s++;
        }
        assert(rep < 10);
        *d++ = '0' + rep;
        *d++ = c;
    }
    *d++ = '\0';
}

void test(char *string, int times)
{
    char *src = malloc(SIZE);
    char *dst = malloc(SIZE);
    strcpy(src, string);
    for (int i = 1; i <= times; i++) {
        xform(dst, src);
        strcpy(src, dst);
        //printf("%2d (%zu)\t %s\n", i, strlen(src), src);
        printf("%2d (%zu)\n", i, strlen(src));
    }
    printf("# String \"%s\"\n- after %d turns, size = %zu\n",
           string, times, strlen(src));

    free(src);
    free(dst);
}

int main(int argc, char *argv[])
{
    printf("AOC 2015 - Day 10 - Look and Say\n");
    // test("1", 40);
	test("3113322113", 40);
    test("3113322113", 50);
    return EXIT_SUCCESS;
}
