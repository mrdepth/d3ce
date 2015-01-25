//
//  WitchDoctor.h
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__WitchDoctor__
#define __d3ce__WitchDoctor__

#include "Hero.h"

namespace d3ce {
	
	class Party;
	
	class WitchDoctor: public Hero {
	public:
		WitchDoctor(std::shared_ptr<Engine> engine, Party* party);
		virtual Entity* cloneIn(Entity* parent);
		virtual ClassMask getClass() const;
		virtual std::string getClassName() const;

	protected:
		WitchDoctor(const WitchDoctor& other, Party* party);
	};
}

#endif /* defined(__d3ce__WitchDoctor__) */
