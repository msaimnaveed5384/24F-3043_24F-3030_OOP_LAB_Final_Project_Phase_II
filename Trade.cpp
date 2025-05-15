#include "Stronghold.h"
#include <sstream> 
using namespace std;
Trade::Trade() {
	sender_id = -1;
	receiver_id = -1;
	resources_offered = "";
	resources_requested = "";
	is_smuggling = false;
}

void Trade::propose_trade() 
{
	cout << "Trade proposed from Player " << sender_id << " to Player " << receiver_id << endl;
	cout << "Offers: " << resources_offered << " | Requests: " << resources_requested << endl;
}
void parse_resources(string data, Resource& res, bool add) 
{
	stringstream ss(data);
	string item;
	while (getline(ss, item, ',')) {
		stringstream kv(item);
		string key;
		int value;
		if (getline(kv, key, ':') && kv >> value) {
			if (key == "food") add ? res.food += value : res.food -= value;
			else if (key == "wood") add ? res.wood += value : res.wood -= value;
			else if (key == "stone") add ? res.stone += value : res.stone -= value;
			else if (key == "iron") add ? res.iron += value : res.iron -= value;
		}
	}
}
void apply_parsed_string_to_resource(Resource& res, const string& input, bool is_add) {
	size_t start = 0;

	while (start < input.length()) {
		size_t comma = input.find(',', start);
		string pair = (comma == string::npos) ? input.substr(start) : input.substr(start, comma - start);

		size_t colon = pair.find(':');
		if (colon != string::npos) {
			string key = pair.substr(0, colon);
			int value = stoi(pair.substr(colon + 1));
			if (!is_add) value = -value;

			if (key == "food") res.food += value;
			else if (key == "wood") res.wood += value;
			else if (key == "stone") res.stone += value;
			else if (key == "iron") res.iron += value;
			else if (key == "gold") res.gold += value;
		}

		if (comma == string::npos) break;
		start = comma + 1;
	}
}

void Trade::attempt_smuggling(Resource& sender_res, Resource& receiver_res) {
	cout << "Attempting smuggling operation..." << endl;
	int chance = rand() % 100;

	if (chance < 60) {
		// Success
		cout << "Smuggling successful! Trade completed secretly." << endl;
		complete_trade(sender_res, receiver_res);

		// Bonus for successful smuggling
		receiver_res.gold += 50;  // Optional: Add 'gold' to Resource if you want
		cout << "Black market bonus: +50 gold to receiver." << endl;
	}
	else {
		// Failure
		cout << "Smuggling operation failed! Guards intercepted the trade." << endl;

		// Penalty: sender loses some offered resources without gain
		parse_resources(resources_offered, sender_res, false);
		cout << "Penalty: Offered resources seized. No trade completed." << endl;
	}
}

void Trade::complete_trade(Resource& sender_res, Resource& receiver_res) {
	cout << "Applying trade...\n";

	// Sender gives offered
	apply_parsed_string_to_resource(sender_res, resources_offered, false);
	apply_parsed_string_to_resource(receiver_res, resources_offered, true);

	// Receiver gives requested
	apply_parsed_string_to_resource(receiver_res, resources_requested, false);
	apply_parsed_string_to_resource(sender_res, resources_requested, true);

	cout << "Trade completed.\n";
}
