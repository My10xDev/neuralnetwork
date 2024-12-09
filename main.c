#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;

void array_print_stdio(Array *a) {
    for (int i = 0;i < a->used; i++) {
        printf("ARRAY VALUE -> %d\n", a->array[i]);
    }

    printf("SIZE? -> %ld\n", a->size);

    return;
}

void initArray(Array *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, int element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

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

    printf("SIGMOID -> %0.15f\n", tanhf(x));
    printf("HELOOOOOOOOOOOOOOOOOOOOOO\n\n\n");

    Array a;
    int i;

    initArray(&a, 5);  // initially 5 elements
    for (i = 0; i < 100; i++){
        insertArray(&a, i);  // automatically resizes as necessary
    }
    printf("%d\n", a.array[9]);  // print 10th element
    printf("%ld\n", a.used);  // print number of elements

    array_print_stdio(&a);

    freeArray(&a);

    return 0;
}