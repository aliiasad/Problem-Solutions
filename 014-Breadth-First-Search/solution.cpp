#include <iostream>

bool breadthFirstSearch(int** maze, int size);

// test case added
int main() {
    int size = 4;
    int mazeData[4][4] = {
        {0, 0, 1, 0},
        {1, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 1, 1, 0}
    };

    int **maze = new int*[size];
    for (int i = 0; i < size; i++) {
        maze[i] = new int[size];
        for (int j = 0; j < size; j++)
            maze[i][j] = mazeData[i][j];
    }

    if (!breadthFirstSearch(maze, size)) {
        std::cout << "No path found." << std::endl;
    }

    for (int i = 0; i < size; i++) 
        delete[] maze[i];
    delete[] maze;

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

    // creating a queue to track the way back using indices that tell me
    // from where i reached the next cell
    int* queuePath = new int [maxSize];

    // since queue has a front (serving) and back (waiting), so two pointers
    int front = 0, back = 0;

    // creating a map that tracks visited cells (current and prev nighbours)
    bool** map = new bool* [maxSize];
    for (int i = 0; i < maxSize; i++)
        map[i] = new bool [maxSize]{false};

    // pushing first indices (row and col) into queues for checking
    queueRow[back] = 0;
    queueCol[back] = 0;

    // since i am starting from (0,0), i reached here from nowhere
    queuePath[back] = -1;
    
    // moving to back of queue
    back++;

    // maping these indices visited (the cell, true)
    map[0][0] = true;

    // maping a flag that tells whether I reached exit or not
    bool reached = false;

    // creating a container for my target index so that i can store its slot (x,y)
    int targetIndex = -1;

    // calculating neighbours untill none left (queues are empty)
    while (front < back)    {

        // before pushing starting indices, let's store from where we reached
        // the cell made by those indices to be pushed
        int currentIndex = front;

        // pushing the start of queues as cells to calculate
        int rowIndex = queueRow[front];
        int colIndex = queueCol[front];

        // poping the first indices from queues as they are being processed
        front++;

        // checking if the cells under processing are escape indices
        if (rowIndex == size - 1 && colIndex == size - 1)   {

            // before breaking the loop, let's store that last slot
            // by using current index as it is last one
            targetIndex = currentIndex;
            reached = true;
            break;
        }

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
                    queueCol[back] = neighbouringColIdx;

                    // push the current index before moving ahead 
                    queuePath[back] = currentIndex;

                    // moving back forward for more elements
                    back++;
                }
        }
    }

    // if we have reached the exit, we can retrieve our path
    // let's first clarify the idea --> we move to one previous possile 
    // neighbour from where we came and store it and then map the final
    // storage according to directions
    if (reached)    {

        // creating a container to store the index we used to reach exit
        int* pathSlots = new int [maxSize];
        int length = 0;

        // assigning my exit to an index
        int idx = targetIndex;

        // now we backtrack neighbours using indices we stored in queuePath
        // until we reach -1 (base index)
        // idea is that every value of pathqueue points to a slot that is its 
        // origin or simply previous closest/shortest path element and at last
        // the base is -1
        while (idx != -1)   {
            pathSlots[length++] = idx;
            idx = queuePath[idx];
        }

        // now the path contains the exact neighbour slots we used in reverse
        // order
        std::cout << "Shortest Path : " << std::endl;
        for (int i = length - 1; i > 0; i--)   {

            // here we calculate the slot from where we are and to where we wanna go
            int fromSlot = pathSlots[i];
            int toSlot = pathSlots[i - 1]; // since we are moving backwards

            // calculating from which row and col and to which row and col
            int fromRow = queueRow[fromSlot];
            int fromCol = queueCol[fromSlot];
            int toRow = queueRow[toSlot];
            int toCol = queueCol[toSlot];

            if (toCol == fromCol - 1)       // left to current
                std::cout << "left";
            else if (toCol == fromCol + 1)  // right to current
                std::cout << "right";
            else if (toRow == fromRow - 1)  // above current
                std::cout << "up";
            else if (toRow == fromRow + 1)  // below current
                std::cout << "down";

            if (i != 1)
                std::cout << ", ";
        }
        std::cout << std::endl;

        // free memory
        delete[] pathSlots;
    }
    delete[] queueRow;
    delete[] queueCol;
    delete[] queuePath;

    for (int i = 0; i < maxSize; i++) 
        delete[] map[i];
    delete[] map;

    return reached;
}