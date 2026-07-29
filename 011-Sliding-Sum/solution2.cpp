#include <iostream>

int* getInput(int& inputSize);
void getWindowSize(int& windowSize, int inputSize);
int* slidingSum(int* input, int inputSize, int windowSize);
void displayResult(int* result, int inputSize, int windowSize);
void deleteStructure(int* arr);

int main()  {
    int inputSize = 0, windowSize = 0;;
    int* input = getInput(inputSize);
    getWindowSize(windowSize, inputSize);
    int* result = slidingSum(input, 7, 3);
    displayResult(result, inputSize, windowSize);
    deleteStructure(input);
    deleteStructure(result);
    return 0;
}

int* getInput(int& inputSize) {
    std::cout << "Enter Elements sseparated by \"Enter\". Hit \"S\" to Stop." << std::endl;
    int size = 10;
    int* input = new int [size];
    int num;
    // lambda to ensure capacity
    auto ensureCapacity = [&]() {
        if (inputSize + 1 >= size)    {
            size *= 2;
            int* tempInput = new int [size];
            for (int i = 0; i < inputSize; i++)
                tempInput[i] = input[i];
            delete[] input;
            input = tempInput;
        }
    };
    while (true)    {
        if (std::cin >> num)    {
           input[inputSize++] = num;
           ensureCapacity(); 
        }
        else {
            std::cin.clear();
            char ch;
            std::cin >> ch;
            if (ch == 'S' || ch == 's')
                break;
            else
                std::cout << "Invalid Input! Try again." << std::endl;
        }
    }
    // make exact length
    int* exactLength = new int [inputSize];
    for (int i = 0; i < inputSize; i++)
        exactLength[i] = input[i];
    delete[] input;
    input = exactLength;
    size = inputSize
;
    return input;
}

void getWindowSize(int& windowSize, int inputSize) {
    std::cout << "Enter Size of Window (<= Size of Input)" << std::endl;
    while (true) {
        std::cin >> windowSize;
        if (windowSize <= inputSize && windowSize >= 0)
            break;
        else 
            std::cout << "Invalid Size! Try Again" << std::endl;
    }
}

int* slidingSum(int* input, int inputSize, int windowSize)   {
    int* movingSum = new int [inputSize - windowSize + 1];
    int k = 0;
    int front = 0, back = 0;
    int sum = 0;
    while (back < inputSize)    {
        while (back - front < windowSize)
            sum += input[back++];
        movingSum[k++] = sum;
        sum -= input[front++]; 
    }
    return movingSum;
}

void displayResult(int* result, int inputSize, int windowSize)  {
    std::cout << "[";
    for (int i = 0; i < inputSize - windowSize + 1; i++)    {
        if (i == inputSize - windowSize)
            std::cout << result[i] << "]";
        else
            std::cout << result[i] << ", ";
    }
    return;
}

void deleteStructure(int* arr)    {
    delete[] arr;
}