//
//  Armor.cpp
//  d3ce
//
//  Created by Artem Shimanski on 28.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Armor.h"

using namespace d3ce;

Armor::Armor(Engine* engine, Entity* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, Hash itemSetBonusHash, int flags, int bitMask, const std::vector<Slot>& possibleSlots) : Gear(engine, parent, itemHash, itemTypesTree, itemSetBonusHash, flags, bitMask, possibleSlots) {
	
}

Armor::Armor(const Armor& other, Entity* parent) : Gear(other, parent) {
}

Entity* Armor::cloneIn(Entity* parent) {
	return new Armor(*this, parent);
}