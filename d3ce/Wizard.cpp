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

Wizard::Wizard(std::shared_ptr<Engine> engine, Party* party) : Hero(engine, party) {
	setAttribute(AttributeStrengthFactorLevelID, AttributeNoneSubID, 1);
	setAttribute(AttributeDexterityFactorLevelID, AttributeNoneSubID, 1);
	setAttribute(AttributeIntelligenceFactorLevelID, AttributeNoneSubID, 3);
	setAttribute(AttributeVitalityFactorLevelID, AttributeNoneSubID, 2);

	setAttribute(AttributeStrengthID, AttributeNoneSubID, 8);
	setAttribute(AttributeDexterityID, AttributeNoneSubID, 8);
	setAttribute(AttributeIntelligenceID, AttributeNoneSubID, 10);
	setAttribute(AttributeVitalityID, AttributeNoneSubID, 9);

	setAttribute(AttributePrimaryDamageAttributeID, AttributeNoneSubID, PrimaryDamageAttributeIntelligence);

	setAttribute(AttributeResourceTypePrimaryID, AttributeNoneSubID, AttributeArcanumSubID);
	setAttribute(AttributeResourceMaxID, AttributeArcanumSubID, 100);
	setAttribute(AttributeResourceRegenPerSecondID, AttributeArcanumSubID, 10);
}

Wizard::Wizard(const Wizard& other, Party* party) : Hero(other, party) {
	
}

Entity* Wizard::cloneIn(Entity* parent) {
	return new Wizard(*this, dynamic_cast<Party*>(parent));
}

ClassMask Wizard::getClass() const {
	return ClassMaskWizard;
}

std::string Wizard::getClassName() const {
	return "Wizard";
}
