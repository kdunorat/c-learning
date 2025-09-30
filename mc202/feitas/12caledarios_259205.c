#include <stdio.h>

int verifica_bissexto(int ano){
    if (ano>=1752){
        if(ano%400 == 0 || (ano%4==0 && ano%100 != 0))//verifica se é ano bissexto, pós 1752
            return 1;

        else return 0;
    }
    else{
        if(ano%4==0) return 1; //caso o ano seja antes de 1752 e divisivel por 4, retorna verdadeiro para ano bissexto

        else return 0;
    }
}

int verifica_data(int dia, int mes, int ano){ //função para verificar se uma data é válida
    if (mes == 2) {
        if (verifica_bissexto(ano)) {
            return (dia >= 1 && dia <= 29);
        } else {
            return (dia >= 1 && dia <= 28);
        }
    }
    else if(ano == 1752 && mes == 9 && dia >= 3 && dia <= 13){
        return 0;
    }
    else if((mes<8 && mes%2 != 0) || (mes >= 8 && mes%2 == 0)){
        if(dia >=1 && dia <= 31)
            return 1;

        else
            return 0;
    }
    else{
        if(dia >=1 && dia <= 30)
            return 1;

        else
            return 0;
    }
}

int qual_dia(int dia, int mes, int ano){//função para verificar qual dia da semana
    int meses[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int cont = 0;
    if(dia == 1 && mes == 1 && ano == 1){
        return 1;
    }
    else{
        if(ano > 1752){
            ano -= 1; //subtrai 1 para contar até o ano da data e depois somar os meses e dias
            cont = ((ano-1752)*365) + (((ano-1752)/4) - 12 - ((ano-1752)/100) + ((ano-1752)/400)); 
            //subtrai 12 dias pois 11 dias foram pulados e o ponto de referencia é sexta (-1)
            ano += 1;
        }
        else{
            ano -= 1;
            cont = (ano*365) + (ano/4);
            ano += 1;
        }

        if(verifica_bissexto(ano)){//
            meses[1] += 1;
            for(int i = 0; i < mes-1; i++){
                cont += meses[i];
            }
            meses[1] -= 1;
        }
        else{
            for(int i = 0; i < mes-1; i++){
                cont += meses[i];
            }
        }
        if(ano == 1752){
            if(mes == 9 && dia >= 14) 
                cont += dia - 11;

            else if(mes > 9) 
                cont += dia - 11;

            else cont += dia;
        }
        else
            cont += dia;
        return (cont%7);
    }
}

int main(void){
    //declaração de variáveis
    int dia, mes, ano;

    //entrada de dados
    do{
        scanf("%d %d %d", &dia, &mes, &ano);
    
        if(verifica_data(dia, mes, ano)){
            switch(qual_dia(dia, mes, ano)){
                case 0:
                    printf("%02d/%02d/%04d: sexta\n", dia, mes, ano);
                    break;
                case 1:
                    printf("%02d/%02d/%04d: sabado\n", dia, mes, ano);
                    break;
                case 2:
                    printf("%02d/%02d/%04d: domingo\n", dia, mes, ano);
                    break;
                case 3:
                    printf("%02d/%02d/%04d: segunda\n", dia, mes, ano);
                    break;
                case 4:
                    printf("%02d/%02d/%04d: terca\n", dia, mes, ano);
                    break;
                case 5:
                    printf("%02d/%02d/%04d: quarta\n", dia, mes, ano);
                    break;
                case 6:
                    printf("%02d/%02d/%04d: quinta\n", dia, mes, ano);
                    break;
            }
        }
        else if(dia == 0 && mes == 0 && ano == 0)
            break;
        else
            printf("%02d/%02d/%04d: invalida\n", dia, mes, ano);
    }while(dia != 0 && mes!= 0 && ano != 0);
}