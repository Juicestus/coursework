#include<iostream>
#include<sstream>
#include "Player.h"
using std::vector, std::string, std::size_t;

Player::Player(bool isAI) /* TODO: initialize */ {
    this->isAI = isAI;
    this->hand = vector<Card*>();
}

void Player::addToHand(Card* c){
    hand.push_back(c); 
}

size_t Player::getHandSize(){
    return hand.size(); 
}

std::string Player::getHandString() {
    string s;
    for (Card* c : hand){
        s += c->getRank() + " " + c->getSuit() + ", ";
    }
    return s.substr(0, s.size() - 2);  // remove trailing comma and space
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit){

    // this is a horrible monstrosity -- please forgive me

    if (this->isAI) { // ai
        for (size_t i = 0; i < hand.size(); i++) {
            if (hand.at(i)->canBePlayed(currentRank, currentSuit)) {
                Card* c = hand.at(i);
                c->play();
                hand.erase(hand.begin() + i);
                currentRank = c->getRank();
                currentSuit = c->getSuit();
                // draw
                return c;
            }
        }
        return nullptr;
    } else { // human
        std::cout << "Your hand contains: " << getHandString() << "\n";
        std::cout << "The next card played must be a " << currentRank << " or " << currentSuit << "\n";
        std::cout << "What would you like to play? (enter \"draw card\" to draw a card)\n";
        while (true) {
            std::string w1, w2;
            std::cin >> w1 >> w2;
            std::cout << "\nREAD: " << w1 << w2 << "\n\n";
            if (w1 == "draw" && w2 == "card") {
                // draw
                return nullptr;
            } else {
                    // play card
                    bool found = false;
                    for (size_t i = 0; i < hand.size(); i++) {
                        if (hand.at(i)->getRank() == w1 && hand.at(i)->getSuit() == w2) {
                            if (w1 == "8" || w1 == currentRank || w2 == currentSuit) {
                                Card* c = hand.at(i);
                                c->play();
                                hand.erase(hand.begin() + i);
                                currentRank = c->getRank();
                                currentSuit = c->getSuit();
                                return c;
                            } else {
                                std::cout << "You can't play that card. Try again.\n";
                                found = true;
                            }
                        }
                    }
                    if (!found)
                        std::cout << "That's not a card you have. Try again.\n";
                    // horribly unsafe and unintuative control flow
            }
        }
    }
}