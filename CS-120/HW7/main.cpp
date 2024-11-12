#include<iostream>
#include<fstream>
#include<string>
#include "Card.h"
#include "Player.h"
#include "Game.h"
using std::string;

bool loadDeck(Game& g){
    string filename;
    std::cout << "Choose a file to load the deck from:" << std::endl;
    std::cin >> filename;
    try{
        g.loadDeckFromFile(filename);
    }
    catch(std::runtime_error const&){
        std::cout << "The file was invalid. Aborting." << std::endl;
        return false;
    }
    return true;
}

int getPlayerCount(){
    std::cout << "Enter number of players:" << std::endl;
    int numPlayers;
    while(true){
        if((!(std::cin >> numPlayers)) || numPlayers <= 0){
            if(std::cin.fail()){
                //Clear the fail flag
                std::cin.clear();
                //Remove the non-integer data from the stream
                string garbage;
                std::cin >> garbage;
            }
            std::cout << "Please enter a positive number" << std::endl;
        }
        else{
            //break out of the loop once we've read a valid number
            break;
        }
    }
    return numPlayers;
}

void setupPlayers(Game& g, int numPlayers){
    // TODO: Determine whether each player is a human or an AI
    // and add them to the game

    // Determine whether each player is a human or AI by asking the user questions of the form "Is player 0 an AI? (y/n)"
// If the user provides an invalid response, ask them to "Please enter y or n" and wait for a new input
// As you figure out whether the players are AIs or humans, add them to the game g

    for (int i = 0; i < numPlayers; i++) {
        std::cout << "Is player " << i << " an AI? (y/n)";
        std::string response;
        while (true) {
            std::cin >> response;
            if (response == "y" || response == "n") break;
            std::cout << "Please enter y or n" << std::endl;
        }
        g.addPlayer(response == "y");
    }
}

void setupGame(Game& g){
    // TODO: Determine how many cards to deal, deal the cards, and
    // print the initial discard
    std::cout << "How many cards should each player start with?\n";
    int numCards;
    while (true) {
        std::cin >> numCards;
        if (numCards > 0) break;
        std::cout << "Please enter a positive number\n";
    }
    Card* initdisc = g.deal(numCards);
    std::cout << "The initial discard is " << initdisc->getRank() << " " << initdisc->getSuit() << "\n";
}

int main(){
    Game g;
    if(!loadDeck(g)){
        return 1;
    }
    int numPlayers = getPlayerCount();
    setupPlayers(g,numPlayers);
    setupGame(g);
    int winner = g.runGame();
    if(winner != -1){
        std::cout << "Player " << winner << " wins!" << std::endl;
    }
    else{
        std::cout << "The game is a draw!" << std::endl;
    }
    std::cout << "The most played suit was " << g.mostPlayedSuit() << std::endl;
    return 0;
}