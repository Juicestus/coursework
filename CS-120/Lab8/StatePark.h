# ifndef _STATEPARK_H
# define _STATEPARK_H

# include <string>
# include <vector>
# include <iostream>

# define INFO(X) std::cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << std::endl;

class Passport;

class StatePark {
	private:
		std::string parkName;
		double entranceFee;
		double trailMiles;
		std::vector<Passport*> camperLog;
	
	public:
		StatePark(std::string parkName, double entranceFee, double trailMiles);
		std::string getParkName();
		double getEntranceFee();
		double getTrailMiles();
		void addCamper(Passport* camper);
		double getRevenue();

		Passport* getCamperAt(unsigned int i) { return camperLog.at(i); }
};

# endif
