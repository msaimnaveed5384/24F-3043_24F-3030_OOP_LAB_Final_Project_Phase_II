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

void Leadership::hold_election(const Population& pop) {
    cout << "\nAn election is being held to choose the new leader...\n";

    // Votes are weighted by population count and happiness
    int peasant_votes = pop.society.peasants.count * pop.society.peasants.happiness;
    int merchant_votes = pop.society.merchants.count * pop.society.merchants.happiness;
    int noble_votes = pop.society.nobles.count * pop.society.nobles.happiness;

    // Random candidates
    string candidates[] = { "Arthur", "Isabella", "Cedric", "Morgana" };
    int scores[4] = { 0 };

    // Assign weighted votes randomly among candidates
    for (int i = 0; i < peasant_votes / 100; i++) scores[rand() % 4]++;
    for (int i = 0; i < merchant_votes / 50; i++) scores[rand() % 4]++;
    for (int i = 0; i < noble_votes / 20; i++) scores[rand() % 4]++;

    // Find the winner
    int winner = 0;
    for (int i = 1; i < 4; i++) {
        if (scores[i] > scores[winner]) winner = i;
    }

    leader_name = candidates[winner];
    popularity = rand() % 50 + 50;

    cout << "EXCELLENT! " << leader_name << " has been elected with popularity " << popularity << "!\n";
}
