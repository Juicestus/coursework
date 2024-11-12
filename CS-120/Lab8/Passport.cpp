# include "Passport.h"

using std::string, std::vector;

// TODO: implement constructor using member initializer list

Passport::Passport(std::string camperName, bool isJuniorPassport) 
: camperName(camperName), isJuniorPassport(isJuniorPassport), parksVisited({}) {}

string Passport::getCamperName() {
	return this->camperName;
}

bool Passport::checkJuniorPassport() {
	return this->isJuniorPassport;
}

void Passport::addParkVisited(StatePark* park) {
	INFO(park)
	park->addCamper(this);
	this->parksVisited.push_back(park);
}

double Passport::getMilesHiked() {
	// TODO: (optional) implement function

	return 0.0;
}

int Passport::getHikerLevel() {
	// TODO: (optional) implement function

	return 0;
}
