#include "Stronghold.h"
Leadership::Leadership() {
	leader_name = "King Arthur";
	popularity = 75;
}
void Leadership::change_leader() {
	string names[] = { "Queen Isabella", "Lord Cedric", "Sir Roland", "Lady Morgana" };
	int idx = rand() % 4;
	leader_name = names[idx];
	popularity = rand() % 50 + 50;
	cout << "New leader is " << leader_name << " with popularity " << popularity << endl;
}

void Leadership::status_report() const {
	cout << "Leader: " << leader_name << ", Popularity: " << popularity << endl;
}
