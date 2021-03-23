#pragma once

#include "stdafx.h"
#include "bqgame.h"



string Place::GetName() { return name; }
int Place::GetType() { return type; }
bool Place::GetGameOver() { return gameOver; }

vector<Item*> Place::GetItems() const
{
	return items;
}
vector<Enemy*> Place::GetEnemies() const
{
	return enemies;
}
vector<Friend*> Place::GetFriends() const
{
	return friends;
}

vector<Place*> Place::GetPlaces() const
{
	return places;
}
void Place::PutItem(Item* item) { items.push_back(item); }
void Place::DropItem(Item* item)
{
	for (int i = 0; i < items.size(); ++i)
		if (items[i]->GetName() == item->GetName()) items.erase(items.begin() + i);
}

void Place::PutEnemy(Enemy* enem)
{
	enemies.push_back(enem);
}
void Place::PutFriend(Friend* frnd)
{
	friends.push_back(frnd);
}
void Place::PutPlace(Place* place)
{
	places.push_back(place);
}


void Place::DropEnemy(Enemy* enem)
{
	for (unsigned i = 0; i < enemies.size(); ++i)
		if (enemies[i]->GetName() == enem->GetName()) enemies.erase(enemies.begin() + i);
}
void Place::DropFriend(Friend* frnd)
{
	for (unsigned i = 0; i < friends.size(); ++i)
		if (friends[i]->GetName() == frnd->GetName()) friends.erase(friends.begin() + i);
}

void Place::DropPlace(Place* place)
{
	for (unsigned i = 0; i < places.size(); ++i)
		if (places[i]->GetName() == place->GetName()) places.erase(places.begin() + i);
}

void Place::PrintList(int type)
{

	int counter = 0;
	switch (type)
	{
	case ITEM:
		for (int i = 0; i < this->items.size(); i++)
			cout << i+1 << ". " << this->items[i]->GetName() << endl;
		break;
	case ENEMY:
		for (int i = 0; i < this->enemies.size(); i++)
		{
			cout << i + 1 << ". " << this->enemies[i]->GetName() << "\t Energy:\t" << this->enemies[i]->GetEnergy() << "\tAnnoying level:\t" << this->enemies[i]->GetDamage() << endl;
		}
		break;
	case FRIEND:
		for (int i = 0; i < this->friends.size(); i++)
		{
			cout << i + 1 << ". " << this->friends[i]->GetName() << endl;
		}
		break;

	case PLACE:
		for (int i = 0; i < this->places.size(); i++)
		{
			cout << i + 1 << ". " << this->places[i]->GetName() << endl;
		}
		break;
	}
}



Item* Place::ChooseItem()
{
	int choice = 0;
	if (this->GetItems().size() > 0)
	{
		while ((choice <= 0 || choice > items.size()) && choice != ESC)
		{
			cout << "Choose item:" << endl;
			for (int i = 0; i < this->GetItems().size(); i++)
				cout << i + 1 << ". " << this->items[i]->GetName() << endl;

			cout << "Choice:";
			choice = Command::Get() - 48;
		}
		if (choice != ESC) return items[choice - 1];
		else return nullptr;
	}
	else
	{
		cout << "There are no items here!" << endl;
		return nullptr;
	}

	return nullptr;
}

Enemy* Place::ChooseEnemy()
{
	int choice = 0;
	if (this->GetEnemies().size() > 0)
	{
		while ((choice <= 0 || choice > this->GetEnemies().size()) && choice != ESC)
		{
			cout << "Choose annoying character:" << endl;
			for (auto i = 0; i < this->GetEnemies().size(); i++)
				cout << i + 1 << ". " << this->GetEnemies()[i]->GetName() << endl;
			cout << "Choice:";
			choice = Command::Get() - 48;
		}
		if (choice != ESC) return this->GetEnemies()[choice - 1];
		else return nullptr;
	}
	else
	{
		cout << "There are no jerks here!" << endl;
		return nullptr;
	}

	return nullptr;
}

Friend* Place::ChooseFriend()
{
	int choice = 0;
	if (this->GetFriends().size() > 0)
	{
		while ((choice <= 0 || choice > this->GetFriends().size()) && choice != ESC)
		{
			cout << "Choose friend:" << endl;
			for (int i = 0; i < this->GetFriends().size(); i++)
				cout << i + 1 << ". " << this->GetFriends()[i]->GetName() << endl;
			cout << "Choice:";
			choice = Command::Get() - 48;
		}
		if (choice != ESC) return this->GetFriends()[choice - 1];
		else return nullptr;
	}
	else
	{
		cout << "There are no friends here!" << endl;
		return nullptr;
	}

	return nullptr;
}
