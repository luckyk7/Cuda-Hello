#include <cuda_runtime.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

__global__ void compare(int *in_d, int* out_d)
{
	if (in_d[blockIdx.x] == 6)
	{
		out_d[blockIdx.x] = 1;
	}
	else
		out_d[blockIdx.x] = 0;
}

#define SIZE 16


int main()
{
	//create two arrays
	size_t bytes = SIZE * sizeof(int);
	int *input, *output;
	input = (int*)malloc(bytes);
	output = (int*)malloc(bytes);

	//fill the input array with random values in [0,9]
	srand(time(0));
	int i;
	for (i = 0; i < SIZE; i++)
	{
		input[i] = rand() % 10;
		output[i] = -1;
	}

	//now allocate both arrays on the gpu
	int *input_d, *output_d;
	cudaMalloc((void**)&input_d, bytes);
	cudaMalloc((void**)&output_d, bytes);

	//now we copy the input array to the gpu
	cudaMemcpy(input_d, input, bytes, cudaMemcpyHostToDevice);

	//launch the kernel
	compare << <SIZE, 1 >> >(input_d, output_d);

	//copy the output array back to the cpu mem
	cudaMemcpy(output, output_d, bytes, cudaMemcpyDeviceToHost);

	//free memory on the gpu
	cudaFree(input_d);
	cudaFree(output_d);
	input_d = 0;
	output_d = 0;

	//display our answers
	int total = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (output[i] == 1)
			total += 1;
	}

	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", input[i]);
	}
	printf("\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", output[i]);
	}

	printf("total sixes = %d\n", total);

	//free our arrays from memory
	free(input);
	free(output);
	input = 0;
	output = 0;

}


