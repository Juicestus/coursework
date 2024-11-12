# include "Database.h"

using std::string, std::vector;

// TODO: implement constructor using member initializer list
Database::Database() : stateParkList({}), camperList({}) {
}

Database::~Database() {
	for (unsigned int i = 0; i < stateParkList.size(); ++i) {
		delete stateParkList.at(i);
	}
	
	for (unsigned int i = 0; i < camperList.size(); ++i) {
		delete camperList.at(i);
	}
}

void Database::addStatePark(string parkName, double entranceFee, double trailMiles) {
	INFO(parkName)
	INFO(entranceFee)
	INFO(trailMiles)

	StatePark* newPark = new StatePark(parkName, entranceFee, trailMiles);
	stateParkList.push_back(newPark);
}

void Database::addPassport(string camperName, bool isJuniorPassport) {
	INFO(camperName)
	INFO(isJuniorPassport)

	// TODO: implement function
	Passport* newPassport = new Passport(camperName, isJuniorPassport);
    camperList.push_back(newPassport);
}

void Database::addParkToPassport(string camperName, string parkName) {
	INFO(camperName)
	INFO(parkName)

	// TODO: implement function
	Passport* foundPassport = nullptr;
    for (Passport* passport : camperList) {
        if (passport->getCamperName() == camperName) {
            foundPassport = passport;
            break;
        }
    }
	if (foundPassport == nullptr) return;

	StatePark* foundPark = nullptr;
	for (StatePark* park : stateParkList) {
		if (park->getParkName() == parkName) {
			foundPark = park;
			break;
		}
	}

	if (foundPark == nullptr) return;

	foundPassport->addParkVisited(foundPark);
}

vector<string> Database::getParksInRevenueRange(double lowerBound, double upperBound) {
	INFO(lowerBound)
	INFO(upperBound)

	// TODO: (optional) implement function
	
	return {};
}

vector<string> Database::getHikersAtLeastLevel(int level) {
	INFO(level)

	// TODO: (optional) implement function

	return {};
}
