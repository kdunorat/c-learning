#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "dequef.h"

// Função auxiliar (privada a este ficheiro) para redimensionar o vetor.
// Retorna 1 em caso de sucesso, 0 em caso de falha de alocação.
static int df_resize(dequef* D, long new_capacity) {
    float *new_data = malloc(new_capacity * sizeof(float));
    if (new_data == NULL) {
        return 0; // Falha na alocação
    }

    // Copia os elementos do vetor antigo para o novo, "descircularizando"
    // para que o primeiro elemento fique sempre no índice 0 do novo vetor.
    for (long i = 0; i < D->size; i++) {
        long old_index = (D->first + i) % D->cap;
        new_data[i] = D->data[old_index];
    }

    free(D->data); // Libera o vetor antigo

    // Atualiza os ponteiros e metadados da deque
    D->data = new_data;
    D->cap = new_capacity;
    D->first = 0;

    return 1; // Sucesso
}

dequef* df_alloc(long capacity, double factor) {
    // Verifica se os parâmetros são válidos
    if (capacity <= 0 || factor <= 1.0) {
        return NULL;
    }

    dequef* D = malloc(sizeof(dequef));
    if (D == NULL) {
        return NULL;
    }

    D->data = malloc(capacity * sizeof(float));
    if (D->data == NULL) {
        free(D);
        return NULL;
    }

    D->cap = capacity;
    D->mincap = capacity;
    D->size = 0;
    D->first = 0;
    D->factor = factor;

    return D;
}

void df_free(dequef* D) {
    if (D != NULL) {
        free(D->data);
        free(D);
    }
}

long df_size(dequef* D) {
    if (D == NULL) return 0;
    return D->size;
}

int df_push(dequef* D, float x) {
    if (D->size == D->cap) {
        long new_cap = D->cap * D->factor;
        if (!df_resize(D, new_cap)) {
            return 0; // Falha no redimensionamento
        }
    }

    long end_index = (D->first + D->size) % D->cap;
    D->data[end_index] = x;
    D->size++;
    return 1; // Sucesso
}

float df_pop(dequef* D) {
    // A main.c já verifica se a deque está vazia.
    D->size--;
    long last_index = (D->first + D->size) % D->cap;
    float value = D->data[last_index];

    // Condição para reduzir o tamanho do vetor
    long new_cap_candidate = D->cap / D->factor;
    if (D->size <= D->cap / (D->factor * D->factor) && new_cap_candidate >= D->mincap) {
        df_resize(D, new_cap_candidate);
    }

    return value;
}

int df_inject(dequef* D, float x) {
    if (D->size == D->cap) {
        long new_cap = D->cap * D->factor;
        if (!df_resize(D, new_cap)) {
            return 0; // Falha no redimensionamento
        }
    }

    // A soma com 'cap' garante que o módulo de um número negativo funcione como esperado
    D->first = (D->first - 1 + D->cap) % D->cap;
    D->data[D->first] = x;
    D->size++;
    return 1; // Sucesso
}

float df_eject(dequef* D) {
    // A main.c já verifica se a deque está vazia.
    float value = D->data[D->first];
    D->first = (D->first + 1) % D->cap;
    D->size--;
    
    // Condição para reduzir o tamanho do vetor
    long new_cap_candidate = D->cap / D->factor;
    if (D->size <= D->cap / (D->factor * D->factor) && new_cap_candidate >= D->mincap) {
        df_resize(D, new_cap_candidate);
    }

    return value;
}

void df_set(dequef* D, long i, float x) {
    // A main.c já verifica se o índice 'i' é válido.
    long real_index = (D->first + i) % D->cap;
    D->data[real_index] = x;
}

float df_get(dequef* D, long i) {
    // A main.c já verifica se o índice 'i' é válido.
    long real_index = (D->first + i) % D->cap;
    return D->data[real_index];
}

void df_print(dequef* D) {
    printf("deque (%d):", (int)D->size);
    for (long i = 0; i < D->size; i++) {
        long real_index = (D->first + i) % D->cap;
        printf(" %.1f", D->data[real_index]);
    }
    printf(" ");
    printf("\n");
}
