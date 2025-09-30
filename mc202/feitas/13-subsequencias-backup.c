#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// checa se subsequencia de tamanho len está em s2
int is_subsequence(char sub[], int len, char s2[], int m) {
    int j = 0; // ponteiro para sub
    // percorre s2 mas avança o ponteiro de sub apenas quando encontra um caractere correspondente
    for (int i = 0; i < m && j < len; i++) {
        if (s2[i] == sub[j]) {
            j++;
        }
    }
    // se j chegou ao final, todos os caracteres de sub foram encontrados em ordem
    return (j == len);
}

// gera todas as subsequências de s1 de tamanho k recursivamente
// retorna 1 se encontrar uma subsequência de s1 que nao está em s2, 0 caso contrário.
int generate_subseq(int pos, int len, char subseq[], int target_len, char s1[], int n, char s2[], int m) {
    // caso base: construímos uma subsequência do tamanho desejado
    if (len == target_len) {
        // termina a string
        subseq[len] = '\0'; 
        if (!is_subsequence(subseq, len, s2, m)) {
            // retorna 1 (encontrado).
            return 1;
        }
        // continua procurando.
        return 0;
    }

    // caso base: percorremos todo s1 e não conseguimos formar a subsequência.
    if (pos >= n) {
        return 0;
    }

    // o ramo "não escolhendo" o caractere s1[pos].
    // se já encontrar uma subsequência problemática, retornamos imediatamente.
    // len parado com pos andando voce pula mantendo o mesmo tamanho da subseq
    if (generate_subseq(pos + 1, len, subseq, target_len, s1, n, s2, m)) {
        return 1;
    }
    // ele vai executar o primeiro ramo inteiro até retornar.
    
    // o ramo "escolhendo" o caractere s1[pos].
    subseq[len] = s1[pos];
    if (generate_subseq(pos + 1, len + 1, subseq, target_len, s1, n, s2, m)) {
        return 1;
    }
    
    // Se nenhum dos ramos encontrou uma subsequência problemática, retorna 0.
    return 0;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m)!= 2){
        return 0;
    }
    if (n == 0 || m == 0){
        return 0;
    }

    // aloca memória para as strings  após ler seus tamanhos
    char *s1 = malloc(n + 1);
    char *s2 = malloc(m + 1);
    char *subseq = malloc(n + 1); 

    if (scanf("%s %s", s1, s2) != 2){
        return 0;
    }

    int grau = 1;

    while (grau <= n) {
        // generate_subseq retorna 1 se encontrar uma subseq que não está em s2
        if (generate_subseq(0, 0, subseq, grau, s1, n, s2, m)) {
            break; 
        }
        grau++;
    }

    printf("%d\n", grau);

    free(s1);
    free(s2);
    free(subseq);

    return 0;
}