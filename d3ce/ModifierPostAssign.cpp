//
//  ModifierPostAssign.cpp
//  d3ce
//
//  Created by Artem Shimanski on 04.10.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "ModifierPostAssign.h"
#include "Expression.h"

using namespace d3ce;

ModifierPostAssign::ModifierPostAssign(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression) : Modifier(entity, attributeID, attributeSubID, expression) {
	
}

ModifierPostAssign::ModifierPostAssign(Entity* entity, AttributeID attributeID, Expression* expression) : Modifier(entity, attributeID, expression) {
	
}

Range ModifierPostAssign::apply(const Range& value) {
	return expression_->value();
}

int ModifierPostAssign::priority() {
	return 4;
}
