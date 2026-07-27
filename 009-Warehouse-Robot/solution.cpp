// this solution exercises file handling techniques but it can 
// be done by other methods
// unfortunately the only available solution is with file handling
// that makes it a bit tricky otherwise it's simple

// the solution assumes that data.txt contains nxn data with no 
// spaces as said in problem statement

// this solution uses direction arrays to showcase better logic building
// but the time complexity is same as taht of the previous solution 
// i.e., O(n)
// the previous commit holds the simpler solution, so you can roll back to see that one
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
    char** wareHouse = extractData(size);
    displayWareHouse(wareHouse, size);
    getRobotCell(size, rRow, rCol);
    setRobotCell(wareHouse, size, rRow, rCol);
    displayWareHouse(wareHouse, size);
    scanWareHouse(wareHouse, size, rRow, rCol);
    deleteWareHouse(wareHouse, size);
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
    
    // extract data from file into wareHouseay
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
    // creating lambda to process distance
    auto processDirections = [&](int dirRow, int dirCol) {
        int distance = 0;
        int row = rRow + dirRow;
        int col = rCol + dirCol;
        while (row >= 0 && row < size && col < size && col >= 0)    {
            distance++;
            if (wareHouse[row][col] == 'b')
                return distance;
            row += dirRow;
            col += dirCol;
        }
        return -1;
    };

    const char* labels[4] = {"Front", "Right", "Back", "Left"};
    int dirRow[4] = {-1, 0, 1, 0};
    int dirCol[4] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++) {
        std::cout << labels[i] << ": " << processDirections(dirRow[i], dirCol[i]) << std::endl;
    }
    return;
}