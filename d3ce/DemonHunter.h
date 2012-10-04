//
//  DemonHunter.h
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__DemonHunter__
#define __d3ce__DemonHunter__

#include "Hero.h"

namespace d3ce {
	
	class Party;
	
	class DemonHunter: public Hero {
	public:
		DemonHunter(Engine* engine, Party* party);
		virtual Entity* cloneIn(Entity* parent);
		virtual ClassMask getClass();
	protected:
		DemonHunter(const DemonHunter& other, Party* party);
	};
}

#endif /* defined(__d3ce__DemonHunter__) */
