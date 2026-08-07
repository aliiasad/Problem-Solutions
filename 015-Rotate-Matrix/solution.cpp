#include <iostream>

void rotateMatrix(int matrix[][3], int size);

int main()  {
    int matrix[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    rotateMatrix(matrix, 3);
    int size = 3;
    for (int i = 0; i < size; i++)  {
        for (int j = 0; j < size; j++)  {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

void rotateMatrix(int matrix[][3], int size)   {

    // transpose
    for (int i = 0; i < size; i++)  {
        for (int j = 0; j < i; j++)  {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }

    // swap rows
    for (int i = 0; i < size; i++)  {
        int start = 0, end = size - 1;
        while (start <= end)    {
            int temp = matrix[i][start];
            matrix[i][start] = matrix[i][end];
            matrix[i][end] = temp;
            start++, end--;
        }
    }
    return;
}