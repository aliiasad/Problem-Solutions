#include <iostream>

bool breadthFirstSearch(int** maze, int size);

int main()  {
    return 0;
}

bool breadthFirstSearch(int** maze, int size)   {
    if (maze[0][0] == 1)
        return false;

    long long maxSize = size * size;
    
    // creating firection arrays for rows and columns
    int rowOffset[4] = {0, 1, 0, -1};
    int colOffset[4] = {1, 0, -1, 0};

    // creating two differnet queues to handle rows and columns
    int* queueRow = new int [maxSize];
    int* queueCol = new int [maxSize];

    // since queue has a front (serving) and back (waiting), so two pointers
    int front = 0, back = 0;

    // creating a map that tracks visited cells (current and prev nighbours)
    bool** map = new bool* [maxSize];
    for (int i = 0; i < maxSize; i++)
        map[i] = new bool [maxSize]{false};

    // pushing first indices (row and col) into queues for checking
    queueRow[back] = 0;
    queueCol[back] = 0;
    
    // moving to back of queue
    back++;

    // maping these indices visited (the cell, true)
    map[0][0] = true;

    // calculating neighbours untill none left (queues are empty)
    while (front < back)    {

        // pushing the start of queues as cells to calculate
        int rowIndex = queueRow[front];
        int colIndex = queueCol[front];

        // poping the first indices from queues as they are being processed
        front++;

        // checking if the cells under processing are escape indices
        if (rowIndex == size - 1 && colIndex == size - 1)
            break;

        // if we haven't reached, we check all neighbours (max 4)
        for (int k = 0; k < 4; k++) {

            // calculating neighbours based on offsets we stored as arrays for ease
            int neighbouringRowIdx = rowIndex + rowOffset[k];
            int neighbouringColIdx = colIndex + colOffset[k];

            // if our calculated neighbour (each cell) is moving on a possible
            // track i.e., it is not hitting walls or boundary, we map it 
            if (neighbouringColIdx >= 0 && neighbouringColIdx <= size - 1 &&
                neighbouringRowIdx >= 0 && neighbouringRowIdx <= size - 1 &&
                maze[neighbouringRowIdx][neighbouringColIdx] == 0 && 
                !map[neighbouringRowIdx][neighbouringColIdx])   {
                    map[neighbouringRowIdx][neighbouringColIdx] = true;

                    // since we maped it, its part of queue and added to back
                    queueRow[back] = neighbouringRowIdx;
                    queueCol[back] = neighbouringRowIdx;

                    // moving back forward for more elements
                    back++;
                }
        }
    }
}