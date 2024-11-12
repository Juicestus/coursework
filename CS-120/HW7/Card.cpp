#include<cctype>
#include<stdexcept>
#include "Card.h"
using std::string;

Card::Card(string rank, string suit) /* TODO: initialize */ {
    // TODO: implement constructor checks
    if (rank.size() <= 0) throw std::invalid_argument("Invalid rank: empty");
    if (suit.size() <= 0) throw std::invalid_argument("Invalid suit: empty");

    for (char c : rank) if (!std::isalpha(c) && !(c >= '0' && c <= '9'))
            throw std::invalid_argument("Invalid rank: contains non-alphabetic characters");
    for (char c : suit) if (!std::isalpha(c) && !(c >= '0' && c <= '9'))
            throw std::invalid_argument("Invalid suit: contains non-alphabetic characters");

    this->rank = rank;
    this->suit = suit;
    this->timesPlayed = 0;
}

string Card::getRank(){
    return this->rank;
}

string Card::getSuit(){
    return this->suit;
}

int Card::getTimesPlayed(){
    return this->timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit){
    return (rank == "8") || (rank == currentRank) || (suit == currentSuit);
}

void Card::play(){
    timesPlayed++;
}