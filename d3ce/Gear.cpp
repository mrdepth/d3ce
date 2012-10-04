//
//  Gear.cpp
//  d3ce
//
//  Created by Artem Shimanski on 28.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Gear.h"
#include <algorithm>

using namespace d3ce;

Gear::Gear(Engine* engine, Entity* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, Hash itemSetBonusHash, int flags, int bitMask, const std::vector<Slot>& possibleSlots) : Item(engine, parent, itemHash, itemTypesTree, flags, bitMask, possibleSlots) {
	itemSetBonusHash_ = itemSetBonusHash;
}

Gear::Gear(const Gear& other, Entity* parent) : Item(other, parent) {
	copyAttributes(other);
	itemSetBonusHash_ = other.itemSetBonusHash_;
	std::vector<Gem*>::const_iterator i, end = other.gems_.end();
	for (i = other.gems_.begin(); i != end; i++)
		gems_.push_back(dynamic_cast<Gem*>((*i)->cloneIn(this)));

}

Gear::~Gear() {
	std::vector<Gem*>::iterator i, end = gems_.end();
	for (i = gems_.begin(); i != end; i++)
		delete *i;
}

bool Gear::twoHanded() {
	return false;
}

Gem* Gear::addGem(Hash itemHash) {
	Gem* gem = dynamic_cast<Gem*>(Item::CreateItem(engine_, this, itemHash));
	gems_.push_back(gem);
	return gem;
}

Gem* Gear::addGem(const std::string& nonNlsKey) {
	Gem* gem = dynamic_cast<Gem*>(Item::CreateItem(engine_, this, nonNlsKey));
	gems_.push_back(gem);
	return gem;
}


void Gear::removeGem(Gem* gem) {
	gems_.erase(std::remove(gems_.begin(), gems_.end(), gem));
	delete gem;
}

const std::vector<Gem*>& Gear::getGems() {
	return gems_;
}

Hash Gear::itemSetBonusHash() {
	return itemSetBonusHash_;
}
