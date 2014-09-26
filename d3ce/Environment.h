//
//  Environment.h
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Environment__
#define __d3ce__Environment__

namespace d3ce {
	class Entity;
	class Hero;
	class Party;
	
	class Environment {
	public:
		Environment() {};
		Environment(Entity* self, Entity* hero, Entity* party) : self(self), hero(hero), party(party) {};
		class Entity* self;
		class Entity* hero;
		class Entity* party;
	};
}

#endif /* defined(__d3ce__Environment__) */
