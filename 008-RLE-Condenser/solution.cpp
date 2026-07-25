// this solution uses high level concepts to implement the 
// solution like lambda expressions, closure and first class 
// function logic along with dynamic resizing multiple times

// [&] means what ever variable is being used 
// inside this function is being used by reference


#include <iostream>

char* condense(char* word);

int main()  {
    char* word = "MISSISSIPPI";
    //std::cout << word[10];
    //std::cout << word;
    char* ans = condense(word);
    std::cout << ans;
    return 0;
}

char* condense(char* word)  {
    int counter = 0, i = 0;
    int size = 5, realSize = 0;
    char* condensedWord = new char [size];

    auto ensureCapacity = [&]()  {
        if (realSize + 1 >= size)   {
                size *= 2;
                char* temp = new char [size];
                for (int j = 0; j < realSize; j++)
                    temp[j] = condensedWord[j];
                delete[] condensedWord;
                condensedWord = temp;
            }
    };  
    while (word[i] != '\0') {
        char c = word[i];
        counter++, i++;

        if (word[i] != c)   {
            ensureCapacity();
            condensedWord[realSize++] = c;

            // counter logic for 9+ repititions
            int num = counter, d = 0;
            char digits[10];
            while (num > 0) {
                digits[d++] = (num % 10) + '0';
                num /= 10;
            }

            // iterate in reverse order
            for (int k = d - 1; k >= 0; k--)    {
                ensureCapacity();
                condensedWord[realSize++] = digits[k];
            }
            
            counter = 0;
        }
    }
    condensedWord[realSize] = '\0';

    // trim to exactSize
    char* exactSize = new char [realSize + 1];
    for (int j = 0; j <= realSize; j++)
        exactSize[j] = condensedWord[j];
    delete[] condensedWord;
    condensedWord = exactSize;
    return condensedWord;
}