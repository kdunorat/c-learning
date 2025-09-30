#include <stdio.h>
#include <stdlib.h>
#include "darray.h"

// Estrutura interna da deque.
// Os campos são definidos em darray.h, mas a struct em si é opaca para o main.c.
struct dequef {
    float *v;               // Vetor dinâmico que armazena os dados
    int capacity;           // Capacidade atual do vetor v
    int initial_capacity;   // Capacidade com que o vetor foi criado
    int size;               // Número de elementos na deque
    int first;              // Índice do primeiro elemento no vetor circular
    float factor;           // Fator de redimensionamento
};

// Função auxiliar interna para redimensionar o vetor.
// Retorna 1 em caso de sucesso, 0 em caso de falha.
static int dequef_resize(dequef *d, int new_capacity) {
    float *new_v = malloc(new_capacity * sizeof(float));
    if (new_v == NULL) {
        return 0; // Falha na alocação
    }

    // Copia os elementos do vetor antigo para o novo, "descircularizando" o array.
    for (int i = 0; i < d->size; i++) {
        int old_index = (d->first + i) % d->capacity;
        new_v[i] = d->v[old_index];
    }

    free(d->v); // Libera o vetor antigo

    // Atualiza os ponteiros e metadados da deque
    d->v = new_v;
    d->capacity = new_capacity;
    d->first = 0; // O primeiro elemento agora está no início do novo vetor

    return 1; // Sucesso
}

dequef *dequef_create(int t, float r) {
    dequef *d = malloc(sizeof(dequef));
    if (d == NULL) {
        return NULL;
    }

    d->v = malloc(t * sizeof(float));
    if (d->v == NULL) {
        free(d); // Libera a struct se a alocação do vetor falhar
        return NULL;
    }

    d->capacity = t;
    d->initial_capacity = t;
    d->size = 0;
    d->first = 0;
    d->factor = r;

    return d;
}

void dequef_destroy(dequef *d) {
    free(d->v);
    free(d);
}

void dequef_push(dequef *d, float x) {
    // Se a deque está cheia, aumenta o tamanho do vetor.
    if (d->size == d->capacity) {
        int new_capacity = d->capacity * d->factor;
        if (!dequef_resize(d, new_capacity)) {
            printf("Unable to resize.\n");
            exit(1);
        }
    }

    // Calcula o índice do final do vetor circular e insere o elemento.
    int end_index = (d->first + d->size) % d->capacity;
    d->v[end_index] = x;
    d->size++;
}

float dequef_pop(dequef *d) {
    if (dequef_is_empty(d)) {
        return 0.0; // Deque vazia, não faz nada
    }

    d->size--;
    int last_index = (d->first + d->size) % d->capacity;
    float value = d->v[last_index];

    // Condição para reduzir o tamanho do vetor.
    int new_capacity_candidate = d->capacity / d->factor;
    if (d->size <= d->capacity / (d->factor * d->factor) && new_capacity_candidate >= d->initial_capacity) {
        dequef_resize(d, new_capacity_candidate);
    }

    return value;
}

void dequef_inject(dequef *d, float x) {
    // Se a deque está cheia, aumenta o tamanho do vetor.
    if (d->size == d->capacity) {
        int new_capacity = d->capacity * d->factor;
        if (!dequef_resize(d, new_capacity)) {
            printf("Unable to resize.\n");
            exit(1);
        }
    }

    // Calcula a nova posição do primeiro elemento e insere.
    // A soma com 'capacity' garante que o resultado do módulo seja positivo.
    d->first = (d->first - 1 + d->capacity) % d->capacity;
    d->v[d->first] = x;
    d->size++;
}

float dequef_eject(dequef *d) {
    if (dequef_is_empty(d)) {
        return 0.0; // Deque vazia, não faz nada
    }

    float value = d->v[d->first];
    d->first = (d->first + 1) % d->capacity;
    d->size--;

    // Condição para reduzir o tamanho do vetor.
    int new_capacity_candidate = d->capacity / d->factor;
    if (d->size <= d->capacity / (d->factor * d->factor) && new_capacity_candidate >= d->initial_capacity) {
        dequef_resize(d, new_capacity_candidate);
    }

    return value;
}

void dequef_set(dequef *d, int i, float x) {
    if (i >= 0 && i < d->size) {A
        int real_index = (d->first + i) % d->capacity;
        d->v[real_index] = x;
    }
}

float dequef_get(dequef *d, int i) {
    if (i >= 0 && i < d->size) {
        int real_index = (d->first + i) % d->capacity;
        return d->v[real_index];
    }
    return 0.0; // Retorno padrão para índice inválido
}

int dequef_is_empty(dequef *d) {
    return d->size == 0;
}

void dequef_print(dequef *d) {
    printf("deque (%d):", d->size);
    for (int i = 0; i < d->size; i++) {
        int real_index = (d->first + i) % d->capacity;
        printf(" %.1f", d->v[real_index]);
    }
    printf("\n");
}
