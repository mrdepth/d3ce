//
//  Gear.h
//  d3ce
//
//  Created by Artem Shimanski on 28.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Gear__
#define __d3ce__Gear__

#include "Item.h"
#include "Gem.h"

namespace d3ce {
	
	class Gear: public Item {
	public:
		Gear(Engine* engine, Entity* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, Hash itemSetBonusHash, int flags, int bitMask, const std::vector<Slot>& possibleSlots);
		virtual ~Gear();
		Gear(const Gear& other, Entity* parent);
		Gem* addGem(Hash itemHash);
		Gem* addGem(const std::string& nonNlsKey);
		void removeGem(Gem* gem);
		const std::vector<Gem*>& getGems();
		virtual bool twoHanded();
		Hash itemSetBonusHash();
	private:
		std::vector<Gem*> gems_;
		Hash itemSetBonusHash_;
	};
}


#endif /* defined(__d3ce__Gear__) */
