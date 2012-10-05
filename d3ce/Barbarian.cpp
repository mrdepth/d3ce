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
	getAttribute(AttributeStrengthTotalFromLevelID)->setValue(3);
	getAttribute(AttributeDexterityTotalFromLevelID)->setValue(1);
	getAttribute(AttributeIntelligenceTotalFromLevelID)->setValue(1);
	getAttribute(AttributeVitalityTotalFromLevelID)->setValue(2);
	
	getAttribute(AttributeStrengthID)->setValue(10);
	getAttribute(AttributeDexterityID)->setValue(8);
	getAttribute(AttributeIntelligenceID)->setValue(8);
	getAttribute(AttributeVitalityID)->setValue(9);
	
	getAttribute(AttributePrimaryDamageAttributeID)->setValue(PrimaryDamageAttributeStrength);
	getAttribute(AttributeClassDamageReductionPercentID)->setValue(0.3);
	
	getAttribute(AttributeResourceTypePrimaryID)->setValue(AttributeFurySubID);
	getAttribute(AttributeResourceMaxID, AttributeFurySubID)->setValue(100);
	getAttribute(AttributeResourceRegenPerSecondID, AttributeFurySubID)->setValue(-2);
}

Barbarian::Barbarian(const Barbarian& other, Party* party) : Hero(other, party) {
	
}

Entity* Barbarian::cloneIn(Entity* parent) {
	return new Barbarian(*this, dynamic_cast<Party*>(parent));
}

ClassMask Barbarian::getClass() {
	return ClassMaskBarbarian;
}