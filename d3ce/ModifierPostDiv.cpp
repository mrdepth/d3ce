//
//  ModifierPostDiv.cpp
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "ModifierPostDiv.h"
#include "Expression.h"

using namespace d3ce;

ModifierPostDiv::ModifierPostDiv(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression) : Modifier(entity, attributeID, attributeSubID, expression) {
	
}

ModifierPostDiv::ModifierPostDiv(Entity* entity, AttributeID attributeID, Expression* expression) : Modifier(entity, attributeID, expression) {
	
}

Range ModifierPostDiv::apply(const Range& value) {
	return value / expression_->value();
}

int ModifierPostDiv::priority() {
	return 3;
}
