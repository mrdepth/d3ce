//
//  Monk.h
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Monk__
#define __d3ce__Monk__

#include "Hero.h"

namespace d3ce {
	
	class Party;
	
	class Monk: public Hero {
	public:
		Monk(std::shared_ptr<Engine> engine, Party* party);
		virtual Entity* cloneIn(Entity* parent);
		virtual ClassMask getClass() const;
		virtual std::string getClassName() const;

	protected:
		Monk(const Monk& other, Party* party);
	};
}


#endif /* defined(__d3ce__Monk__) */
