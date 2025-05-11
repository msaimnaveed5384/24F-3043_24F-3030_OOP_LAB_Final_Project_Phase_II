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

void Trade::propose_trade() {
	cout << "Trade proposed from Player " << sender_id << " to Player " << receiver_id << endl;
	cout << "Offers: " << resources_offered << " | Requests: " << resources_requested << endl;
}
void parse_resources(string data, Resource& res, bool add) {
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
void Trade::complete_trade(Resource& sender_res, Resource& receiver_res) {
	// Apply changes
	parse_resources(resources_offered, sender_res, false); // Deduct from sender
	parse_resources(resources_offered, receiver_res, true); // Add to receiver
	parse_resources(resources_requested, receiver_res, false); // Deduct from receiver
	parse_resources(resources_requested, sender_res, true);    // Add to sender

	cout << "Trade completed successfully." << endl;
}

void Trade::attempt_smuggling(Resource& sender_res, Resource& receiver_res) {
	cout << "⚠️ Attempting smuggling operation..." << endl;
	int chance = rand() % 100;

	if (chance < 60) {
		// Success
		cout << "✅ Smuggling successful! Trade completed secretly." << endl;
		complete_trade(sender_res, receiver_res);

		// Bonus for successful smuggling
		receiver_res.gold += 50;  // Optional: Add 'gold' to Resource if you want
		cout << "Black market bonus: +50 gold to receiver." << endl;
	}
	else {
		// Failure
		cout << "🚨 Smuggling operation failed! Guards intercepted the trade." << endl;

		// Penalty: sender loses some offered resources without gain
		parse_resources(resources_offered, sender_res, false);
		cout << "Penalty: Offered resources seized. No trade completed." << endl;
	}
}
