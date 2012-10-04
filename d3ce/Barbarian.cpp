//
//  Barbarian.cpp
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Barbarian.h"
#include "Party.h"

using namespace d3ce;

Barbarian::Barbarian(Engine* engine, Party* party) : Hero(engine, party) {
	getAttribute(AttributeClassBarbarianID)->setValue(1);
	getAttribute(AttributePrimaryDamageAttributeID)->setValue(PrimaryDamageAttributeStrength);
}

Barbarian::Barbarian(const Barbarian& other, Party* party) : Hero(other, party) {
	
}

Entity* Barbarian::cloneIn(Entity* parent) {
	return new Barbarian(*this, dynamic_cast<Party*>(parent));
}

ClassMask Barbarian::getClass() {
	return ClassMaskBarbarian;
}