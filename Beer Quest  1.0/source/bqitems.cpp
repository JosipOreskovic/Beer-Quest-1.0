#pragma once

#include "stdafx.h"
#include "bqgame.h"


int Item::GetPrice() const { return price; }
int Item::GetType() const { return type; }
string Item::GetName() const { return name; }
void Item::SetPrice(int price) { this->price = price; }
int Item::GetDamage() { return NULL; }
int Item::GetMoneyBoost() { return NULL; }
int Item::GetEnergyBoost() { return NULL; }
int Item::GetReduceDamage() { return NULL; };
void Item::SetEnergyBoost(int incEnergy) {};
void Item::SetMoneyBoost(int incMoney) {};
void Item::SetDamage(int damage) {};
void Item::SetReduceDamage(int reduceDamage) {}



int EnergyReduce::GetDamage() const { return damage; }
void EnergyReduce::SetDamage(int damage) { this->damage = damage; }

int DamageReduce::GetReduceDamage() const { return reduceDamage; }
void DamageReduce::SetReduceDamage(int reduceDamage) { this->reduceDamage = reduceDamage; }

int EnergyBoost::GetEnergyBoost() const { return incEnergy; }
void EnergyBoost::SetEnergyBoost(int incEnergy) { this->incEnergy = incEnergy; }

int MoneyBoost::GetMoneyBoost() const { return incMoney; }
void MoneyBoost::SetMoneyBoost(int incMoney) { this->incMoney = incMoney; }
