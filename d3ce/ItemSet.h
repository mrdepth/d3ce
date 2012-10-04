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
		ItemSet(Engine* engine, Entity* parent, Hash setBonusHash);
		virtual ~ItemSet();
		virtual Entity* cloneIn(Entity* parent);
		void addItem(Gear* item);
		void removeItem(Gear* item);
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
		std::vector<Gear*> items_;
		
		void update();
	};
	
}

#endif /* defined(__d3ce__ItemSet__) */
