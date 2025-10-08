#include <stdio.h>
#include <stdlib.h>

// Dinamik olarak matris oluşturma fonksiyonu
// Function to create matrix dynamically
double** create_matrix(int rows, int cols) {
    double** matrix = (double**)malloc(rows * sizeof(double*)); 
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double)); 
    }
    return matrix;
}

// Bellekten matrisi serbest bırakma fonksiyonu
// Function to free the allocated memory for the matrix
void free_matrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]); 
    }
    free(matrix); 
}

// Matrisi ekrana yazdırma fonksiyonu
// Function to print the matrix to the screen
void print_matrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%5.f ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Kullanıcıdan matris girdisi alma fonksiyonu
// Function to input matrix from the user
void input_matrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Matris[%d][%d]: ", i, j);
            scanf("%lf", &matrix[i][j]);
        }
    }
}

// Matris toplama fonksiyonu
// Function for matrix addition
double** matrix_addition(double** A, double** B, int rows, int cols) {
    double** result = create_matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// Matris çıkarma fonksiyonu
// Function for matrix subtraction
double** matrix_subtraction(double** A, double** B, int rows, int cols) {
    double** result = create_matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

// Skaler çarpım fonksiyonu
// Scalar multiplication function
void scalar_multiplication(double** matrix, int rows, int cols, double scalar) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] *= scalar;
        }
    }
}

// Hadamard çarpımı fonksiyonu
// Hadamard product function
double** hadamard_product(double** A, double** B, int rows, int cols) {
    double** result = create_matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] * B[i][j];
        }
    }
    return result;
}

// Standart matris çarpımı fonksiyonu
// Standard matrix multiplication function
double** standard_matrix_multiplication(double** A, int rowsA, int colsA, double** B, int rowsB, int colsB) {
    if (colsA != rowsB) { 
        return NULL; // Boyutlar uyumsuzsa NULL döner
    }
    double** result = create_matrix(rowsA, colsB);
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
            for (int k = 0; k < colsA; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Kronecker çarpımı fonksiyonu
// Kronecker product function
double** kronecker_product(double** A, int rowsA, int colsA, double** B, int rowsB, int colsB) {
    int rowsR = rowsA * rowsB;
    int colsR = colsA * colsB;
    double** result = create_matrix(rowsR, colsR);
    
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsA; j++) {
            for (int k = 0; k < rowsB; k++) {
                for (int l = 0; l < colsB; l++) {
                    result[i * rowsB + k][j * colsB + l] = A[i][j] * B[k][l];
                }
            }
        }
    }
    return result;
}

int main() {
    int rowsA, colsA, rowsB, colsB, rows, cols, choice;

    while (1) { 
        printf("Yapmak istediginiz islemi secin:\n");
        printf("1. Matris Toplama\n");
        printf("2. Matris Cikarma\n");
        printf("3. Standart Matris Carpimi\n");
        printf("4. Kronecker Carpimi\n");
        printf("5. Hadamard Carpimi\n");
        printf("6. Skaler Carpim\n");
        printf("7. Cikis\n");
        scanf("%d", &choice);

        if (choice == 1 || choice == 2) { // Toplama veya çıkarma seçildiyse   //If addition or subtraction is selected
            printf("Matrisler icin satir ve sutun sayisini girin: ");
            scanf("%d %d", &rows, &cols);

            double** A = create_matrix(rows, cols);
            double** B = create_matrix(rows, cols);

            printf("Matris A elemanlarini girin:\n");
            input_matrix(A, rows, cols);
            printf("Matris B elemanlarini girin:\n");
            input_matrix(B, rows, cols);

            double** result;
            if (choice == 1) { 
                result = matrix_addition(A, B, rows, cols);
                printf("\nMatris Toplama Sonucu:\n");
            } else { 
                result = matrix_subtraction(A, B, rows, cols);
                printf("\nMatris Cikarma Sonucu:\n");
            }

            print_matrix(result, rows, cols);

            // Belleği serbest bırak
            //release memory
            free_matrix(A, rows);
            free_matrix(B, rows);
            free_matrix(result, rows);
        } 
        else if (choice == 3) { // Standart matris çarpımı      //Standard matrix multiplication
            printf("Matris A icin satir ve sutun sayisini girin: ");
            scanf("%d %d", &rowsA, &colsA);
            printf("Matris B icin satir ve sutun sayisini girin: ");
            scanf("%d %d", &rowsB, &colsB);

            if (colsA != rowsB) {
                printf("Matrisler carpilmaya uygun degil!\n");
                continue;
            }

            double** A = create_matrix(rowsA, colsA);
            double** B = create_matrix(rowsB, colsB);

            printf("Matris A elemanlarini girin:\n");
            input_matrix(A, rowsA, colsA);
            printf("Matris B elemanlarini girin:\n");
            input_matrix(B, rowsB, colsB);

            double** standard_result = standard_matrix_multiplication(A, rowsA, colsA, B, rowsB, colsB);
            if (standard_result) {
                printf("\nStandart Matris Carpimi Sonucu:\n");
                print_matrix(standard_result, rowsA, colsB);
                free_matrix(standard_result, rowsA);
            }

            free_matrix(A, rowsA);
            free_matrix(B, rowsB);
        } 
        else if (choice == 4) { // Kronecker çarpımı        //Kronecker matrix multiplication
            printf("Matris A icin satir ve sutun sayisini girin: ");
            scanf("%d %d", &rowsA, &colsA);
            printf("Matris B icin satir ve sutun sayisini girin: ");
            scanf("%d %d", &rowsB, &colsB);

            double** A = create_matrix(rowsA, colsA);
            double** B = create_matrix(rowsB, colsB);

            printf("Matris A elemanlarini girin:\n");
            input_matrix(A, rowsA, colsA);
            printf("Matris B elemanlarini girin:\n");
            input_matrix(B, rowsB, colsB);

            double** kronecker_result = kronecker_product(A, rowsA, colsA, B, rowsB, colsB);
            printf("\nKronecker Carpimi Sonucu:\n");
            print_matrix(kronecker_result, rowsA * rowsB, colsA * colsB);
            free_matrix(kronecker_result, rowsA * rowsB);

            free_matrix(A, rowsA);
            free_matrix(B, rowsB);
        }
        else if (choice == 5) { // Hadamard çarpımı     //Hadamard matrix multiplication
            printf("Matris A icin satir ve sutun sayisini girin: ");
            scanf("%d %d", &rowsA, &colsA);
            printf("Matris B icin satir ve sutun sayisini girin: ");
            scanf("%d %d", &rowsB, &colsB);

            if (rowsA != rowsB || colsA != colsB) {
                printf("Hadamard carpimi icin matrisler ayni boyutta olmalidir.\n");
                continue;
            }

            double** A = create_matrix(rowsA, colsA);
            double** B = create_matrix(rowsB, colsB);

            printf("Matris A elemanlarini girin:\n");
            input_matrix(A, rowsA, colsA);
            printf("Matris B elemanlarini girin:\n");
            input_matrix(B, rowsB, colsB);

            double** hadamard_result = hadamard_product(A, B, rowsA, colsA);
            printf("\nHadamard Carpimi Sonucu:\n");
            print_matrix(hadamard_result, rowsA, colsA);
            free_matrix(hadamard_result, rowsA);

            free_matrix(A, rowsA);
            free_matrix(B, rowsB);
        }
        else if (choice == 6) { // Skaler çarpım        //Scalar matrix multiplication

            double scalar;
            printf("Skaler carpim icin katsayiyi giriniz: ");
            scanf("%lf", &scalar);

            printf("Matris A icin satir ve sutun sayisini girin: ");
            scanf("%d %d", &rowsA, &colsA);

            double** A = create_matrix(rowsA, colsA);

            printf("Matris A elemanlarini girin:\n");
            input_matrix(A, rowsA, colsA);

            scalar_multiplication(A, rowsA, colsA, scalar);
            printf("\nSkaler Carpim Sonucu:\n");
            print_matrix(A, rowsA, colsA);

            free_matrix(A, rowsA);
        }
        else if (choice == 7) { // Çıkış        //Exit
            break;
        }
        else {
            printf("Gecersiz secim! Tekrar deneyin.\n");
        }
    }

    return 0;
}