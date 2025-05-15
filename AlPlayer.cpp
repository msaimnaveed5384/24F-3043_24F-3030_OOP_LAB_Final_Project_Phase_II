#include "Stronghold.h"

AIPlayer::AIPlayer() {
    name = "AI Kingdom";
    kingdom_id = 2;
    is_ai = true;
    army = make_shared<Army>();
    resource = make_shared<Resource>();
}

void AIPlayer::take_turn(Population& pop, Army& army, Leadership& lead,
    Economy& eco, Bank& bank, Resource& res, Event& event,
    Player& opponent, Alliance& alliance) 
{

        {
            cout << "\n AI is making decisions..." << endl;

            if (eco.treasury < 500) 
            {
                bank.take_loan(eco);
            }

            if (res.food < 200) {
                res.gather();
            }

            if (army.soldiers < 30) {
                army.recruit(pop);
            }

            if (rand() % 5 == 0) { // 20% chance to change leader
                lead.change_leader();
            }

            if (rand() % 4 == 0) 
            { // 25% chance for event
                event.random_disaster(pop, army, res, eco);
            }

            eco.collect_tax(pop);
            army.feed();
            army.pay(eco);

            // AI War Decision (30% chance)
            if (rand() % 10 < 3) 
            { // 30% chance to consider war
                cout << "🤖 AI " << name << " is evaluating war options...\n";

                // Target strongest human
                int target_id = -1;
                int max_gold = -1;
                for (int i = 0; i < 4; i++) {

                    if (!opponent.is_ai && opponent.resource->gold > max_gold && opponent.kingdom_id != kingdom_id) {
                        target_id = opponent.kingdom_id;
                        max_gold = opponent.resource->gold;
                    }
                }

                if (target_id != -1) 
                {
                    Player& target = opponent;

                    int my_power = this->army->soldiers + this->army->morale;
                    int their_power = target.army->soldiers + target.army->morale;

                    if (my_power >= their_power - 10) 
                    {
                        cout << " AI attacks Player " << target.name << "!\n";

                             Conflict::declare_war(static_cast<Player&>(*this), target, alliance);
                    }
                    else {
                        cout << " AI decides not to attack — opponent too strong.\n";
                    }
                }
            }
            cout << "🤖 AI turn complete.\n";
        }
}
