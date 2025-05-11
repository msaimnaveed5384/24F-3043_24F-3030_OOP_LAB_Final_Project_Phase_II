#include "Stronghold.h"
#include <iostream>

void Peasant::grow() {
    int added = rand() % 20 + 5;
    count += added;
    happiness += 1;
    cout << "Peasant population grew by " << added << endl;
}

void Peasant::shrink() {
    int lost = rand() % 15 + 3;
    count = max(0, count - lost);
    happiness -= 3;
    cout << "Peasant population decreased by " << lost << endl;
}

void Peasant::report() const {
    cout << "Peasants - Count: " << count << ", Happiness: " << happiness << endl;
}

void Merchant::grow() {
    int added = rand() % 5 + 1;
    count += added;
    happiness += 2;
    cout << "Merchant population grew by " << added << endl;
}

void Merchant::shrink() {
    int lost = rand() % 3 + 1;
    count = max(0, count - lost);
    happiness -= 5;
    cout << "Merchant population decreased by " << lost << endl;
}

void Merchant::report() const {
    cout << "Merchants - Count: " << count << ", Happiness: " << happiness << endl;
}

void Noble::grow() {
    int added = (rand() % 2 == 0) ? 1 : 0;
    count += added;
    happiness += 1;
    cout << "Noble population grew by " << added << endl;
}

void Noble::shrink() {
    int lost = (rand() % 2 == 0) ? 1 : 0;
    count = max(0, count - lost);
    happiness -= 2;
    cout << "Noble population decreased by " << lost << endl;
}

void Noble::report() const {
    cout << "Nobles - Count: " << count << ", Happiness: " << happiness << endl;
}

Society::Society() : peasants(), merchants(), nobles() {}

void Society::simulate_growth() {
    peasants.grow();
    merchants.grow();
    nobles.grow();
}

void Society::simulate_decline() {
    peasants.shrink();
    merchants.shrink();
    nobles.shrink();
}

void Society::display_society() {
    cout << "\n=== Social Class Report ===" << endl;
    peasants.report();
    merchants.report();
    nobles.report();
}

int Society::total_population() const {
    return peasants.count + merchants.count + nobles.count;
}
