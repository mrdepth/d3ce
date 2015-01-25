//
//  Weapon.cpp
//  d3ce
//
//  Created by Artem Shimanski on 28.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Weapon.h"

using namespace d3ce;

Weapon::Weapon(std::shared_ptr<Engine> engine, Entity* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, Hash itemSetBonusHash, int flags, int bitMask, Slot possibleSlots) : Gear(engine, parent, itemHash, itemTypesTree, itemSetBonusHash, flags, bitMask, possibleSlots) {
	if (bitMask & Weapon2HandedMask)
		setAttribute(AttributeWeapon2HID, AttributeNoneSubID, 1);
	else
		setAttribute(AttributeWeapon1HID, AttributeNoneSubID, 1);
}

Weapon::Weapon(const Weapon& other, Entity* parent) : Gear(other, parent) {
	if (bitMask_ & Weapon2HandedMask)
		setAttribute(AttributeWeapon2HID, AttributeNoneSubID, 1);
	else
		setAttribute(AttributeWeapon1HID, AttributeNoneSubID, 1);
}

Entity* Weapon::cloneIn(Entity* parent) {
	return new Weapon(*this, parent);
}

bool Weapon::twoHanded() const {
	return (bitMask_ & Weapon2HandedMask) != 0;
}
