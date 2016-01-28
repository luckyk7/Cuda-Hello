#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

int main()
{
	float* A;
	float* B;
	float* C;

	size_t size = 100*sizeof(float);
	
	A =(float*) malloc(size);

	if (A==NULL)
	{
		puts("Cannot allocate memory for matrix A");
		return 0;
	}
	
	B = (float*) malloc(size);
	if (B==NULL)
	{
		puts("Cannot allocate memory for matrix B");
		return 0;
	}

	C = (float*) malloc(size);
	if (C==NULL)
	{
		puts("Cannot allocate memory for matrix C");
		return 0;
	}

	int i = 0;
	for (i =0; i < 100; i++)
	{
		A[i] = ((float)rand() / (float)RAND_MAX) * 10;
		B[i] = ((float)rand() / (float)RAND_MAX) * 10;
	}

	//display the a matrix
	for (i =1; i < 101; i++)
	{
		printf("%f " , A[i-1]);
		if ( i % 10 ==0)
			printf("\n");
	}
	
}

