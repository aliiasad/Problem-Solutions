#include <iostream>

int** getpestCount(int topLeftX, int topLeftY, int p_count[][10]);

int** getpestCount(int topLeftX, int topLeftY, int p_count[][10])  {

    int** result = new int* [4];

    int temp1[101], temp2[101], temp3[101], temp4[101];
    int idx1 = 0, idx2 = 0, idx3 = 0, idx4 = 0;

    for (int i = 0; i < 10; i++)    {
        for (int j = 0; j < 10; j++)    {
            
            // we always move rightward from starting point onj x axis (cols)
            int x = topLeftX + j;

            // we always move downward from starting point on y axis (rows)
            int y = topLeftY - i;

            // if the coordinates are both positive, put in Q1 --> row 0
            if (x >= 0 && y > 0) 
                temp1[idx1++] = p_count[i][j];

            // if coordinates are negative and positive, put in Q2 --> row 1
            else if (x < 0 && y > 0) 
                temp2[idx2++] = p_count[i][j];

            // if  coordinates are negative and negative, put in Q3 --> row 2
            else if (x < 0 && y <= 0) 
                temp3[idx3++] = p_count[i][j];

            // if  coordinates are positive and negative, put in Q4 --> row 3
            // also since example (pest.png) includes origin points in Q4 --> <= & >=
            else if (x >= 0 && y <= 0) 
                temp4[idx4++] = p_count[i][j];
        }
    }

    // for row 1/4
    result[0] = new int [idx1 + 1]; // +1 for sentinel
    // for row 2/4
    result[1] = new int [idx2 + 1]; // +1 for sentinel
    // for row 3/4
    result[2] = new int [idx3 + 1]; // +1 for sentinel
    // for row 4/4
    result[3] = new int [idx4 + 1]; // +1 for sentinel

    // putting values from temp buffers into result
    for (int i = 0; i < idx1; i++)
        result[0][i] = temp1[i];

    for (int i = 0; i < idx2; i++)
        result[1][i] = temp2[i];

    for (int i = 0; i < idx3; i++)
        result[2][i] = temp3[i];

    for (int i = 0; i < idx4; i++)
        result[3][i] = temp4[i];

    // putting -1
    result[0][idx1] = -1;
    result[1][idx2] = -1;
    result[2][idx3] = -1;
    result[3][idx4] = -1;

    return result;
}