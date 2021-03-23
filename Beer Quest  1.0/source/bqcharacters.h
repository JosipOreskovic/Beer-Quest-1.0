#pragma once

#include "stdafx.h"
#include "bqitems.h"



class Character
{
	friend class Command;

private:
	string name;
	int type;
public:
	Character(string name, int type) : name(name), type(type) {}
	string GetName() const;
	int GetType() const;
	void SetName(string);
};

class Enemy : public Character
{

private:
	int energy;
	int damage;
public:
	Enemy(string name, int type) : Character(name, type) { energy = NULL; damage = NULL; }
	int GetEnergy() const;
	int GetDamage() const;
	void SetEnergy(int);
	void SetDamage(int);
};

class Friend : public Character
{

private:
	int incEnergy;
	int incMoney;
	Item* item;
public:
	Friend(string name, int type) : Character(name, type) { item = nullptr; }
	int GetEnergyBoost() const;
	int GetMoneyBoost() const;
	Item* GetItem() const;
	void SetEnergyBoost(int);
	void SetMoneyBoost(int);
	void PutItem(Item*);
	void DropItem();
};
