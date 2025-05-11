#include "Stronghold.h"
#include <fstream>

void Conflict::declare_war(Player& attacker, Player& defender, Alliance& alliance) {
    cout << attacker.name << " has declared war on " << defender.name << "!" << endl;

    bool was_allied = (alliance.active &&
        ((alliance.member_ids[0] == attacker.kingdom_id && alliance.member_ids[1] == defender.kingdom_id) ||
            (alliance.member_ids[1] == attacker.kingdom_id && alliance.member_ids[0] == defender.kingdom_id)));

    if (was_allied) {
        cout << "⚠️ Betrayal! An ally has been attacked. Penalty applied." << endl;
        attacker.army->morale -= 10;
        defender.army->morale += 5;
        alliance.break_alliance();
    }

    int attack_power = attacker.army->soldiers + (rand() % 20);
    int defense_power = defender.army->soldiers + (rand() % 20);

    if (attack_power > defense_power) {
        cout << "✅ " << attacker.name << " won the battle!" << endl;
        defender.army->soldiers -= rand() % 10 + 5;
        attacker.resource->gold += 100;
        defender.resource->gold = max(0, defender.resource->gold - 100);
    }
    else {
        cout << "❌ " << attacker.name << " lost the battle!" << endl;
        attacker.army->soldiers -= rand() % 10 + 5;
        defender.resource->gold += 50;
        attacker.resource->gold = max(0, attacker.resource->gold - 50);
    }

    ofstream log("war_log.txt", ios::app);
    log << attacker.name << " declared war on " << defender.name << ". Result: "
        << (attack_power > defense_power ? "Attacker won" : "Defender won") << endl;
    log.close();
}
