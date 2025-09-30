#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

int main(void){
    int quant_testes = 1;
    int casos;
    while(true){    // pega as entradas até que casos seja 0
        scanf("%d", &casos);
        if(casos == 0){
          quant_testes = 1;
            break;
        }
        int joaozinho;
        int cofre_joao = 0;
        int zezinho;
        int cofre_ze = 0;
        printf("Teste %d\n", quant_testes);
        for(int i = 0; i < casos; i++){  
            scanf("%d %d", &joaozinho, &zezinho);
            cofre_joao += joaozinho;
            cofre_ze += zezinho;
            printf("%d\n", (cofre_joao - cofre_ze));
        }
        printf("\n");
        quant_testes++;
    }
    return 0;
  }