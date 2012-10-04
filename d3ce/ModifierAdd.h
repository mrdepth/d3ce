//
//  ModifierAdd.h
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__ModifierAdd__
#define __d3ce__ModifierAdd__

#include "Modifier.h"

namespace d3ce {
	
	class ModifierAdd: public Modifier {
	public:
		ModifierAdd(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression);
		ModifierAdd(Entity* entity, AttributeID attributeID, Expression* expression);
		
		virtual Range apply(const Range& value);
		virtual int priority();
	};
}

#endif /* defined(__d3ce__ModifierAdd__) */
