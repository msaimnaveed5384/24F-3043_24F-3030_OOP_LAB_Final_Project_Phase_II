#include "Stronghold.h"
#include <fstream>

void Conflict::declare_war(Player& attacker, Player& defender, Alliance& alliance) {
    cout << "\n⚔️ " << attacker.name << " has declared war on " << defender.name << "!\n";

    // Check betrayal
    bool was_allied = (alliance.active &&
        ((alliance.member_ids[0] == attacker.kingdom_id && alliance.member_ids[1] == defender.kingdom_id) ||
            (alliance.member_ids[1] == attacker.kingdom_id && alliance.member_ids[0] == defender.kingdom_id)));

    if (was_allied) {
        cout << "⚠️ Betrayal! Alliance broken between " << attacker.name << " and " << defender.name << ".\n";
        attacker.army->morale -= 10;
        defender.army->morale += 5;
        alliance.break_alliance();
    }

    // Army power (add random modifier)
    int attacker_power = attacker.army->soldiers + attacker.army->morale + (rand() % 20);
    int defender_power = defender.army->soldiers + defender.army->morale + (rand() % 20);

    cout << "Attacker power: " << attacker_power << " | Defender power: " << defender_power << endl;

    if (attacker_power > defender_power) {
        cout << "✅ " << attacker.name << " won the battle!\n";

        // Damage to defender
        int lost = rand() % 10 + 5;
        defender.army->soldiers = max(0, defender.army->soldiers - lost);
        defender.army->morale -= 5;

        // Rewards to attacker
        int loot = min(100, defender.resource->gold);
        attacker.resource->gold += loot;
        defender.resource->gold -= loot;
        cout << "💰 Looted " << loot << " gold.\n";
    }
    else {
        cout << "❌ " << attacker.name << " lost the battle!\n";

        int lost = rand() % 10 + 5;
        attacker.army->soldiers = max(0, attacker.army->soldiers - lost);
        attacker.army->morale -= 5;

        // Defender gains morale and gold
        defender.army->morale += 3;
        defender.resource->gold += 50;
        attacker.resource->gold = max(0, attacker.resource->gold - 50);
        cout << "💥 Attacker lost soldiers and 50 gold.\n";
    }

    // Log war
    ofstream log("war_log.txt", ios::app);
    log << attacker.name << " vs " << defender.name
        << " | Result: " << (attacker_power > defender_power ? "Attacker won" : "Defender won")
        << " | A:" << attacker_power << " D:" << defender_power << endl;
    log.close();
}

