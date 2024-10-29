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
    std::ifstream file(fileName);

    if (!file.is_open()) return nullptr;
    file >> maxRow >> maxCol;
    if (maxRow > INT32_MAX / maxCol || maxRow <= 0 || maxCol <= 0) return nullptr;
    file >> player.row >> player.col;
    if (player.row < 0 || player.row >= maxRow || player.col < 0 || player.col >= maxCol) return nullptr;

    char** map = createMap(maxRow, maxCol);

    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) { 
            if (file.fail()) return nullptr;
            file >> (map[i][j]); 
        }
    }

    if (map[player.row][player.col] != TILE_OPEN) return nullptr;
    map[player.row][player.col] = TILE_PLAYER;
    char _;
    file >> _;
    if (!file.fail()) return nullptr;

    file.close();

    return map;
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
    case MOVE_UP: --nextRow; break;
    case MOVE_DOWN: ++nextRow; break;
    case MOVE_LEFT: --nextCol; break;
    case MOVE_RIGHT: ++nextCol; break;
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
    if (maxRow <= 0 || maxCol <= 0) return nullptr;

    char** map = new char*[maxRow];
    for (int i = 0; i < maxRow; i++) {
        map[i] = new char[maxCol];
        for (int j = 0; j < maxCol; j++) { map[i][j] = TILE_OPEN; }
    }
    return map;
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
    for (int i = 0; i < maxRow; ++i) { delete[] map[i]; }
    delete[] map;
    map = nullptr;
    maxRow = 0;
}
// reference:
// https://github.com/Juicestus/Computer-Science-Private/blob/master/CS-120/HW5/functions.cpp

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
    if (map == nullptr || maxRow <= 0 || maxCol <= 0) return nullptr;
    int new_row = maxRow * 2, new_col = maxCol * 2;
    char** new_map = createMap(new_row, new_col);
    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            new_map[i][j] = map[i][j];
            if (map[i][j] == TILE_PLAYER) map[i][j] = TILE_OPEN;
            new_map[i + maxRow][j] = map[i][j];
            new_map[i][j + maxCol] = map[i][j];
            new_map[i + maxRow][j + maxCol] = map[i][j];
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
    // Dont care about moving the player:
    if (nextRow < 0 || nextRow >= maxRow || nextCol < 0 || nextCol >= maxCol) return STATUS_STAY;
    if (map[nextRow][nextCol] == TILE_PILLAR || map[nextRow][nextCol] == TILE_MONSTER) return STATUS_STAY;
   
    // Concerned with moving the player:
    int ret_status = STATUS_MOVE;
    if (map[nextRow][nextCol] == TILE_DOOR) {
        ret_status = STATUS_LEAVE;
    }
    if (map[nextRow][nextCol] == TILE_TREASURE) {
        map[player.row][player.col] = TILE_OPEN;
        player.treasure++;
        ret_status = STATUS_TREASURE;
    }
    if (map[nextRow][nextCol] == TILE_EXIT) {
        if (player.treasure < 1) return STATUS_STAY;
        ret_status = STATUS_ESCAPE;
    }
    if (map[nextRow][nextCol] == TILE_AMULET) {
        ret_status = STATUS_AMULET;
    }

    // Actually move player
    map[player.row][player.col] = TILE_OPEN;
    player.row = nextRow;
    player.col = nextCol;
    map[player.row][player.col] = TILE_PLAYER;
    return ret_status;
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

    for (int row = player.row - 1; row >= 0; row--) {
        if (map[row][player.col] == TILE_MONSTER) {
            map[row][player.col] = TILE_OPEN;
            map[row + 1][player.col] = TILE_MONSTER;
        } 
        else { if (map[row][player.col] == TILE_PILLAR) break; }
    }
    for (int row = player.row + 1; row < maxRow; row++) {
        if (map[row][player.col] == TILE_MONSTER) {
            map[row][player.col] = TILE_OPEN;
            map[row - 1][player.col] = TILE_MONSTER;
        }
        else { if (map[row][player.col] == TILE_PILLAR) break; }
    }
    for (int col = player.col - 1; col >= 0; col--) {
        if (map[player.row][col] == TILE_MONSTER) {
            map[player.row][col] = TILE_OPEN;
            map[player.row][col + 1] = TILE_MONSTER;
        }
        else { if (map[player.row][col] == TILE_PILLAR) break; }
    }
    for (int col = player.col + 1; col < maxCol; col++) {
        if (map[player.row][col] == TILE_MONSTER) {
            map[player.row][col] = TILE_OPEN;
            map[player.row][col - 1] = TILE_MONSTER;
        }
        else { if (map[player.row][col] == TILE_PILLAR) break; }
    }
    return (map[player.row][player.col] == TILE_MONSTER);
}
