//
//  Attribute.h
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Attribute__
#define __d3ce__Attribute__

#include <vector>
#include "Range.h"
#include "AttributeIDs.h"

namespace d3ce {

	class Entity;
	class Attribute {
	public:
		Attribute(const Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, const Range& value);
		AttributeID getAttributeID() const {return attributeID_;};
		AttributeSubID getAttributeSubID() const {return attributeSubID_;};
		const Entity* getEntity() const { return entity_; };
		Range value() const { return value_;};
		operator Range() const {return value();};
	private:
		AttributeID attributeID_;
		AttributeSubID attributeSubID_;
		const Entity* entity_;
		Range value_;
	};
}

#endif /* defined(__d3ce__Attribute__) */
