#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int number_of_threads;

int multiply_possible(int cols, int rows) {
	return (cols == rows) ? 1: 0;
}

int** input_matrix(int rows, int cols) {
	int **arr = (int **) malloc( rows * sizeof(int *) );
	int element;
	for(int i = 0; i < rows; ++i) {
		arr[i] = (int *) malloc( cols * sizeof(int) );
		
		for(int j=0; j<cols; ++j) {
			scanf("%d ", &element);
			arr[i][j] = element;
		}
	}

	return arr;
}

void print_matrix(int** arr, int rows, int cols) {
	for(int i = 0; i < rows; ++i) {
		
		for(int j=0; j < cols; ++j) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}	
}

int** multiply_matrix(int** a, int** b, int rows_1, int cols_1, int cols_2) {

	int **result = (int **) malloc( rows_1 * sizeof(int *) );
	for(int i = 0; i < rows_1; ++i) {
		result[i] = (int *) malloc( cols_2 * sizeof(int) );
		
		for(int j = 0; j < cols_2; ++j) {
			result[i][j] = 0;
		}

	}

	#pragma omp parallel for num_threads(6) 
	{
		for(int i=0; i < rows_1; ++i) {

			#pragma omp parallel for num_threads(3)

			for(int j=0; j < cols_2; ++j) {
				for(int k=0; k < cols_1; ++k) {
					result[i][j] += a[i][k] * b[k][j];
				}
			}
		}
	}

	return result;
}

int** transpose(int** m, int rows, int cols) {
	int **result = (int **) malloc( cols * sizeof(int *) );
	for(int i = 0; i < cols; ++i) {
		result[i] = (int *) malloc( rows * sizeof(int) );

		for(int j=0; j < rows; ++j) {
			result[i][j] = m[j][i];
		}
	}

	return result;
}

int main(int argc, char const *argv[])
{
	//Size of first matrix
	int matrix1_rows = atoi(argv[1]);
	int matrix1_cols = atoi(argv[2]);

	//Size of second matrix
	int matrix2_rows = atoi(argv[3]);
	int matrix2_cols = atoi(argv[4]);

	//Number of threads
	int number_of_threads = atoi(argv[5]);

	printf("Size of Matrix\n1: %dx%d\n2: %dx%d\n", matrix1_rows, matrix1_cols , matrix2_rows, matrix2_cols);

	//Matrix Multiplication
	if (!multiply_possible(matrix1_cols, matrix2_rows)) {
		dprintf(2, "Error! Matrix Multiplication NOT possible\n\n");
	} else {

		//Input Matrices
		int** m1 = input_matrix(matrix1_rows, matrix1_cols);
		printf("\nMatrix 1:\n");
		print_matrix(m1, matrix1_rows, matrix1_cols);

		int** m2 = input_matrix(matrix2_rows, matrix2_cols);
		printf("\nMatrix 2:\n");
		print_matrix(m2, matrix2_rows, matrix2_cols);

		int** c  = multiply_matrix(m1, m2, matrix1_rows, matrix1_cols, matrix2_cols);
		printf("\nMatrix 3:\n");
		print_matrix(c, matrix1_rows, matrix2_cols);

		int** m1_t = transpose(m1, matrix1_rows, matrix1_cols);
		int** m2_t = transpose(m2, matrix2_rows, matrix2_cols);
		int** c_t  = transpose(c, matrix1_rows, matrix2_cols);

		printf("Transposes:\n");
		printf("M1:\n");
		print_matrix(m1_t, matrix1_cols, matrix1_rows);
		printf("\nM2:\n");
		print_matrix(m2_t, matrix2_cols, matrix2_rows);
		printf("\nM3:\n");
		print_matrix(c_t, matrix2_cols, matrix1_rows);
	}



	// omp_set_num_threads(3);
	// #pragma omp parallel
	// {

	// 	int thread_ID = omp_get_thread_num();
	// 	int num_threads = omp_get_num_threads();

	// 	#pragma omp barrier;

	// 	printf("Hello World from thread %d of %d \n", thread_ID, num_threads);

	// }

	return 0;

}