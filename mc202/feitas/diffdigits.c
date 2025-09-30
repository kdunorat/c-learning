/* 
    MADE BY: HEITOR LEITE DE ALMEIDA
    RA: 245293
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 10

int hasTwoEqualNums(int tryNum) {
    int number = tryNum;
    int hasAppearedArray[ARRAY_SIZE] = {0};

    while (number != 0) {
        int remainder = number % 10;
        if (hasAppearedArray[remainder] == 1) {
            return 1;
        } else {
            hasAppearedArray[remainder] = 1;
        }
        number /= 10;
    }

    return 0;
}

void loopThroughNums(int *counter, int firstNum, int lastNum) {
    int i = firstNum;
    int j = lastNum + 1;
    for (; i < j; i++) {
        int response = hasTwoEqualNums(i);

        if (response == 1) {
            continue;
        } else {
            (*counter)++;
        }
    }
}

int main() {
    int first, last;
    int counter = 0;

    scanf("%d", &first);
    scanf("%d", &last);

    loopThroughNums(&counter, first, last);

    printf("%d\n", counter);
    return 0;
}