#include <stdio.h>

// retorna 1 se o ano for bissexto na Inglaterra, 0 caso contrario
int is_bissexto(int ano) {
    if (ano < 1752) {
        return (ano % 4 == 0);
    } else {
        return (ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0);
    }
}

// retorna o numero de dias em um determinado mes de um ano
int dias_no_mes(int mes, int ano) {
    if (mes == 2) {
        return 28 + is_bissexto(ano);
    }
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        return 30;
    }
    return 31;
}

// retorna 1 se a data for valida, se nao 0
int data_is_valida(int dia, int mes, int ano) {
    if (ano < 1 || mes < 1 || mes > 12 || dia < 1) {
        return 0;
    }
    if (dia > dias_no_mes(mes, ano)) {
        return 0;
    }
    // lida com o buraco de dias
    if (ano == 1752 && mes == 9 && dia > 2 && dia < 14) {
        return 0;
    }
    return 1;
}

// calcula o numero total de dias corridos desde 01/01/0001
long calcular_total_dias(int dia, int mes, int ano) {
    long total = 0;
    int i;

    // soma os dias dos anos completos que ja passaram
    for (i = 1; i < ano; i++) {
        total += 365 + is_bissexto(i);
    }

    // soma os dias dos meses completos do ano atual
    for (i = 1; i < mes; i++) {
        total += dias_no_mes(i, ano);
    }

    // soma os dias do mes atual
    total += dia;

    // ajusta para os 11 dias pulados
    if (ano > 1752 || (ano == 1752 && mes > 9) || (ano == 1752 && mes == 9 && dia >= 14)) {
        total -= 11;
    }

    return total;
}

int main() {
    int dia, mes, ano;
    // se o dia 01/01/0001 foi um sabado:
    const char* dias_semana[] = {"sabado", "domingo", "segunda", "terca", "quarta", "quinta", "sexta"};

    while (scanf("%d %d %d", &dia, &mes, &ano) == 3 && (dia != 0 || mes != 0 || ano != 0)) {
        printf("%02d/%02d/%04d: ", dia, mes, ano);
        if (data_is_valida(dia, mes, ano)) {
            long total_dias = calcular_total_dias(dia, mes, ano);            
            // o indice do dia da semana sera o resto da divisao por 7
            int indice_dia = (total_dias - 1) % 7; // faz o -1 pois o array começa em 0, para o dia 1 do ano 1 ser a posição 0
            printf("%s\n", dias_semana[indice_dia]);
        } else {
            printf("invalida\n");
        }
    }

    return 0;
}