//
//  ModifierSub.cpp
//  d3ce
//
//  Created by Artem Shimanski on 27.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "ModifierSub.h"
#include "Expression.h"

using namespace d3ce;

ModifierSub::ModifierSub(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression) : Modifier(entity, attributeID, attributeSubID, expression) {
	
}

ModifierSub::ModifierSub(Entity* entity, AttributeID attributeID, Expression* expression) : Modifier(entity, attributeID, expression) {
	
}

Range ModifierSub::apply(const Range& value){
	return value - expression_->value();
}

int ModifierSub::priority() {
	return 2;
}
