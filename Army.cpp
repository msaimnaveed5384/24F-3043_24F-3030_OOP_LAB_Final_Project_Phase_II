#include "Stronghold.h"
Army::Army() {
	soldiers = 20;
	morale = 70;
}
void Army::recruit(Population& pop) {
	int recruits = rand() % 10 + 5;
	if (pop.total >= recruits) {
		soldiers += recruits;
		pop.total -= recruits;
		morale += 2;
		cout << recruits << " soldiers recruited from population." << endl;
	}
	else {
		cout << "Not enough population to recruit soldiers!" << endl;
	}
}
void Army::feed() {
	morale += 1;
	cout << "Army fed properly. Morale increased." << endl;
}
void Army::pay(Economy& eco) 
{
	int payment = soldiers * 5;
	if (eco.treasury >= payment) 
	{
		eco.treasury -= payment;
		morale += 3;
		cout << "Army paid. Morale increased significantly." << endl;
	}
	else {
		morale -= 5;
		cout << "Treasury too low to pay army! Morale dropped!" << endl;
	}
}


void Army::status_report() const {
	cout << "Army: " << soldiers << " soldiers, Morale: " << morale << endl;
}
