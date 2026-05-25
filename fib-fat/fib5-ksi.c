
#include <stdio.h>
#include <time.h>

#define N 100000000

#define fim_string -1
#define AP -2L 
#define FP -3L 
#define K -4L
#define S -5L
#define I -6L
#define ADD -7L
#define SUB -8L
#define MUL -9L
#define LT -10L
#define TRUE -11L
#define FALSE -12L

static long long entrada[N] = {S, AP, K, AP, S, I, I, FP, FP, AP, S, AP, S, AP, K, S, FP, K, FP, AP, K, AP, S, I, I, FP, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, K, I, FP, FP, AP, S, AP, K, K, FP, AP, K, 2, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, LT, FP, FP, FP, FP, AP, K, I, FP, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, K, K, FP, I, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, K, I, FP, FP, AP, S, AP, K, K, FP, AP, K, 1, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, SUB, FP, FP, FP, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, K, K, FP, I, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, K, I, FP, FP, AP, S, AP, K, K, FP, AP, K, 2, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, SUB, FP, FP, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, ADD, FP, FP, FP, FP, 5, fim_string};

static long long saida[N];

void printar_array(long long *array1) {
    int i;
    int fimString = -1;
    for (i = 0; array1[i] != fimString; i++) {
        switch (array1[i]) {
        case S:
            printf("S");
            break;
        case K:
            printf("K");
            break;
        case I:
            printf("I");
            break;
        case FP:
            printf(")");
            break;
        case AP:
            printf("(");
            break;
        case ADD:
            printf("+");
            break;
        case SUB:
            printf("-");
            break;
        case MUL:
            printf("*");
            break;
        case LT:
            printf("<");
            break;
        case fim_string:
            break;
        default:
            printf("%lld ", array1[i]);
        }
    }
    printf("\n");
}

/*
 * Remove o parenteses da posição 0 e seu oposto
 */

void remove_parenteses(long long *array1) {
    int p = 0;
    int paren = 1;
    while (paren) {
        array1[p] = array1[p + 1];
        p++;
        if (array1[p] == AP) {
            paren++;
        }
        else if (array1[p] == FP) {
            paren--;
        }
    }
    p--;
    while (array1[p + 1] != fim_string && array1[p + 2] != fim_string) {
        array1[p] = array1[p + 2];
        p++;
    }
    array1[p] = fim_string;
}

/*
 * Procura o fim do conjunto de inteiros
 */
void casa_parenteses(long long *array1, int *p) {
    int paren = 1;
    int a = *p;
    while (paren) {
        unsigned int c = array1[a];
        if (c == AP) {
            paren++;
        }
        else if (c == FP) {
            paren--;
        }
        a++;
    }
    *p = a;
}

/*
 * Verifica se a posicao do array é um inteiro ou um conjunto de inteiros
 */
void acha_argumento(long long *array1, int *p) {
    int c = (*p)++;
    if (array1[c] == AP) {
        casa_parenteses(array1, p);
    }
}

/*
 * Kab = a
 */

void reduz_K(long long *array1, long long *array2) {
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

/*
 * Sabc = ac(bc)
 */
void reduz_S(long long *array1, long long *array2) {
    int A, nA;
    int b, nb;
    int c, nc;
    int n = 1;
    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    b = n;
    acha_argumento(array1, &n);
    nb = n - 1;
    c = n;
    acha_argumento(array1, &n);
    nc = n - 1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = c; i <= nc; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = b; i <= nb; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = c; i <= nc; i++) {
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

/*
 * Ia = a
 */
void reduz_I(long long *array1, long long *array2) {
    int A, nA;
    int n = 1;

    A = n;

    acha_argumento(array1, &n);
    nA = n - 1;

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

void swap_inteiro(long long *array1, long long *array2) {
    if (array1[0] < 0L) {
        return;
    }

    int iB, nB;
    int iC, nC;
    int n = 1;

    iB = n;
    acha_argumento(array1, &n);
    nB = n - 1;

    iC = n;
    acha_argumento(array1, &n);
    nC = n - 1;

    int k = 0;
    int i;

    for (i = iB; i <= nB; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (i = iC; i <= nC; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = array1[0];
    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void add(long long *array1, long long *array2) {
    int n = 3;
    int k = 1;

    array2[0] = array1[1] + array1[2];

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void sub(long long *array1, long long *array2) {
    int n = 3;
    int k = 1;

    array2[0] = array1[1] - array1[2];

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void mul(long long *array1, long long *array2) {
    int n = 3;
    int k = 1;

    array2[0] = array1[1] * array1[2];

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void lt(long long *array1, long long *array2) {
    int n = 3;
    int k = 1;
    array2[0] = FALSE;

    if (array1[1] < array1[2]) {
        array2[0] = TRUE;
    }

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void reduz_TRUE(long long *array1, long long *array2) {
    int iA, nA;
    int iB, nB;
    int n = 1;

    iA = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    iB = n;
    acha_argumento(array1, &n);
    nB = n - 1;

    int k = 0;
    int i;

    for (i = iA; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (n = n; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void reduz_FALSE(long long *array1, long long *array2) {
    int iA, nA;
    int iB, nB;
    int n = 1;

    iA = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    iB = n;
    acha_argumento(array1, &n);
    nB = n - 1;

    int k = 0;
    int i;

    for (i = iB; i <= nB; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (n = n; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

int main()
{
    long long *array1, *array2, *array3;
    array1 = entrada;
    array2 = saida;

    while (array1[1] != fim_string)
    {
        switch (array1[0])
        {
        case AP:
            remove_parenteses(array1);
            array2[0] = fim_string;
            break;
        case I:
            reduz_I(array1, array2);
            break;
        case K:
            reduz_K(array1, array2);
            break;
        case S:
            reduz_S(array1, array2);
            break;
        case ADD:
            add(array1, array2);
            break;
        case SUB:
            sub(array1, array2);
            break;
        case MUL:
            mul(array1, array2);
            break;
        case LT:
            lt(array1, array2);
            break;
        case TRUE:
            reduz_TRUE(array1, array2);
            break;
        case FALSE:
            reduz_FALSE(array1, array2);
            break;
        default:
            swap_inteiro(array1, array2);
            break;
        }
        array3 = array1;
        array1 = array2;
        array2 = array3;
    }

    printar_array(array1);
    printf("\nTempo = %lf\n", ((double)clock()) / CLOCKS_PER_SEC);
    return 0;
}
