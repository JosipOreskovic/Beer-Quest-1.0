#pragma once

#include "stdafx.h"
#include "bqitems.h"

class Action
{
private:
	string name;
	int type;

public:
	Action(string name, int type) : name(name), type(type) {}
	string GetName();
	int GetType();
	int virtual GetDamage();
	int virtual GetReduceDamage();
	int virtual GetIncEnergy();
	int virtual GetIncMoney();
	virtual Item* GetPlayerItem();
	void virtual SetDamage(int);
	void virtual SetReduceDamage(int);
	void virtual SetIncEnergy(int);
	void virtual SetIncMoney(int);
	void virtual SetPlayerItem(Item*);
};

class GetItemAction : public Action
{
private:
	Item* item;
public:
	GetItemAction(string name, int type) : Action(name, type), item(nullptr){}
	Item* GetItem();
	void SetItem(Item*);
};

class GetEnergyBoost : public Action
{
private:
	int incEnergy;
public:
	GetEnergyBoost(string name, int type): Action(name, type), incEnergy(NULL){}
	int GetIncEnergy();
	void SetIncEnergy(int);
};

class GetMoneyBoost : public Action
{
private:
	int incMoney;
public:
	GetMoneyBoost(string name, int type): Action(name, type), incMoney(NULL){}
	int GetIncMoney();
	void SetIncMoney(int);
};

class MakeDamage : public Action
{
private:
	int damage;
public:
	int GetDamage();
	void SetDamage(int);
};