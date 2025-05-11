#include "Stronghold.h"
Event::Event() {
	srand(time(0));
}
void Event::random_disaster(Population& pop, Army& army, Resource& res, Economy& eco) {
	int event_num = rand() % 4;
	if (event_num == 0) {
		cout << "Famine struck the land!" << endl;
		res.food -= 100;
		pop.shrink();
	}
	else if (event_num == 1) {
		cout << "War broke out!" << endl;
		army.morale -= 10;
		army.soldiers -= 5;
	}
	else if (event_num == 2) {
		cout << "A deadly plague spreads!" << endl;
		pop.shrink();
		pop.shrink();
	}
	else {
		cout << "Severe drought reduced resources!" << endl;
		res.food -= 50;
		res.wood -= 30;
	}
}
