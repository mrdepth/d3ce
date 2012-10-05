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
	getAttribute(AttributeStrengthTotalFromLevelID)->setValue(1);
	getAttribute(AttributeDexterityTotalFromLevelID)->setValue(3);
	getAttribute(AttributeIntelligenceTotalFromLevelID)->setValue(1);
	getAttribute(AttributeVitalityTotalFromLevelID)->setValue(2);
	
	getAttribute(AttributeStrengthID)->setValue(8);
	getAttribute(AttributeDexterityID)->setValue(10);
	getAttribute(AttributeIntelligenceID)->setValue(8);
	getAttribute(AttributeVitalityID)->setValue(9);
	
	getAttribute(AttributePrimaryDamageAttributeID)->setValue(PrimaryDamageAttributeDexterity);
	getAttribute(AttributeClassDamageReductionPercentID)->setValue(0.3);
	
	getAttribute(AttributeResourceTypePrimaryID)->setValue(AttributeSpiritSubID);
	getAttribute(AttributeResourceMaxID, AttributeSpiritSubID)->setValue(150);
}

Monk::Monk(const Monk& other, Party* party) : Hero(other, party) {
	
}

Entity* Monk::cloneIn(Entity* parent) {
	return new Monk(*this, dynamic_cast<Party*>(parent));
}

ClassMask Monk::getClass() {
	return ClassMaskMonk;
}