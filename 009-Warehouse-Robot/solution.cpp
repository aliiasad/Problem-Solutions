// this solution exercises file handling techniques but it can 
// be done by other methods
// unfortunately the only available solution is with file handling
// that makes it a bit tricky otherwise it's simple

// the solution assumes that data.txt contains nxn data with no 
// spaces as said in problem statement

// Note that the current solution uses 4x identical loops
// the next commit/push will use direction arrays to exercise better logic building
// if you need simpler solution roll back to previous commit

#include <iostream>
#include <limits>
#include <fstream>

char** extractData(int& size);
void displayWareHouse(char** wareHouse, int size);
void deleteWareHouse(char** wareHouse, int size);
void getRobotCell(int size, int& rRow, int& rCol);
void setRobotCell(char**& wareHouse, int size, int& rRow, int& rCol);
void scanWareHouse(char** wareHouse, int size, int rRow, int rCol);

int main()  {
    int size = 0, rRow, rCol;
    char** arr = extractData(size);
    std::cout << size << std::endl;
    displayWareHouse(arr, size);
    getRobotCell(size, rRow, rCol);
    setRobotCell(arr, size, rRow, rCol);
    displayWareHouse(arr, size);
    scanWareHouse(arr, size, rRow, rCol);
    deleteWareHouse(arr, size);

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
        inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');    
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

void deleteWareHouse(char** wareHouse, int size)    {
    // delete each pointer to row
    for (int i = 0; i < size; i++)
        delete[] wareHouse[i];
    delete[] wareHouse;
    return;
}

void getRobotCell(int size, int& rRow, int& rCol) {
    std::cout << "Enter Row for Robot (0-indexed): " << std::endl;
    while (true)    {
        std::cin >> rRow;
        if (rRow >= 0 && rRow < size)
            break;
        else
            std::cout << "Invalid Cell! Try Again" << std::endl;  
    }
    std::cout << "Enter Column for Robot (0-indexed): " << std::endl;
    while (true)    {
        std::cin >> rCol;
        if (rCol >= 0 && rCol < size)
            break;
        else
            std::cout << "Invalid Cell! Try Again" << std::endl;  
    }
}

void setRobotCell(char**& wareHouse, int size, int& rRow, int& rCol) {  

    while (wareHouse[rRow][rCol] == 'b')    {
        std::cout << "Cannot overwrite a cell with box \'b\'!" << std::endl;
        getRobotCell(size, rRow, rCol);
    }
    // set position
    wareHouse[rRow][rCol] = '*';
    return;
}

void scanWareHouse(char** wareHouse, int size, int rRow, int rCol)  {
    int front = 0, left = 0, right = 0, back = 0;
    int i = 0;
    bool flagF = false, flagB = false, flagL = false, flagR = false;

    i = rRow - 1;
    while (i >= 0 && !flagF)    {
        front++;
        if (wareHouse[i][rCol] == 'b')
            flagF = true;
        i--;
    }
    i = rCol - 1;
    while (i >= 0 && !flagL)    {
        left++;
        if (wareHouse[rRow][i] == 'b')
            flagL = true;
        i--;
    }
    i = rRow + 1;
    while (i < size && !flagB)  {
        back++;
        if (wareHouse[i][rCol] == 'b')
            flagB = true;
        i++;
    }
    i = rCol + 1;
    while (i < size && !flagR)  {
        right++;
        if (wareHouse[rRow][i] == 'b')
            flagR = true;
        i++;
    }

    std::cout << "-1 means No Box in Sight in this Direction!" << std::endl;
    (flagF == true) ? std::cout << "Front: " << front : std::cout << "Front: " << -1;
    std::cout << std::endl;
    (flagR == true) ? std::cout << "Right: " << right : std::cout << "Right: " << -1;
    std::cout << std::endl;
    (flagB == true) ? std::cout << "Back: " << back : std::cout << "Back: " << -1;
    std::cout << std::endl;
    (flagL == true) ? std::cout << "Left: " << left : std::cout << "Left: " << -1;
    std::cout << std::endl;
    return;
}