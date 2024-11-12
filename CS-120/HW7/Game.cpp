#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "Game.h"
using std::string, std::vector;



Game::Game(): players({}), suits({}), ranks({}), 
    deck({}), drawPile({}), discardPile({}) {}

void LoadLineToVec(std::ifstream* file, std::vector<std::string>* vec) {
    string line;
    std::getline(*file, line);
    std::istringstream iss(line);
    while (!iss.eof()) {
        string suit;
        iss >> suit;
        if (suit != "") vec->push_back(suit);
    }
}

bool VecIncludes(std::vector<std::string>* vec, string what) {
    for (auto& suit : *vec) {
        if (suit == what) return true;
    }
    return false;
}

void Game::loadDeckFromFile(string filename){
    std::ifstream file(filename);

// Line 1: Suits: A list of suits in the deck separated by spaces
// Line 2: Ranks: A list of ranks in the game separated by spaces. One of these ranks should be “8”
// Lines 3+: These lines contain the individual cards, one per line. Each line consists of a rank and a suit, separated by a space

    if (!file.is_open()) throw std::runtime_error("Cannot open file");

    // cursed c++
    LoadLineToVec(&file, &suits);
    LoadLineToVec(&file, &ranks);

    while (!file.eof()) {
        string rank, suit;
        file >> rank;
        if (!VecIncludes(&ranks, rank)) throw std::runtime_error("Invalid rank");
        if (file.eof()) throw std::runtime_error("Bad format");
        file >> suit;
        if (!VecIncludes(&suits, suit)) throw std::runtime_error("Invalid suit");
        try {
            deck.push_back(new Card(rank, suit));
        } catch (std::invalid_argument& e) {
            throw std::runtime_error("Invalid card format");
        }
    }

    for (int i = deck.size() - 1; i >= 0; i--) {
        drawPile.push_back(deck.at(i));
    }

    file.close();
}

void Game::addPlayer(bool isAI){
    players.push_back(new Player(isAI)); 
}

void Game::drawCard(Player* p){
    // TODO: Move the top card of the draw pile to Player p's hand
    // If the draw pile is empty, flip the discard pile to create a new one

    Card* c = drawPile.at(drawPile.size() - 1);
    p->addToHand(c);
    drawPile.pop_back();
}

//deals numCards cards to each player
Card* Game::deal(int numCards){
    // TODO: Flip the top card of the draw pile to be the initial discard
    // then deal numCards many cards to each player

    if (drawPile.size() == 0) return nullptr;
    Card* c = drawPile.at(drawPile.size() - 1);
    discardPile.push_back(c);
    for (Player* p : players) {
        for (int i = 0; i < numCards; i++) {
            drawCard(p);
        }
    }
    return c;
}

string Game::mostPlayedSuit() {
    std::vector<int> cts(suits.size());
    for (auto& c : deck) {
        for (unsigned int i = 0; i < suits.size(); i++) {
            if (c->getSuit() == suits.at(i)) cts.at(i) += c->getTimesPlayed();
        }
    }
    int max_ct = 0, max_i = 0;
    for (size_t i = 0; i < cts.size(); i++) {
        if (cts.at(i) > max_ct) {
            max_ct = cts.at(i);
            max_i = i;
        }
    }
    return suits.at(max_i);
}

int Game::runGame(){
    // TODO: Run the game and return the number of the winning player


// At the start of each turn you should announce "Player <Player #>'s turn!" -- 

// You should determine which card the player is playing, if any -- 
// If the player is playing a card:
// You should announce the rank and suit of this card 
// If the card is an 8, you should announce the new suit that the player has chosen
// You should add the played card to the top (end) of the discard pile
// If the player is drawing a card
// You should announce this
// You should draw a card and add it to their hand
// If there are no more cards to draw, print "Player  <Player #> cannot draw a card." and return -1 to indicate a draw (tied game).
// You will need to catch the exception thrown by drawCard to detect this
// Whenever any player has 0 cards remaining in hand, end the game and return the winner.


    // for (int c = 0; ; c++) {
    //     int i = players.size() % c;
    //     std::cout << "Player " << i << "'s turn!";
    //     auto p = players[i];
    //     // p->playCard(cur)




    // }

    return 0;
}

//Destructor--Deallocates all the dynamic memory we allocated
Game::~Game(){
    for (unsigned int i = 0; i < deck.size(); i++){
        delete deck.at(i);
    }
    for (unsigned int i = 0; i < players.size(); i++) {
        delete players.at(i);
    }
}