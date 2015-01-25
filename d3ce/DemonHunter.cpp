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

DemonHunter::DemonHunter(std::shared_ptr<Engine> engine, Party* party) : Hero(engine, party) {
	setAttribute(AttributeStrengthFactorLevelID, AttributeNoneSubID, 1);
	setAttribute(AttributeDexterityFactorLevelID, AttributeNoneSubID, 3);
	setAttribute(AttributeIntelligenceFactorLevelID, AttributeNoneSubID, 1);
	setAttribute(AttributeVitalityFactorLevelID, AttributeNoneSubID, 2);

	setAttribute(AttributeStrengthID, AttributeNoneSubID, 8);
	setAttribute(AttributeDexterityID, AttributeNoneSubID, 10);
	setAttribute(AttributeIntelligenceID, AttributeNoneSubID, 8);
	setAttribute(AttributeVitalityID, AttributeNoneSubID, 9);

	setAttribute(AttributePrimaryDamageAttributeID, AttributeNoneSubID, PrimaryDamageAttributeDexterity);

	setAttribute(AttributeResourceTypePrimaryID, AttributeNoneSubID, AttributeHatredSubID);
	setAttribute(AttributeResourceTypeSecondaryID, AttributeNoneSubID, AttributeDisciplineSubID);
	setAttribute(AttributeResourceMaxID, AttributeHatredSubID, 125);
	setAttribute(AttributeResourceRegenPerSecondID, AttributeHatredSubID, 4);
	setAttribute(AttributeResourceMaxID, AttributeDisciplineSubID, 30);
	setAttribute(AttributeResourceRegenPerSecondID, AttributeDisciplineSubID, 1);
}

DemonHunter::DemonHunter(const DemonHunter& other, Party* party) : Hero(other, party) {
	
}

Entity* DemonHunter::cloneIn(Entity* parent) {
	return new DemonHunter(*this, dynamic_cast<Party*>(parent));
}

ClassMask DemonHunter::getClass() const {
	return ClassMaskDemonHunter;
}

std::string DemonHunter::getClassName() const {
	return "Demon Hunter";
}