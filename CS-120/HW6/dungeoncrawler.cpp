#include <iostream>
#include <fstream>
#include <string>
#include "helper.h"
#include "logic.h"
using std::cin, std::cout, std::endl, std::string, std::ifstream;


int main() {
    // display greeting message
    printInstructions();

    string dungeon;
    int total_rooms;
    
    Player player;

    cout << "Please enter the dungeon name and number of levels: ";
    cin >> dungeon >> total_rooms;

    int total_moves = 0;
    for(int current_room = 1; current_room <= total_rooms; current_room++) {
        cout << "Level " << current_room << endl;
        string fileName = dungeon + std::to_string(current_room) + ".txt";

        // declare variables
        int maxRow  = 0;
        int maxCol  = 0;
        int nextRow = 0;
        int nextCol = 0;

        // create map, or quit if map load error
        char** map = loadLevel(fileName, maxRow, maxCol, player);
        if (map == nullptr) {
            cout << "Returning you back to the real word, adventurer!" << endl;
            return 1;
        }
        
        // display map
        outputMap(map, maxRow, maxCol);

        // move player
        char input = 0;
        int status = 0;
        while (true) {
            // get user input
            cout << "Enter command (w,a,s,d: move, e: stay still, q: quit): ";
            cin >> input;

            // quit game if user inputs quit
            if (input == INPUT_QUIT) {
                cout << "Thank you for playing!" << endl;
                deleteMap(map, maxRow);
                return 0;
            } 

            // reprompt if invalid command
            if (input !=  MOVE_UP && input != MOVE_LEFT && input != MOVE_DOWN && input != MOVE_RIGHT && input != INPUT_STAY) {
                cout << "I did not understand your command, adventurer!" << endl;
                continue;
            }

            // increment dungeon movement counter
            total_moves++;
            if (input == INPUT_STAY) {
                status = STATUS_STAY;
            } else {
                // translate from the character input to a direction
                // we will use the player's current location and pass-by-reference to find the intended next location
                nextRow = player.row;
                nextCol = player.col;
                getDirection(input, nextRow, nextCol);

                // move player to new location index, if possible, and get player status
                status = doPlayerMove(map, maxRow, maxCol, player, nextRow, nextCol);
            }

            // quit game if user escapes
            if (status == STATUS_ESCAPE) {
                outputMap(map, maxRow, maxCol);
                outputStatus(status, player, total_moves);
                deleteMap(map, maxRow);
                return 0;
            }

            // go to next level if user goes through door
            if (status == STATUS_LEAVE) {
				outputMap(map, maxRow, maxCol);
                outputStatus(status, player, total_moves);
                break;
            }

            // move monsters, end if player is caught
            if (doMonsterAttack(map, maxRow, maxCol, player)) {
                outputMap(map, maxRow, maxCol);
                cout << "You died, adventurer! Better luck next time!" << endl;
                deleteMap(map, maxRow);
                return 0;
            }

            // use amulet
            if (status == STATUS_AMULET) {
                map = resizeMap(map, maxRow, maxCol);
            }
            
            // display map and status
            outputMap(map, maxRow, maxCol);
            outputStatus(status, player, total_moves);
            
        }

        // delete map
        deleteMap(map, maxRow);
    }
    return 0;
}
