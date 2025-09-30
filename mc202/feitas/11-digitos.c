#include <stdio.h>
#include <stdbool.h>


bool checa_repetido(int numero){
    int digitos_passados[10] = {0};
    int digito;

    while (numero>0){
        // isso pega o ultimo digito, exemplo: 123,4 -> 1234,5
        digito = numero % 10;

        if (digitos_passados[digito] == 1){
            return true;
        }

        digitos_passados[digito] = 1;
        
        numero /= 10; // agora vira 1234
    }

    return false;
}

int main(){
    int n, m;

    // leitura.
    scanf("%d", &n);
    scanf("%d", &m);

    int contador = 0;
    // itera no intervalo n a m.
    for (int i = n; i <= m; i++) {
        // incrementa o contador em caso de nao houver repetidos.
        if (!checa_repetido(i)) {
            contador++;
        }
    }

    printf("%d\n", contador);

    return 0;
}

