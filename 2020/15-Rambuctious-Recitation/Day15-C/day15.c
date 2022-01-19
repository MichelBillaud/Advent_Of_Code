#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int compute(int initial[], int nb_initial, int nth)
{
    int date[3000] = {0};
    for (int t=1; t < nb_initial; t++) {
        date[initial[t-1]] = t;
    }
    int last = initial[nb_initial - 1];
    for (int t = nb_initial  ; t < nth; t++) {
        // printf("t = %d, last = %d, date = %d\n", t, last, date[last]);
        int next = (date[last] == 0 ? 0 : t - date[last]);
        date[last] = t;
        last = next;
        // printf("..%d\n", last);
    }
    // printf("\n");

    return last;
}

int compute_dyn(int initial[], int nb_initial, int nth)
{
	int *date = malloc(nth *sizeof(int));
	for (int i = 0; i < nth; i++) {
		date[i] = 0;
	}
	for (int t=1; t < nb_initial; t++) {
        date[initial[t-1]] = t;
    }
    int last = initial[nb_initial - 1];
    for (int t = nb_initial  ; t < nth; t++) {
        // printf("t = %d, last = %d, date = %d\n", t, last, date[last]);
        int next = (date[last] == 0 ? 0 : t - date[last]);
        date[last] = t;
        last = next;
        // printf("..%d\n", last);
    }
    // printf("\n");

    return last;
}

void test(int initial[], int nb_initial, int nth, int expected)
{
    printf("# Expected %d as %d-th with ", expected, nth);
    for (int i = 0; i < nb_initial; i++)
        printf("%d ", initial[i]);
    printf("\n");
    int obtained = compute_dyn(initial, nb_initial, nth);
    printf("- obtained %d\n\n", obtained);


}

void tests_part1() {
  test((int[]) {
        0,3,6
    }, 3, 2020, 436);

    test((int[]) {
        1,3,2
    }, 3, 2020, 1);
    test((int[]) {
        2, 1, 3
    }, 3, 2020, 10);
    test((int[]) {
        1,2,3
    }, 3, 2020, 27);
    test((int[]) {
        2,3,1
    }, 3, 2020, 78);
    test((int[]) {
        3,2,1
    }, 3, 2020, 438);
    test((int[]) {
        3,1,2
    }, 3, 2020, 1836);

    test((int[]) {
        0,3,6
    }, 3, 2020, 436);

}


void tests_part2() {

	printf("# Tests part 2\n");
 
    test((int[]) {
        0,3,6
    }, 3, 30000000, 175594);
}

int main()
{
    printf("# AOC 2020 - day 15\n");
	
	// tests_part1();
	int starting[] = {
        18,8,0,5,4,1,20
    };
    int result1 = compute(starting, 7, 2020);

	printf("# Part 1, result is %d\n", result1);

	// tests_part2();
	int result2 = compute_dyn(starting, 7, 30000000);
	printf("# Part 2, result is %d\n", result2);
    return EXIT_SUCCESS;
}
