//
//  ItemSet.h
//  d3ce
//
//  Created by mr_depth on 30.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__ItemSet__
#define __d3ce__ItemSet__

#include "Entity.h"
#include "SetBonus.h"

namespace d3ce {
	class Gear;
	
	class ItemSet: public Entity {
	public:
		ItemSet(std::shared_ptr<Engine> engine, Entity* parent, Hash setBonusHash);
		virtual ~ItemSet();
		virtual Entity* cloneIn(Entity* parent);
		void addItem(std::shared_ptr<Gear> item);
		void removeItem(std::shared_ptr<Gear> item);
		virtual Attribute getAttribute(AttributeID attributeID, AttributeSubID attributeSubID = AttributeNoneSubID) const;
		Hash getSetBonusHashe() const;
	protected:
		ItemSet(const ItemSet& other, Entity* parent);
		virtual Environment environment();
	private:
		struct Bonus {
			Hash setBonusHash;
			int numOfSet;
		};
		
		Hash setBonusHash_;
		std::vector<SetBonus*> setBonuses_;
		std::vector<Bonus> bonuses_;
		std::vector<std::shared_ptr<Gear>> items_;
		
		void update();
	};
	
}

#endif /* defined(__d3ce__ItemSet__) */
