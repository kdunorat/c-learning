#include <stdio.h>

int main(){
    int x1, y1, x2, y2, n;
    int x_met, y_met;
    int teste_n = 1;
    
    while(1){
        // lembrar que scanf retorna o inteiro numero de itens
        if (scanf("%d %d %d %d", &x1, &y1, &x2, &y2) != 4){
            break;
        }

        if (x1==0 && y1==0 && x2==0 && y2==0){
            break;
        }

        scanf("%d", &n);
        int n_caidos = 0;
        for(int i=0; i<n; i++){
            scanf("%d %d", &x_met, &y_met);
            if(y_met >= y2 && y_met <= y1 && x_met >= x1 && x_met <= x2){
                n_caidos ++;
            }  
        }
        
        printf("Teste %d\n", teste_n);
        printf("%d\n\n", n_caidos);
        teste_n ++;
    }

    return 0;

}
