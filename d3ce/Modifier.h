//
//  Modifier.h
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Modifier__
#define __d3ce__Modifier__

#include "Range.h"
#include "AttributeIDs.h"

namespace d3ce {
	class Entity;
	class Attribute;
	class Expression;
	
	class Modifier {
	public:
		Modifier(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression);
		Modifier(Entity* entity, AttributeID attributeID, Expression* expression);
		virtual ~Modifier();
		AttributeID attributeID_;
		AttributeSubID attributeSubID_;
		Expression* expression_;
		Entity* entity_;
		
		virtual Range apply(const Range& value) = 0;
		virtual int priority() = 0;
	};
}

#endif /* defined(__d3ce__Modifier__) */
