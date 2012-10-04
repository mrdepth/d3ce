//
//  DemonHunter.cpp
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "DemonHunter.h"
#include "Party.h"

using namespace d3ce;

DemonHunter::DemonHunter(Engine* engine, Party* party) : Hero(engine, party) {
	getAttribute(AttributeClassDemonHunterID)->setValue(1);
	getAttribute(AttributePrimaryDamageAttributeID)->setValue(PrimaryDamageAttributeDexterity);
}

DemonHunter::DemonHunter(const DemonHunter& other, Party* party) : Hero(other, party) {
	
}

Entity* DemonHunter::cloneIn(Entity* parent) {
	return new DemonHunter(*this, dynamic_cast<Party*>(parent));
}

ClassMask DemonHunter::getClass() {
	return ClassMaskDemonHunter;
}