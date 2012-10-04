//
//  ModifierPostBoost.cpp
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "ModifierPostBoost.h"
#include "Expression.h"

using namespace d3ce;

ModifierPostBoost::ModifierPostBoost(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression) : Modifier(entity, attributeID, attributeSubID, expression) {
	
}

ModifierPostBoost::ModifierPostBoost(Entity* entity, AttributeID attributeID, Expression* expression) : Modifier(entity, attributeID, expression) {
	
}

Range ModifierPostBoost::apply(const Range& value) {
	return value * (expression_->value() + Range(1));
}

int ModifierPostBoost::priority() {
	return 3;
}
