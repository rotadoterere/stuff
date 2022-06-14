#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBER 10

/*
 * The program generates pseudo-random numbers to build magic square matrices.
 *
 * 				006 004 003 
 *				001 005 007 
 *				006 004 003
 *
 * The MAX_NUMBER is a constant that will be the intervel pseudo-numbers from
 * the range 0 to MAX_NUMBER.
 *
 * The argv[1] is the number of rows and columns of the generated matrix.
 *
*/

int diagonal(int **matrix, int size)
{
	int i = 0, j = 0, main_diagonal = 0, sec_diagonal = 0;

	for (i = 0; i < size; ++i)
		main_diagonal += matrix[i][i];
	for (i = 0, j = size - 1; i < size; ++i, --j)
		sec_diagonal += matrix[i][j];
	
	if (main_diagonal == sec_diagonal)
		return 0;

	return 1;
}

int lines(int **matrix, int size)
{
	int i = 0, j = 0, sum = 0;
	int *array = (int *) malloc(sizeof(int) * size);

	for (i = 0; i < size; ++i) {
		for (j = 0; j < size; ++j)
			sum += matrix[i][j];
		array[i] = sum;
		sum = 0;
	}

	for (i = 0; i < size - 1; ++i) {
		if (array[i] != array[i + 1]) {
			free(array);
			array = NULL;
			return 1;
		}
		else
			continue;
	}

	free(array);
	array = NULL;
	
	return 0;
}

int columns(int **matrix, int size)
{
	int i = 0, j = 0,  sum = 0;
	int *array = (int *) malloc(sizeof(int) * size);

	for (i = 0; i < size; ++i) {
		for (j = 0; j < size; ++j)
			sum += matrix[j][i];
		array[i] = sum;
		sum = 0;
	}
	
	for (i = 0; i < size - 1; ++i) {
		if (array[i] != array[i + 1]) {
			free(array);
			array = NULL;
			return 1;
		}
		else
			continue;
	}
	
	free(array);
	array = NULL;
	
	return 0;
}

void genMatrix(int **matrix, int size)
{
	int i = 0, j = 0;

	for (i = 0; i < size; ++i) {
		matrix[i] = (int *) malloc(sizeof(int) * size);
		for (j = 0; j < size; ++j)
			matrix[i][j] = rand() % MAX_NUMBER;
	}
}

int main(int argc, char *argv[])
{
	int size = strtol(argv[1], NULL, 10);
	int **matrix = (int **) malloc(sizeof(int *) * size);
	int i = 0, j = 0;

	srand(time(NULL));

	genMatrix(matrix, size);

	while (diagonal(matrix, size) || lines(matrix, size) || columns(matrix, size)) {
		for (i = 0; i < size; ++i) {
			free(matrix[i]);
			matrix[i] = NULL;
		}
		genMatrix(matrix, size);
	}

	printf("Found the Matrix :)\n");

	for (i = 0; i < size; ++i) {
		for (j = 0; j < size; ++j)
			printf("%02d ", matrix[i][j]);
		printf("\n");
	}
	
	for (i = 0; i < size; ++i) {
		free(matrix[i]);
		matrix[i] = NULL;
	}

	free(matrix);
	matrix = NULL;

	return 0;
}
