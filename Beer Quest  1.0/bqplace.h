#pragma once

#include "stdafx.h"
#include "bqcharacters.h"


class Place
{
	friend class Command;

private:
	string name;
	int type;
	bool gameOver = false;

	vector<Item*> items;
	vector<Enemy*> enemies;
	vector<Friend*> friends;
	vector<Place*> places;

public:
	Place(string name, int type) : name(name), type(type) {}
	string GetName();
	int GetType();
	bool GetGameOver();
	vector<Item*> GetItems() const;
	vector<Enemy*> GetEnemies() const;
	vector<Friend*> GetFriends() const;
	vector<Place*> GetPlaces() const;
	void PutItem(Item*);
	void PutEnemy(Enemy*);
	void PutFriend(Friend*);
	void PutPlace(Place*);
	void DropItem(Item*);
	void DropEnemy(Enemy*);
	void DropFriend(Friend*);
	void DropPlace(Place*);
	void PrintList(int);
	Item* ChooseItem();
	Enemy* ChooseEnemy();
	Friend* ChooseFriend();
};
