#include <iostream>
#include <vector>

using namespace std;

// Direction vectors for moving in the maze
const vector<int> r = {0, 0, 1, -1};
const vector<int> c = {1, -1, 0, 0};

// Function to print the maze
void printMaze(const vector<vector<int>>& maze) {
    for (const auto& row : maze) {
        for (int cell : row) {
            if (cell == -1) {
                cout << "* "; // Path
            } else {
                cout << cell << " ";
            }
        }
        cout << endl;
    }
}

// Function to check if a position is valid
bool isValid(const vector<vector<int>>& maze, int x, int y) {
    return (x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && 
            (maze[x][y] == 0 || maze[x][y] == 2));
}

// Depth-First Search to solve the maze
bool solveMaze(vector<vector<int>>& maze, int x, int y) {
    if (maze[x][y] == 2) { // Check if we reached the goal
        return true;
    }

    // Mark the current cell as part of the path
    maze[x][y] = -1;

    for (int i = 0; i < 4; i++) {
        int newX = x + r[i];
        int newY = y + c[i];

        if (isValid(maze, newX, newY) && solveMaze(maze, newX, newY)) {
            return true;
        }
    }

    // Backtrack: unmark the cell
    maze[x][y] = 0;
    return false;
}

int main() {
    int rows, cols;
    cout << "Enter the number of rows and columns in the maze: ";
    cin >> rows >> cols;

    if (rows <= 0 || cols <= 0) {
        cout << "Maze dimensions must be positive integers." << endl;
        return 1;
    }

    vector<vector<int>> maze(rows, vector<int>(cols));

    cout << "Enter the maze (0 for path, 1 for wall, 2 for goal):" << endl;
    bool goalExists = false;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> maze[i][j];
            if (maze[i][j] == 2) {
                goalExists = true;
            }
        }
    }

    if (!goalExists) {
        cout << "The maze must contain at least one goal (2)." << endl;
        return 1;
    }

    int startX, startY;
    cout << "Enter the starting position (row and column): ";
    cin >> startX >> startY;

    // Validate the starting position
    if (startX < 0 || startX >= rows || startY < 0 || startY >= cols || 
        (maze[startX][startY] != 0 && maze[startX][startY] != 2)) {
        cout << "Invalid starting position! It must be within the maze and a valid path (0) or the goal (2)." << endl;
        return 1;
    }

    cout << "Maze before solving:\n";
    printMaze(maze);

    if (solveMaze(maze, startX, startY)) {
        cout << "Path to the goal found:\n";
    } else {
        cout << "No path to the goal exists.\n";
    }

    printMaze(maze);

    return 0;
}
