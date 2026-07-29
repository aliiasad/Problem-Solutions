// this solution (solution1.cpp) contains O(nxk) time complexity solution
// the requirement of the problem is to implement O(n) so this solution will
// not be completely implemented

// you can use the remianing functions from the other solution (solution2.cpp)
// which implements O(n) average and worst case

// however this is completely valid and correct solution for given problem 
// fot beginner purposes


#include <iostream>

void slidingSum(int input[], int sizInput, int sizeWindow);

int main()  {
    int input[] = {3,1,4,1,5,9,2};
    slidingSum(input, 7, 3);
    return 0;
}

void slidingSum(int input[], int sizeInput, int sizeWindow)    {
    std::cout << "[";
    for (int i = 0; i < sizeInput - sizeWindow + 1; i++)    {
        int sum = 0;
        for (int j = 0; j < sizeWindow; j++)
            sum += input[i + j];
        if (i == sizeInput - sizeWindow)    
            std::cout << sum << "]";
        else
            std::cout << sum << ", ";
    }
    return;
}