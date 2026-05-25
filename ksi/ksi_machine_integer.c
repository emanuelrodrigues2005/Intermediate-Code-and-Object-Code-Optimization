#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000

#define fim_string -1
#define AP -2
#define FP -3
#define K -4
#define S -5
#define I -6
#define lt -13
#define sub -14
#define mul -15
#define add -16

static int entrada[N] = {S, AP, K, AP, S, I, I, FP, FP, AP, S, AP, S, AP, K, S, FP, K, FP, AP, K, AP, S, I, I, FP, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, K, I, FP, FP, AP, S, AP, K, K, FP, AP, K, 2, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, lt, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, 1, FP, FP, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, K, I, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, K, K, FP, I, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, K, I, FP, FP, AP, S, AP, K, K, FP, AP, K, 1, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, sub, FP, FP, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, mul, FP, FP, FP, FP, 5, fim_string};

static int saida[N];

void casa_parenteses(int* array1, int* p) {
    int paren = 1;
    int c = *p;
    while (paren != 0) {
        if (array1[c] == AP) {
            paren++;
        } else if (array1[c] == FP) {
            paren--;
        }
        c++;
    }
    *p = c;
}

void acha_argumento(int* array1, int* p) {
    int c = *p;
    if (array1[c] == AP) {
        c++;
        casa_parenteses(array1, &c);
    } else {
        c++;
    }
    *p = c;
}

void reduzK(int* array1, int* array2) {
    int A, nA;
    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    acha_argumento(array1, &n);

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void reduzS(int* array1, int* array2) {
    int A, nA;
    int B, nB;
    int C, nC;
    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    B = n;
    acha_argumento(array1, &n);
    nB = n - 1;
    C = n;
    acha_argumento(array1, &n);
    nC = n - 1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = C; i <= nC; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = B; i <= nB; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = C; i <= nC; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void recebeParenteses(int* array1) {
    int c = 1;
    casa_parenteses(array1, &c);

    int i;
    for (i = 0; i < c - 2; i++) {
        array1[i] = array1[i + 1];
    }

    array1[i] = array1[i + 2];
    i++;
    while (array1[i + 2] != fim_string) {
        array1[i] = array1[i + 2];
        i++;
    }
    array1[i] = fim_string;
}

void printar_array(int* array1) {
    int i;
    for (i = 0; array1[i] != fim_string; i++) {
        switch (array1[i]) {
            case S: printf("S"); break;
            case K: printf("K"); break;
            case I: printf("I"); break;
            case FP: printf(")"); break;
            case AP: printf("("); break;
            case lt: printf("lt "); break;
            case sub: printf("sub "); break;
            case mul: printf("mul "); break;
            case add: printf("add "); break;
            default: printf("%d ", array1[i]); break;
        }
    }
    printf("\n");
}

int main() {
    int* array1 = entrada;
    int* array2 = saida;
    int* array3;

    while (array1[1] != fim_string) {
        switch (array1[0]) {
            case K:
                reduzK(array1, array2);
                break;
            case S:
                reduzS(array1, array2);
                break;
            case I:
                array1++;
                continue;
            case AP:
                recebeParenteses(array1);
                array2[0] = -99;
                break;
            default:
                break;
        }
        array3 = array1;
        array1 = array2;
        array2 = array3;
    }

    printar_array(array1);
    printf("Tempo = %lf\n", (double)clock() / CLOCKS_PER_SEC);

    return 0;
}