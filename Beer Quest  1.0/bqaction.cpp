#pragma once

#include "stdafx.h"
#include "bqaction.h"

string Action::GetName() { return name; }
int Action::GetType() { return type; }
int Action::GetDamage() { return NULL; }
int Action::GetReduceDamage() { return NULL; }
int Action::GetIncEnergy() { return NULL; }
int Action::GetIncMoney() { return NULL; }
Item* Action::GetPlayerItem(){ return nullptr; }
void Action::SetDamage(int damage) {}
void Action::SetReduceDamage(int reduceDamage) {}
void Action::SetIncEnergy(int incEnergy) {}
void Action::SetIncMoney(int incMoney) {}
void Action::SetPlayerItem(Item* item){}

Item* GetItemAction::GetItem() { return item; }
void GetItemAction::SetItem(Item* item) { this->item = item; }

int GetEnergyBoost::GetIncEnergy() { return incEnergy; }
void GetEnergyBoost::SetIncEnergy(int energy) { this->incEnergy = energy; }

int GetMoneyBoost::GetIncMoney() { return incMoney; }
void GetMoneyBoost::SetIncMoney(int money) { this->incMoney = money; }

int MakeDamage::GetDamage() { return damage; }
void MakeDamage::SetDamage(int) { this->damage = damage; }