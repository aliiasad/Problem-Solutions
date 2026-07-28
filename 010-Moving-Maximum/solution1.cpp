// this solution (solution1.cpp) uses simple technique
// of a nested loop traversal in order to slide the window 
// over given dataset

// the time complexity for this solution is O(nxk) and O(n^2) 
// in worst case (n approx. k) which is acceptable
// for this level of problem solving

// however there exists a method called deque method that runs in 
// O(n) time complexity but is a little hard to understand
// once the intuition kicks in, its not that difficult

// the other solution will first explain the method and then
// provide a simple check list or sequence to perform 
// in order to get respective solution

// for starting / beginner purposes, this solution is complete
// for logic testing


#include <iostream>

int* getInput(int& size);
void getWindowSize(int& winSize, int size);
void movingMaximum(int input[], int sizeInput, int sizeWindow);
void deleteInput(int* input);

int main()  {
    int size = 0, winSize = 0;
    int* input = getInput(size);
    getWindowSize(winSize, size);
    movingMaximum(input, size, winSize);
    deleteInput(input);
    return 0;
}

int* getInput(int& size) {
    std::cout << "Enter Elements for Input Array (Hit \"S\" to STOP)" << std::endl;
    int counter = 0, localSize = 10;
    int* input = new int [localSize];
    int num;
    // lambda to call for input
    auto ensureCapacity = [&]() {
        if (counter >= localSize)    {
            localSize *= 2;
            int* newInput = new int [localSize];
            for (int i = 0; i < counter; i++)
            newInput[i] = input[i];
            delete[] input;
            input = newInput;
            }
    };
    while (true)    {
        if (std::cin >> num)    {
            input[counter++] = num;
            ensureCapacity();
        }
        else {
            std::cin.clear();
            char ch;
            std::cin >> ch;
            if (ch == 'S' || ch == 's')
                break;
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

void getWindowSize(int& winSize, int size)    {
    std::cout << "Enter Size for Window (<= Input Size): " << std::endl;
    while (true)    {
        std::cin >> winSize;
        if (winSize <= size)
            break;
        else 
            std::cout << "Invalid Size! Try Again" << std::endl;
    }
    return;
}

void movingMaximum(int input[], int sizeInput, int sizeWindow)    {
    std::cout << "[";
    for (int i = 0; i < sizeInput - sizeWindow + 1; i++)    {
        int max = input[i];
        for (int j = 0; j < sizeWindow; j++)    {
            if (input[i + j] >= max)
                max = input[i + j];
        }
        if (i == sizeInput - sizeWindow)
            std::cout << max << "]";
        else 
            std::cout << max << ", ";
    }
    return;
}

void deleteInput(int* input)  {
    delete[] input;
}