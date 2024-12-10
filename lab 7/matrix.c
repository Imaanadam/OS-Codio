#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 20
#define MAX_THREADS 10

// Declare matrices and results
int matA[MAX][MAX]; 
int matB[MAX][MAX];
int matSumResult[MAX][MAX];
int matDiffResult[MAX][MAX]; 
int matProductResult[MAX][MAX];

// Struct to pass data to each thread (start row and end row)
typedef struct {
    int startRow;
    int endRow;
} ThreadData;

// Function to fill matrix with random values
void fillMatrix(int matrix[MAX][MAX]) {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            matrix[i][j] = rand() % 10 + 1; // Random values between 1 and 10
        }
    }
}

// Function to print matrix
void printMatrix(int matrix[MAX][MAX]) {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Thread function to compute sum
void* computeSum(void* args) {
    ThreadData* data = (ThreadData*)args;
    for (int i = data->startRow; i < data->endRow; i++) {
        for (int j = 0; j < MAX; j++) {
            matSumResult[i][j] = matA[i][j] + matB[i][j];
        }
    }
    free(data); // Free the allocated memory
    pthread_exit(0);
}

// Thread function to compute difference
void* computeDiff(void* args) {
    ThreadData* data = (ThreadData*)args;
    for (int i = data->startRow; i < data->endRow; i++) {
        for (int j = 0; j < MAX; j++) {
            matDiffResult[i][j] = matA[i][j] - matB[i][j];
        }
    }
    free(data); // Free the allocated memory
    pthread_exit(0);
}

// Thread function to compute product (dot product)
void* computeProduct(void* args) {
    ThreadData* data = (ThreadData*)args;
    for (int i = data->startRow; i < data->endRow; i++) {
        for (int j = 0; j < MAX; j++) {
            matProductResult[i][j] = 0;
            for (int k = 0; k < MAX; k++) {
                matProductResult[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
    free(data); // Free the allocated memory
    pthread_exit(0);
}

int main() {
    srand(time(0));  // Initialize random seed
    
    // Fill matrices A and B with random values
    fillMatrix(matA);
    fillMatrix(matB);

    // Print initial matrices
    printf("Matrix A:\n");
    printMatrix(matA);
    printf("Matrix B:\n");
    printMatrix(matB);
    
    pthread_t threads[MAX_THREADS];
    int rowsPerThread = MAX / MAX_THREADS;

    // Create threads to compute sum
    for (int i = 0; i < MAX_THREADS; i++) {
        ThreadData* data = (ThreadData*)malloc(sizeof(ThreadData));
        data->startRow = i * rowsPerThread;
        data->endRow = (i == MAX_THREADS - 1) ? MAX : data->startRow + rowsPerThread;
        pthread_create(&threads[i], NULL, computeSum, data);
    }
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Create threads to compute difference
    for (int i = 0; i < MAX_THREADS; i++) {
        ThreadData* data = (ThreadData*)malloc(sizeof(ThreadData));
        data->startRow = i * rowsPerThread;
        data->endRow = (i == MAX_THREADS - 1) ? MAX : data->startRow + rowsPerThread;
        pthread_create(&threads[i], NULL, computeDiff, data);
    }
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Create threads to compute product (dot product)
    for (int i = 0; i < MAX_THREADS; i++) {
        ThreadData* data = (ThreadData*)malloc(sizeof(ThreadData));
        data->startRow = i * rowsPerThread;
        data->endRow = (i == MAX_THREADS - 1) ? MAX : data->startRow + rowsPerThread;
        pthread_create(&threads[i], NULL, computeProduct, data);
    }
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the results
    printf("Results:\n");
    printf("Sum:\n");
    printMatrix(matSumResult);
    printf("Difference:\n");
    printMatrix(matDiffResult);
    printf("Product:\n");
    printMatrix(matProductResult);

    return 0;
}
