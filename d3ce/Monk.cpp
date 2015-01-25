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

Monk::Monk(std::shared_ptr<Engine> engine, Party* party) : Hero(engine, party) {
	setAttribute(AttributeStrengthFactorLevelID, AttributeNoneSubID, 1);
	setAttribute(AttributeDexterityFactorLevelID, AttributeNoneSubID, 3);
	setAttribute(AttributeIntelligenceFactorLevelID, AttributeNoneSubID, 1);
	setAttribute(AttributeVitalityFactorLevelID, AttributeNoneSubID, 2);

	setAttribute(AttributeStrengthID, AttributeNoneSubID, 8);
	setAttribute(AttributeDexterityID, AttributeNoneSubID, 10);
	setAttribute(AttributeIntelligenceID, AttributeNoneSubID, 8);
	setAttribute(AttributeVitalityID, AttributeNoneSubID, 9);

	setAttribute(AttributePrimaryDamageAttributeID, AttributeNoneSubID, PrimaryDamageAttributeDexterity);
	setAttribute(AttributeClassDamageReductionPercentID, AttributeNoneSubID, 0.3);

	setAttribute(AttributeResourceTypePrimaryID, AttributeNoneSubID, AttributeSpiritSubID);
	setAttribute(AttributeResourceMaxID, AttributeSpiritSubID, 125);
	setAttribute(AttributeHitpointsFactorResourceID, AttributeSpiritSubID, 9);
}

Monk::Monk(const Monk& other, Party* party) : Hero(other, party) {
	
}

Entity* Monk::cloneIn(Entity* parent) {
	return new Monk(*this, dynamic_cast<Party*>(parent));
}

ClassMask Monk::getClass() const {
	return ClassMaskMonk;
}

std::string Monk::getClassName() const {
	return "Monk";
}
