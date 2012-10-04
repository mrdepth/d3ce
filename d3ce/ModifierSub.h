//
//  ModifierSub.h
//  d3ce
//
//  Created by Artem Shimanski on 27.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__ModifierSub__
#define __d3ce__ModifierSub__

#include "Modifier.h"

namespace d3ce {
	
	class ModifierSub: public Modifier {
	public:
		ModifierSub(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression);
		ModifierSub(Entity* entity, AttributeID attributeID, Expression* expression);
		
		virtual Range apply(const Range& value);
		virtual int priority();
	};
}

#endif /* defined(__d3ce__ModifierSub__) */
