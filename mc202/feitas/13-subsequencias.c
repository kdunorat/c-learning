#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_subsequence(char sub[], int len, char s2[], int m) {
    int j = 0; 
    for (int i = 0; i < m && j < len; i++) {
        if (s2[i] == sub[j]) {
            j++;
        }
    }
    // se j chegou ao final, todos os caracteres de sub foram encontrados em ordem
    return (j == len);
}


int proxima_combinacao(int indices[], int k, int n) {
    // Começa pelo ultimo indice e vai para a esquerda
    for (int i = k - 1; i >= 0; i--) {
        // Encontra o primeiro indice da direita que ainda não atingiu seu valor máximo
        if (indices[i] < n - k + i) {
            // Incrementa esse indice
            indices[i]++;
            // Ajusta todos os indices à direita para serem os menores valores possíveis
            for (int j = i + 1; j < k; j++) {
                indices[j] = indices[j - 1] + 1;
            }
            return 1; // Nova combinação encontrada
        }
    }
    return 0; // Não há mais combinações
}


int verificar_todas_iterativo(int k, char s1[], int n, char s2[], int m) {
    // Array para guardar os indices da subsequencia atual
    int *indices = malloc(k * sizeof(int));
    // Buffer para construir a string da subsequencia
    char *sub_atual = malloc(k + 1);
    
    // Inicializa com a primeira combinação (ex: {0, 1, ..., k-1})
    for (int i = 0; i < k; i++) {
        indices[i] = i;
    }

    do {
        for (int i = 0; i < k; i++) {
            sub_atual[i] = s1[indices[i]];
        }
        sub_atual[k] = '\0';

        if (!is_subsequence(sub_atual, k, s2, m)) {
            free(indices);
            free(sub_atual);
            return 1; // Falha encontrada
        }

    } while (proxima_combinacao(indices, k, n));

    free(indices);
    free(sub_atual);
    return 0; // Todas existem
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m)!= 2){
        return 1;
    }
    
    char *s1 = malloc(n + 1);
    char *s2 = malloc(m + 1);

    if (scanf("%s %s", s1, s2) != 2){
        free(s1);
        free(s2);
        return 1;
    }

    int grau = 1;

    while (grau <= n) {
        // Chama a nova função iterativa
        if (verificar_todas_iterativo(grau, s1, n, s2, m)) {
            break; 
        }
        grau++;
    }

    printf("%d\n", grau);

    free(s1);
    free(s2);

    return 0;
}
