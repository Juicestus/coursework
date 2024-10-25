#include "logic.h"
#include <fstream>
#include <iostream>
#include <string>

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading
 * fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    std::ifstream file(fileName.c_str());

    if (!file.is_open()) return nullptr;

    file >> maxRow >> maxCol;

    double total_spaces = maxRow * maxCol;
    if (total_spaces > INT32_MAX || maxRow <= 0 || maxCol <= 0) return nullptr;

    file >> player.row >> player.col;
    if (player.row < 0 || player.row >= maxRow || player.col < 0 || player.col >= maxCol) return nullptr;

    char** map = createMap(maxRow, maxCol);

    for (int i = 0; i < maxRow; ++i) {
        for (int j = 0; j < maxCol; ++j) {
            if (file.fail()) return nullptr;
            file >> map[i][j];
        }
    }
    map[player.row][player.col] = TILE_PLAYER;
    char _;
    file >> _;
    if (!file.fail()) return nullptr;

    file.close();

    return nullptr;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    switch (input) {
        case MOVE_UP:
            --nextRow;
            break;
        case MOVE_DOWN:
            ++nextRow;
            break;
        case MOVE_LEFT:
            --nextCol;
            break;
        case MOVE_RIGHT:
            ++nextCol;
            break;
    }
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    char** m = new char*[maxRow];
    for (int i = 0; i < maxCol; i++) {
        m[i] = new char[maxCol];
        memset(m, 0, maxCol);
    }
    return m;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    for (int i = 0; i < maxRow; ++i) {
        delete[] map[i];
    }
    delete[] map;
    map = nullptr;
    maxRow = 0;
}
// reference:
//https://github.com/Juicestus/Computer-Science-Private/blob/master/CS-120/HW5/functions.cpp

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    int new_row = maxRow * 2, new_col = maxCol * 2;
    char** new_map = createMap(new_row, new_col);
    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            new_map[i][j] = map[i][j];
            if (map[i][j] == TILE_PLAYER) map[i][j] = TILE_OPEN;
            new_map[i+maxRow][j] = map[i][j];
            new_map[i][j+maxCol] = map[i][j];
            new_map[i+maxRow][j+maxCol] = map[i][j];
        }
    }
    deleteMap(map, maxRow);
    maxRow = new_row;
    maxCol = new_col;
    return new_map;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure.
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    return 0;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    return false;
}
