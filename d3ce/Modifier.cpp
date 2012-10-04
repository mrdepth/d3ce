//
//  Modifier.cpp
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Modifier.h"
#include "Expression.h"

using namespace d3ce;

Modifier::Modifier(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, Expression* expression) : entity_(entity), attributeID_(attributeID), attributeSubID_(attributeSubID), expression_(expression) {
	
}

Modifier::Modifier(Entity* entity, AttributeID attributeID, Expression* expression) : entity_(entity), attributeID_(attributeID), attributeSubID_(AttributeNoneSubID), expression_(expression) {
	
}

Modifier::~Modifier() {
	delete expression_;
}