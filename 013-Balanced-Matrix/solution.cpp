#include <iostream>

char** getInput(int& rows);
void displayInput(char** input, int size);
void deleteInput(char** input, int rows);
int length(char* str);

// functions for balanced matrix
bool isSquareMatrix(char** input, int size);
bool isSumEqual(char** input, int size);
bool isDiagonalSumEqual(char** input, int size);

int main()  {
    int rows = 0;
    char** input = getInput(rows);
    displayInput(input, rows);
    deleteInput(input, rows);
    (isDiagonalSumEqual(input, rows)) ? std::cout << "T" : std::cout << "F";
    return 0;
}

char** getInput(int& rows)   {
    std::cout << "Enter Elements Consecutively for each Row! Hit Enter for new Row!" << std::endl;
    std::cout << "Hit Enter at an Empty Row to Stop!" << std::endl;

    // setup for 2d array
    int extendableCapacity = 2; 
    rows = 0;
    char** matrix = new char* [extendableCapacity];

    int size, counter;
    char* word = nullptr;

    // lambdas for both inner and outer capacity
    auto ensureInnerCapacity = [&]() {
        if (counter >= size)    {
            size *= 2;
            char* newWord = new char [size];
            for (int i = 0; i < counter; i++)
                newWord[i] = word[i];
            delete[] word;
            word = newWord;
        }
    };
    auto ensureOuterCapacity = [&]() {
        if (rows >= extendableCapacity) {
            extendableCapacity *= 2;
            char** newMatrix = new char* [extendableCapacity];
            for (int i = 0; i < rows; i++)
                newMatrix[i] = matrix[i];
            delete[] matrix;
            matrix = newMatrix;
        }
    };
    auto shrinkToExact = [&]() {
        char* exactSize = new char [counter + 1];
        for (int i = 0; i <= counter; i++)
            exactSize[i] = word[i];
        delete[] word;
        word = exactSize;
    };

    while (true)    {
        // setup for each row
        size = 10, counter = 0;
        word = new char [size];
        word[counter] = '\0';
        char ch;

        while (std::cin.get(ch) && ch != '\n')  {
            if (ch > '9' || ch < '0') {
                std::cout << "Skipped Non-Digit Characters" << std::endl;
                continue;
            }
            word[counter++] = ch;
            ensureInnerCapacity();
            word[counter] = '\0';
        }
        // check if empty row
        if (counter == 0)   {
            delete[] word;
            break;
        }
        // ensure no leaks on each row
        shrinkToExact();

        // ensure rows are available
        ensureOuterCapacity();

        matrix[rows++] = word;
    }
    return matrix;
}

void deleteInput(char** input, int rows)    {
    for (int i = 0; i < rows; i++)
        delete[] input[i];
    delete[] input;
    return;
}

void displayInput(char** input, int size)   {
    for (int i = 0; i < size; i++)  {
        for (int j = 0; j < length(input[i]); j++)
            std::cout << input[i][j] << " ";
        std::cout << std::endl;
    }
        
    return;
}

int length(char* str)   {
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

bool isSquareMatrix(char** input, int size) {
    for (int i = 0; i < size; i++)
        if (size != length(input[i]))
            return false;
    return true;
}

bool isSumEqual(char** input, int size) {
    for (int i = 0; i < size; i++)  {
        int rSum = 0, cSum = 0;
        for (int j = 0; j < length(input[i]); j++)  {
            rSum += input[i][j];
            cSum += input[j][i];
        }
        if (rSum != cSum) 
            return false;
    }
    return true;
}

bool isDiagonalSumEqual(char** input, int size) {
    int pj = 0, npj = size - 1;
    int pSum = 0, npSum = 0;
    for (int i = 0; i < size; i++)  {
        pSum += input[i][pj++];
        npSum += input[i][npj--];
    }
    if (pSum != npSum) 
        return false;
    return true;
}