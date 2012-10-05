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
	getAttribute(AttributeStrengthTotalFromLevelID)->setValue(1);
	getAttribute(AttributeDexterityTotalFromLevelID)->setValue(3);
	getAttribute(AttributeIntelligenceTotalFromLevelID)->setValue(1);
	getAttribute(AttributeVitalityTotalFromLevelID)->setValue(2);
	
	getAttribute(AttributeStrengthID)->setValue(8);
	getAttribute(AttributeDexterityID)->setValue(10);
	getAttribute(AttributeIntelligenceID)->setValue(8);
	getAttribute(AttributeVitalityID)->setValue(9);
	
	getAttribute(AttributePrimaryDamageAttributeID)->setValue(PrimaryDamageAttributeDexterity);
	
	getAttribute(AttributeResourceTypePrimaryID)->setValue(AttributeHatredSubID);
	getAttribute(AttributeResourceTypeSecondaryID)->setValue(AttributeDisciplineSubID);
	getAttribute(AttributeResourceMaxID, AttributeHatredSubID)->setValue(125);
	getAttribute(AttributeResourceRegenPerSecondID, AttributeHatredSubID)->setValue(4);
	getAttribute(AttributeResourceMaxID, AttributeDisciplineSubID)->setValue(30);
	getAttribute(AttributeResourceRegenPerSecondID, AttributeDisciplineSubID)->setValue(1);
}

DemonHunter::DemonHunter(const DemonHunter& other, Party* party) : Hero(other, party) {
	
}

Entity* DemonHunter::cloneIn(Entity* parent) {
	return new DemonHunter(*this, dynamic_cast<Party*>(parent));
}

ClassMask DemonHunter::getClass() {
	return ClassMaskDemonHunter;
}