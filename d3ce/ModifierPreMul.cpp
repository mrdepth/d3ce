//
//  ModifierPreMul.cpp
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "ModifierPreMul.h"
#include "Expression.h"

using namespace d3ce;

ModifierPreMul::ModifierPreMul(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression) : Modifier(entity, attributeID, attributeSubID, expression) {
	
}

ModifierPreMul::ModifierPreMul(Entity* entity, AttributeID attributeID, Expression* expression) : Modifier(entity, attributeID, expression) {
	
}

Range ModifierPreMul::apply(const Range& value) {
	return value * expression_->value();
}

int ModifierPreMul::priority() {
	return 1;
}
