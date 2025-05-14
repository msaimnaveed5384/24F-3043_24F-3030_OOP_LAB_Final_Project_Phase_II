#include "Stronghold.h"

Population::Population() {
    total = 100;
    happiness = 70;
    society = Society();  // initialize with default class values
    update_total();       // sync total with social class count
}
void Population::grow(Resource& res) 
{
    if (res.food < 100) 
    {
        cout << " Not enough food! Growth is stunted." << endl;
        happiness -= 5;
        return;
    }
    society.simulate_growth();
    update_total();
    happiness += 2;
    res.food -= 100; // consume food
    cout << "Population classes grew. Happiness slightly increased." << endl;
}



void Population::shrink() {
    society.simulate_decline();
    update_total();
    happiness -= 5;
    cout << "Population declined. General happiness decreased." << endl;
}

void Population::check_revolt(Leadership& lead) {
    bool unrest = false;

    if (society.peasants.happiness < 30) {
        cout << "Peasants are angry and might revolt!" << endl;
        lead.popularity -= 5;
        unrest = true;
    }

    if (society.merchants.happiness < 30) {
        cout << "Merchants are unhappy. Economic unrest possible!" << endl;
        lead.popularity -= 3;
        unrest = true;
    }

    if (!unrest) {
        cout << "Social classes are stable... for now." << endl;
    }
}


void Population::update_total() {
    total = society.total_population();
}

void Population::status_report() const {
    cout << "Total Population: " << total << " (Happiness: " << happiness << ")" << endl;
}
