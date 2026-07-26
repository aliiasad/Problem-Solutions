// this solution uses high level concepts to implement the 
// solution like lambda expressions, closure and first class 
// function logic along with dynamic resizing multiple times

// [&] means what ever variable is being used 
// inside this function is being used by reference


#include <iostream>


int length(char* str);
char* extractWord(char* sentence, int startIndex, int& endIndex);
bool compare(char* str1, char* str2);
void writeBack(char*& sentence, char* targetWord, char* condensedWord,
                int start, int end);
char* condense(char* word);
void condenseWord(char*& sentence, char* targetWord);

int main()  {
    char* rawSentence = "The word MISSISSIPPI is long";
    int len = length(rawSentence);
    char* sentence = new char[len + 1];
    for (int i = 0; i <= len; i++) {
        sentence[i] = rawSentence[i];
    }

    char* word = "MISSISSIPPI";
    condenseWord(sentence, word);
    std::cout << sentence;
    return 0;
}

int length(char* str)   {
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

char* extractWord(char* sentence, int startIndex, int& endIndex)    {
    int size = 10, i = startIndex, counter = 0;
    char* extractedWord = new char[size];

    while (sentence[i] != '\0' && sentence[i] != ' ') {
        extractedWord[counter++] = sentence[i++];
        if (counter + 1 >= size)    {
            size *= 2;
            char* temp = new char [size];
            for (int j = 0; j < counter; j++)
                temp[j] = extractedWord[j];
            delete[] extractedWord;
            extractedWord = temp;
        }
    }
    extractedWord[counter] = '\0';
    endIndex = i;

    // trim to exact
    char* exactSize = new char [counter + 1];
    for (int j = 0; j <= counter; j++)
        exactSize[j] = extractedWord[j];
    delete[] extractedWord;
    extractedWord = exactSize;
    return extractedWord;
}

bool compare(char* str1, char* str2)    {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')  {
        if (str1[i] != str2[i])
            return false;
        else
            i++;
    }
    return str1[i] == str2[i];
}

void writeBack(char*& sentence, char* targetWord, char* condensedWord,
                int start, int end) {
                    int lengthCondensedWord = length(condensedWord),
                        lengthTargetWord = length(targetWord),
                        lengthSentence = length(sentence);
                    
                    int newLength = lengthSentence - lengthTargetWord
                                    + lengthCondensedWord + 1;

                    char* newSentence = new char [newLength];

                    int j = 0;

                    for (int i = 0; i < start; i++)
                        newSentence[j++] = sentence[i];

                    for (int i = 0; i < lengthCondensedWord; i++)

                        newSentence[j++] = condensedWord[i];
                    for (int i = end; i < lengthSentence; i++)
                        newSentence[j++] = sentence[i];

                    newSentence[j] = '\0';

                    delete[] sentence;
                    sentence = newSentence;
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

void condenseWord(char*& sentence, char* targetWord) {
    int start = 0, end;
    char* condensedWord = condense(targetWord);

    while (sentence[start] != '\0') {
        // skip leading spaces
        while (sentence[start] == ' ') {
            start++;
        }
        // break if nothing in sentence
        if (sentence[start] == '\0') break;

        char* word = extractWord(sentence, start, end);

        if (compare(word, targetWord)) {
            writeBack(sentence, targetWord, condensedWord, start, end);
            start += length(condensedWord);
        } else {
            start = end;
        }

        delete[] word;
    }
    delete[] condensedWord;
    return;
}