#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char tipo;  // 'd', 'f', 's', 'c'
    union {
        long d;
        double f;
        char *s;
        char c;
    } dado;
} V_type;

void imprimir(V_type *vetor, int k) {
    printf("V (%d): ", k);
    for (int i = 0; i < k; i++) {
        switch (vetor[i].tipo) {
            case 'd':
                printf("%ld", vetor[i].dado.d);
                break;
            case 'f':
                printf("%.4f", vetor[i].dado.f);
                break;
            case 'c':
                printf("%c", vetor[i].dado.c);
                break;
            case 's':
                printf("%s", vetor[i].dado.s);
                break;
        }
        if (i < k - 1) printf(", ");
    }
    if (k > 0) {
        printf(" ");
    }
    printf("\n");
}

void inserir(V_type *vetor, int *k, int n, int j, char t, char *x) {
    if (*k >= n) return; // cheio

    if (j > *k) j = *k; // insere no fim

    // desloca para abrir espaço
    for (int i = *k; i > j; i--) {
        vetor[i] = vetor[i-1];
    }

    vetor[j].tipo = t;
    switch (t) {
        case 'd':
            vetor[j].dado.d = atoi(x); //string para int
            break;
        case 'f':
            vetor[j].dado.f = atof(x); // string para =float
            break;
        case 'c':
            vetor[j].dado.c = x[0];
            break;
        case 's':
            vetor[j].dado.s = malloc(strlen(x) + 1);
            strcpy(vetor[j].dado.s, x);
            break;
    }
    (*k)++;
}

void remover(V_type *vetor, int *k, int j) {
    if (*k == 0) return;
    if (j >= *k) j = 0;

    if (vetor[j].tipo == 's') {
        free(vetor[j].dado.s); // liberar string
    }

    for (int i = j; i < *k - 1; i++) {
        vetor[i] = vetor[i+1];
    }
    (*k)--;
}

int main() {
    V_type *V = NULL;
    int n = 0, k = 0; 
    char opt;

    while (scanf(" %c", &opt) == 1) {
        if (opt == 'c') {
            scanf("%d", &n);
            if (V) free(V);
            V = malloc(sizeof(V_type) * n);
            k = 0;
        }
        else if (opt == 'i') {
            int j;
            char t, x[12000];
            scanf("%d %c", &j, &t);
            scanf(" %[^\n]", x); // le o resto (tudo que não seja \n)
            inserir(V, &k, n, j, t, x);
        }
        else if (opt == 'r') {
            int j;
            scanf("%d", &j);
            remover(V, &k, j);
        }
        else if (opt == 'p') {
            imprimir(V, k);
        }
        else if (opt == 'f') {
            break;
        }
    }

    if (V != NULL) {
    for(int i = 0; i < k; i++) {
        if (V[i].tipo == 's') {
            free(V[i].dado.s);
        }
    }}

    free(V);
    return 0;
}