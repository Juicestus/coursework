# ifndef _CARD_H
# define _CARD_H

#include<string>
#include<vector>

class Card{
    private:
        std::string rank; 
        std::string suit; 
        int timesPlayed;
    public:
        Card(std::string rank, std::string suit);
        std::string getRank();
        std::string getSuit();
        int getTimesPlayed();
        bool canBePlayed(std::string currentRank, std::string currentSuit);
        void play();
};
# endif