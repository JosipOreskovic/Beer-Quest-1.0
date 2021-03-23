#pragma once

#include "stdafx.h"
#include "bqgame.h"


int Player::GetEnergy() const { return energy; }
void Player::SetEnergy(int energy) { this->energy += energy; }
int Player::GetMoney() const { return money; }
void Player::SetMoney(int money) { this->money += money; }
int Player::GetLevel() const { return level; }
void Player::SetLevel(int inclevel) { level += inclevel; }
void Player::SetPoints(int incpoints) { points += incpoints; }
int Player::GetPoints() const { return points; }
vector<Item*> Player::GetItems() const { return items; }

void Player::BuyItem(Item* item)
{
	items.push_back(item);
	money -= item->GetPrice();
}
void Player::PutItem(Item* item)
{
	items.push_back(item);
}
void Player::SellItem(Item* item, int price)
{
	cout << "You sold " << item->GetName() << endl;
	DropItem(item);
	money += price;
}
void Player::DropItem(Item* item)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i]->GetName() == item->GetName())
			items.erase(items.begin() + i);
	}
}

void Player::PickUpItem(Place* activePlace)
{
	Item* item;
	item = activePlace->ChooseItem();
	if (item != NULL)
	{
		cout << "You picked up " << item->GetName() << endl;
		this->PutItem(item);
		activePlace->DropItem(item);
	}
}

void Player::PrintItemsList()
{
	cout << "You carry:" << endl;
	for (int i = 0; i < this->items.size(); i++)
		cout << i + 1 << ". " << this->items[i]->GetName() << endl;
}


//char Player::GetCommand()
//{
//	int c = 0;
//	while (!_kbhit())
//	{
//	}
//	c = _getch();
//	c = toupper(c);
//	system("cls");
//	return char(c);
//}

void Player::PrintPlayerStat()
{
	cout << "Player name:\t" << this->GetName() << endl;
	cout << "Level:\t" << this->GetLevel() << endl;
	cout << "Points:\t" << this->GetPoints() << "/" << pow((this->GetLevel()), 2)*NEXT_LEVEL << endl;
	cout << "Money:\t" << this->GetMoney() << endl;
	cout << "Energy:\t" << this->GetEnergy() << endl << endl;
}

Item* Player::ChooseItem(Place* activePlace)
{
	int choice = 0;

	if (this->items.size() > 0)
	{
		while ((choice <= 0 || choice > this->GetItems().size()) && choice != ESC)
		{
			cout << "Choose item:" << endl;
			for (int i = 0; i < this->items.size(); i++)
			{
				cout << i + 1 << ". " << this->items[i]->GetName() << endl;
			}
			cout << "Choice:";
			choice = Command::Get() - 48;
		}
		if (choice != ESC) return items[choice - 1];
		else return nullptr;
	}
	else
	{
		cout << "You don't carry any items!" << endl;
		return nullptr;
	}
	return nullptr;
}

void Player::Talk(Friend* frend)
{

	if (frend != nullptr)
	{
		if (frend->GetEnergyBoost() > 0)
		{
			cout << "Hi " << frend->GetName() << "! I am so happy to se you!" << endl;
			cout << "You got energy boost:\t" << frend->GetEnergyBoost() << endl;
			this->SetEnergy(frend->GetEnergyBoost());
		}

		if (frend->GetMoneyBoost() > 0)
		{
			cout << "Hi " << this->GetName() << "! Here is the money I borroved from you last week!" << endl;
			cout << "You got Money boost:\t" << frend->GetMoneyBoost() << endl;
			this->SetMoney(frend->GetMoneyBoost());
		}

		if (frend->GetItem() != nullptr)
		{
			cout << "Hi " << this->GetName() << "! I have little something for you!" << endl;
			cout << "You got\t" << frend->GetItem()->GetName() << endl;
			this->PutItem(frend->GetItem());
			frend->DropItem();
		}
	}
}

void Player::UseItem(Place* activePlace)
{
	Item* item;
	Enemy* enemy;
	int choice = 0;

	item = this->ChooseItem(activePlace);

	if (item != nullptr)
	{
		switch (item->GetType())
		{
		case ENERGY_REDUCE:
			enemy = activePlace->ChooseEnemy();
			if (enemy != nullptr)
				for (int i = 0; i < activePlace->GetEnemies().size(); i++)
					if (enemy->GetName() == activePlace->GetEnemies()[i]->GetName())
					{
						cout << "You hit " << enemy->GetName() << " with " << item->GetName() << endl;
						activePlace->GetEnemies()[i]->SetEnergy(-(((EnergyReduce*)item)->GetDamage()));
						if (activePlace->GetEnemies()[i]->GetEnergy() <= 0)
						{
							cout << "Thank's god, " <<enemy->GetName() << " run away from you!" << endl;
							activePlace->DropEnemy(enemy);
						}
						this->DropItem(item);
					}
			break;
		case DAMAGE_REDUCE:
			enemy = activePlace->ChooseEnemy();
			if (enemy != nullptr)
				for (int i = 0; i < activePlace->GetEnemies().size(); i++)
					if (enemy->GetName() == activePlace->GetEnemies()[i]->GetName())
					{
						cout << "This is a little gift for you!" << endl;
						cout << "The jerk is now little less annoying" << endl;
						activePlace->GetEnemies()[i]->SetDamage(-(((DamageReduce*)item)->GetReduceDamage()));
						if (activePlace->GetEnemies()[i]->GetDamage() <= 0)	activePlace->GetEnemies()[i]->SetDamage(-activePlace->GetEnemies()[i]->GetDamage());
						this->DropItem(item);
					}
			break;
		case MONEY_BOOST:
			this->SetMoney((((MoneyBoost*)item)->GetMoneyBoost()));
			this->DropItem(item);
			break;
		case ENERGY_BOOST:
			this->SetEnergy((((EnergyBoost*)item)->GetEnergyBoost()));
			this->DropItem(item);
			break;
		}
	}
}

int Player::Argue(Place* activePlace)
{
	Enemy* enemy;

	enemy = activePlace->ChooseEnemy();

	if (enemy != NULL)
	{
		while (this->GetEnergy() > 0 && enemy->GetEnergy() > 0)
		{
			this->SetEnergy(-enemy->GetDamage());
			enemy->SetEnergy(-((this->GetEnergy())/ARGUE_FACTOR));

			if (this->GetEnergy() <= 0)
			{
				cout << "You obviously can't win this argue! Better give up and have some beer!" << endl;
				this->SetEnergy(-this->GetEnergy());
				this -> SetEnergy(0);
			}
			else if (enemy->GetEnergy() <= 0)
			{
				cout << "Get out of my site!!! " << enemy->GetName() <<" left the " << activePlace->GetName() << "." << endl;
				activePlace->DropEnemy(enemy);
				return ARGUE_POINTS;
			}
		}
	}
	return 0;
}

void Player::MeetEnemy(Place* activePlace)
{
	vector<Enemy*> enemies;
	enemies = activePlace->GetEnemies();
	for (int i = 0; i < enemies.size(); i++)
	{
		this->SetEnergy(-(enemies[i]->GetDamage()));

		if (this->GetEnergy() <= 0)
		{
			cout << "You are exhausted! Better go away and have some beer!" << endl;
			this->SetEnergy(-this->GetEnergy());
			this->SetEnergy(0);
		}
	}
}
