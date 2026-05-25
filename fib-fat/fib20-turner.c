#include <stdio.h>
#include <time.h>

#define N 1000000

#define fim_string -1
#define AP -2L // Abre Parenteses
#define FP -3L // Fecha Parenteses
#define K -4L
#define S -5L
#define I -6L
#define B -7L
#define C -8L
#define D -9L
#define E -10L
#define F -11L
#define Y -12L
#define ADD -13L
#define SUB -14L
#define MUL -15L
#define LT -16L
#define TRUE -17L
#define FALSE -18L
#define EQ -19L

static long entrada[N] = {Y, AP, B, AP, S, AP, S, AP, C, AP, C, I, 2, FP, LT, FP, I, FP, FP, AP, F, C, AP, S, AP, F, D, I, AP, C, AP, C, I, 2, FP, SUB, FP, FP, AP, F, B, I, AP, C, AP, C, I, 1, FP, SUB, FP, FP, FP, ADD, FP, FP, 20, fim_string};

static long saida[N];

void printar_array(long *array1)
{
    int i;
    int fimString = -1;
    for (i = 0; array1[i] != fimString; i++)
    {
        switch (array1[i])
        {
        case S:
            printf("S");
            break;
        case K:
            printf("K");
            break;
        case I:
            printf("I");
            break;
        case B:
            printf("B");
            break;
        case C:
            printf("C");
            break;
        case D:
            printf("D");
            break;
        case E:
            printf("E");
            break;
        case F:
            printf("F");
            break;
        case Y:
            printf("Y");
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
            printf("%ld ", array1[i]);
        }
    }
    printf("\n");
}

/*
 * Remove o parenteses da posição 0 e seu oposto
 */

void remove_parenteses(long *array1)
{
    int p = 0;
    int paren = 1;
    while (paren)
    {
        array1[p] = array1[p + 1];
        p++;
        if (array1[p] == AP)
        {
            paren++;
        }
        else if (array1[p] == FP)
        {
            paren--;
        }
    }
    p--;
    while (array1[p + 1] != fim_string && array1[p + 2] != fim_string)
    {
        array1[p] = array1[p + 2];
        p++;
    }
    array1[p] = fim_string;
}

/*
 * Procura o fim do conjunto de inteiros
 */
void casa_parenteses(long *array1, int *p)
{
    int paren = 1;
    int a = *p;
    while (paren)
    {
        unsigned int c = array1[a];
        if (c == AP)
        {
            paren++;
        }
        else if (c == FP)
        {
            paren--;
        }
        a++;
    }
    *p = a;
}

/*
 * Verifica se a posicao do array é um inteiro ou um conjunto de inteiros
 */
void acha_argumento(long *array1, int *p)
{
    int c = (*p)++;
    if (array1[c] == AP)
    {
        casa_parenteses(array1, p);
    }
}

/*
 * Kab = a
 */

void reduz_K(long *array1, long *array2)
{
    int A, nA;
    int n = 1;

    A = n;
    acha_argumento(array1, &n);

    nA = n - 1;
    acha_argumento(array1, &n);

    int k = 0;
    int i;

    for (i = A; i <= nA; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

/*
 * Sabc = ac(bc)
 */
void reduz_S(long *array1, long *array2)
{
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

    for (i = A; i <= nA; i++)
    {
        array2[k] = array1[i];
        k++;
    }
    for (i = c; i <= nc; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = b; i <= nb; i++)
    {
        array2[k] = array1[i];
        k++;
    }
    for (i = c; i <= nc; i++)
    {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = FP;
    k++;
    for (; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * Ia = a
 */
void reduz_I(long *array1, long *array2)
{
    int A, nA;
    int n = 1;

    A = n;

    acha_argumento(array1, &n);
    nA = n - 1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

/*
 * Bfgx = f(gx)
 */
void reduz_B(long *array1, long *array2)
{
    int f, nf;
    int G, nG;
    int X, nX;
    int n = 1;

    f = n;
    acha_argumento(array1, &n);
    nf = n - 1;
    G = n;
    acha_argumento(array1, &n);
    nG = n - 1;
    X = n;
    acha_argumento(array1, &n);
    nX = n - 1;

    int k = 0;
    int i;

    for (i = f; i <= nf; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = G; i <= nG; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (i = X; i <= nX; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

/*
 * Cfgx = fxg
 */
void reduz_C(long *array1, long *array2)
{
    int f, nf;
    int G, nG;
    int X, nX;
    int n = 1;

    f = n;
    acha_argumento(array1, &n);
    nf = n - 1;
    G = n;
    acha_argumento(array1, &n);
    nG = n - 1;
    X = n;
    acha_argumento(array1, &n);
    nX = n - 1;

    int k = 0;
    int i;

    for (i = f; i <= nf; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (i = X; i <= nX; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (i = G; i <= nG; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

/**
 * Dcfgx = c(fx)(gx)
 */
void reduz_D(long *array1, long *array2)
{
    int c, nc;
    int f, nf;
    int g, ng;
    int x, nx;

    int n = 1;

    c = n;
    acha_argumento(array1, &n);
    nc = n - 1;
    f = n;
    acha_argumento(array1, &n);
    nf = n - 1;
    g = n;
    acha_argumento(array1, &n);
    ng = n - 1;
    x = n;
    acha_argumento(array1, &n);
    nx = n - 1;

    int k = 0;
    int i;

    for (i = c; i <= nc; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = f; i <= nf; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (i = x; i <= nx; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    array2[k] = AP;
    k++;

    for (i = g; i <= ng; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (i = x; i <= nx; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

/*
 * Ecfgx = cf(gx)
 */
void reduz_E(long *array1, long *array2)
{
    int c, nc;
    int f, nf;
    int g, ng;
    int x, nx;
    int n = 1;

    c = n;
    acha_argumento(array1, &n);
    nc = n - 1;
    f = n;
    acha_argumento(array1, &n);
    nf = n - 1;
    g = n;
    acha_argumento(array1, &n);
    ng = n - 1;
    x = n;
    acha_argumento(array1, &n);
    nx = n - 1;

    int k = 0;
    int i;

    for (i = c; i <= nc; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (i = f; i <= nf; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = g; i <= ng; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (i = x; i <= nx; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

/*
 * Fcfgx=c(fx)g
 */
void reduz_F(long *array1, long *array2)
{
    int c, nc;
    int f, nf;
    int g, ng;
    int x, nx;
    int n = 1;

    c = n;
    acha_argumento(array1, &n);
    nc = n - 1;
    f = n;
    acha_argumento(array1, &n);
    nf = n - 1;
    g = n;
    acha_argumento(array1, &n);
    ng = n - 1;
    x = n;
    acha_argumento(array1, &n);
    nx = n - 1;

    int k = 0;
    int i;

    for (i = c; i <= nc; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = f; i <= nf; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (i = x; i <= nx; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (i = g; i <= ng; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

/*
 * Yx = x(Yx)
 */
void reduz_Y(long *array1, long *array2)
{
    int x, nx;
    int n = 1;

    x = n;
    acha_argumento(array1, &n);
    nx = n - 1;

    int k = 0;
    int i;

    for (i = x; i <= nx; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    array2[k] = Y;
    k++;

    for (i = x; i <= nx; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void swap_inteiro(long *array1, long *array2)
{
    if (array1[0] < 0L)
    {
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

    for (i = iB; i <= nB; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (i = iC; i <= nC; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = array1[0];
    k++;

    for (; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void add(long *array1, long *array2)
{
    int n = 3;
    int k = 1;

    array2[0] = array1[1] + array1[2];

    for (; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void sub(long *array1, long *array2)
{
    int n = 3;
    int k = 1;

    array2[0] = array1[1] - array1[2];

    for (; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void mul(long *array1, long *array2)
{
    int n = 3;
    int k = 1;

    array2[0] = array1[1] * array1[2];

    for (; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void lt(long *array1, long *array2)
{
    int n = 3;
    int k = 1;
    array2[0] = FALSE;

    if (array1[1] < array1[2])
    {
        array2[0] = TRUE;
    }

    for (; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void reduz_TRUE(long *array1, long *array2)
{
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

    for (i = iA; i <= nA; i++)
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

void reduz_FALSE(long *array1, long *array2)
{
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
    long *array1, *array2, *array3;
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
        case D:
            reduz_D(array1, array2);
            break;
        case F:
            reduz_F(array1, array2);
            break;
        case B:
            reduz_B(array1, array2);
            break;
        case K:
            reduz_K(array1, array2);
            break;
        case S:
            reduz_S(array1, array2);
            break;
        case C:
            reduz_C(array1, array2);
            break;
        case E:
            reduz_E(array1, array2);
            break;
        case Y:
            reduz_Y(array1, array2);
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
