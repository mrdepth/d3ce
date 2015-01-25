//
//  Crusader.h
//  d3ce
//
//  Created by Artem Shimanski on 05.01.15.
//  Copyright (c) 2015 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Crusader__
#define __d3ce__Crusader__

#include "Hero.h"

namespace d3ce {
	
	class Party;
	
	class Crusader: public Hero {
	public:
		Crusader(std::shared_ptr<Engine> engine, Party* party);
		virtual Entity* cloneIn(Entity* parent);
		virtual ClassMask getClass() const;
		virtual std::string getClassName() const;
		
	protected:
		Crusader(const Crusader& other, Party* party);
	};
}

#endif /* defined(__d3ce__Crusader__) */
