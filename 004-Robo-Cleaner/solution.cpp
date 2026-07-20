// the solution contains minimal file handling practices
// but focuses on the logic instead

void readInput(char carpet[][8]);
void displayGrid(char carpet[][8]);
void getRobotPosition(int& robotRow, int& robotCol);
void markRobot(char carpet[][8], int row, int col);
void seeCarpet(char carpet[][8], int robotRow, int robotCol);

#include <iostream>
#include <fstream>

int main()  {
    char carpet[8][8];
    int row, col;

    readInput(carpet);
    getRobotPosition(row, col);
    markRobot(carpet, row, col);
    displayGrid(carpet);
    seeCarpet(carpet, row - 1, col - 1);

    return 0;
}

void readInput(char carpet[][8])    {
    std::ifstream inputFile("carpet.txt");

    if (!inputFile)     {
        std::cout << "Could not open file!" << std::endl;
        return;
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            inputFile.get(carpet[i][j]);
        }
        char newline;   // after 8 chars, there is a newline which is not needed
        inputFile.get(newline);
    }
    return;
}

void displayGrid(char carpet[][8])  {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << carpet[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return;
}

void getRobotPosition(int& robotRow, int& robotCol) {
    std::cout << "Enter Robot's Row (1-indexed): ";
    std::cin >> robotRow;
    std::cout << "Enter Robot's Column (1-indexed): ";
    std::cin >> robotCol;
    return;
}

void markRobot(char carpet[][8], int row, int col)    {
    carpet[row - 1][col - 1] = '*';
    return;
}

void seeCarpet(char carpet[][8], int robotRow, int robotCol)    {
    // storing dirty blocks
    int front = 0, back = 0, left = 0   , right = 0;

    // front of robot
    for (int i = robotRow - 1; i >= 0; i--) {
        if (carpet[i][robotCol] == 'd')
            front++;
    }

    // back of robot
    for (int i = robotRow + 1; i < 8; i++)  {
        if (carpet[i][robotCol] == 'd')
            back++;
    }

    // right of robot
    for (int i = robotCol + 1; i < 8; i++)  {
        if (carpet[robotRow][i] == 'd')
            right++;
    }

    // left of robot
    for (int i = 0; i < robotCol; i++)  {
        if (carpet[robotRow][i] == 'd')
            left++;
    }

    std::cout << "Number of Dirty Block at the Front are " << front << std::endl;
    std::cout << "Number of Dirty Block at the Back are " << back << std::endl;
    std::cout << "Number of Dirty Block at the Left are " << left << std::endl;
    std::cout << "Number of Dirty Block at the Right are " << right << std::endl;
    return;
}