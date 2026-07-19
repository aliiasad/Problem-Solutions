// this solution (solution1.cpp) exercises the use of pointers and 
// dynamic memory allocation techniques which may require extra 
// space to solve given problem. If you wish to solve the problem
// in place i.e., use no extra space (O(1)), you may visit other 
// solution (solution2.cpp)


// note that solution2.cpp is under work and not currently available

// constraints: no use of built-in strings (no data types and functions allowed)

#include <iostream>

int len (char* str);
char toLower (char c);
char* extractWord (char* sentence, int startIndex, int& endIndex);
bool compare(char* str1, char* str2);
void sortWord (char* extractedWord);
void writeBack(char* sentence, char* word, int start, int end);
void scrambleWord(char* sentence, char* targetWord);

int len(char* str)  {
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

char toLower(char c)   {
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

char* extractWord(char* sentence, int startIndex, int& endIndex)   {
    int size = 20, i = startIndex, counter = 0;
    char* extractedWord = new char [size];

    while (sentence[i] != ' ' && sentence[i] != '\0')   {
        extractedWord[counter++] = sentence[i++];
        if (counter >= size)    {
            size *= 4;
            char* newExtraction = new char [size];
            for (int j = 0; j < counter; j++)
                newExtraction[j] = extractedWord[j];
            delete[] extractedWord;
            extractedWord = newExtraction;
        }
    }
    extractedWord[counter] = '\0';
    endIndex = i;

    // trim extra space
    char* exactSize = new char [counter + 1];
    for (int i = 0; i <= counter; i ++)
        exactSize[i] = extractedWord[i];
    delete[] extractedWord;
    extractedWord = exactSize;
    return extractedWord;
}

// case in-sensitive comparison since it is not mentioned
bool compare(char* str1, char* str2)    {
    int i = 0;
    while (toLower(str1[i]) != '\0' && toLower(str2[i]) != '\0')  {
        if (toLower(str1[i]) != toLower(str2[i]))
            return false;
        i++;
    }
    return toLower(str1[i]) == toLower(str2[i]);
}

void sortWord(char* extractedWord) {
    int wordLength = len(extractedWord);
    for (int i = 0; i < wordLength - 1; i++)    {
        for (int j = 0; j < wordLength - i - 1; j++)    {
            if (extractedWord[j] > extractedWord[j + 1])    {
                char temp = extractedWord[j];
                extractedWord[j] = extractedWord[j + 1];
                extractedWord[j + 1] = temp;
            }
        }
    }
    return;
}

void writeBack(char* sentence, char* word, int start, int end)  {
    int j = 0;
    for (int i = start; i < end; i++)
        sentence[i] = word[j++];
    return;
}

void scrambleWord(char* sentence, char* targetWord)   {
    int start = 0, end;
    while (sentence[start] != '\0') {
        char* word = extractWord(sentence, start, end);

        if (compare(word, targetWord))  {
            sortWord(word);
            writeBack(sentence, word, start, end);
        }
        delete[] word;
        start = end + 1;
    }
    return;
}