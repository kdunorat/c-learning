#include <stdio.h>

int main() {
    int n, numero;
    int ultimo_marcado; 
    int contagem = 0;
    
    if (scanf("%d", &n) != 1) {
        return 0; 
    }
    
    if (scanf("%d", &numero) != 1) {
        return 0;
    }
    
    ultimo_marcado = numero;
    contagem = 1; // marca o primeiro numero
    
    for (int i = 1; i < n; i++) {
        if (scanf("%d", &numero) != 1) {
            return 0;
        }
        
        if (numero != ultimo_marcado) {
            contagem++; 
            ultimo_marcado = numero;
        }
    }
    
    printf("%d\n", contagem);
    
    return 0;
}