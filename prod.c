#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define M_PI 3.14159265358979323846

typedef struct {
    float *array;
    size_t used;
    size_t size;
} FloatArray;

float geluf(float x) {
    float sqrt_2_over_pi = sqrtf(2.0f / M_PI);
    float tanh_x = tanhf(sqrt_2_over_pi * (x + 0.044715f * powf(x, 3.0f)));
    return 0.5f * x * (1.0f + tanh_x);
}

float random_uniform() {
    return ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
}

void FloatArray_print_stdio(FloatArray *a) {
    for (int i = 0; i < (int)a->used; i++) {
        printf("ARRAY VALUE -> %0.15f\n", a->array[i]);
    }
    printf("SIZE? -> %zu\n", a->size);
}

void FloatArray_initialize(FloatArray *a, size_t initialSize) {
    a->array = malloc(initialSize * sizeof(float));
    a->used = 0;
    a->size = initialSize;
}

void FloatArray_insert_float(FloatArray *a, float element) {
    if (a->used == a->size) {
        a->size *= 2;
        a->array = realloc(a->array, a->size * sizeof(float));
    }
    a->array[a->used++] = element;
}

void FloatArray_free(FloatArray *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

float FloatArray_math_dotproduct(FloatArray *x, FloatArray *y) {
    float dotproduct = 0.0f;
    for (int i = 0; i < (int)x->used; i++) {
        dotproduct += (x->array[i] * y->array[i]);
    }
    return dotproduct;
}

typedef struct {
    FloatArray *weights;
    FloatArray *inputs;
    float *activation;
    size_t size;
} Neuron;

float Neuron_math_activation(Neuron *n) {
    float activation = geluf(FloatArray_math_dotproduct(n->weights, n->inputs));
    if (n->activation == NULL) {
        n->activation = malloc(sizeof(float));
    }
    *n->activation = activation;
    return activation;
}

void Neuron_initialize(Neuron *n, size_t input_size) {
    n->weights = malloc(sizeof(FloatArray));
    n->inputs = malloc(sizeof(FloatArray));
    n->activation = NULL;
    n->size = input_size;

    FloatArray_initialize(n->weights, input_size);
    FloatArray_initialize(n->inputs, input_size);

    // Initialize weights randomly
    for (int i = 0; i < (int)input_size; i++) {
        FloatArray_insert_float(n->weights, random_uniform());
    }
}

// Frees a single neuron
void Neuron_free(Neuron *n) {
    if (n->weights) {
        FloatArray_free(n->weights);
        free(n->weights);
    }
    if (n->inputs) {
        FloatArray_free(n->inputs);
        free(n->inputs);
    }
    if (n->activation) {
        free(n->activation);
    }
}

////////////////////////
// LAYER STRUCT & FUNCS
////////////////////////

typedef struct {
    Neuron *neurons;
    size_t num_neurons;
    size_t input_size; // All neurons in this layer share the same input size
} Layer;

void Layer_initialize(Layer *layer, size_t num_neurons, size_t input_size) {
    layer->num_neurons = num_neurons;
    layer->input_size = input_size;
    layer->neurons = malloc(num_neurons * sizeof(Neuron));

    for (size_t i = 0; i < num_neurons; i++) {
        Neuron_initialize(&layer->neurons[i], input_size);
    }
}

void Layer_free(Layer *layer) {
    for (size_t i = 0; i < layer->num_neurons; i++) {
        Neuron_free(&layer->neurons[i]);
    }
    free(layer->neurons);
    layer->neurons = NULL;
    layer->num_neurons = 0;
    layer->input_size = 0;
}

FloatArray Layer_compute_activations(Layer *layer) {
    FloatArray activations;
    FloatArray_initialize(&activations, layer->num_neurons); // Initialize for the number of neurons

    for (size_t i = 0; i < layer->num_neurons; i++) {
        // Ensure that the neuron has inputs set. The caller should have set inputs beforehand.
        // If inputs are not set, Neuron_math_activation will compute based on what's currently in n->inputs.
        float act = Neuron_math_activation(&layer->neurons[i]);
        FloatArray_insert_float(&activations, act);
    }

    return activations;
}


int main() {
    srand((unsigned int)time(NULL));

    // Example: Create a layer with 5 neurons, each neuron having input size 4
    Layer layer;
    Layer_initialize(&layer, 5, 4);

    // For demonstration, we can set some inputs to the layer's first neuron:
    for (int i = 0; i < (int)layer.neurons[0].size; i++) {
        // Insert random inputs for demonstration
        if (layer.neurons[0].inputs->used < layer.neurons[0].inputs->size) {
            FloatArray_insert_float(layer.neurons[0].inputs, random_uniform());
        } else {
            // If initial size is small, you may need to ensure proper resizing logic
            FloatArray_insert_float(layer.neurons[0].inputs, random_uniform());
        }
    }

    // Calculate activation of the first neuron in the layer
    float act = Neuron_math_activation(&layer.neurons[0]);
    printf("Activation of first neuron: %f\n", act);

    // Just for demonstration using your vector code
    FloatArray vector_1;
    FloatArray vector_2;
    FloatArray_initialize(&vector_1, 5);
    FloatArray_initialize(&vector_2, 5);

    for (int i = 0; i < 5; i++) {
        FloatArray_insert_float(&vector_1, random_uniform());
        FloatArray_insert_float(&vector_2, random_uniform());
    }

    printf("DOTPRODUCT -> %0.15f\n", FloatArray_math_dotproduct(&vector_1, &vector_2));

    FloatArray_free(&vector_1);
    FloatArray_free(&vector_2);

    Layer_free(&layer);

    return 0;
}
