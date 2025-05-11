#include "Stronghold.h"

Map::Map() 
{
	for (int i = 0; i < 4; i++) 
    {
		player_positions[i] = i;
	}
}
void Map::move_player(int player_id, int new_position) 
{
	player_positions[player_id] = new_position;
	cout << "Player " << player_id << " moved to position " << new_position << endl;
}
void Map::display_map() 
{
    cout << "\n=== Kingdom Map (2x2 Grid) ===" << endl;

    for (int row = 0; row < 2; row++) 
    {
        for (int col = 0; col < 2; col++) 
        {
            int pos = row * 2 + col;
            cout << "| ";
            bool player_here = false;

            for (int i = 0; i < 4; i++) 
            {
                if (player_positions[i] == pos) 
                {
                    cout << "P" << i << " ";
                    player_here = true;
                    break;
                }
            }

            if (!player_here)
                cout << "  ";
        }
        cout << "|" << endl;
    }
}
