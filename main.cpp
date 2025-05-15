#include "Stronghold.h"

Logger<int> pop_logger("population");
Logger<int> treasury_logger("treasury");
Logger<int> army_logger("army");

int main() {
    int turn_number = 1;

    try {
        // Shared game systems
        auto pop = make_shared<Population>();
        auto army = make_shared<Army>();
        auto lead = make_shared<Leadership>();
        auto eco = make_shared<Economy>();
        auto bank = make_shared<Bank>();
        auto res = make_shared<Resource>();
        auto event = make_shared<Event>();

        auto current_alliance = make_shared<Alliance>();
        auto current_trade = make_shared<Trade>();
        auto game_map = make_shared<Map>();

        // Players
        const int total_players = 4;
        Player* players[total_players];

        for (int i = 0; i < total_players; ++i) {
            if (i < 2) {
                players[i] = new Player();
                players[i]->is_ai = false;
            }
            else {
                players[i] = new AIPlayer();
                players[i]->is_ai = true;
            }

            players[i]->name = "Player " + to_string(i);
            players[i]->kingdom_id = i;
        }

        load_game(*pop, *army, *lead, *eco, *bank, *res, *current_alliance, *game_map);

        int exit_choice = 1;

        while (exit_choice != 0) {
            cout << "\n======= 🌍 Turn " << turn_number << " =======" << endl;

            for (int i = 0; i < total_players; ++i) {
                cout << "\n🎮 Turn for " << players[i]->name << endl;

                if (players[i]->is_ai) {
                    AIPlayer* ai_ptr = dynamic_cast<AIPlayer*>(players[i]);
                    if (ai_ptr) {
                        ai_ptr->take_turn(*pop, *army, *lead, *eco, *bank, *res, *event,
                            *players[0], *current_alliance);

                    }
                }
                else {
                    int choice;
                    do {
                        cout << "\n=== Stronghold Kingdom Management ===" << endl;
                        cout << "1. Simulate Social Class Growth/Decline\n"
                            << "2. Manage Population\n"
                            << "3. Train Army\n"
                            << "4. Change Leadership\n"
                            << "5. Manage Economy\n"
                            << "6. Use Bank\n"
                            << "7. Collect Resources\n"
                            << "8. Handle Random Event\n"
                            << "9. Show Kingdom Status\n"
                            << "10. Send Message to Another Player\n"
                            << "11. Manage Alliances\n"
                            << "12. Trade with Another Player\n"
                            << "13. View and Move on Map\n"
                            << "14. Declare War\n"
                            << "0. End Turn\n";

                        cout << "Enter your choice: ";
                        if (!(cin >> choice)) throw GameException("Invalid input!");

                        switch (choice) {
                        case 1: {
                            cout << "1. Grow  2. Decline: ";
                            int action;
                            cin >> action;
                            if (action == 1) pop->society.simulate_growth();
                            else if (action == 2) pop->society.simulate_decline();
                            else throw GameException("Invalid social class action");
                            pop->society.display_society();
                            break;
                        }
                        case 2:
                            pop->grow(*res);
                            pop->check_revolt(*lead);
                            break;
                        case 3:
                            army->recruit(*pop);
                            army->feed();
                            army->pay(*eco);
                            break;
                        case 4:
                            lead->change_leader();
                            break;
                        case 5:
                            eco->collect_tax(*pop);
                            eco->adjust_inflation();
                            break;
                        case 6: {
                            cout << "1. Take Loan  2. Repay Loan: ";
                            int bank_choice;
                            cin >> bank_choice;
                            if (bank_choice == 1)
                                bank->take_loan(*eco);
                            else if (bank_choice == 2)
                                bank->repay_loan(*eco);
                            else throw GameException("Invalid bank option.");
                            break;
                        }
                        case 7:
                            res->gather();
                            break;
                        case 8:
                            event->random_disaster(*pop, *army, *res, *eco);
                            break;
                        case 9: {
                            vector<KingdomEntity*> systems = { pop.get(), army.get(), lead.get(), eco.get(), bank.get(), res.get() };
                            for (auto sys : systems) sys->status_report();
                            break;
                        }
                        case 10: {
                            cout << "Enter recipient ID (0-3): ";
                            int recipient_id;
                            cin >> recipient_id;
                            cin.ignore();
                            cout << "Enter message: ";
                            string msg;
                            getline(cin, msg);
                            players[i]->send_message(*players[recipient_id], msg);
                            break;
                        }
                        case 11: {
                            cout << "1. Form Alliance  2. Break Alliance: ";
                            int a_choice;
                            cin >> a_choice;
                            if (a_choice == 1)
                                current_alliance->form_alliance(i, (i + 1) % total_players);
                            else if (a_choice == 2)
                                current_alliance->break_alliance();
                            else throw GameException("Invalid alliance option");
                            break;
                        }
                        case 12: {
                            current_trade->sender_id = i;
                            current_trade->receiver_id = (i + 1) % total_players;
                            cin.ignore();
                            cout << "Offer (e.g., food:50): ";
                            getline(cin, current_trade->resources_offered);
                            cout << "Request (e.g., stone:30): ";
                            getline(cin, current_trade->resources_requested);
                            cout << "Smuggling? (0/1): ";
                            int smug;
                            cin >> smug;
                            current_trade->is_smuggling = (smug == 1);
                            current_trade->propose_trade();
                            if (current_trade->is_smuggling)
                                current_trade->attempt_smuggling(*res, *res);
                            else
                                current_trade->complete_trade(*res, *res);
                            break;
                        }
                        case 13:
                            game_map->display_map();
                            cout << "Move player (0 = No, 1 = Yes): ";
                            int move;
                            cin >> move;
                            if (move == 1) {
                                    int pid;
                                    cout << "Your player ID (0–3): ";
                                    cin >> pid;
                                    if (pid < 0 || pid > 3) throw GameException("❌ Invalid player ID.");

                                    int new_pos;
                                    cout << "Enter new position (0–15): ";
                                    cin >> new_pos;
                                    if (new_pos < 0 || new_pos >= 16) throw GameException("❌ Position out of map bounds.");

                                    if (game_map->is_occupied(new_pos))
                                        throw GameException("❌ That position is already occupied. Try another.");

                                    game_map->move_player(pid, new_pos);
                            }
                            break;


                        case 14:
                            cout << "Target player ID (0-3): ";
                            int target_id;
                            cin >> target_id;
                            if (target_id == i || target_id < 0 || target_id >= total_players)
                                throw GameException("Invalid target.");
                            Conflict::declare_war(*players[i], *players[target_id], *current_alliance);
                            break;
                        case 0:
                            break;
                        default:
                            throw GameException("Invalid menu option");
                        }
                        // Election trigger logic (after all players' turn)
                        if (lead->popularity < 40) {
                            cout << "\n⚠️ Leadership popularity is low (" << lead->popularity << ")...\n";
                            lead->hold_election(*pop); // Early election due to crisis
                        }
                        else if (turn_number % 10 == 0) {
                            cout << "\n📆 Scheduled election for Turn " << turn_number << "\n";
                            lead->hold_election(*pop); // Scheduled periodic election
                        }
                        // Log and save
                        pop_logger.log(pop->total);
                        treasury_logger.log(eco->treasury);
                        army_logger.log(army->soldiers);
                        log_score(turn_number, *pop, *army, *eco, *res);
                        save_game(*pop, *army, *lead, *eco, *bank, *res, *current_alliance, *game_map);
                    } while (choice != 0);
                }
            }

            

            cout << "\nContinue? (1 = Yes, 0 = Exit): ";
            cin >> exit_choice;
            turn_number++;
        }

        // Save logs & analytics
        pop_logger.save_to_file();
        treasury_logger.save_to_file();
        army_logger.save_to_file();
        pop_logger.save_summary();
        treasury_logger.save_summary();
        army_logger.save_summary();

        // Clean up memory
        for (int i = 0; i < total_players; ++i)
            delete players[i];

        cout << "\n✅ Game Over. Summary and logs saved.\n";
    }
    catch (const GameException& e) {
        cout << "Game Error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "Standard Error: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown Error occurred.\n";
    }

    return 0;
}
