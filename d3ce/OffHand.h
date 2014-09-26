//
//  OffHand.h
//  d3ce
//
//  Created by Artem Shimanski on 28.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__OffHand__
#define __d3ce__OffHand__

#include "Gear.h"

namespace d3ce {
	
	class OffHand: public Gear {
	public:
		OffHand(std::shared_ptr<Engine> engine, Entity* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, Hash itemSetBonusHash, int flags, int bitMask, const std::vector<Slot>& possibleSlots);
		virtual Entity* cloneIn(Entity* parent);
	protected:
		OffHand(const OffHand& other, Entity* parent);
	private:
	};
}

#endif /* defined(__d3ce__OffHand__) */
