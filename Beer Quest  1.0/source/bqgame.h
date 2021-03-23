#pragma once

#include "stdafx.h"
#include <fstream>
#include "bqplayer.h"


class Game
{
	friend class Command;

private:
	bool gameOver;
	string playerName;
	char gameType;
	Place* activePlace;
	vector<Item*> items;
	vector<Character*> characters;
	vector<Place*> places;
	const int ESC = -21, BATTLE_POINTS = 10, ITEM_POINTS = 3, FRIEND_POINTS = 5, MAX_ENERGY = 100, TIME_ENERGY = 10, INC_ENERGY = 1;

	Item* Staple = new EnergyReduce("Staple Gun", ENERGY_REDUCE);
	Item* Mobile = new EnergyReduce("Mobile Phone", ENERGY_REDUCE);
	Item* Stool = new EnergyReduce("Bar Stool", ENERGY_REDUCE);

	Item* Flowers = new DamageReduce("Bouquet of Roses", DAMAGE_REDUCE);
	Item* Chocolate = new DamageReduce("Box of Chocolates", DAMAGE_REDUCE);
	Item* Beer = new EnergyBoost("Beer", ENERGY_BOOST);
	Item* Bonus = new MoneyBoost("Christmas Bonus", MONEY_BOOST);
	Item* Salary = new MoneyBoost("Salary Cheque", MONEY_BOOST);
	Item* Pizza = new EnergyBoost("Pizza", ENERGY_BOOST);

	Enemy* MotherInLaw = new Enemy("Mother In Law", ENEMY);
	Enemy* Boss = new Enemy("Boss", ENEMY);
	Enemy* Wife = new Enemy("Wife", ENEMY);
	Enemy* Drunk = new Enemy("Annoying Drunk", ENEMY);

	Friend* Ambrozije = new Friend("Ambrozije", FRIEND);
	Friend* Luka = new Friend("Luka", FRIEND);
	Friend* Ana = new Friend("Ana", FRIEND);
	Friend* Bojan = new Friend("Bojan", FRIEND);

	Player* player = new Player("New", PLAYER);

	Place* Home = new Place("Player's House", ACTION_PLACE);
	Place* Street = new Place("Town Street", ACTION_PLACE);
	Place* Office = new Place("Company Office", ACTION_PLACE);
	Place* Konzum = new Place("Konzum", BUY_STORE);
	Place* Pown = new Place("Pown", BUY_SELL_STORE);
	Place* Bar = new Place("Bar", BUY_STORE);
	Place* Square = new Place("Town Square", ACTION_PLACE);
	Place* Suburb = new Place("Town Suburb", ACTION_PLACE);
	Place* House = new Place("Mother in Law House", ACTION_PLACE);
	Place* Pizzeria = new Place("Pizzeria", BUY_STORE);


public:
	Game() {};
	void Play();
//	char GetCommand();
	void MainMenu();
	void NewGame(string);
	void Instructions();
	void Action();
	void SaveGame();
	void ResumeGame();
	void GoPlace();
	void PutPlace(Place*);
	void PutItem(Item*);
	void PutCharacter(Character*);
	void GameBackup();
	void GameOver();
	void AddPoints(int);
	void AddEnergy(int);
	Place* GetActivePlace();
};




