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
		Gear(std::shared_ptr<Engine> engine, Entity* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, Hash itemSetBonusHash, int flags, int bitMask, Slot possibleSlots);
		virtual ~Gear();
		Gear(const Gear& other, Entity* parent);
		std::shared_ptr<Gem> addGem(Hash itemHash);
		std::shared_ptr<Gem> addGem(const std::string& nonNlsKey);
		void removeGem(std::shared_ptr<Gem> gem);
		const std::vector<std::shared_ptr<Gem>>& getGems() const;
		virtual bool twoHanded() const;
		Hash itemSetBonusHash() const;
		float perfection() const;
		virtual bool isWeapon() const;

		virtual Attribute getAttribute(AttributeID attributeID, AttributeSubID attributeSubID = AttributeNoneSubID) const;
	private:
		std::vector<std::shared_ptr<Gem>> gems_;
		Hash itemSetBonusHash_;
	};
}


#endif /* defined(__d3ce__Gear__) */
