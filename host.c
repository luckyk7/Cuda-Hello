#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cuda_runtime.h>


void allocateHost(float **M_h, int dim)
{
	*M_h = (float*)malloc(dim *dim*sizeof(float));
	if (M_h == 0)
	{
		puts("Error, could not allocate memory on host.");
		exit(0);
	}
}

void fillMatrix(float M_h[], int dim, int range)
{
	int i = 0;
	for (i = 0; i < dim* dim; i++)
	{
		M_h[i] = ((float)rand() / (float)RAND_MAX) * range;
	}
}


//only will work right for square matrix
void print(float* M_h, int dim)
{
	int i;
	for (i = 1; i <= dim * dim; i++)
	{
		printf("%f ", M_h[i - 1]);
		if (i % dim == 0)
			printf("\n");
	}
}

float* transferToDevice(float* M_h, int dim)
{
	int size = dim * dim;
	float* M_d;

	cudaMalloc((void**)&M_d, size);
	cudaMemcpy(M_d, M_h, size, cudaMemcpyHostToDevice);
	
	return M_d;
}

void matrixMult(float*A_h, float* B_h, float* C_h, int dim)
{
	float* A_d = transferToDevice(A_h, dim);
	float* B_d = transferToDevice(B_h, dim);

}

int main()
{
	srand(time(0));
	float *A_d;
	float *B_d;
	float *C_d;

	//we want all matrices to be 20x20
	int dim = 20;

	//allocate memory on the host	
	allocateHost(&A_d, dim);
	allocateHost(&B_d, dim);
	allocateHost(&C_d, dim);

	//fill A, B with random floats in [0,10]
	fillMatrix(A_d, dim, 10);
	fillMatrix(B_d, dim, 10);

	//delete allocated memory on the host
	free(A_d);
	free(B_d);
	free(C_d);


}
