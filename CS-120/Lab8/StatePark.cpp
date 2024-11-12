# include "Passport.h"

using std::string, std::vector;

StatePark::StatePark(std::string parkName, double entranceFee, double trailMiles) 
: parkName(parkName), entranceFee(entranceFee), trailMiles(trailMiles), camperLog({}){}

string StatePark::getParkName() {
	return this->parkName;
}

double StatePark::getEntranceFee() {
	return this->entranceFee;
}

double StatePark::getTrailMiles() {
	return this->trailMiles;
}

void StatePark::addCamper(Passport* camper) {
	INFO(camper)
	this->camperLog.push_back(camper);
}

double StatePark::getRevenue() {
	return 0.0;
}
