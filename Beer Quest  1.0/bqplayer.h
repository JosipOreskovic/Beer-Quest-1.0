#pragma once

#include "stdafx.h"
#include "bqplace.h"



class Player : public Character
{

private:
	int energy;
	int money;
	int level;
	int points;
	vector<Item*> items;

public:
	Player(string name, int type) : Character(name, type) { energy = 0; money = 0; level = 0; points = 0; }
	int GetMoney() const;
	int GetEnergy() const;
	int GetLevel() const;
	int GetPoints() const;
	void SetLevel(int inclevel);
	void SetPoints(int incpoints);
	vector<Item*> GetItems() const;
	void SetEnergy(int energy);
	void SetMoney(int gold);
	void BuyItem(Item* item);
	void PutItem(Item* item);
	void SellItem(Item* item, int price);
	void PickUpItem(Place* activePlace);
	void DropItem(Item* item);
	void PrintPlayerStat();
	void PrintItemsList();
	Item* ChooseItem(Place*);
	void Talk(Friend*);
	void UseItem(Place*);
	int Argue(Place*);
	void MeetEnemy(Place* activePlace);
};
