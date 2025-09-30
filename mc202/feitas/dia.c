#include <stdio.h>
#include <stdlib.h>
int main() {
    int(*v)[13][32] = malloc(sizeof(int)*10000*13*32);
    int dia = 6, meses[13];
    char* semana[7] = {"domingo","segunda","terca","quarta","quinta","sexta","sabado"};
    for (int i = 1; i < 13; i++) {
        if (i <= 7) {
            meses[i] = i%2;
        }
        else {
            meses[i] = (i%2 == 0);
        }
    }
    for (int i = 1; i < 10000; i++) {
        int bissexto;
        if (i <= 1752) {
            bissexto = (i%4 == 0);
        }
        else {
            bissexto = (i%4 == 0 && (i%100 != 0 || i%400 == 0));
        }
        for (int j = 1; j < 13; j++) {
            for (int k = 1; k < 32; k++) {
                if (((k <= 28) || (k <= 30 && j != 2) || (k == 31 && meses[j]) || (k == 29 && bissexto)) && !(k < 13 && k >= 2 && j == 9 && i == 1752)) {
                    v[i][j][k] = dia;
                    dia = (dia + 1)%7;
                }
                else {
                    v[i][j][k] = -1;
                }
            }
        }
    }
    v[1752][9][13] = -1;
    while (1) {
        int dia,mes,ano;
        scanf("%d %d %d",&dia,&mes,&ano);
        if (dia == 0 && mes == 0 && ano == 0) {
            return 0;
        }
        int resp = v[ano][mes][dia];
        char* c;
        if (resp == -1) {
            c = "invalida";
        }
        else {
            c = semana[resp];
        }
        printf("%02d/%02d/%04d: %s\n",dia,mes,ano,c);
    }
    return 0;
}