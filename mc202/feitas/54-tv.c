#include <stdio.h>
#include <stdlib.h>

// Função para alocar dinamicamente uma matriz 2D
int** alocar_matriz(int linhas, int colunas) {
    int** matriz = (int**)malloc(linhas * sizeof(int*)); // é o endereço da lista de endereços. Cada item nessa lista é do tipo ponteiro int
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int*)malloc(colunas * sizeof(int));
    }
    return matriz;
}

// Função para liberar a memória de uma matriz 2D
void liberar_matriz(int** matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Função para imprimir a matriz
void imprimir_matriz(int** matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d", matriz[i][j]);
            if (j < colunas - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main() {
    int M, N;
    int caso_teste = 1;

    // Loop principal para processar múltiplos conjuntos de teste
    while (scanf("%d %d", &M, &N) == 2 && (M != 0 || N != 0)) {
        
        int** imagem_original = alocar_matriz(M, N);
        
        // Lê a matriz da imagem original
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                scanf("%d", &imagem_original[i][j]);
            }
        }

        int dx, dy;
        int total_dx = 0;
        int total_dy = 0;

        // Loop para ler e acumular os comandos de deslocamento
        while (scanf("%d %d", &dx, &dy) == 2 && (dx != 0 || dy != 0)) {
            total_dx += dx;
            total_dy += dy;
        }

        int** imagem_resultante = alocar_matriz(M, N);

        // Calcula a imagem resultante aplicando o deslocamento total
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                // Calcula a posição de origem do pixel na matriz original
                // dy positivo = para cima (diminui o índice da linha)
                // dx positivo = para a direita (aumenta o índice da coluna)
                // A fórmula inversa é usada para encontrar a origem
                int orig_i = (i + total_dy);
                int orig_j = (j - total_dx);

                // Aplica a lógica modular para o efeito "wrap-around"
                // Adiciona M ou N antes do módulo para tratar corretamente os resultados negativos
                orig_i = (orig_i % M + M) % M;
                orig_j = (orig_j % N + N) % N;

                imagem_resultante[i][j] = imagem_original[orig_i][orig_j];
            }
        }

        // Imprime a saída formatada
        printf("Teste %d\n", caso_teste++);
        imprimir_matriz(imagem_resultante, M, N);
        printf("\n");

        // Libera a memória alocada para as matrizes
        liberar_matriz(imagem_original, M);
        liberar_matriz(imagem_resultante, M);
    }

    return 0;
}