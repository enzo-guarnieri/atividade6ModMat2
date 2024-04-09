#include <stdio.h>
#include <stdlib.h>

void recurMultMatriz(int **A, int **B, int **C, int m, int n, int p, int i, int j, int k, int soma) {
    if (i == m) return;
    if (j == n) {
        C[i][k] = soma;
        if (k + 1 < p) recurMultMatriz(A, B, C, m, n, p, i, 0, k + 1, 0);
        else recurMultMatriz(A, B, C, m, n, p, i + 1, 0, 0, 0);
    } else {
        recurMultMatriz(A, B, C, m, n, p, i, j + 1, k, soma + A[i][j] * B[j][k]);
    }
}

void printMatrizProblema1(int **C, int m, int p) {
    printf("Tijolo | Tinta | Vidro | Madeira | Ferro\n");
    printf("----------------------------------------\n");
    char *tipos[3] = {"Moderno", "Mediterraneo", "Colonial"};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            printf("%7d ", C[i][j]);
        }
        printf(" (%s)\n", tipos[i]);
    }
}

void printMatrizProblema2(int **F, int m, int p) {
    printf("Proteina | Gordura | Carboidratos\n");
    printf("-------------------------------\n");
    char *grupos[2] = {"Adultos", "Criancas"};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            printf("%9d ", F[i][j]);
        }
        printf(" (%s)\n", grupos[i]);
    }
}

int main(void) {


    int m = 2, n = 3, p = 4;
    int **A = (int **)malloc(m * sizeof(int *));
    int **B = (int **)malloc(n * sizeof(int *));
    int **C = (int **)malloc(m * sizeof(int *));

    for(int i = 0; i < m; i++) A[i] = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) B[i] = (int *)malloc(p * sizeof(int));
    for(int i = 0; i < m; i++) C[i] = (int *)calloc(p, sizeof(int));


    A[0][0] = 4; A[0][1] = 2; A[0][2] = 6;
    A[1][0] = 2; A[1][1] = 5; A[1][2] = 3;
    B[0][0] = 5; B[0][1] = 2; B[0][2] = 4; B[0][3] = 1;
    B[1][0] = 2; B[1][1] = 3; B[1][2] = 1; B[1][3] = 0;
    B[2][0] = 1; B[2][1] = 2; B[2][2] = 7; B[2][3] = 6;

    recurMultMatriz(A, B, C, m, n, p, 0, 0, 0, 0);
    printf("\n1.\n");

    printMatrizProblema1(C, m, p);

    for(int i = 0; i < m; i++) free(A[i]);
    free(A);
    for(int i = 0; i < n; i++) free(B[i]);
    free(B);
    for(int i = 0; i < m; i++) free(C[i]);
    free(C);

    printf("\n2. Resolvendo o Problema 1:\n");

    int m1 = 3, n1 = 5, p1 = 1;
    int recursos[3][5] = {{17, 7, 16, 20, 5}, {21, 9, 12, 18, 7}, {23, 5, 8, 25, 6}};
    int quantidades[5][1] = {{5}, {7}, {12}, {0}, {0}};

    int **X = (int **)malloc(m1 * sizeof(int *));
    int **Y = (int **)malloc(n1 * sizeof(int *));
    int **Z = (int **)malloc(m1 * sizeof(int *));

    for (int i = 0; i < m1; i++) X[i] = (int *)malloc(n1 * sizeof(int));
    for (int i = 0; i < n1; i++) Y[i] = (int *)malloc(p1 * sizeof(int));
    for (int i = 0; i < m1; i++) Z[i] = (int *)malloc(p1 * sizeof(int));


    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < n1; j++) {
            X[i][j] = recursos[i][j];
        }
    }
    for (int i = 0; i < n1; i++) {
        Y[i][0] = quantidades[i][0];
    }

    recurMultMatriz(X, Y, Z, m1, n1, p1, 0, 0, 0, 0);
    printf("Recursos necessarios por tipo de casa:\n");
    printMatrizProblema1(Z, m1, p1);

    for (int i = 0; i < m1; i++) free(X[i]);
    free(X);
    for (int i = 0; i < n1; i++) free(Y[i]);
    free(Y);
    for (int i = 0; i < m1; i++) free(Z[i]);
    free(Z);

    printf("\n3. Resolvendo o Problema 2:\n");

    int m2 = 2, n2 = 2, p2 = 3;
    int participantes[2][2] = {{200, 120}, {100, 80}};
    int nutrientes[2][3] = {{20, 20, 20}, {30, 20, 10}};

    int **D = (int **)malloc(m2 * sizeof(int *));
    int **E = (int **)malloc(n2 * sizeof(int *));
    int **F = (int **)malloc(m2 * sizeof(int *));

    for (int i = 0; i < m2; i++) D[i] = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n2; i++) E[i] = (int *)malloc(p2 * sizeof(int));
    for (int i = 0; i < m2; i++) F[i] = (int *)malloc(p2 * sizeof(int));


    for (int i = 0; i < m2; i++) {
        for (int j = 0; j < n2; j++) {
            D[i][j] = participantes[i][j];
        }
    }
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < p2; j++) {
            E[i][j] = nutrientes[i][j];
        }
    }

    recurMultMatriz(D, E, F, m2, n2, p2, 0, 0, 0, 0);
    printf("Consumo total por grupo:\n");
    printMatrizProblema2(F, m2, p2);

    for (int i = 0; i < m2; i++) free(D[i]);
    free(D);
    for (int i = 0; i < n2; i++) free(E[i]);
    free(E);
    for (int i = 0; i < m2; i++) free(F[i]);
    free(F);

    return 0;
}
