//
//  Weapon.cpp
//  d3ce
//
//  Created by Artem Shimanski on 28.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Weapon.h"

using namespace d3ce;

Weapon::Weapon(Engine* engine, Entity* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, Hash itemSetBonusHash, int flags, int bitMask, const std::vector<Slot>& possibleSlots) : Gear(engine, parent, itemHash, itemTypesTree, itemSetBonusHash, flags, bitMask, possibleSlots) {
	if (bitMask & Weapon2HandedMask)
		this->getAttribute(AttributeWeapon2HID)->setValue(1);
	else
		this->getAttribute(AttributeWeapon1HID)->setValue(1);
}

Weapon::Weapon(const Weapon& other, Entity* parent) : Gear(other, parent) {
	if (bitMask_ & Weapon2HandedMask)
		this->getAttribute(AttributeWeapon2HID)->setValue(1);
	else
		this->getAttribute(AttributeWeapon1HID)->setValue(1);
}

Entity* Weapon::cloneIn(Entity* parent) {
	return new Weapon(*this, parent);
}

bool Weapon::twoHanded() {
	return (bitMask_ & Weapon2HandedMask) != 0;
}
