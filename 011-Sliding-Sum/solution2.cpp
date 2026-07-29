#include <iostream>

int* getInput(int& counter);
void getWindowSize(int& windowSize, int counter);
void slidingSum(int input[], int inputSize, int windowSize);

int main()  {
    int input[] = {3,1,4,1,5,9,2};
    slidingSum(input, 7, 3);
    return 0;
}

int* getInput() {
    std::cout << "Enter Elements sseparated by \"Enter\". Hit \"S\" to Stop." << std::endl;
    int size = 10, counter = 0;
    int* input = new int [size];
    int num;
    // lambda to ensure capacity
    auto ensureCapacity = [&]() {
        if (counter + 1 >= size)    {
            size *= 2;
            int* tempInput = new int [size];
            for (int i = 0; i < counter; i++)
                tempInput[i] = input[i];
            delete[] input;
            input = tempInput;
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
                std::cout << "Invalid Input! Try again." << std::endl;
        }
    }
}

void getWindowSize(int& windowSize, int counter) {
    std::cout << "Enter Size of Window (<= Size of Input)" << std::endl;
    std::cin >> windowSize;
    while (true) {
        std::cin >> windowSize;
        if (windowSize > counter && windowSize <= 0)
            break;
        else 
            std::cout << "Invalid Size! Try Again" << std::endl;
    }
}

void slidingSum(int input[], int inputSize, int windowSize)   {
    int front = 0, back = 0;
    int sum = 0;
    std::cout << "[";
    while (back < inputSize)    {
        while (back - front < windowSize)
            sum += input[back++];
        if (back == inputSize)
            std::cout << sum << "]";
        else
            std::cout << sum << ", ";
        sum -= input[front++]; 
    }
    return;
}