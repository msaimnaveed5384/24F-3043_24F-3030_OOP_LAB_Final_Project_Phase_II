#include "Stronghold.h"
#include <memory>

Logger<int> pop_logger("population");
Logger<int> treasury_logger("treasury");
Logger<int> army_logger("army");

int main()
{
    int current_player_index = 0;
    try
    {
        auto pop = make_shared<Population>();
        auto army = make_shared<Army>();
        auto lead = make_shared<Leadership>();
        auto eco = make_shared<Economy>();
        auto bank = make_shared<Bank>();
        auto res = make_shared<Resource>();
        auto event = make_shared<Event>();

        Player players[2];
        players[0].name = "Player 0";
        players[0].kingdom_id = 0;
        players[1].name = "Player 1";
        players[1].kingdom_id = 1;
        Player* current_player = &players[current_player_index];

        auto current_alliance = make_shared<Alliance>();
        auto current_trade = make_shared<Trade>();
        auto game_map = make_shared<Map>();

        load_game(*pop, *army, *lead, *eco, *bank, *res, *current_alliance, *game_map);

        int choice;
        do
        {
            current_player = &players[current_player_index];
            cout << "\n=== Stronghold Kingdom Management ===" << endl;
            cout << "1. Simulate Social Class Growth/Decline" << endl;
            cout << "2. Manage Population" << endl;
            cout << "3. Train Army" << endl;
            cout << "4. Change Leadership" << endl;
            cout << "5. Manage Economy" << endl;
            cout << "6. Use Bank" << endl;
            cout << "7. Collect Resources" << endl;
            cout << "8. Handle Random Event" << endl;
            cout << "9. Show Kingdom Status" << endl;
            cout << "10. Send Message to Another Player" << endl;
            cout << "11. Manage Alliances" << endl;
            cout << "12. Trade with Another Player" << endl;
            cout << "13. View and Move on Map" << endl;
            cout << "14. Declare War on Another Player" << endl;

            cout << "0. Exit Game" << endl;

            cout << "Enter your choice: ";
            if (!(cin >> choice))
            {
                throw GameException("Invalid input! Please enter a number.");
            }

            cout << endl;

            switch (choice)
            {
            case 1:
                cout << "1. Grow  2. Decline: ";
                int social_action;
                if (!(cin >> social_action)) throw GameException("Invalid input.");
                if (social_action == 1) pop->society.simulate_growth();
                else if (social_action == 2) pop->society.simulate_decline();
                else throw GameException("Choose 1 or 2.");
                pop->society.display_society();
                break;

            case 2:
                pop->grow();
                pop->check_revolt();
                break;
            case 3:
                army->recruit(*pop);
                army->feed();
                army->pay();
                break;
            case 4:
                lead->change_leader();
                break;
            case 5:
                eco->collect_tax(*pop);
                eco->adjust_inflation();
                break;
            case 6:
            {
                cout << "1. Take Loan  2. Repay Loan: ";
                int bank_choice;
                if (!(cin >> bank_choice)) {
                    throw GameException("Invalid bank option. Enter 1 or 2.");
                }
                if (bank_choice == 1)
                    bank->take_loan(*eco);
                else if (bank_choice == 2)
                    bank->repay_loan(*eco);
                else throw GameException("Invalid bank choice selected.");
                break;
            }
            case 7:
                res->gather();
                break;
            case 8:
                event->random_disaster(*pop, *army, *res, *eco);
                break;
            case 9:
            {
                vector<KingdomEntity*> systems = { pop.get(), army.get(), lead.get(), eco.get(), bank.get(), res.get() };
                for (auto sys : systems) sys->status_report();
                break;
            }
            case 10:
            {
                cout << "Enter recipient ID (0 or 1): ";
                int recipient_id;
                if (!(cin >> recipient_id) || recipient_id < 0 || recipient_id > 1) {
                    throw GameException("Invalid recipient ID. Choose 0 or 1.");
                }
                cin.ignore();
                cout << "Enter your message: ";
                string message;
                getline(cin, message);
                players[0].send_message(players[recipient_id], message);
                break;
            }
            case 11:
            {
                cout << "1. Form Alliance  2. Break Alliance: ";
                int alliance_choice;
                if (!(cin >> alliance_choice)) {
                    throw GameException("Invalid input for alliance management.");
                }
                if (alliance_choice == 1)
                    current_alliance->form_alliance(0, 1);
                else if (alliance_choice == 2)
                    current_alliance->break_alliance();
                else
                    throw GameException("Choose only 1 or 2 for alliance options.");
                break;
            }
            case 12:
            {
                current_trade->sender_id = 0;
                current_trade->receiver_id = 1;

                cout << "Enter resources to offer (e.g., 'food:50,wood:30'): ";
                cin.ignore();
                getline(cin, current_trade->resources_offered);

                cout << "Enter resources to request (e.g., 'iron:20,stone:40'): ";
                getline(cin, current_trade->resources_requested);

                cout << "Is this a smuggling trade? (0 = No, 1 = Yes): ";
                int smug;
                cin >> smug;
                current_trade->is_smuggling = (smug == 1);

                current_trade->propose_trade();

                if (current_trade->is_smuggling) {
                    current_trade->attempt_smuggling(*res, *res);
                }
                else {
                    current_trade->complete_trade(*res, *res);
                }

                save_game(*pop, *army, *lead, *eco, *bank, *res, *current_alliance, *game_map);
                break;
            }
            case 13:
            {
                game_map->display_map();
                cout << "Move player (0=No, 1=Yes): ";
                int move;
                if (!(cin >> move) || (move != 0 && move != 1)) {
                    throw GameException("Invalid choice. Enter 0 or 1.");
                }

                if (move == 1)
                {
                    cout << "Enter new position (0-3): ";
                    int new_pos;
                    if (!(cin >> new_pos) || new_pos < 0 || new_pos > 3) {
                        throw GameException("Invalid position. Choose between 0 and 3.");
                    }
                    game_map->move_player(0, new_pos);
                }
                break;
            }


            case 14:
            {
                cout << "Enter target player ID (0 or 1): ";
                int target_id;
                if (!(cin >> target_id) || target_id < 0 || target_id > 1 || target_id == 0) {
                    throw GameException("Invalid target ID. You cannot attack yourself.");
                }

                Conflict::declare_war(players[0], players[target_id], *current_alliance);
                break;
            }

            case 0:
                cout << "Exiting game. Goodbye!" << endl;
                break;
            default:
                throw GameException("Invalid menu option. Please try again.");
            }
            pop_logger.log(pop->total);
            treasury_logger.log(eco->treasury);
            army_logger.log(army->soldiers);

            save_game(*pop, *army, *lead, *eco, *bank, *res, *current_alliance, *game_map);
        } while (choice != 0);

        pop_logger.save_to_file();
        treasury_logger.save_to_file();
        army_logger.save_to_file();
    }
    catch (const GameException& e)
    {
        cout << "Game Error! " << e.what() << endl;
    }
    catch (const exception& e)
    {
        cout << "Standard Error! " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Unknown Error! Something went wrong." << endl;
    }

    return 0;
}
