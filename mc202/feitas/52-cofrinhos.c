#include <stdio.h>

int main(){
    int n, j, z;
    int teste_n = 1;
    while(1){
        if (scanf("%d", &n) != 1){
            break;
        }
        if (n==0){
            break;
        }
        int diff = 0;
        printf("Teste %d\n", teste_n);
        for (int i=0; i<n; i++){
            scanf("%d %d", &j, &z);  
            diff += (j - z);
            printf("%d\n", diff);
        }
        printf("\n");
        teste_n ++;
    }
    return 0;
}   