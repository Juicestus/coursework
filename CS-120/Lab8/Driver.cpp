# include <fstream>
# include <sstream>
# include "Database.h"

using std::cout, std::cin, std::endl, std::string, std::ifstream, std::istringstream, std::vector;

int main() {
	// TODO: uncomment after completing Task 1

	// Database db;
	
	// ifstream ifs_parks("park_data.txt");
	
	// if (!ifs_parks.is_open()) {
	// 	cout << "Error: could not open park data file" << endl;
	// 	return 1;
	// }
	
	// while (!ifs_parks.eof()) {
	// 	string park_name = "";
	// 	string s_park_fee = "";
	// 	string s_trail_length = "";
	// 	getline(ifs_parks, park_name, ',');
	// 	getline(ifs_parks, s_park_fee, ',');
	// 	getline(ifs_parks, s_trail_length);
	// 	db.addStatePark(park_name, stod(s_park_fee), stod(s_trail_length));
	// }
	
	// ifstream ifs_campers("camper_data.txt");
	
	// if (!ifs_campers.is_open()) {
	// 	cout << "Error: could not open camper data file" << endl;
	// 	return 1;
	// }
	
	// while (!ifs_campers.eof()) {
	// 	string line = "";
	// 	getline(ifs_campers, line, '\n');
	// 	if (line == "") break;
	// 	string camper_name = "";
	// 	string s_junior = "";
	// 	istringstream iss_line(line);
	// 	getline(iss_line, camper_name, ',');
	// 	getline(iss_line, s_junior, ',');
	// 	bool junior = static_cast<bool>(stoi(s_junior));
	// 	db.addPassport(camper_name, junior);
	// 	while (!iss_line.eof()) {
	// 		string park = "";
	// 		getline(iss_line, park, ',');
	// 		park.erase(0, 1);
	// 		db.addParkToPassport(camper_name, park);
	// 	}
	// }
	
	cout << "Welcome to the State Park Passport Database!" << endl;
	cout << "Please select from the following options:" << endl;
	cout << "1: Get all parks with revenue in range." << endl;
	cout << "2: Get all hikers at or above a certain level." << endl;
	cout << "Your Selection: " << endl;
	int selection = 0;
	cin >> selection;
	
	// TODO: uncomment after completing Task 2
	
	// if (selection == 1) {
	// 	double lower_bound = 0, upper_bound = 0;
	// 	cout << "Enter Lower Bound then Upper bound: ";
	// 	cin >> lower_bound >> upper_bound;
	// 	vector<string> park_result = db.getParksInRevenueRange(lower_bound, upper_bound);
		
	// 	cout << "These are all the parks with revenue in the range given" << endl;
	// 	for (unsigned int i = 0; i < park_result.size(); ++i) {
	// 		cout << park_result.at(i) << endl;
	// 	}
	// }
	
	// TODO: uncomment after completing Task 3

	// if (selection == 2) {
	// 	int hiking_level = 0;
	// 	cout << "Enter Hiking Level: ";
	// 	cin >> hiking_level;
	// 	vector<string> hiker_results = db.getHikersAtLeastLevel(hiking_level);
		
	// 	cout << "These are all the campers with hiking level at least " << hiking_level << endl;
	// 	for (unsigned int i = 0; i < hiker_results.size(); ++i) {
	// 		cout << hiker_results.at(i) << endl;
	// 	}
	// }
	
	return 0;
}
