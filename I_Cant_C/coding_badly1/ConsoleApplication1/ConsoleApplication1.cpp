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
    Board2048() {
        board = {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
        };
    };

    int* getTile(int coord[2]) {
        cout << "Tile at [" << coord[0] << ", " << coord[1] << "] is '" << board[coord[0]][coord[1]] << "'\n";
        return &board[coord[0]][coord[1]];
    }

    void newRandTile() {
        // assumes board has empty space, if it doesnt, infinite while

        // generate a random coordinate
        int coord[2] = { rand() / (RAND_MAX / 4), rand() / (RAND_MAX / 4) };

        // while the tile at given coord
        while (!(*getTile(coord) != 0)) {
            int coord[2] = { rand() / (RAND_MAX / 4), rand() / (RAND_MAX / 4) };
        }
        *getTile(coord) = rand() / (RAND_MAX / 4) == 1 ? 4 : 2;
        cout << "now: ";
        getTile(coord);
    }

    void inputUp() {
        //do whatever
    }
    void inputDown() {
        //do whatever
    }
    void inputLeft() {
        //do whatever
    }
    void inputRight() {
        //do whatever
    }

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
    bool running = true;
    Board2048 myBoard;

    myBoard.newRandTile();
    myBoard.newRandTile();

    while (running) {
        cout << "2048: \n";
        myBoard.draw();
        cout << "Your Move [wasd to move, p to quit]: ";

        string user_input;
        cin >> user_input;

        //user_input = user_input[1];

        if (user_input == "w") {
            myBoard.inputUp();
        } else if (user_input == "a") {
            myBoard.inputLeft();
        } else if (user_input == "s") {
            myBoard.inputDown();
        } else if (user_input == "d") {
            myBoard.inputRight();
        } if (user_input == "p") {
            cout << "Quiting...";
            running = false;
            break;
        }

        myBoard.newRandTile();

        cout << "\n\n";
    }

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
