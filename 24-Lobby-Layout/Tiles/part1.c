#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINE_SIZE 100
#define MAX_NB_POINTS 500

typedef struct s_point {
    int x, y;
} point;


//NW, NE, W, E, SW, SE
const int D[6][2] = {
    {0, -1}, {1, 0},
    {-1,-1}, {1, 1},
    {-1, 0}, {0, 1}
};

point address(const char *string)
{
    int x = 0, y = 0;
    int v = 2;
    for (const char *p = string; *p; p++) {
        switch (*p) {
        case 'n' :
            v = 0;
            break;
        case 's' :
            v = 4;
            break;
        case 'w' :
            x += D[v][0];
            y += D[v][1];
            v = 2;
            break;
        case 'e' :
            x += D[v+1][0];
            y += D[v+1][1];
            v = 2;
            break;
		default:
			//ignore others
			break;
        }
    }
	return (point){x, y};
}

int point_order(const void *a1, const void *a2) {
	const point *p1 = a1, *p2 = a2;
	int r = p1->x - p2->x;
	if (r == 0) r = p1->y - p2->y;
	return r;
}

void part1(const char filename[]) {
	printf("# %s\n", filename);
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		perror("loading data");
		exit(EXIT_FAILURE);
	}
	int nb_points = 0;
	point points[MAX_NB_POINTS];

	for (char line[100]; fgets(line, 100, f) != NULL; ) {
		point p = address(line);
		points[nb_points++] = p;
		// printf("(%d,%d) ", p.x, p.y);
	}
	fclose(f);
	
	qsort(points, nb_points, sizeof(point), point_order);
	for (int i = 0; i < nb_points; i++) {
		printf("(%d,%d) ", points[i].x, points[i].y);
	}
	printf("\n");

	int total = 0;
	int i = 0;
	while (i < nb_points) {
		point first = points[i];
		int count = 0;
		while ((i < nb_points) 
			&& ((first.x == points[i].x) 
			&& (first.y == points[i].y))) {
				count = 1-count;
				i++;
		}
		total += count;
	}
	printf("- total %d points changed\n", total);
}

int main()
{
    printf("AOC 2020, day 24, Lobby Layout\n");
	part1("../test.txt");
	part1("../puzzle.txt");

    return EXIT_SUCCESS;
}
