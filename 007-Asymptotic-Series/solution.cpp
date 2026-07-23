#include <iostream>

void input (int& x, int& n);
void printTerm(int x, int n);
int factorial(int fact);
void series(int x, int n);
int pow(int x, int i);

int main()  {
    int x, n;
    input(x, n);
    series(x, n);
    return 0;
}

void input (int& x, int& n) {
    std::cout << "Enter x: " << std::endl;
    std::cin >> x;
    std::cout << "Enter n: " << std::endl;
    std::cin >> n;
    return;
}

void printTerm(int x, int n)    {
    for (int i = 1; i <= n; i++)
        std::cout << "(" << (2 * i) - 1 << "! / " << x << "^" << (2 * i) - 1 << ") + ";
    std::cout << std::endl;
    return;
}

int factorial(int fact)    {
    int n = 1;
    for (int i = 1; i <= fact; i++)
        n = n * i;
    return n;
}

int pow(int x, int i)   {
    int result = 1;
    while (i > 0)   {
        result *= x;
        i--;
    }
    return result;
}

void series(int x, int n)   {

    printTerm(x, n);
    std::cout << std::endl;
    double sum = 0;
    for (int i = 1; i <= 2 * n - 1; i += 2)
        sum += (double)factorial(i) / pow(x, i);
    std::cout << "Sum: " << sum << std::endl;
    return;
}
//(2n-1)! / x^(2n-1)