//
//  ModifierPostReduce.cpp
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "ModifierPostReduce.h"
#include "Expression.h"

using namespace d3ce;

ModifierPostReduce::ModifierPostReduce(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression) : Modifier(entity, attributeID, attributeSubID, expression) {
	
}

ModifierPostReduce::ModifierPostReduce(Entity* entity, AttributeID attributeID, Expression* expression) : Modifier(entity, attributeID, expression) {
	
}

Range ModifierPostReduce::apply(const Range& value) {
	return value * (Range(1) - expression_->value());
}

int ModifierPostReduce::priority() {
	return 3;
}
