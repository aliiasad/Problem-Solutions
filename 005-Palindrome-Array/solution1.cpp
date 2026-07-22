// this solution uses pointers and heap memory for complete implementation
// if you want to use static arrays and no pointers, consider other 
// solution (solution2.cpp)

// note that solution2.cpp is under work and not available at the current 
// moment

#include <iostream>

char** inputMatrix(int& rows);
int len(char* str);
void deleteMatrix(char** matrix, int& rows);
bool isSquareMatrix(char** matrix, int rows);
bool isDiagonalPalindrome(char** matrix, int rows);
bool isColumnPalindrome(char** matrix, int rows);
bool isRowPalindrome(char** matrix, int rows);
bool palindromeMatrix(char** matrix, int rows);

int main()  {
    int rows = 0;
    char** array = inputMatrix(rows);
    // for (int i = 0; i < rows; i++)
    //     std::cout << array[i] << std::endl;
    (palindromeMatrix(array, rows)) ? std::cout << "True" : std::cout << "False"; 
    deleteMatrix(array, rows);
    return 0;
}

char** inputMatrix(int& rows)    {
    std::cout << "How many words (rows) do you want to enter?" << std::endl;
    std::cin >> rows;
    std::cin.ignore();

    char** matrix = new char* [rows];

    for (int i = 0; i < rows; i++)  {
        std::cout << "Enter Word #" << i + 1 << std::endl;
        int size = 20, counter = 0;
        char* word = new char [size];
        char ch;
        while (std::cin.get(ch) && ch != '\n')  {
            word[counter++] = ch;
            if (counter >= size)    {
                size *= 2;
                char* newWord = new char [size];
                for (int i = 0; i < counter; i++)
                    newWord[i] = word[i];
                delete[] word;
                word = newWord;
            }
        }
        word[counter] = '\0';

        // make exact length
        char* exactSize = new char [counter + 1];
        for (int i = 0; i <= counter; i ++)
            exactSize[i] = word[i];
        delete[] word;
        word = exactSize;
        // place the word inside matrix
        matrix[i] = word;
    }
    return matrix;

}

int len(char* str)  {
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

void deleteMatrix(char** matrix, int& rows) {
    for (int i = 0; i < rows; i++)
        delete[] matrix[i];
    delete[] matrix;
}

bool isSquareMatrix(char** matrix, int rows)    {
    for (int i = 0; i < rows; i++)  {
        if (rows != len(matrix[i]))
            return false;
    }
    return true;
}

bool isDiagonalPalindrome(char** matrix, int rows)  {
    int start_i = 0, start_j = 0;
    int end_i = rows - 1 , end_j = rows - 1; // this step is only reached if square matrix

    while (start_i <= end_i && start_j <= end_j)   {
        if (matrix[start_i][start_j] != matrix[end_i][end_j])
            return false;
        else 
            start_i++, start_j++, end_i--, end_j--;
    }
    return true;
}

bool isColumnPalindrome(char** matrix, int rows)    {
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

bool isRowPalindrome(char** matrix, int rows)    {
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

bool palindromeMatrix(char** matrix, int rows)  {
    if (isSquareMatrix(matrix, rows) && isDiagonalPalindrome(matrix, rows)
        && isColumnPalindrome(matrix, rows) && isRowPalindrome(matrix, rows))
        return true;
    return false;
}