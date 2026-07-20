#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <random>
#include <typeinfo>

using namespace std;

vector<vector<int>> clear_board(vector<vector<int>> *board, int size); //TODO make
// set board contents to 0s

void draw_board(vector<vector<int>> *board) {
    //prints board to cout
    for (auto row : *board) {
        for (int tile : row) {
            printf("%i\t", tile);
        }
        printf("\n");
    }
}

int main() {
    // Create Board
    int size = 4;

    vector<vector<int>> board;
    printf(board);
    printf
    for (int i = 0; i++; i > size) {
        vector<int> row = {};
        for (int i = 0; i++; i > size) {
            row.push_back(0);
        }
        board.push_back(row);
    }

    draw_board(&board);

}