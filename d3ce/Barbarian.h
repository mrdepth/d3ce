//
//  Barbarian.h
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Barbarian__
#define __d3ce__Barbarian__

#include "Hero.h"

namespace d3ce {
	
	class Party;
	
	class Barbarian: public Hero {
	public:
		Barbarian(std::shared_ptr<Engine> engine, Party* party);
		virtual Entity* cloneIn(Entity* parent);
		virtual ClassMask getClass() const;
	protected:
		Barbarian(const Barbarian& other, Party* party);
	};
}

#endif /* defined(__d3ce__Barbarian__) */
