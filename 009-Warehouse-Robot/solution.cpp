// this solution exercises file handling techniques but it can 
// be done by other methods
// unfortunately the only available solution is with file handling
// that makes it a bit tricky otherwise it's simple

// the solution assumes that data.txt contains nxn data with no 
// spaces as said in problem statement

#include <iostream>
#include <fstream>

char** extractData(int& size);
void displayWareHouse(char** wareHouse, int size);

int main()  {
    int size = 0;
    char** arr = extractData(size);
    std::cout << size << std::endl;
    displayWareHouse(arr, size);
    return 0;
}

char** extractData(int& size) {
    std::ifstream inputFile("data.txt");
    if (!inputFile) {
        std::cout << "Couldn't open file!" << std::endl;
        return nullptr;
    }
    char ch;
    while (inputFile.get(ch) && ch != '\n') {
        if (ch != '\r')
            size++;
    }
    //inputFile.close();

    // declare NxN wareHouse
    char** wareHouse = new char* [size];
    for (int i = 0; i < size; i++)
        wareHouse[i] = new char [size];
    
    // reset file cursor
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);
    
    // extract data from file into array
    for (int i = 0; i < size; i++)  {
        for (int j = 0; j < size; j++)  {
            inputFile.get(wareHouse[i][j]);
        }
        char newline;
        inputFile.get(newline);
    }
    inputFile.close();
    return wareHouse;
}

void displayWareHouse(char** wareHouse, int size)   {
    for (int i = 0; i < size; i++)  {
        for (int j = 0; j < size; j++)  {
            std::cout << wareHouse[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return;
}