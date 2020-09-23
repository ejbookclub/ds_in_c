#include <stdio.h>
#include <string.h>

#define SQUARE_SIZE 9

void print_square(int (*square)[SQUARE_SIZE])
{
	int i, j, k;

	for (i = 0; i < SQUARE_SIZE; i++) {

		for (k = 0; k < (SQUARE_SIZE * 3 + 1); k++)
			printf("-");
		printf("\n|");

		for (j = 0; j < SQUARE_SIZE; j++) {
			printf("%2d|", square[i][j]);
		}
		printf("\n");
	}

	for (k = 0; k < (SQUARE_SIZE * 3 + 1); k++)
		printf("-");
	printf("\n");
}

void fill_in_square(int (*square)[SQUARE_SIZE])
{
	int i, j, count;

	count = 1;
	i = -1;
	j = (SQUARE_SIZE - 1) / 2;

	while(count <= (SQUARE_SIZE * SQUARE_SIZE)) {
		if((count % SQUARE_SIZE) == 1) {
			i++;
		} else {
			i--;
			j++;
		}

		if(i < 0)
			i = (SQUARE_SIZE - 1);

		if(j > (SQUARE_SIZE - 1))
			j = 0;

		square[i][j] = count++;
	}
}

int main() {
	int square[SQUARE_SIZE][SQUARE_SIZE];

	fill_in_square(square);
	print_square(square);

	return 0;
}
