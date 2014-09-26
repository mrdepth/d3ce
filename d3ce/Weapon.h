//
//  Weapon.h
//  d3ce
//
//  Created by Artem Shimanski on 28.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Weapon__
#define __d3ce__Weapon__

#include "Gear.h"

namespace d3ce {
	
	class Weapon: public Gear {
	public:
		Weapon(std::shared_ptr<Engine> engine, Entity* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, Hash itemSetBonusHash, int flags, int bitMask, const std::vector<Slot>& possibleSlots);
		virtual Entity* cloneIn(Entity* parent);
		bool twoHanded();
		virtual bool isWeapon() const {
			return true;
		}
	protected:
		Weapon(const Weapon& other, Entity* parent);
	private:
	};
}

#endif /* defined(__d3ce__Weapon__) */
