#ifndef STRONGHOLD_H
#define STRONGHOLD_H
#include <iostream>
#include<vector>
#include <fstream>
#include <string>
#include <memory>  // for smart pointers
#include <cstdlib>
#include <ctime>
using namespace std;

class KingdomEntity 
{
public:
	virtual void status_report() const = 0;
	virtual ~KingdomEntity() {}
};

class SocialClass {
public:
	int count;
	int happiness;

	SocialClass(int c = 0, int h = 50) : count(c), happiness(h) {}
	virtual void grow() = 0;
	virtual void shrink() = 0;
	virtual void report() const = 0;
	virtual ~SocialClass() {}
};

class Peasant : public SocialClass {
public:
	Peasant(int c = 100, int h = 60) : SocialClass(c, h) {}
	void grow() override;
	void shrink() override;
	void report() const override;
};

class Merchant : public SocialClass {
public:
	Merchant(int c = 20, int h = 70) : SocialClass(c, h) {}
	void grow() override;
	void shrink() override;
	void report() const override;
};

class Noble : public SocialClass {
public:
	Noble(int c = 5, int h = 80) : SocialClass(c, h) {}
	void grow() override;
	void shrink() override;
	void report() const override;
};

class Society {
public:
	Peasant peasants;
	Merchant merchants;
	Noble nobles;

	Society();
	void simulate_growth();
	void simulate_decline();
	void display_society();
	int total_population() const;
};
class Resource;
class Leadership;
class Population : public KingdomEntity {
public:
	int total;
	int happiness;
	Society society;

	Population();
	void grow(Resource& );
	void shrink();
	void check_revolt(Leadership&);
	void update_total();
	void status_report() const override;
};
class Economy;
class Army : public KingdomEntity {
public:
	int soldiers;
	int morale;

	Army();
	void recruit(Population& pop);
	void feed();
	void pay(Economy& eco);
	void status_report() const override;
};

class Leadership : public KingdomEntity {
public:
	string leader_name;
	int popularity;

	Leadership();
	void change_leader();
	void hold_election(const Population& pop);  // New election function
	void status_report() const override;
};

class Economy : public KingdomEntity {
public:
	int treasury;
	int tax_rate;

	Economy();
	void collect_tax(Population& pop);
	void adjust_inflation();
	void status_report() const override;
};
class Bank : public KingdomEntity {
public:
	int loan_amount;
	int interest_rate;
	
	Bank();
	void take_loan(Economy& eco);
	void repay_loan(Economy& eco);
	void status_report() const override;
};
class Resource : public KingdomEntity {
public:
	int food;
	int wood;
	int stone;
	int iron;
	int gold;

	Resource();
	void gather();
	void status_report() const override;
};
class Event {
public:
	Event();
	void random_disaster(Population& pop, Army& army, Resource& res, Economy& eco);
};
class Player {
public:
    string name;
    int kingdom_id;
    bool is_ai;

    shared_ptr<Army> army;
    shared_ptr<Resource> resource;

    Player();
    virtual ~Player() {}  // ✅ This enables dynamic_cast!

    void send_message(Player& recipient, string message);
};

class Alliance;
// AI driven bonus task
class AIPlayer : public Player {
public:
	AIPlayer();

	void take_turn(Population& pop, Army& army, Leadership& lead,
		Economy& eco, Bank& bank, Resource& res, Event& event,
		Player& opponent, Alliance& alliance);

};


class Alliance {
public:
	int member_ids[2]; // Simple array for 2 players
	bool active;
	Alliance();
	void form_alliance(int player1_id, int player2_id);
	void break_alliance();
};
class Trade {
public:
	int sender_id;
	int receiver_id;
	string resources_offered;
	string resources_requested;
	bool is_smuggling;

	Trade();
	void propose_trade();
	void complete_trade(Resource& sender_res, Resource& receiver_res);
	void attempt_smuggling(Resource& sender_res, Resource& receiver_res);
};
const int MAP_SIZE = 16;

class Map {
public:
	int player_positions[4];        // player_positions[player_id] = cell number
	bool occupied[MAP_SIZE];        // true if someone is standing in the cell

	Map();
	void move_player(int player_id, int new_position);
	void display_map();
	bool is_occupied(int cell) const;
};

class Conflict {
public:
	static void declare_war(Player& attacker, Player& defender, Alliance& alliance);
};

class GameException : public exception {
	string message;
public:
	GameException(const string& msg) : message(msg) {}
	const char* what() const noexcept override 
	{
		return message.c_str();
	}
};


void save_game(Population& pop, Army& army, Leadership& lead, Economy& eco, Bank& bank, Resource& res,
	Alliance& alliance, Map& map);
void load_game(Population& pop, Army& army, Leadership& lead, Economy& eco, Bank& bank, Resource& res,
	Alliance& alliance, Map& map);
// LOG SCORE
void log_score(int turn, const Population& pop, const Army& army, const Economy& eco, const Resource& res);

//Analytics Logger
template <typename T>
class Logger 
{
private:
	string category;
	vector<T> data;

public:
	Logger(const string& name) : category(name) {}

	void log(T value) 
	{
		data.push_back(value);
	}

	void save_to_file() const 
	{
		ofstream fout("log_" + category + ".txt");
		if (!fout.is_open()) {
			cout << "Logger Error: Cannot open file for " << category << endl;
			return;
		}

		fout << "Log for: " << category << "\n";
		for (size_t i = 0; i < data.size(); ++i) {
			fout << "Turn " << i + 1 << ": " << data[i] << "\n";
		}
		fout.close();
	}

	void save_summary() const 
	{
		if (data.empty()) 
			return;

		T min_val = data[0], max_val = data[0];
		double total = 0;
		for (T val : data) 
		{
			min_val = min(min_val, val);
			max_val = max(max_val, val);
			total += val;
		}

		double average = total / data.size();

		ofstream fout("analytics_summary.txt", ios::app);
		if (!fout.is_open()) {
			cout << "Analytics Error: Could not write summary.\n";
			return;
		}

		fout << " " << category << " Analytics:\n";
		fout << "  Turns Logged: " << data.size() << "\n";
		fout << "  Min: " << min_val << " | Max: " << max_val << " | Average: " << average << "\n";
		fout << "---------------------------------------\n";
		fout.close();
	}
};

#endif
