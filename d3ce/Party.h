//
//  Party.h
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Party__
#define __d3ce__Party__

#include "Entity.h"

namespace d3ce {

	class Party: public Entity {
	public:
		Party(Engine* engine);
		Party* clone();
		Hero* addHero(ClassMask classMask);
		void removeHero(Hero* hero);
		const std::vector<Hero*>& getHeroes();
	protected:
		virtual Environment environment();
		std::vector<Hero*> heroes_;

		Party(const Party& other);
	private:
		virtual Entity* cloneIn(Entity* parent);
	};
	
}

#endif /* defined(__d3ce__Party__) */
