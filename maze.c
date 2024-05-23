#include <stdio.h>
#include <unistd.h> // for sleep and usleep functions

#define ROWS 12
#define COLS 12

// viusalise directions as {N, E, S, W} with directions as array index e.g. 0 -> N

void printGrid(char grid[ROWS][COLS], int rows, int cols);
int mazeTraverse(char maze[ROWS][COLS], int row, int col, int start_row, int start_col, int direction, int moveNumber);
int isValidMove(char grid[ROWS][COLS], int row, int col, int changeY, int changeX);
char getDirectionChar(int);

void printGrid(char grid[ROWS][COLS], int rows, int cols) {
    printf("\033[H\033[J"); // Clear screen ANSI escape code
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    usleep(200000); // Delay of 200 milliseconds
}

int isValidMove(char grid[ROWS][COLS], int row, int col, int changeY, int changeX) {
    int newY = row + changeY;
    int newX = col + changeX;

    if (newY < 0 || newX < 0) {
        return 0; // out of bounds move
    } else if (newY >= ROWS || newX >= COLS) {
        return 0; // out of bounds move
    } else if (grid[newY][newX] == '#') {
        return 0; // that's a wall
    } else {
        return 1; // not out of bounds or dead end movement
    }
}

char getDirectionChar(int number) {
    switch (number) {
        case 0:
            return 'N';
        case 1:
            return 'E';
        case 2:
            return 'S';
        case 3:
            return 'W';
        default:
            return '?';
    }
}

int mazeTraverse(char maze[ROWS][COLS], int row, int col, int start_row, int start_col, int direction, int moveNumber) {
    int vectors[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // Up, Right, Down, Left
    
    //printf("Step %d: Currently in row = %d, col = %d, facing: %c.\n", moveNumber, row, col, getDirectionChar(direction)); // just to monitor algorithm for debugging
    if (maze[row][col] != 'x') {
        maze[row][col] = 'x';
    }
    printGrid(maze, ROWS, COLS);
    
    // baseCase - arrived at exit.
    if ((row == 0 || row == ROWS - 1 || col == 0 || col == COLS - 1) && (row != start_row || col != start_col)) {
        puts("");
        printf("Maze successfully traversed in %d moves!\n", moveNumber);
        return 1;
    }

    // base case - arrived back at start.
    if (row == start_row && col == start_col && moveNumber != 0) {
        puts("");
        printf("Maze traversal failed! %d moves taken.\n", moveNumber);
        return 0;
    }

    // proceed algorithm - recursive case.
    int newDirection = (direction + 1) % 4; // by default try and turn right  
    int changeY = vectors[newDirection][0];
    int changeX = vectors[newDirection][1];

    if (isValidMove(maze, row, col, changeY, changeX)) {
        return mazeTraverse(maze, row + changeY, col + changeX, start_row, start_col, newDirection, moveNumber + 1);
    } else {
        changeY = vectors[direction][0];
        changeX = vectors[direction][1];

        if (isValidMove(maze, row, col, changeY, changeX)) {
            return mazeTraverse(maze, row + changeY, col + changeX, start_row, start_col, direction, moveNumber + 1);
        } else {
            newDirection = (direction - 1 + 4) % 4; // Update the direction to the new direction
            return mazeTraverse(maze, row, col, start_row, start_col, newDirection, moveNumber);
        }
    }   
}

int main() {

    char grid[ROWS][COLS] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'.', '.', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#'},
        {'#', '#', '#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '#', '#', '#', '.', '#', '.', '.'},
        {'#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '.', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
        {'#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };
    
    mazeTraverse(grid, 2, 0, 2, 0, 3, 0);
}




