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
		Party(std::shared_ptr<Engine> engine);
		std::shared_ptr<Hero> addHero(ClassMask classMask);
		void removeHero(std::shared_ptr<Hero> hero);
		const std::vector<std::shared_ptr<Hero>>& getHeroes();
	protected:
		virtual Environment environment();
		std::vector<std::shared_ptr<Hero>> heroes_;

		Party(const Party& other);
	private:
		virtual Entity* cloneIn(Entity* parent);
	};
	
}

#endif /* defined(__d3ce__Party__) */
