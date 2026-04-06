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
        /* assumes board has empty space, if it doesnt, infinite while */

        // generate a random coordinate
        int coord[2] = { rand() / (RAND_MAX / 4), rand() / (RAND_MAX / 4) };

        // while the tile at given coord doesn't have a value of 0
        while (!(*getTile(coord) != 0)) {
            // generate a new random coordinate
            int coord[2] = { rand() / (RAND_MAX / 4), rand() / (RAND_MAX / 4) };
        }
        // assign random value to generated coordinate
        *getTile(coord) = rand() / (RAND_MAX / 4) == 1 ? 4 : 2;

        cout << "now: ";
        getTile(coord);
    }

    bool collapseInDir(int collapseVec[2]) {
        /*
        Iterates through all tiles in 4x4 grid
        attempts to collapse each tile to the next based on the :param collapseVec:
        returns whether or not any tiles were collapsed
        */
        int changed_tiles = 0;
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                //check tile exists
                int this_tile = *getTile((int[2]){y, x});
                if (this_tile == 0) { continue; }

                //check tile is on border or non-interactable tile
                int next_tile;
                try {
                    next_tile = *getTile((int[2]){y + collapseVec[1], x + collapseVec[0]});
                    if (next_tile != 0 && next_tile != this_tile) { continue; }
                } catch (exception) {
                    continue;
                }

                // don't need to re-fetch next_tile as code will be continued if next_tile err'd

                if (next_tile == this_tile) {
                    *getTile((int[2]){y + collapseVec[1], x + collapseVec[0]}) = this_tile * 2;
                    *getTile((int[2]){y, x}) = 0;
                    ++changed_tiles;
                }
                
            }
        }
        return changed_tiles != 0;
    }
    void fullCollapseInDir(int collapseVec[2]) {
        // runs collapseInDir until no more collapsing can be done, should never require more than 4 collapses
        for (int i=0; i < 4; i++) {
            if (!collapseInDir(collapseVec)) {break;}
        }
    }

    void inputUp() {
        fullCollapseInDir((int[2]){0, -1});
    }
    void inputDown() {
        fullCollapseInDir((int[2]){0, 1});
    }
    void inputLeft() {
        fullCollapseInDir((int[2]){-1, 0});
    }
    void inputRight() {
        fullCollapseInDir((int[2]){1, 0});
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
