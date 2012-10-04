//
//  ModifierPostReduce.h
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__ModifierPostReduce__
#define __d3ce__ModifierPostReduce__

#include "Modifier.h"

namespace d3ce {
	
	class ModifierPostReduce: public Modifier {
	public:
		ModifierPostReduce(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression);
		ModifierPostReduce(Entity* entity, AttributeID attributeID, Expression* expression);

		virtual Range apply(const Range& value);
		virtual int priority();
	};
}

#endif /* defined(__d3ce__ModifierPostReduce__) */
