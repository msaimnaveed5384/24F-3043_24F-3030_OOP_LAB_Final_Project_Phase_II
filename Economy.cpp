#include "Stronghold.h"
Economy::Economy() {
	treasury = 1000;
	tax_rate = 10;
}
void Economy::collect_tax(Population& pop) {
    int tax = (pop.total * tax_rate) / 100;
    treasury += tax;

    // Tax burden affects mer
    // chant happiness
    int burden = tax_rate / 5 + (rand() % 3);  // penalty between ~2 to 5
    pop.society.merchants.happiness -= burden;

    cout << "Collected " << tax << " gold from taxes." << endl;
    cout << "Merchants feel burdened. Happiness decreased by " << burden << "." << endl;

    if (pop.society.merchants.happiness < 30) {
        cout << "⚠️ Merchants are very unhappy due to excessive taxation!" << endl;
    }
}

void Economy::adjust_inflation() {
	int loss = rand() % 100;
	treasury -= loss;
	cout << "Inflation caused a loss of " << loss << " gold from treasury." << endl;
}

void Economy::status_report() const {
	cout << "Treasury: " << treasury << " gold, Tax Rate: " << tax_rate << "%" << endl;
}
