/*
    MADE BY: HEITOR LEITE DE ALMEIDA
    RA: 245293
*/

#include <stdio.h>

int isCesarianLeap(int y) {
    if (y % 4 == 0) return 1;
    return 0;
}

int isGregorianLeap(int y, int m, int d) {
        if (y % 400 == 0) return 1;
        if (y % 100 == 0) return 0;
        if (y % 4 == 0) return 1;

    return 0;
}

int isGregorianCalendar(int y, int m, int d) {
    if (y < 1752) return 0;
    if (y == 1752 && (m < 9 || (m == 9 && d <= 2))) return 0;
    return 1;
}

/*
q is the day of the month
m is the month
K is the year of the century (year % 100)
J is the year divided by 100

h is the week day result (0 = sta, 1 = sunday, ..., 6 = friday)
*/
int zeller(int isGregorian, int y, int m, int d, int datesMonth[]) {
    if (m == 1) {
        m = 13;
        y--;
    }
    if (m == 2) {
        m = 14;
        y--;
    }

    int q = d;
    int k = y % 100;
    int j = y / 100;

    int h;
    if (isGregorian) {
        h = (q + (((m + 1) * 13) / 5) + k + (k / 4) + (j / 4) + (5 * j)) % 7;
    } else {
        h = (q + (((m + 1) * 13) / 5) + k + (k / 4) + 5 - j) % 7;
    }

    return h;
};

int isValidDate(int y, int m, int d, int datesMonth[], int isLeapYear) {
    if (y == 1752 && m == 9 && 2 < d && d < 14) return -1;

    /* I guess the exercise doesn't consider this rule below
     for evaluating an invalid date... If there's test case going wrong, maybe
     I need to enable this rule 
     */
    // if (y == 1582 && m == 10 && 4 < d && d < 15) return -1;

    if (y < 1 || m < 1 || m > 12 || d < 1) return 0;

    if (m == 2 && isLeapYear) {
        if (datesMonth[m] + 1 < d) return 0;
        return 1;
    }

    if (datesMonth[m] < d) return 0;

    return 1;
}

int main() {
    int y, m, d;
    scanf("%d %d %d\n", &d, &m, &y);

    int datesMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31};
    const char *weekDays[] = {"sabado", "domingo", "segunda", "terca", "quarta", "quinta", "sexta"};

    while (y != 0 && m != 0 && d != 0) {
        int isGregCal = isGregorianCalendar(y, m, d);
        int isLeap = isGregCal ? isGregorianLeap(y, m, d) : isCesarianLeap(y);
        int isValid = isValidDate(y, m, d, datesMonth, isLeap);

        if (isValid == 1) {
            int h = zeller(isGregCal, y, m, d, datesMonth);
            printf("%02d/%02d/%04d: %s\n", d, m, y, weekDays[h]);
        } else {
            printf("%02d/%02d/%04d: invalida\n", d, m, y);
        }

        scanf("%d %d %d", &d, &m, &y);
    }
    printf("\n");
    return 0;
}