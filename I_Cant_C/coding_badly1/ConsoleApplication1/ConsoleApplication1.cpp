// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <random>

using namespace std;

class Board2048 {
private:
    vector<vector<int>> board;

public:
    int* getTile(int coord[2]) {
        return &board[coord[0]][coord[1]];
    }

    void newRandTile() {
        // assumes board has empty space, if it doesnt, infinite while

        int coord[2] = { rand() / (RAND_MAX / 4), rand() / (RAND_MAX / 4) };
        while (!getTile(coord) != 0) {
            int coord[2] = { rand() / (RAND_MAX / 4), rand() / (RAND_MAX / 4) };
        }
        *getTile(coord) = 2;
    }

    Board2048() {
        board = {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
        };
    };

    void draw() {
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                cout << board[y][x] << '\t';
            }
            cout << "\n";
        }
    }
};


int main() {
    Board2048 myBoard;

    myBoard.newRandTile();
    myBoard.newRandTile();
    myBoard.newRandTile();
    myBoard.newRandTile();
    myBoard.newRandTile();

    myBoard.draw();

    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
