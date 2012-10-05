//
//  WitchDoctor.cpp
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "WitchDoctor.h"
#include "Party.h"

using namespace d3ce;

WitchDoctor::WitchDoctor(Engine* engine, Party* party) : Hero(engine, party) {
	getAttribute(AttributeStrengthTotalFromLevelID)->setValue(1);
	getAttribute(AttributeDexterityTotalFromLevelID)->setValue(1);
	getAttribute(AttributeIntelligenceTotalFromLevelID)->setValue(3);
	getAttribute(AttributeVitalityTotalFromLevelID)->setValue(2);
	
	getAttribute(AttributeStrengthID)->setValue(8);
	getAttribute(AttributeDexterityID)->setValue(8);
	getAttribute(AttributeIntelligenceID)->setValue(10);
	getAttribute(AttributeVitalityID)->setValue(9);
	
	getAttribute(AttributePrimaryDamageAttributeID)->setValue(PrimaryDamageAttributeIntelligence);
	
	getAttribute(AttributeResourceTypePrimaryID)->setValue(AttributeManaSubID);
	getAttribute(AttributeResourceMaxID, AttributeManaSubID)->setValue(150);
	getAttribute(AttributeResourceRegenPerSecondID, AttributeManaSubID)->setValue(10);
	getAttribute(AttributeResourceFactorLevelID, AttributeManaSubID)->setValue(10);
}

WitchDoctor::WitchDoctor(const WitchDoctor& other, Party* party) : Hero(other, party) {
	
}

Entity* WitchDoctor::cloneIn(Entity* parent) {
	return new WitchDoctor(*this, dynamic_cast<Party*>(parent));
}

ClassMask WitchDoctor::getClass() {
	return ClassMaskWitchDoctor;
}