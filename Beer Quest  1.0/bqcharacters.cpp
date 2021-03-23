#pragma once

#include "stdafx.h"
#include "bqgame.h"


string Character::GetName() const { return name; }
int Character::GetType() const { return type; }
void Character::SetName(string name) { this->name = name; }

int Enemy::GetEnergy() const { return energy; }
int Enemy::GetDamage() const { return damage; }
void Enemy::SetDamage(int damage) { this->damage += damage; }
void Enemy::SetEnergy(int energy) { this->energy += energy; }


int Friend::GetEnergyBoost() const { return incEnergy; }
int Friend::GetMoneyBoost() const { return incMoney; }
Item* Friend::GetItem() const { return item; }
void Friend::SetEnergyBoost(int energy) { this->incEnergy = energy; }
void Friend::SetMoneyBoost(int money) { this->incMoney = money; }
void Friend::PutItem(Item* item) { this->item = item; }
void Friend::DropItem() { this->item = nullptr; }

