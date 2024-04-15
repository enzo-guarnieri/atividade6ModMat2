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

int** multiplyMatrixRowByArray(int rows, int cols, int matrix[][cols], int* factors) {
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


void printMatrizProblema2a(int **C, int m, int p, int*totalPrice) {
    printf("  Ferro | Madeira | Vidro | Tinta | Tijolo\n");
    for (int i = 0; i < 75; i++) {
        printf("-");
    }
    printf("\n");
    char *tipos[3] = {"Moderno", "Mediterraneo", "Colonial"};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            printf("%7d ", C[i][j]);
        }
        printf(" (%s) MATERIAL TOTAL: %d\n", tipos[i],totalPrice[i]);
    }
    for (int i = 0; i < 75; i++) {
        printf("-");
    }
    printf("\n");
    printf("\n");
}



void printMatrizProblema2b(int **C, int m, int p, int*totalPrice) {
    printf("  Ferro | Madeira | Vidro | Tinta | Tijolo\n");
    for (int i = 0; i < 75; i++) {
        printf("-");
    }
    printf("\n");
    char *tipos[3] = {"Moderno", "Mediterraneo", "Colonial"};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            printf("%7d ", C[i][j]);
        }
        printf(" (%s) MATERIAL TOTAL: %d\n", tipos[i],totalPrice[i]);
    }
    for (int i = 0; i < 75; i++) {
        printf("-");
    }
    printf("\n");
    printf("\n");
}

void printMatrizProblema2(int **F, int m, int p) {
    printf("Proteina | Gordura | Carboidratos\n");
    for (int i = 0; i < 75; i++) {
        printf("-");
    }
    printf("\n");
    char *grupos[2] = {"Maculino", "Feminino"};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            printf("%9d ", F[i][j]);
        }
        printf(" (%s)\n", grupos[i]);
    }
}

int getUserInput() {
    int input;
    int result;

    printf("Digite um inteiro: ");
    result = scanf("%d", &input);

    while (result != 1) {
        while (getchar() != '\n');
        printf("Erro: a entrada não é um inteiro.\n Tente novamente:");
        result = scanf("%d", &input);
    }
    return input;
}

int** createMatrix(int rows, int cols) {
    int** resultingMatrix = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Digite qual valor deseja para a posicao  LINHA[%d] COLUNA[%d] da matriz \n",i,j);
            resultingMatrix[i][j] = getUserInput();
        }
    }
    return resultingMatrix;
}


int main(void) {
    // EX 1
    printf("\n1.\n");
    printf("\nQuantas Linhas deseja na sua Matriz?:\n");
    int row1 = getUserInput();
    printf("\nQuantas Colunas deseja na sua Matriz?:\n");
    int col1 = getUserInput();
    int **matrixA  = createMatrix(row1,col1);
    printf("\n");

    printf("\nQuantas Linhas deseja na sua segunda Matriz?:\n");
    int row2 = getUserInput();
    printf("\nQuantas Colunas deseja na sua Matriz?:\n");
    int col2 = getUserInput();
    int **matrixB  = createMatrix(row1,col1);
    printf("\n");

    if(col1 == row2){
        int **matrixC = (int **)malloc(row1 * sizeof(int *));
        for (int i = 0; i < row1; i++) matrixC[i] = (int *)malloc(col2 * sizeof(int));
        recurMultMatriz(matrixA, matrixB, matrixC, row1, col1, col2, 0, 0, 0, 0);
        printf("Resultado:\n");
        printMatrix(matrixC,row1,col2);
        printf("");
          
    }
    else{
        printf("Não é possivel fazer a multiplicação dessas Matrizes.");
    }

    


    printf("\n\n");
    
    // EX 2a
    printf("\n2. Resolvendo o Problema 2 :\n");

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
    int** finalResultMatrix = multiplyMatrixRowByArray(rows, cols, matrix, quantities);
    int* totalCost = sumMatrixRows(rows,cols,finalResultMatrix);
    // Print the resulting matrix
    printf("Resulting Matrix:\n");
    printMatrizProblema2a(finalResultMatrix, rows, cols,totalCost);


    
    // EX 2b
    printf("\n2. Resolvendo o Problema 2b:\n");
    finalResultMatrix = multiplyMatrixColumnByArray(rows, cols, matrix, prices);
    totalCost = sumMatrixRows(rows,cols,finalResultMatrix);
    // Print the resulting matrix
    printf("Resulting Matrix:\n");
    printMatrizProblema2b(finalResultMatrix, rows, cols,totalCost);




    
    // Free the allocated memory
    freeMatrix(finalResultMatrix, rows);


    // EX 3
    printf("\n3. Resolvendo o Problema 3:\n");
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
