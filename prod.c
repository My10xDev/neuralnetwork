#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
  float *array;
  size_t used;
  size_t size;
} FloatArray;

// Function to generate a random float between -1 and 1
float random_uniform() {
    return ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
}

void FloatArray_print_stdio(FloatArray *a) {
    for (int i = 0;i < a->used; i++) {
        printf("ARRAY VALUE -> %0.15f\n", a->array[i]);
    }

    printf("SIZE? -> %ld\n", a->size);
    return;
}

void FloatArray_initialize(FloatArray *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void FloatArray_insert_float(FloatArray *a, float element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

// Frees the memory allocated by the array,
// "closes" the FloatArray, so only use when done.
void FloatArray_free(FloatArray *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

float FloatArray_math_dotproduct(FloatArray *x, FloatArray *y) {

  if (x->used != y->used) {return 0.0;}

  float dotproduct = 0.0;

  for (int i = 0;i < x->used; i++) {dotproduct+=(x->array[i]*y->array[i]);}

  return dotproduct;
}

typedef struct {
  FloatArray *weights;
  FloatArray *inputs;
  float *gradient;
  float *activation;

  size_t size;
} Neuron;

void Neuron_initialize(Neuron *n, size_t input_size) {
  FloatArray weights;
  FloatArray inputs;

  FloatArray_initialize(&weights,input_size);
  FloatArray_initialize(&inputs,input_size); 

  n->weights = &weights;
  n->inputs = &inputs;
  n->size = input_size;
}

int main(){

  srand((unsigned int)time(NULL));

  FloatArray vector_1;
  FloatArray vector_2;
  FloatArray_initialize(&vector_1, 5);
  FloatArray_initialize(&vector_2, 5);

  for (int i = 0; i < 5; i++) {
    FloatArray_insert_float(&vector_1, random_uniform());
    FloatArray_insert_float(&vector_2, random_uniform());
  }

  printf("DOTPRODUCT -> %0.15f\n", FloatArray_math_dotproduct(&vector_1, &vector_2));

}