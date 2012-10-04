//
//  Skill.h
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Skill__
#define __d3ce__Skill__

#include "Entity.h"

namespace d3ce {

	class Skill: public Entity {
	public:
		Skill(Engine* engine, Entity* parent, const std::string& skillName);
		Skill(const Skill& other, Entity* parent);
		virtual Entity* cloneIn(Entity* parent);
		const std::string& skillName();
	protected:
		virtual Environment environment();
	private:
		std::string skillname_;
	};

}
#endif /* defined(__d3ce__Skill__) */
