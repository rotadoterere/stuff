#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

/*
 * The program generates prime numbers using a model like Sieve of Erastosthenes.
 *
 * 				1 2 3 | X 2 3 
 * 				4 5 6 | X 5 X
 * 				7 8 9 | 7 X X
 *
 * Compile using the flag -lm on gcc :) .
*/ 

typedef unsigned long long int ulli;

int f_order(ulli limit)
{
	int order = 0;

  	while (limit >= 1) {
    		limit /= 10;
    		order++;
  	}

	return order;  
}

void fill(ulli *ptr, ulli *limit)
{
	ulli i = 0, j = 0;

  	for (i = 2, j = 0; j < *limit; i++, j++)
    		*(ptr + j) = i;
}

void calc(ulli *ptr, ulli *limit, ulli *square)
{
	ulli i = 0, j = 0;

  	for (i = 2; i <= *square; i++) {
    		for (j = 0; j < *limit; j++)
      			if ((*(ptr + j) % i  == 0) && (i != *(ptr + j)))
        			*(ptr + j) = 0;
  	}
}

void print_primes(ulli *ptr, ulli *limit, int order)
{
	ulli i = 0, t = 0;

	printf("Prime Numbers:\n");
  
  	for (i = 0; i < *limit; i++) {
    		if (*(ptr + i) != 0) {
      			printf("%0*llu ", order, *(ptr + i));
      			t++;
    		}
    		if (t == 15) {
     			printf("\n");
      			t = 0;
    		}
  	}
  	printf("\n");
}

int main(int argc, char *argv[])
{
	ulli limit = strtol(argv[1], NULL, 10) - 1;
  	ulli *primes = (ulli *) malloc(sizeof(ulli) * limit);
  	ulli square = sqrt(limit);
  	int order = 0;

  	order = f_order(limit);
  	fill(primes, &limit);
 	calc(primes, &limit, &square);
  	print_primes(primes, &limit, order);

  	free(primes);
 	primes = NULL;

  	return 0;
}
