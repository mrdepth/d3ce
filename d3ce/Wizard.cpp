//
//  Wizard.cpp
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Wizard.h"
#include "Party.h"

using namespace d3ce;

Wizard::Wizard(Engine* engine, Party* party) : Hero(engine, party) {
	getAttribute(AttributeStrengthTotalFromLevelID)->setValue(1);
	getAttribute(AttributeDexterityTotalFromLevelID)->setValue(1);
	getAttribute(AttributeIntelligenceTotalFromLevelID)->setValue(3);
	getAttribute(AttributeVitalityTotalFromLevelID)->setValue(2);
	
	getAttribute(AttributeStrengthID)->setValue(8);
	getAttribute(AttributeDexterityID)->setValue(8);
	getAttribute(AttributeIntelligenceID)->setValue(10);
	getAttribute(AttributeVitalityID)->setValue(9);
	
	getAttribute(AttributePrimaryDamageAttributeID)->setValue(PrimaryDamageAttributeIntelligence);
	
	getAttribute(AttributeResourceTypePrimaryID)->setValue(AttributeArcanumSubID);
	getAttribute(AttributeResourceMaxID, AttributeArcanumSubID)->setValue(100);
	getAttribute(AttributeResourceRegenPerSecondID, AttributeArcanumSubID)->setValue(10);
}

Wizard::Wizard(const Wizard& other, Party* party) : Hero(other, party) {
	
}

Entity* Wizard::cloneIn(Entity* parent) {
	return new Wizard(*this, dynamic_cast<Party*>(parent));
}

ClassMask Wizard::getClass() {
	return ClassMaskWizard;
}