// this solution uses static (fixed-size) 2D arrays only.
// no pointers, no heap memory (no `new`/`delete` anywhere).
// logic is otherwise identical to the pointer/heap version (solution1.cpp)

#include <iostream>

const int MAX = 20;   // upper bound on rows/columns for this static solution

void inputMatrix(char matrix[MAX][MAX], int& rows);
int len(char str[]);
bool isSquareMatrix(char matrix[MAX][MAX], int rows);
bool isDiagonalPalindrome(char matrix[MAX][MAX], int rows);
bool isColumnPalindrome(char matrix[MAX][MAX], int rows);
bool isRowPalindrome(char matrix[MAX][MAX], int rows);
bool palindromeMatrix(char matrix[MAX][MAX], int rows);

int main()  {
    char matrix[MAX][MAX];
    int rows = 0;

    inputMatrix(matrix, rows);

    (palindromeMatrix(matrix, rows)) ? std::cout << "True" : std::cout << "False";
    std::cout << std::endl;

    return 0;
}

void inputMatrix(char matrix[MAX][MAX], int& rows)    {
    std::cout << "How many words (rows) do you want to enter? (MAX = 20)" << std::endl;
    std::cin >> rows;
    std::cin.ignore();

    std::cout << "Note that the length of each word should be less than 20" << std::endl;
    for (int i = 0; i < rows; i++)  {
        std::cout << "Enter Word #" << i + 1 << std::endl;
        int counter = 0;
        char ch;
        while (std::cin.get(ch) && ch != '\n')  {
            matrix[i][counter] = ch;
            counter++;
        }
        matrix[i][counter] = '\0';
    }
    return;
}

int len(char str[])  {
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

bool isSquareMatrix(char matrix[MAX][MAX], int rows)    {
    for (int i = 0; i < rows; i++)  {
        if (rows != len(matrix[i]))
            return false;
    }
    return true;
}

bool isDiagonalPalindrome(char matrix[MAX][MAX], int rows)  {
    int start_i = 0, start_j = 0;
    int end_i = rows - 1, end_j = rows - 1;

    while (start_i <= end_i && start_j <= end_j)   {
        if (matrix[start_i][start_j] != matrix[end_i][end_j])
            return false;
        else 
            start_i++, start_j++, end_i--, end_j--;
    }
    return true;
}

bool isColumnPalindrome(char matrix[MAX][MAX], int rows)    {
    for (int i = 0; i < rows; i++)  {
        int start = 0, end = rows - 1;
        while (start <= end)    {
            if (matrix[start][i] != matrix[end][i])
                return false;
            else 
                start++, end--;
        }
    }
    return true;
}

bool isRowPalindrome(char matrix[MAX][MAX], int rows)    {
    for (int i = 0; i < rows; i++)  {
        int start = 0, end = rows - 1;
        while (start <= end)    {
            if (matrix[i][start] != matrix[i][end])
                return false;
            else 
                start++, end--;
        }
    }
    return true;
}

bool palindromeMatrix(char matrix[MAX][MAX], int rows)  {
    if (isSquareMatrix(matrix, rows) && isDiagonalPalindrome(matrix, rows)
        && isColumnPalindrome(matrix, rows) && isRowPalindrome(matrix, rows))
        return true;
    return false;
}