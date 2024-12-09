#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Function to generate a random float between -1 and 1
float random_uniform() {
    return ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
}

struct Neuron {
    float x[10];
    float y[10];
};

float tanh_derivative(float x) {
    return 1-pow(tanhf(x),2);
}

int main(){

    srand((unsigned int)time(NULL));

    // Define array size
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    // Allocate memory for the array
    float *array = (float *)malloc(size * sizeof(float));
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Fill the array with random values and print them
    printf("Random numbers between -1 and 1:\n");
    for (int i = 0; i < size; i++) {
        array[i] = random_uniform();
        printf("%f\n", array[i]);
    }

    // Free the allocated memory
    free(array);

    float x = 1.352F;

    printf("SIGMOID -> %0.15f\n", atanhf(x));

    return 0;
}