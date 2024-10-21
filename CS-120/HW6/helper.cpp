#include <iostream>
#include "helper.h"
using std::cout, std::endl;


// do not change
void printInstructions() {
    cout << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Good day, adventurer!"                                     << endl;
    cout << "Your goal is to get the treasure and escape the dungeon!"  << endl;
    cout << " --- SYMBOLS ---"                                          << endl;
    cout << " o          : That is you, the adventurer!"                << endl;
    cout << " $          : These are treasures. Lots of money!"         << endl;
    cout << " @          : These magical amulets resize the level."     << endl;
    cout << " M          : These are monsters; avoid them!"             << endl;
    cout << " +, -, |    : These are unpassable obstacles."             << endl;
    cout << " ?          : A door to another level."                    << endl;
    cout << " !          : A door to escape the dungeon."               << endl;
    cout << " --- CONTROLS ---"                                         << endl;
    cout << " w, a, s, d : Keys for moving up, left, down, and right."  << endl;
    cout << " e          : Key for staying still for a turn."           << endl;
    cout << " q          : Key for abandoning your quest."              << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << endl;
}

// do not change
void outputMap(char** map, const int maxRow, const int maxCol) {
    // output top border
    cout << "+";
    for (int i = 0; i < maxCol * DISPLAY_WIDTH; ++i) {
        cout << "-";
    }
    cout << "+";
    cout << endl;
    
    for (int i = 0; i < maxRow; ++i) {
        // output left border
        cout << "|";

        // output inner blocks
        for (int j = 0; j < maxCol; ++j) {
            // output current block
            cout << " ";
            if (map[i][j] == TILE_OPEN) {
                cout << " ";
            } else {
                cout << map[i][j];
            }
            cout << " ";
        }

        // output right border
        cout << "|";
        cout << endl;
    }
    
    // output bottom border
    cout << "+";
    for (int i = 0; i < maxCol * DISPLAY_WIDTH; ++i) {
        cout << "-";
    }
    cout << "+";
    cout << endl;
}

// do not change
void outputStatus(const int status, const Player& player, int moves) {
    if (status != STATUS_STAY) {
        cout << "You have moved to row " << player.row << " and column " << player.col << endl;
    }
    switch (status) {
        case STATUS_STAY :
			cout << "You stayed at row " << player.row << " and column " << player.col << endl;
            cout << "You didn't move. Are you lost?" << endl;
            break;
        case STATUS_MOVE :
            break;
        case STATUS_TREASURE :
            cout << "Well done, adventurer! You found some treasure." << endl;
            cout << "You now have " << player.treasure << (player.treasure > 1 ? " treasures." : " treasure.") << endl;
            break;
        case STATUS_AMULET :
            cout << "The magic amulet sparkles and crumbles into dust." << endl;
            cout << "The ground begins to rumble. Are the walls moving?" << endl;
            break;
        case STATUS_LEAVE :
            cout << "You go through the doorway into the unknown beyond..." << endl;
            break;
        case STATUS_ESCAPE :
            cout << "Congratulations, adventurer! You have escaped the dungeon!" << endl;
            cout << "You escaped with " << player.treasure << (player.treasure > 1 ? " treasures " : " treasure ");
            cout << "and in " << moves << " total moves." << endl;
            break;
    }
    cout << endl;
}
