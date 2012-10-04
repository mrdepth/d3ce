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
#include "Environment.h"

namespace d3ce {

	class Modifier;
	class Entity;
	class Attribute {
	public:
		Attribute(AttributeID attributeID, AttributeSubID attributeSubID, const Environment& environment, const Range& value);
		~Attribute();
		Range value();
		Range getInitialValue();
		void setValue(const Range& value);
		
		AttributeID getAttributeID() {return attributeID_;};
		AttributeSubID getAttributeSubID() {return attributeSubID_;};

		void applyModifiers();
		void removeModifiers();

	private:
		AttributeID attributeID_;
		AttributeSubID attributeSubID_;
		Range initialValue_;
		Environment environment_;
		
		std::vector<Modifier*> modifiers_;
	};
}

#endif /* defined(__d3ce__Attribute__) */
