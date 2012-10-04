//
//  Monk.cpp
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Monk.h"
#include "Party.h"

using namespace d3ce;

Monk::Monk(Engine* engine, Party* party) : Hero(engine, party) {
	getAttribute(AttributeClassMonkID)->setValue(1);
	getAttribute(AttributePrimaryDamageAttributeID)->setValue(PrimaryDamageAttributeDexterity);
}

Monk::Monk(const Monk& other, Party* party) : Hero(other, party) {
	
}

Entity* Monk::cloneIn(Entity* parent) {
	return new Monk(*this, dynamic_cast<Party*>(parent));
}

ClassMask Monk::getClass() {
	return ClassMaskMonk;
}