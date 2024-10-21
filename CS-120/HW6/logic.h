#ifndef LOGIC_H
#define LOGIC_H

#define INFO(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << endl;
#include <iostream>
#include <fstream>
#include <string>

using std::cin, std::cout, std::endl, std::string, std::ifstream;

// Player object container
struct Player {
	int row = 0;
	int col = 0;
	int treasure = 0;
};

// constants for tile status
const char TILE_OPEN      = '-';    // blank tile
const char TILE_PLAYER    = 'o';    // tile for player's current location
const char TILE_TREASURE  = '$';    // tile for treasure location
const char TILE_AMULET    = '@';    // tile for hazard that enlarges the dungeon
const char TILE_MONSTER   = 'M';    // tile for monster current location
const char TILE_PILLAR    = '+';    // tile for unpassable pillar location
const char TILE_DOOR      = '?';    // tile for door to the next room
const char TILE_EXIT      = '!';    // tile for exit door out of dungeon

// constants for movement status flags 
const int STATUS_STAY     = 0;      // flag indicating player has stayed still
const int STATUS_MOVE     = 1;      // flag indicating player has moved in a direction
const int STATUS_TREASURE = 2;      // flag indicating player has stepped onto the treasure
const int STATUS_AMULET   = 3;      // flag indicating player has stepped onto an amulet
const int STATUS_LEAVE    = 4;      // flag indicating player has left the current room
const int STATUS_ESCAPE   = 5;      // flag indicating player has gone through the dungeon exit

// constants for user's keyboard inputs
const char INPUT_QUIT     = 'q';    // quit command
const char INPUT_STAY     = 'e';    // no movement
const char MOVE_UP        = 'w';    // up movement
const char MOVE_LEFT      = 'a';    // left movement
const char MOVE_DOWN      = 's';    // down movement
const char MOVE_RIGHT     = 'd';    // right movement


// function signatures, do not change

/**
 * TODO(student): write tests for this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @update  maxRow, maxCol, player
 */
char** loadLevel(const std::string& fileName, int& maxRow, int& maxCol, Player& player);

/**
 * TODO(student): write tests for this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return None
 * @update nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol);

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol);

/**
 * TODO(student): write tests for this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow);

/**
 * TODO(student): write tests for this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol);

/**
 * TODO(student): write tests for this function
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
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol);

/**
 * TODO(student): write tests for this function
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
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player);

#endif
