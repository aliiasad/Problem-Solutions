// this extended solution uses heap memory and pointers to return not only
// the dirty cell count but the coordinates for them too in clockwise 
// direction from the front 

#include <iostream>
#include <fstream>

char** readInput();
void displayCarpet(char** carpet);
void deleteCarpet(char** carpet);
void markRobot(char** carpet);
void seeCarpet(char** carpet);
int** getDirtyCells(char** carpet, int& count);
void deleteCoordinateContainer(int** container, int count);
void displayCoordinates(int** cells, char** carpet, int count);

int main()  {
    int count = 0;
    char** carpet = readInput();
    displayCarpet(carpet);
    markRobot(carpet);
    displayCarpet(carpet);
    seeCarpet(carpet);
    int** cells = getDirtyCells(carpet, count);
    displayCoordinates(cells, carpet, count);
    deleteCarpet(carpet);
    deleteCoordinateContainer(cells, count);

    return 0;
}

char** readInput()   {
    // declare a 2d-array (pointer-to-pointer)
    char** carpet = new char* [8];
    for (int i = 0; i < 8; i++)
        carpet[i] = new char [8];
    
    // read data from text file
    std::ifstream inputFile("carpet.txt");
    if (!inputFile) {
        std::cout << "Could not open file!" << std::endl;
        return carpet;
    }   
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            inputFile.get(carpet[i][j]);
        char newline;
        inputFile.get(newline);     // waste the \n from txt file
    }
    return carpet;
}

void displayCarpet(char** carpet)   {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            std::cout << carpet[i][j] << " ";
        std::cout << std::endl;
    }
    return;
}

void deleteCarpet(char** carpet)    {
    for (int i = 0; i < 8; i++)
        delete[] carpet[i];
    delete[] carpet;
    return;
}

void markRobot(char** carpet)   {
    int row, col;
    std:: cout << "Enter Row and Column (0-based): " << std::endl;
    std::cin >> row >> col;
    carpet[row][col] = '*';
    return;
}

void seeCarpet(char** carpet)   {
    int row, col;
    // retrive robot's coordinates
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (carpet[i][j] == '*')
                row = i, col = j;
        }
    }

    int front = 0, back = 0, left = 0   , right = 0;

    // front
    for (int i = 0; i < row; i++)
        if (carpet[i][col] == 'd')
            front++;
    // back
    for (int i = row + 1; i < 8; i++)
        if (carpet[i][col] == 'd')
            back++;
    // left
    for (int i = 0; i < col; i++)
        if (carpet[row][i] == 'd')
            left++;
    //right
    for (int i = col + 1; i < 8; i++)
        if (carpet[row][i] == 'd')
            right++;

    std::cout << "Number of Dirty Block at the Front are " << front << std::endl;
    std::cout << "Number of Dirty Block at the Back are " << back << std::endl;
    std::cout << "Number of Dirty Block at the Left are " << left << std::endl;
    std::cout << "Number of Dirty Block at the Right are " << right << std::endl;
    return;
}

int** getDirtyCells(char** carpet, int& count)     {
    // locate robot
    int row, col;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (carpet[i][j] == '*')
                row = i, col = j;
    
    // count total dirty cells
    count = 0;
    for (int i = 0; i < row; i++)
        if (carpet[i][col] == 'd') 
            count++;   // front

    for (int j = col + 1; j < 8; j++)
        if (carpet[row][j] == 'd') 
            count++;   // right

    for (int i = row + 1; i < 8; i++)
        if (carpet[i][col] == 'd') 
            count++;   // back

    for (int j = 0; j < col; j++)
        if (carpet[row][j] == 'd') 
            count++;    // left

    // create a (poniter to pointer) 2d array to store coordinates
    int** dirtyCellsInVision = new int* [count];

    // tranverse robot's vision
    int k = 0;
    // front
    for (int i = 0; i < row; i++)   {
        if (carpet[i][col] == 'd')    {
            dirtyCellsInVision[k] = new int [2];
            dirtyCellsInVision[k][0] = i;
            dirtyCellsInVision[k][1] = col;
            k++;
        }
    }
    // right
    for (int j = col + 1; j < 8; j++)   {
        if (carpet[row][j] == 'd')    {
            dirtyCellsInVision[k] = new int [2];
            dirtyCellsInVision[k][0] = row;
            dirtyCellsInVision[k][1] = j;
            k++;
        }
    }
    // back
    for (int i = row + 1; i < 8; i++)   {
        if (carpet[i][col] == 'd')    {
            dirtyCellsInVision[k] = new int [2];
            dirtyCellsInVision[k][0] = i;
            dirtyCellsInVision[k][1] = col;
            k++;
        }
    }
    // left
    for (int j = 0; j < col; j++)   {
        if (carpet[row][j] == 'd')    {
            dirtyCellsInVision[k] = new int [2];
            dirtyCellsInVision[k][0] = row;
            dirtyCellsInVision[k][1] = j;
            k++;
        }
    }
    return dirtyCellsInVision;
}

void deleteCoordinateContainer(int** container, int count)    {
    for (int i = 0; i < count; i++)
        delete[] container[i];
    delete[] container;
    return;
}

void displayCoordinates(int** cells, char** carpet, int count)    {
    int row, col;
    // retrive robot's coordinates
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (carpet[i][j] == '*')
                row = i, col = j;
        }
    }

    int front = 0, back = 0, left = 0   , right = 0;

    // front
    for (int i = 0; i < row; i++)
        if (carpet[i][col] == 'd')
            front++;
    // back
    for (int i = row + 1; i < 8; i++)
        if (carpet[i][col] == 'd')
            back++;
    // left
    for (int i = 0; i < col; i++)
        if (carpet[row][i] == 'd')
            left++;
    //right
    for (int i = col + 1; i < 8; i++)
        if (carpet[row][i] == 'd')
            right++;

    std::cout << "Coordinates of Dirty Cells in Front of Robo-Cleaner:" << std::endl;
    if (front == 0)
        std::cout << "None" << std::endl;
    for (int i = 0; i < front; i++) 
        std::cout << "(" << cells[i][0] << ", " << cells[i][1] << ")" << std::endl;


    std::cout << "Coordinates of Dirty Cells to the Right of Robo-Cleaner:" << std::endl;
    if (right == 0)
        std::cout << "None" << std::endl;
    for (int i = front; i < front + right; i++) 
        std::cout << "(" << cells[i][0] << ", " << cells[i][1] <<")" << std::endl;

    
    std::cout << "Coordinates of Dirty Cells to the Back of Robo-Cleaner:" << std::endl;
    if (back == 0)
        std::cout << "None" << std::endl;
    for (int i = front + right; i < front + right + back; i++) 
        std::cout << "(" << cells[i][0] << ", " << cells[i][1] << ")" << std::endl;

    std::cout << "Coordinates of Dirty Cells to the Left of Robo-Cleaner:" << std::endl;
    if (left == 0)
        std::cout << "None" << std::endl;
    for (int i = front + right + back; i < count; i++) 
        std::cout << "(" << cells[i][0] << ", " << cells[i][1] << ")" << std::endl;

    return;
}