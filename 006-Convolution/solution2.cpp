// this solution (solution2.cpp) uses pointers and heap 
// memory to implemnt the solution
// logic is consistent

// this code takes input for both arrays and doesn't use main()
// for implementation

// the following solution exercises the notion to not input any size 
// but calculate later and grow arrays

#include <iostream>

int* getInput(int& size);
int* getFilter(int& size);
int* convolution(int* input, int inputSize, int* filter, int filterSize);
void deleteArray(int* array, int size);
void displayConvolution(int* convolution, int inputSize, int filterSize);

int main()  {
    int sizeInput = 0, sizeFilter = 0;

    int* input = getInput(sizeInput);
    int* filter = getFilter(sizeFilter);

    if (sizeFilter >= sizeInput)    {
        std::cout << "Filter is larger than Input" << std::endl;
        return 0;
    }
    
    int* convolutedArray = convolution(input, sizeInput, filter, sizeFilter);

    displayConvolution(convolutedArray, sizeInput, sizeFilter);
    deleteArray(input, sizeInput);
    deleteArray(filter, sizeFilter);
    deleteArray(convolutedArray, sizeInput - sizeFilter + 1);
    return 0;
}

int* getInput(int& size) {
    std::cout << "Enter Elements for Input Array (Hit \"S\" to STOP)" << std::endl;
    int counter = 0, localSize = 10;
    int* input = new int [localSize];
    int num;
    while (true)    {
        if (std::cin >> num)    {
            input[counter++] = num;
            if (counter >= localSize)    {
                localSize *= 2;
                int* newInput = new int [localSize];
                for (int i = 0; i < counter; i++)
                    newInput[i] = input[i];
                delete[] input;
                input = newInput;
            }
        }
        else {
            // cin failed because non-numeric input was entered
            std::cin.clear(); // Reset cin error flag
            
            char ch;
            std::cin >> ch; // Read the single character entered
                
            if (ch == 'S' || ch == 's')
                break; // Stop loop cleanly
            else
                std::cout << "Invalid input! Try again." << std::endl;
        }
    }
    // make exact length
    int* exactLength = new int [counter];
    for (int i = 0; i < counter; i++)
        exactLength[i] = input[i];
    delete[] input;
    input = exactLength;
    size = counter;
    return input;
}

int* getFilter(int& size)   {
    std::cout << "Enter Elements for Filter Array (Hit \"S\" to STOP)" << std::endl;
    int counter = 0, localSize = 10;
    int* filter = new int [localSize];
    int num;
    while (true)    {
        if (std::cin >> num)    {
            filter[counter++] = num;
            if (counter >= localSize)    {
                localSize *= 2;
                int* newInput = new int [localSize];
                for (int i = 0; i < counter; i++)
                    newInput[i] = filter[i];
                delete[] filter;
                filter = newInput;
            }
        }
        else {
            // cin failed because non-numeric input was entered
            std::cin.clear(); // Reset cin error flag
            
            char ch;
            std::cin >> ch; // Read the single character entered
                
            if (ch == 'S' || ch == 's')
                break; // Stop loop cleanly
            else
                std::cout << "Invalid input! Try again." << std::endl;
        }
    }
    // make exact length
    int* exactLength = new int [counter];
    for (int i = 0; i < counter; i++)
        exactLength[i] = filter[i];
    delete[] filter;
    filter = exactLength;
    size = counter;
    return filter;
}

int* convolution(int* input, int inputSize, int* filter, int filterSize)    {
    int convolutionSize = inputSize - filterSize + 1;
    int* convolutedArray = new int [convolutionSize];
    for (int i = 0; i < convolutionSize; i++)   {
        int sum = 0;
        for (int j = 0; j < filterSize; j++)
            sum += input[i + j] * filter[j];
        convolutedArray[i] = sum;
    }
    return convolutedArray;
}

void deleteArray(int* array, int size)  {
    delete[] array;
    return;
}

void displayConvolution(int* convolution, int inputSize, int filterSize)    {
    std::cout << "[";
    for (int i = 0; i < inputSize - filterSize + 1; i++)    {
        if (i != inputSize - filterSize)
            std::cout << convolution[i] << ", ";
        else
            std::cout << convolution[i] << "]";
    }
    return;
}