//
//  SetBonus.h
//  d3ce
//
//  Created by mr_depth on 30.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__SetBonus__
#define __d3ce__SetBonus__

#include "Entity.h"

namespace d3ce {
	
	class SetBonus: public Entity {
	public:
		SetBonus(Engine* engine, Entity* parent, Hash setBonusHash, Hash parentHash, int numOfSet);
		virtual Entity* cloneIn(Entity* parent);
		int numOfSet();
		Hash setBonusHash();
	protected:
		SetBonus(const SetBonus& other, Entity* parent);
		virtual Environment environment();
	private:
		Hash setBonusHash_;
		Hash parentHash_;
		int numOfSet_;
	};
	
}

#endif /* defined(__d3ce__SetBonus__) */
