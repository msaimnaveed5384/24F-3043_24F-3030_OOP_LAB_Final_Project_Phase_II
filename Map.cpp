#include "Stronghold.h"

Map::Map() {
    for (int i = 0; i < 4; ++i) {
        player_positions[i] = i;         // Spawn at positions 0,1,2,3
    }
    for (int i = 0; i < MAP_SIZE; ++i) {
        occupied[i] = false;
    }
    for (int i = 0; i < 4; ++i) {
        occupied[player_positions[i]] = true;
    }
}
bool Map::is_occupied(int cell) const {
    if (cell < 0 || cell >= MAP_SIZE) return false;
    return occupied[cell];
}


void Map::move_player(int player_id, int new_position) {
    if (player_id < 0 || player_id >= 4 || new_position < 0 || new_position >= MAP_SIZE) {
        cout << "❌ Invalid move. Out of bounds.\n";
        return;
    }

    if (occupied[new_position]) {
        cout << "❌ That position is already occupied by another player.\n";
        return;
    }

    // Free old position
    occupied[player_positions[player_id]] = false;

    // Move
    player_positions[player_id] = new_position;
    occupied[new_position] = true;

    cout << "✅ Player " << player_id << " moved to position " << new_position << endl;
}


void Map::display_map() {
    cout << "\n🌍 === Kingdom Map (4x4 Grid) ===\n";

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            int cell = row * 4 + col;
            cout << "| ";

            bool found = false;
            for (int i = 0; i < 4; ++i) {
                if (player_positions[i] == cell) {
                    cout << "P" << i;
                    found = true;
                    break;
                }
            }

            if (!found) cout << "  ";
            cout << " ";
        }
        cout << "|\n";
    }
}
