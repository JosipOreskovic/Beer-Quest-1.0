#pragma once

#include "stdafx.h"
#include "bqgame.h"


void Game::PutPlace(Place* place) { places.push_back(place); }
void Game::PutItem(Item* item) { items.push_back(item); }
void Game::PutCharacter(Character* character) { characters.push_back(character); }
Place* Game::GetActivePlace() { return activePlace; }

void Game::Play()
{
	GameBackup();
	MainMenu();
	while (gameType != 'E')
	{
		gameOver = false;
		switch (gameType)
		{
		case 'N':
			cout << "Player name: ";
			getline(cin, playerName);
			NewGame(playerName);
			system("cls");
			break;
		case 'R': ResumeGame();  break;
		case 'E': gameType = 'E'; break;
		default: gameType = ' '; break;
		}

		while (!gameOver)
		{
			Action();
			SaveGame();
		}
		cout << "GAME OVER!" << endl;
		SaveGame();
		GameOver();
		MainMenu();
	}
}

void Game::MainMenu()
{
	gameType = ' ';
	while (gameType != 'N' && gameType != 'R' && gameType != 'E')
	{
		cout << "N - New game" << endl;
		cout << "R - Resume game" << endl;
		cout << "E - Exit" << endl;
		cout << "Choose: ";
		gameType = Command::Get();
	}
}

void Game::NewGame(string playerName)
{
	player->SetName(playerName);
	player->SetEnergy(100);
	player->SetMoney(100);
	player->SetLevel(1);
	player->SetPoints(0);
	activePlace = Home;

	Staple->SetDamage(20);
	Mobile->SetDamage(10);
	Stool->SetDamage(5);
	Staple->SetPrice(20);
	Mobile->SetPrice(10);
	Stool->SetDamage(5);

	Flowers->SetReduceDamage(5);
	Chocolate->SetReduceDamage(10);
	Beer->SetEnergyBoost(10);
	Bonus->SetMoneyBoost(10);
	Salary->SetMoneyBoost(30);
	Pizza->SetEnergyBoost(20);
	Flowers->SetPrice(5);
	Chocolate->SetPrice(5);
	Beer->SetPrice(5);
	Pizza->SetPrice(10);

	MotherInLaw->SetEnergy(15);
	Boss->SetEnergy(30);
	Wife->SetEnergy(30);
	Drunk->SetEnergy(15);
	MotherInLaw->SetDamage(15);
	Boss->SetDamage(10);
	Wife->SetDamage(15);
	Drunk->SetDamage(5);

	Ana->SetEnergyBoost(20);
	Ambrozije->PutItem(Beer);
	Luka->PutItem(Beer);
	Bojan->PutItem(Pizza);

	Home->PutPlace(Street);
	Home->PutItem(Salary);
	Home->PutItem(Mobile);
	
	Street->PutPlace(Home);
	Street->PutPlace(Pizzeria);
	Street->PutPlace(Square);
	Street->PutEnemy(Wife);

	Pizzeria->PutPlace(Street);
	Pizzeria->PutItem(Pizza);
	Pizzeria->PutFriend(Bojan);

	Square->PutPlace(Street);
	Square->PutPlace(Office);
	Square->PutPlace(Konzum);
	Square->PutPlace(Bar);
	Square->PutPlace(Suburb);
	Square->PutEnemy(Drunk);
	Square->PutFriend(Ana);

	Konzum->PutPlace(Square);
	Konzum->PutItem(Beer);
	Konzum->PutItem(Chocolate);
	Konzum->PutItem(Flowers);

	Office->PutPlace(Square);
	Office->PutItem(Staple);
	Office->PutItem(Bonus);
	Office->PutEnemy(Boss);

	Bar->PutPlace(Square);
	Bar->PutItem(Beer);
	Bar->PutFriend(Ambrozije);
	Bar->PutFriend(Luka);
	Bar->PutEnemy(Drunk);

	Suburb->PutPlace(Square);
	Suburb->PutPlace(House);
	Suburb->PutPlace(Pown);

	Pown->PutPlace(Suburb);

	House->PutEnemy(MotherInLaw);
	House->PutPlace(Suburb);
}

void Game::Action()
{
	int choice;
	Item* myitem;
	cout << "You are in the " << activePlace->GetName() << endl;

	if (activePlace->GetItems().size() > 0)
	{
		if (activePlace->GetType() == ACTION_PLACE) cout << "Items you can pick up:" << endl;
		else cout << "Items you can buy:" << endl;
		activePlace->PrintList(ITEM);
	}
	if (activePlace->GetFriends().size() > 0)
	{
		cout << "You see some frienly faces." << endl;
		activePlace->PrintList(FRIEND);
	}
	if (activePlace->GetEnemies().size() > 0)
	{
		cout << "There are some annoying people around! Be cearfull, they suck your energy every time you run into them!" << endl;
		activePlace->PrintList(ENEMY);
	}
	cout << "You can go to:" << endl;
	activePlace->PrintList(PLACE);
	cout << endl << endl;
	player->PrintPlayerStat();
	cout << "Command:";
	choice = 0;
	while (choice <= 0 || choice >= 256)
	{
		choice = Command::Get();
//		this->AddEnergy(Command::GetElapsedtime());
	}

	switch (choice)
	{
	case 'A':
		AddPoints(player->Argue(activePlace));
		break;
	case 'G':
		GoPlace();
		player->MeetEnemy(activePlace);
		break;
	case 'B':
		Item* itemToBuy;
		if (activePlace->GetType() == BUY_STORE || activePlace->GetType() == BUY_SELL_STORE)
		{
			itemToBuy = activePlace->ChooseItem();
			if (itemToBuy != nullptr)
				player->BuyItem(itemToBuy);
		}
		else cout << "You can't buy items here." << endl;
		break;
	case 'S':
		Item* itemToSell;
		if (activePlace->GetType() == BUY_SELL_STORE || activePlace->GetType() == SELL_STORE)
		{
			itemToSell = player->ChooseItem(activePlace);
			if (itemToSell != nullptr)
				player->SellItem(itemToSell, itemToSell->GetPrice());
		}
		else cout << "You can't sell items here." << endl;
		break;
	case 'P':
		if (activePlace->GetType() == ACTION_PLACE)
			if (activePlace->GetItems().size() > 0)
			{
				player->PickUpItem(activePlace);
				AddPoints(ITEM_POINTS);
			}
			else cout << "There are no items here to pick up." << endl;
		else cout << "You can't pick up items here." << endl;
		break;
	case 'U':
		player->UseItem(activePlace);
		break;
	case 'T':
		if (activePlace->GetFriends().size() > 0)
		{
			Friend* frend = activePlace->ChooseFriend();
			if (frend != nullptr)
			{
				player->Talk(frend);
				activePlace->DropFriend(frend);
				AddPoints(FRIEND_POINTS);
			}
		}
		else cout << "There are nobody here to talk to." << endl;
		break;
	case 'I':
		player->PrintItemsList();
		break;
	case 'H':
		Instructions();
		break;
	case 'Q':
		gameOver = true;
		break;

	default:
		cout << "Don't recognize that command!" << endl; break;
	}
}


void Game::AddPoints(int points)
{
	player->SetPoints(points);
	if (player->GetPoints() > (pow((player->GetLevel()), 2)*NEXT_LEVEL))
		player->SetLevel(1);
}

void Game::AddEnergy(int elapsedTime)
{
	if (elapsedTime >= TIME_ENERGY)
		player->SetEnergy(INC_ENERGY*(elapsedTime/TIME_ENERGY));
	if (player->GetEnergy() >= MAX_ENERGY)
		{
			player->SetEnergy(-player->GetEnergy());
			player->SetEnergy(100);
		}
}

void Game::GoPlace()
{
	int choice = 0;
	while ((choice <= 0 || choice > activePlace->GetPlaces().size()) && choice != ESC)
	{
		for (int i = 0; i < activePlace->GetPlaces().size(); i++)
		{
			cout << i + 1 << ". " << activePlace->GetPlaces()[i]->GetName() << endl;
		}
		cout << "Where do you want to go? ";
		choice = Command::Get() - 48;
	}
	if (choice != ESC)
	{
		for (int i = 0; i < activePlace->GetPlaces().size(); i++)
		{
			if ((choice - 1) == i)
			{
				cout << "You went to " << activePlace->GetPlaces()[i]->GetName() << endl;
				activePlace = activePlace->GetPlaces()[i];
			}
		}
	}
}

void Game::SaveGame()
{
	fstream gameSave;
	gameSave.open("saved_game.txt", ios::out | ios::trunc);

	gameSave << (player->GetName()).c_str() << endl;
	gameSave << player->GetEnergy() << endl;
	gameSave << player->GetMoney() << endl;
	gameSave << player->GetLevel() << endl;
	gameSave << player->GetPoints() << endl;

	if (player->GetItems().size() != 0)
	{
		gameSave << player->GetItems().size() << endl;
		for (int i = 0; i < player->GetItems().size(); i++)
			gameSave << (player->GetItems()[i]->GetName()).c_str() << endl;
	}
	else gameSave << "None" << endl;

	for (int i = 0; i < places.size(); i++)
	{
		if (places[i]->GetItems().size() != 0)
		{
			gameSave << places[i]->GetItems().size() << endl;
			for (int j = 0; j < places[i]->GetItems().size(); j++)
			{
				gameSave << (places[i]->GetItems()[j]->GetName()).c_str() << endl;
			}
		}
		else gameSave << "None" << endl;

		if (places[i]->GetEnemies().size() != 0)
		{
			gameSave << places[i]->GetEnemies().size() << endl;
			for (int j = 0; j < places[i]->GetEnemies().size(); j++)
			{
				gameSave << (places[i]->GetEnemies()[j]->GetName()).c_str() << endl;
				gameSave << (places[i]->GetEnemies()[j]->GetEnergy()) << endl;
				gameSave << (places[i]->GetEnemies()[j]->GetDamage()) << endl;
			}
		}
		else gameSave << "None" << endl;

		if (places[i]->GetFriends().size() != 0)
		{
			gameSave << places[i]->GetFriends().size() << endl;
			for (int j = 0; j < places[i]->GetFriends().size(); j++)
				gameSave << (places[i]->GetFriends()[j]->GetName()).c_str() << endl;
		}
		else gameSave << "None" << endl;

		if (places[i]->GetPlaces().size() != 0)
		{
			gameSave << places[i]->GetPlaces().size() << endl;
			for (int j = 0; j < places[i]->GetPlaces().size(); j++)
				gameSave << (places[i]->GetPlaces()[j]->GetName()).c_str() << endl;
		}
		else gameSave << "None" << endl;
	}
	gameSave << (activePlace->GetName()).c_str() << endl;
	gameSave.close();
}

void Game::ResumeGame()
{
	string line;
	fstream gameSave;
	int numberOfObjects, number;

	gameSave.open("saved_game.txt", ios::in);

	getline(gameSave, line);
	player->SetName(line);
	getline(gameSave, line);
	player->SetEnergy(atoi(line.c_str()));
	getline(gameSave, line);
	player->SetMoney(atoi(line.c_str()));
	getline(gameSave, line);
	player->SetLevel(atoi(line.c_str()));
	getline(gameSave, line);
	player->SetPoints(atoi(line.c_str()));
	getline(gameSave, line);

	if (line != "None")
	{
		numberOfObjects = atoi(line.c_str());
		for (int i = 0; i < numberOfObjects; i++)
		{
			getline(gameSave, line);
			for (int j = 0; j < items.size(); j++)
			{
				if (line == items[j]->GetName())
					player->PutItem(items[j]);
			}
		}
	}

	for (int i = 0; i < places.size(); i++)
	{
		getline(gameSave, line);
		if (line != "None")
		{
			numberOfObjects = atoi(line.c_str());
			for (int j = 0; j < numberOfObjects; j++)
			{
				getline(gameSave, line);
				for (int k = 0; k < items.size(); k++)
					if (line == items[k]->GetName())
						places[i]->PutItem(items[k]);
			}
		}

		getline(gameSave, line);
		if (line != "None")
		{
			numberOfObjects = atoi(line.c_str());
			for (int j = 0; j < numberOfObjects; j++)
			{
				getline(gameSave, line);
				for (int k = 0; k < characters.size(); k++)
					if (line == characters[k]->GetName())
					{
						places[i]->PutEnemy((Enemy*)characters[k]);
						getline(gameSave, line);
						number = atoi(line.c_str());
						((Enemy*)characters[k])->SetEnergy(number);
						getline(gameSave, line);
						number = atoi(line.c_str());
						((Enemy*)characters[k])->SetDamage(number);
					}
			}
		}

		getline(gameSave, line);
		if (line != "None")
		{
			numberOfObjects = atoi(line.c_str());
			for (int j = 0; j < numberOfObjects; j++)
			{
				getline(gameSave, line);
				for (int k = 0; k < characters.size(); k++)
					if (line == characters[k]->GetName())
						places[i]->PutFriend((Friend*)characters[k]);
			}
		}

		getline(gameSave, line);
		if (line != "None")
		{
			numberOfObjects = atoi(line.c_str());
			for (int j = 0; j < numberOfObjects; j++)
			{
				getline(gameSave, line);
				for (int k = 0; k < places.size(); k++)
					if (line == places[k]->GetName())
						places[i]->PutPlace(places[k]);
			}
		}
	}

	getline(gameSave, line);
	for (int j = 0; j < places.size(); j++)
		if (line == places[j]->GetName())
			activePlace = places[j];
}


void Game::Instructions()
{
	cout << "A - Argue" << endl;
	cout << "G - Go" << endl;
	cout << "B - Buy" << endl;
	cout << "S - Sell" << endl;
	cout << "P - Pick up item" << endl;
	cout << "U - Use item" << endl;
	cout << "T - Talk" << endl;
	cout << "I - List items" << endl;
	cout << "H - Instructions" << endl;
	cout << "Q - Quit game" << endl;
	cout << endl;
}

void Game::GameBackup()
{
	PutPlace(Home);
	PutPlace(Street);
	PutPlace(Konzum);
	PutPlace(Office);
	PutPlace(Bar);
	PutPlace(Square);
	PutPlace(House);
	PutPlace(Suburb);
	PutPlace(Pown);

	PutItem((EnergyReduce*)Staple);
	PutItem((EnergyReduce*)Mobile);
	PutItem((EnergyReduce*)Stool);
	PutItem((DamageReduce*)Flowers);
	PutItem((DamageReduce*)Chocolate);
	PutItem((EnergyBoost*)Beer);
	PutItem((MoneyBoost*)Bonus);
	PutItem((MoneyBoost*)Salary);

	PutCharacter((Enemy*)MotherInLaw);
	PutCharacter((Enemy*)Boss);
	PutCharacter((Enemy*)Wife);
	PutCharacter((Enemy*)Drunk);
	PutCharacter((Friend*)Ambrozije);
	PutCharacter((Friend*)Luka);
	PutCharacter((Friend*)Ana);

	Staple->SetDamage(20);
	Mobile->SetDamage(10);
	Stool->SetDamage(5);
	Flowers->SetReduceDamage(5);
	Chocolate->SetReduceDamage(10);
	Beer->SetEnergyBoost(10);
	Bonus->SetMoneyBoost(10);
	Salary->SetMoneyBoost(30);
	Staple->SetPrice(20);
	Mobile->SetPrice(10);
	Stool->SetPrice(5);
	Flowers->SetPrice(5);
	Chocolate->SetPrice(5);
	Beer->SetPrice(5);
}


void Game::GameOver()
{
	int size;

	player->SetEnergy(-player->GetEnergy());
	player->SetMoney(-player->GetMoney());
	player->SetLevel(-player->GetLevel());
	player->SetPoints(-player->GetPoints());

	size = player->GetItems().size();
	for (int j = 0; j<size; j++) player->DropItem(player->GetItems()[0]);

	for (int i = 0; i < characters.size(); i++)
	{
		if (characters[i]->GetType() == ENEMY)
		{
			((Enemy*)characters[i])->SetEnergy(-((Enemy*)characters[i])->GetEnergy());
			((Enemy*)characters[i])->SetDamage(-((Enemy*)characters[i])->GetDamage());
		}
	}

	for (int i = 0; i < places.size(); i++)
	{
		size = places[i]->GetItems().size();
		for (int j = 0; j<size; j++) places[i]->DropItem(places[i]->GetItems()[0]);
		size = places[i]->GetFriends().size();
		for (int j = 0; j<size; j++) places[i]->DropFriend(places[i]->GetFriends()[0]);
		size = places[i]->GetEnemies().size();
		for (int j = 0; j<size; j++) places[i]->DropEnemy(places[i]->GetEnemies()[0]);
		size = places[i]->GetPlaces().size();
		for (int j = 0; j<size; j++) places[i]->DropPlace(places[i]->GetPlaces()[0]);

	}
	activePlace = nullptr;
	gameOver = false;
}

