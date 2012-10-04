//
//  ModifierPostAssign.h
//  d3ce
//
//  Created by Artem Shimanski on 04.10.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__ModifierPostAssign__
#define __d3ce__ModifierPostAssign__

#include "Modifier.h"

namespace d3ce {
	
	class ModifierPostAssign: public Modifier {
	public:
		ModifierPostAssign(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression);
		ModifierPostAssign(Entity* entity, AttributeID attributeID, Expression* expression);
		
		virtual Range apply(const Range& value);
		virtual int priority();
	};
}

#endif /* defined(__d3ce__ModifierPostAssign__) */
