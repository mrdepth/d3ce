//
//  ModifierPreAssign.cpp
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "ModifierPreAssign.h"
#include "Expression.h"

using namespace d3ce;

ModifierPreAssign::ModifierPreAssign(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression) : Modifier(entity, attributeID, attributeSubID, expression) {

}

ModifierPreAssign::ModifierPreAssign(Entity* entity, AttributeID attributeID, Expression* expression) : Modifier(entity, attributeID, expression) {
	
}

Range ModifierPreAssign::apply(const Range& value) {
	return expression_->value();
}

int ModifierPreAssign::priority() {
	return 0;
}
