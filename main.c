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

int** allocateMatrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}


int** multiplyMatrixColumnByArray(int rows, int cols, int matrix[rows][cols], int* factors) {
    int** result = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix[i][j] * factors[j];
        }
    }
    return result;
}

int** multiplyMatrixRowByArray(int rows, int cols, int** matrix, int* factors) {
    int** result = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix[i][j] * factors[i];
        }
    }
    return result;
}

int* sumMatrixRows(int rows, int cols, int** matrix ) {
    int* result = (int*)malloc(3 * sizeof(int));
    int total = 0;
    for (int i = 0; i < rows; i++) {
        total = 0;
        for (int j = 0; j < cols; j++) {
            total = total + matrix[i][j] ;
        }
        result[i] = total;
    }
    return result;
}


void printMatrizProblema1(int **C, int m, int p, int*totalPrice) {
    printf("Ferro | Madeira | Vidro | Tinta | Tijolo\n");
    printf("----------------------------------------\n");
    char *tipos[3] = {"Moderno", "Mediterraneo", "Colonial"};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            printf("%7d ", C[i][j]);
        }
        printf(" (%s) CUSTO TOTAL: R$ %d\n", tipos[i],totalPrice[i]);
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
    printf("\n1.\n");
    int input;
    int result;

    printf("Digite um inteiro: ");
    result = scanf("%d", &input);

    if (result == 1) {
        printf("Você digitou o inteiro: %d\n", input);
    } else {
        // Limpa o buffer de entrada
        while (getchar() != '\n');

        printf("Erro: a entrada não é um inteiro.\n");
    }

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


    printMatrix(C, m, p);

    for(int i = 0; i < m; i++) free(A[i]);
    free(A);
    for(int i = 0; i < n; i++) free(B[i]);
    free(B);
    for(int i = 0; i < m; i++) free(C[i]);
    free(C);

    printf("\n2. Resolvendo o Problema 1:\n");

    int matrix[3][5] = {
            {5, 20, 16, 7, 17},  // Moderno
            {7, 18, 12, 9, 21},  // Mediterrâneo
            {6, 25, 8, 5, 23}    // Colonial
    };
    // Given prices array
    int prices[5] = {15, 8, 5, 1, 10};
    int quantities[3] = {5,7,12};

    // Rows and columns
    int rows = 3, cols = 5;

    // Multiply the matrix by the column factors
    int** resultMatrix = multiplyMatrixColumnByArray(rows, cols, matrix, prices);
    int** finalResultMatrix = multiplyMatrixRowByArray(rows, cols, resultMatrix, quantities);
    int* totalCost = sumMatrixRows(rows,cols,finalResultMatrix);


    // Print the resulting matrix
    printf("Resulting Matrix:\n");
    printMatrizProblema1(finalResultMatrix, rows, cols,totalCost);


    // Free the allocated memory
    freeMatrix(resultMatrix, rows);
    freeMatrix(finalResultMatrix, rows);

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
