#pragma once

#include "stdafx.h"
#include "bqcommand.h"


using namespace std;

enum TYPE { PLACE, PLAYER, ENEMY, FRIEND, ITEM, ENERGY_REDUCE, DAMAGE_REDUCE, MONEY_BOOST, ENERGY_BOOST, ACTION_PLACE, BUY_STORE, SELL_STORE, BUY_SELL_STORE };
const int ESC = -21, ARGUE_POINTS = 10, ITEM_POINTS = 3, FRIEND_POINTS = 5, MAX_ENERGY = 100, TIME_ENERGY = 10, INC_ENERGY = 1, NEXT_LEVEL = 10, ARGUE_FACTOR = 10;


class Item
{

private:
	string name;
	int type;
	int price;
public:
	Item(string name, int type) : name(name), type(type) {}
	string GetName() const;
	int GetType() const;
	int GetPrice() const;
	void SetPrice(int);
	int virtual GetDamage();
	int virtual GetMoneyBoost();
	int virtual GetEnergyBoost();
	int virtual GetReduceDamage();
	void virtual SetEnergyBoost(int);
	void virtual SetMoneyBoost(int);
	void virtual SetDamage(int);
	void virtual SetReduceDamage(int);


};

class EnergyReduce : public Item
{

private:
	int damage;

public:
	EnergyReduce(string name, int type) : Item(name, type) {}
	int GetDamage() const;
	void SetDamage(int);
};

class DamageReduce : public Item
{

private:
	int reduceDamage;

public:
	DamageReduce(string name, int type) : Item(name, type) {}
	int GetReduceDamage() const;
	void SetReduceDamage(int);
};

class EnergyBoost : public Item
{

private:
	int incEnergy;
public:
	EnergyBoost(string name, int type) : Item(name, type) {}
	int GetEnergyBoost() const;
	void SetEnergyBoost(int);
};

class MoneyBoost : public Item
{

private:
	int incMoney;

public:
	MoneyBoost(string name, int type) : Item(name, type) {}
	int GetMoneyBoost() const;
	void SetMoneyBoost(int);
};
