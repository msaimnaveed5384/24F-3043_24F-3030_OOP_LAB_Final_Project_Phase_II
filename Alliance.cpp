#include "Stronghold.h"
Alliance::Alliance() {
	member_ids[0] = -1;
	member_ids[1] = -1;
	active = false;
}
void Alliance::form_alliance(int player1_id, int player2_id) {
	member_ids[0] = player1_id;
	member_ids[1] = player2_id;
	active = true;
	cout << "Alliance formed between Player " << player1_id << " and Player " << player2_id << endl;
}
void Alliance::break_alliance() {
	cout << "Alliance broken between Player " << member_ids[0] << " and Player " << member_ids[1] << endl;
	active = false;
	member_ids[0] = -1;
	member_ids[1] = -1;
}
