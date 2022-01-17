#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Advent of code 2020 - Day 25 - part 1
 */

long transform(long subject, int loop_size)
{
    long value = 1;
    for (int i = 0; i <loop_size; i++) {
        value *= subject;
        value %= 20201227;
    }
    return value;
}

long loop_size(long subject, long key) {
	long value = 1;
	int size = 0;
	while (value != key) {
		 value *= subject;
        value %= 20201227;
		size += 1;
	}
	return size;
}

void part1(const char message[], long card_key, long door_key)
{
	printf("# Part1 (%s)\n", message);
	int card_loop_size = loop_size(7, card_key);
	int door_loop_size = loop_size(7, door_key);
	printf("- card loop size = %d\n", card_loop_size);
	printf("- door loop size = %d\n", door_loop_size);

	printf("- enc 1 = %ld\n", transform(card_key, door_loop_size));
	printf("- enc 2 = %ld\n", transform(door_key, card_loop_size));	
}

int main()
{
    printf("AOC 2020 - Day 25 \n");
    part1("test", 17807724, 5764801);
	part1("puzzle", 1327981, 2822615);

    return EXIT_SUCCESS;
}
