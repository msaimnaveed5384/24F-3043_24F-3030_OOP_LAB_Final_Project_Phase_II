#include "Stronghold.h"
Resource::Resource() {
    food = 500;
    wood = 300;
    stone = 200;
    iron = 100;
}
void Resource::gather() {
    int food_gain = rand() % 50 + 20;
    int wood_gain = rand() % 30 + 10;
    int stone_gain = rand() % 20 + 5;
    int iron_gain = rand() % 15 + 3;
    food += food_gain;
    wood += wood_gain;
    stone += stone_gain;
    iron += iron_gain;

    cout << "Resources gathered: " << food_gain << " food, " << wood_gain << " wood, "
        << stone_gain << " stone, " << iron_gain << " iron." << endl;
}

void Resource::status_report() const {
    cout << "Resources - Food: " << food << ", Wood: " << wood
        << ", Stone: " << stone << ", Iron: " << iron << endl;
}
