#include "Stronghold.h"

Player::Player() {
    name = "Player";
    kingdom_id = 0;
    is_ai = false;
    army = make_shared<Army>();
    resource = make_shared<Resource>();
}


void Player::send_message(Player& recipient, string message) {
    cout << "Message from " << name << " to " << recipient.name << ": " << message << endl;
    // Log to file
    ofstream log("chat_log.txt", ios::app);
    log << name << " to " << recipient.name << ": " << message << endl;
    log.close();
}