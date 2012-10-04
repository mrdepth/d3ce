//
//  ModifierAdd.cpp
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "ModifierAdd.h"
#include "Expression.h"

using namespace d3ce;

ModifierAdd::ModifierAdd(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression) : Modifier(entity, attributeID, attributeSubID, expression) {
	
}

ModifierAdd::ModifierAdd(Entity* entity, AttributeID attributeID, Expression* expression) : Modifier(entity, attributeID, expression) {
	
}

Range ModifierAdd::apply(const Range& value){
	return value + expression_->value();
}

int ModifierAdd::priority() {
	return 2;
}
