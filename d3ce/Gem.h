//
//  Gem.h
//  d3ce
//
//  Created by Artem Shimanski on 28.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Gem__
#define __d3ce__Gem__

#include "Item.h"

namespace d3ce {
	
	class Gem: public Item {
	public:
		Gem(Engine* engine, Item* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, int flags, int bitMask, const std::vector<Slot>& possibleSlots);
		virtual Entity* cloneIn(Entity* parent);
	protected:
		virtual Environment environment();
		Gem(const Gem& other, Entity* parent);
		
	private:
	};
}

#endif /* defined(__d3ce__Gem__) */
