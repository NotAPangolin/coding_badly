// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <random>
#include <typeinfo>

using namespace std;

class Board2048 {
private:
    vector<vector<int>> board;
    int oob_tile = -1;

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
        //cout << "Tile at [" << coord[0] << ", " << coord[1] << "] is '" << board[coord[0]][coord[1]] << "'\n";
        return &board[coord[0]][coord[1]];
    }
    int* getTile(int x, int y) {
        //cout << "Tile at [" << x << ", " << y << "] is '" << board[x][y] << "'\n";
        try {
            return &board.at(x).at(y);
        }
        catch (...) {
            return &oob_tile;
        }
    }

    bool newRandTile() {
        // check that empty space exists
        int nil_count = 0;
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                if (*getTile(x, y) == 0) {
                    nil_count++;
                }
            }
        }
        if (nil_count == 0) {
            return true;
        }

        // generate a random tile until you find an empty space
        do {
            // generate random coordinate
            int coord[2] = { rand() / (RAND_MAX / 4), rand() / (RAND_MAX / 4) };

            // If the value at that coordinate is 0, we're done
            int val = *getTile(coord);
            if (val == 0) {
                // assign random value to generated coordinate
                *getTile(coord) = rand() / (RAND_MAX / 4) == 1 ? 4 : 2;

                //cout << "now: ";
                getTile(coord);   
                return false;
            }

            //cout << "had to rerandomize\n";
        } while (true);
    }

    bool collapseInDir(int collapse_x, int collapse_y) {
        /*
        Iterates through all tiles in 4x4 grid
        attempts to collapse each tile to the next based on the :param collapseVec:
        returns whether or not any tiles were collapsed
        */
        int changed_tiles = 0;
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                //cout << "crnt tile: " << x << ", " << y << " - ";
                //cout << "collapse tile: " << x+collapse_x << ", " << y+collapse_y << "\n\t- ";
                //check tile has value
                int this_tile = *getTile(y, x);
                if (this_tile == 0) {
                    //cout << "crnt tile doesnt have value\n";
                    continue;
                }

                //check tile is on border
                int next_tile;
                //cout << "attempting fetch of next tile\n\t- ";
                if (y + collapse_y < 0 or y + collapse_y > 3 or x + collapse_x < 0 or x + collapse_x > 3) {
                    //cout << "next tile is border\n";
                    continue;
                }

                // check tile is on non-collapsable tile
                next_tile = *getTile(y + collapse_y, x + collapse_x);
                if (next_tile != 0 && next_tile != this_tile) {
                    //cout << "next tile has different value\n";
                    continue;
                }

                // move tile if next is empty
                if (next_tile == 0) {
                    *getTile(y + collapse_y, x + collapse_x) = this_tile;
                    *getTile(y, x) = 0;
                    ++changed_tiles;
                    //cout << "moved tile to 0\n";
                }

                // collapse tiles if same value
                if (next_tile == this_tile) {
                    *getTile(y + collapse_y, x + collapse_x) = this_tile * 2;
                    *getTile(y, x) = 0;
                    ++changed_tiles;
                    //cout << "collapsed tiles\n";
                }
                
            }
        }
        // returns True if collapse resulted in no change
        return changed_tiles != 0;
    }
    void fullCollapseInDir(int x, int y) {
        // this does not follow standard 2048 solving functionality
        // runs collapseInDir until no more collapsing can be done, should never require more than 4 collapses
        for (int i=0; i < 4; i++) {
            if (!collapseInDir(x, y)) {break;}
        }
    }

    bool fallInDir(int collapse_x, int collapse_y) {
        vector<vector<int>> new_board = board;

        /*
        Iterates through all tiles in 4x4 grid
        attempts to collapse each tile to the next based on the :param collapseVec:, proceeding its collapse direction until finding a non-collapsable tile
        returns whether or not any tiles were collapsed
        */
        int changed_tiles = 0;
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                //cout << "crnt tile: " << x << ", " << y << " - ";
                //cout << "collapse tile: " << x+collapse_x << ", " << y+collapse_y << "\n\t- ";
                //------------check tile has value------------
                int this_tile = *getTile(x, y);
                if (this_tile == 0) {
                    //cout << "crnt tile doesnt have value\n";
                    continue;
                }

                //------------find next tile------------
                // we have: current tile position, crnt tile value
                int next_tile;
                int next2_tile;
                int i = 0;

                while (true) {
                    i++;
                    next_tile = *getTile(x + collapse_x * i, y + collapse_y * i);
                    next2_tile = *getTile(x + collapse_x * (i + 1), y + collapse_y * (i + 1));

                    bool next_is_collapsable = (next_tile == this_tile || next_tile == 0);
                    bool next2_is_collapsable = (next2_tile == this_tile || next2_tile == 0);

                    if (next_is_collapsable) {
                        if (next2_is_collapsable) {
                            continue;
                        }
                        new_board[x][y] = 0;
                        new_board[x + collapse_x][y + collapse_y] = this_tile + next_tile;

                        //*getTile(y + collapse_y, x + collapse_x) = this_tile * 2;
                        //*getTile(y, x) = 0;

                        ++changed_tiles;
                        break;
                    }
                    else {
                        break;
                    }
                }
            }
            // returns True if collapse resulted in no change
            printf("new is old?: " + (&new_board == &board));
            return changed_tiles != 0;
        }
    }

    void inputUp() {
        fallInDir(0, -1);
        //fullCollapseInDir(0, -1);
    }
    void inputDown() {
        fullCollapseInDir(0, 1);
    }
    void inputLeft() {
        fullCollapseInDir(-1, 0);
    }
    void inputRight() {
        fullCollapseInDir(1, 0);
    }

    void draw() {
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                int tile = *getTile(y, x);
                cout << "\u001b[" << ((tile != 0) ? "1;" : "") << to_string(30 + (tile / (2048 / 9))) << "m" << board[y][x] << "\t" << "\u001b[0m";
            }
            cout << "\n";
        }
    }

    int sum() {
        int sum = 0;
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                sum += *getTile(y, x);
            }
        }
        return sum;
    }
};


int main() {
    bool running = true;
    Board2048 myBoard;

    myBoard.newRandTile();
    myBoard.newRandTile();

    cout << "Welcome to 2048!\nPress Any Key to Start";
    while (!_kbhit()) {}
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\u001b[1J";
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\u001b[1J";
    myBoard.draw();

    while (running) {
        if (_kbhit() != 0) {
            // get and verify user input
            char user_input = _getch();
            if (!(user_input == 'w' or user_input == 'a' or user_input == 's' or user_input == 'd' or user_input == 'p')) {
                cout << user_input;
                continue;
            }

            if (user_input == 'w') {
                myBoard.inputUp();
            } else if (user_input == 'a') {
                myBoard.inputLeft();
            } else if (user_input == 's') {
                myBoard.inputDown();
            } else if (user_input == 'd') {
                myBoard.inputRight();
            } if (user_input == 'p') {
                cout << "Quiting...";
                running = false;
                return 0;
            }

            if (myBoard.newRandTile()) {
                cout << "\n\nHaha you lost, dummy\nScore: " << to_string(myBoard.sum()) << "\nPress enter to acknowledge";
                string _;
                cin >> _;
                running = false;
                return 0;
            }

            cout << "\u001b[1J";
            myBoard.draw();
        }

    }
    return 0;

}