#include <iostream>

// required functions to be implemented
char* readParagraph();
char** readKeywords(int& keywordCount);
void removeDuplicateKeywords(char*& paragraph, char** keywords, int keywordCount);
void displayParagraph(const char* paragraph);
void deallocateMemory(char* paragraph, char** keywords, int keywordCount);

// helper functions to be implemented 
int len(const char*);
char* cpy(const char*, char*);
bool cmp(const char*, const char*);


int main()  {
    return 0;
}

// implementation of helper functions

int len(const char* str)    {
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

char* cpy(const char* src, char* dest)  {
    int i = 0;
    while (src[i] != '\0')  {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

bool cmp(const char* str1, const char* str2)    {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')  {
        if (str1[i] != str2[i])
            return false;
        i++;
    }
    return str1[i] == str2[i];
}

// implementation of required funstions

char* readParagraph()   {
    int size = 20, counter = 0;
    char temp[5001];
    char* paragraph = new char [size];

    while (std::cin >> temp)   {
        if (cmp(temp, "END"))
            break;

        if (counter > 0)    {
            if (counter >= size)    {
                size *= 2;

                char* newArray = new char [size];
                for (int i = 0; i < counter; i++)   
                    newArray[i] = paragraph[i];

                delete[] paragraph;
                paragraph = newArray;
            }
            paragraph[counter] = ' ';
            counter++;
        }

        for (int i = 0; i < len(temp); i++) {
            if (counter >= size)    {
                size *= 2;

                char* newArray = new char [size];
                for (int j = 0; j < counter; j++)
                    newArray[j] = paragraph[j];
                
                    delete[] paragraph;
                    paragraph = newArray;
            }
            paragraph[counter++] = temp[i];
        }
    }
    paragraph[counter] = '\0';

    char* exactSize = new char [counter + 1];
    cpy(exactSize, paragraph);
    delete[] paragraph;

    paragraph = exactSize;
    return paragraph;
}

char** readKeywords(int& keywordCount)  {
    int size = 0;
    
    char** keywords = new char* [size];
    char temp[5001];

    while (std::cin >> temp)    {
        if (keywordCount >= size)   {
            size *= 2;

            char** newArray = new char* [size];
            for (int i = 0; i < keywordCount; i++)
                newArray[i] = keywords[i];

            delete[] keywords;
            keywords = newArray;
        }

        keywords[keywordCount] = new char [len(temp) + 1];
        cpy(keywords[keywordCount], temp);
        keywordCount++;
    }
    char** exactSize = new char* [keywordCount];
    for (int i = 0; i < keywordCount; i++)
        cpy(keywords[i], exactSize[i]);
    
    delete keywords;
    keywords = exactSize;
    return keywords;
}