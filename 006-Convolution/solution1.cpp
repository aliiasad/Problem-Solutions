// this solution is exactly according to waht is instructed in 
// problem statement
// if you wish to see an array returned and pointers/heap, check 
// solution2.cpp

#include <iostream>

void convolution(int input[], int sizeInput, int filter[], int sizeFilter);

int main()  {
    int input[6] = {1,2,3,4,5,6};
    int filter[3] = {1,4,2};
    convolution(input, 6, filter, 3);
    return 0;
}
// convolution can be perfomed sizeInput - sizeFilter + 1 total times
void convolution(int input[], int sizeInput, int filter[], int sizeFilter)  {
    std::cout << "[";
    for (int i = 0; i < sizeInput - sizeFilter + 1; i++)    {
        int sum = 0;
        for (int j = 0; j < sizeFilter; j++)
            sum += input[i + j] * filter[j];
        std::cout << sum;
        if (i != sizeInput - sizeFilter)
            std::cout << ", ";
        else 
            std::cout << "]";
    }
}