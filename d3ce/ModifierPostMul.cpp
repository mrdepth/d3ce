//
//  ModifierPostMul.cpp
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "ModifierPostMul.h"
#include "Expression.h"

using namespace d3ce;

ModifierPostMul::ModifierPostMul(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression) : Modifier(entity, attributeID, attributeSubID, expression) {
	
}

ModifierPostMul::ModifierPostMul(Entity* entity, AttributeID attributeID, Expression* expression) : Modifier(entity, attributeID, expression) {
	
}

Range ModifierPostMul::apply(const Range& value) {
	return value * expression_->value();
}

int ModifierPostMul::priority() {
	return 3;
}
