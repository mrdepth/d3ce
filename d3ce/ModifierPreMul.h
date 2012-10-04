//
//  ModifierPreMul.h
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__ModifierPreMul__
#define __d3ce__ModifierPreMul__

#include "Modifier.h"

namespace d3ce {
	
	class ModifierPreMul: public Modifier {
	public:
		ModifierPreMul(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression);
		ModifierPreMul(Entity* entity, AttributeID attributeID, Expression* expression);

		virtual Range apply(const Range& value);
		virtual int priority();
	};
}

#endif /* defined(__d3ce__ModifierPreMul__) */
