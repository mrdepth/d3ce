//
//  Armor.h
//  d3ce
//
//  Created by Artem Shimanski on 28.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Armor__
#define __d3ce__Armor__

#include "Gear.h"

namespace d3ce {
	
	class Armor: public Gear {
	public:
		Armor(std::shared_ptr<Engine> engine, Entity* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, Hash itemSetBonusHash, int flags, int bitMask, const std::vector<Slot>& possibleSlots);
		virtual Entity* cloneIn(Entity* parent);
	protected:
		Armor(const Armor& other, Entity* parent);
	private:
	};
}

#endif /* defined(__d3ce__Armor__) */
