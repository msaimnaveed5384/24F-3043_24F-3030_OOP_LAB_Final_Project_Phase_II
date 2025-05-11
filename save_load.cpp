#include "Stronghold.h"

void save_game(Population& pop, Army& army, Leadership& lead, Economy& eco, Bank& bank, Resource& res,
    Alliance& alliance, Map& map) {
    ofstream fout("game_save.txt");
    if (!fout.is_open()) {
        throw GameException("Error: Unable to write to save file.");
    }

    fout << pop.total << " " << pop.happiness << endl;
    fout << army.soldiers << " " << army.morale << endl;
    fout << lead.leader_name << " " << lead.popularity << endl;
    fout << eco.treasury << " " << eco.tax_rate << endl;
    fout << bank.loan_amount << " " << bank.interest_rate << endl;
    fout << res.food << " " << res.wood << " " << res.stone << " " << res.iron << endl;
    fout << alliance.member_ids[0] << " " << alliance.member_ids[1] << " " << alliance.active << endl;
    for (int i = 0; i < 4; i++) {
        fout << map.player_positions[i] << " ";
    }
    fout << endl;
    fout.close();
}


void load_game(Population& pop, Army& army, Leadership& lead, Economy& eco, Bank& bank, Resource& res,
    Alliance& alliance, Map& map) {
    ifstream fin("game_save.txt");
    if (!fin.is_open()) {
        throw GameException("Error: Save file not found or cannot be opened.");
    }

    try {
        fin >> pop.total >> pop.happiness;
        fin >> army.soldiers >> army.morale;
        fin >> lead.leader_name >> lead.popularity;
        fin >> eco.treasury >> eco.tax_rate;
        fin >> bank.loan_amount >> bank.interest_rate;
        fin >> res.food >> res.wood >> res.stone >> res.iron;
        fin >> alliance.member_ids[0] >> alliance.member_ids[1] >> alliance.active;
        for (int i = 0; i < 4; i++) {
            fin >> map.player_positions[i];
        }
        fin.close();
    }
    catch (...) {
        throw GameException("Error: Malformed save file or reading issue.");
    }
}
