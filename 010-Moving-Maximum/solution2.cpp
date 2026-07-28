#include <iostream>

int* getInput(int& size);
void getWindowSize(int& winSize, int size);
int* movingMaximum(int* input, int sizeInput, int sizeWindow);
void displayWindow(int* window, int size);
void deleteInput(int* input);

int main()  {
    int size = 0, winSize = 0;
    int* input = getInput(size);
    getWindowSize(winSize, size);
    int* window = movingMaximum(input, size, winSize);
    displayWindow(window, size - winSize + 1);
    deleteInput(input);
    deleteInput(window);
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

int* movingMaximum(int* input, int sizeInput, int sizeWindow)  {
    int* window = new int [sizeInput - sizeWindow + 1];
    int* dq = new int [sizeInput];
    int front = 0, back = 0;
    int k = 0;

    for (int i = 0; i < sizeInput; i++) {
        while (front != back && input[dq[back - 1]] <= input[i])
            back--; // pop_back 
        dq[back++] = i; // push_back

        if (dq[front] <= i - sizeWindow)
            front++; // pop_front
        
        if (i >= sizeWindow - 1)
            window[k++] = input[dq[front]];
    }
    delete[] dq;
    return window;
}

void displayWindow(int* window, int size)    {
    std::cout << "[";
    for (int i = 0; i < size; i++)   {
        if (i == size - 1)
            std::cout << window[i] << "]";
        else
            std::cout << window[i] << ", ";
    }
    return;
}

void deleteInput(int* input)  {
    delete[] input;
    return;
}