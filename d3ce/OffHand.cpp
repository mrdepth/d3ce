//
//  OffHand.cpp
//  d3ce
//
//  Created by Artem Shimanski on 28.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "OffHand.h"

using namespace d3ce;

OffHand::OffHand(std::shared_ptr<Engine> engine, Entity* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, Hash itemSetBonusHash, int flags, int bitMask, Slot possibleSlots) : Gear(engine, parent, itemHash, itemTypesTree, itemSetBonusHash, flags, bitMask, possibleSlots) {
	
}

OffHand::OffHand(const OffHand& other, Entity* parent) : Gear(other, parent) {
}

Entity* OffHand::cloneIn(Entity* parent) {
	return new OffHand(*this, parent);
}