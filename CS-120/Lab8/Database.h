# ifndef _DATABASE_H
# define _DATABASE_H

# include "Passport.h"

class Database {
	private:
		std::vector<StatePark*> stateParkList;
		std::vector<Passport*> camperList;
	
	public:
		Database();
		~Database();
		void addStatePark(std::string parkName, double entranceFee, double trailMiles);
		void addPassport(std::string camperName, bool isJuniorPassport);
		void addParkToPassport(std::string camperName, std::string parkName);
		std::vector<std::string> getParksInRevenueRange(double lowerBound, double upperBound);
		std::vector<std::string> getHikersAtLeastLevel(int level);
		StatePark* getParkAt(unsigned int i) { return stateParkList.at(i); }
		Passport* getCamperAt(unsigned int i) { return camperList.at(i); }
};

# endif
