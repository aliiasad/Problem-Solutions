// the following solution (solution1.cpp) uses brute force calculation
// of the combination

// however this solution is compltely correct and acceptable
// for smaller values of n 

// the other solution (soution2.cpp) however, uses a general formula
// for calculation which may save from overflow errors

#include <iostream>

void binomialSeries(int n);
void printTerm(int n, int r);
long long factorial(int n);
void getInput(int& n);

int main()  {
    int n = 0;
    getInput(n);
    binomialSeries(n);
    return 0;
}

void getInput(int& n)  {
    std::cout << "Enter n: " << std::endl;
    while (true)    {
        std::cin >> n;
        if (n >= 0)
            break;
        else
            std::cout << "Invalid Input! Try Again" << std::endl;
    }
    return;
}

void printTerm(int n, int r)   {
    std::cout << n << "C" << r << " + ";
    return;
}

long long factorial(int n)    {
    long long fact = 1;
    for (int i = 1; i <= n; i++)
        fact *= i;
    return fact;
}

void binomialSeries(int n)  {
    for (int r = 0; r < n + 1; r++)
        printTerm(n, r);
    std::cout << std::endl;

    double sum = 0;
    long long coef = 1;
    for (int r = 0; r < n + 1; r++)
        sum = sum + (factorial(n) / ((factorial(r)) * factorial(n - r)));
    std::cout << "Sum = " << sum;
}