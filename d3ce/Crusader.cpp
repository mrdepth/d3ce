//
//  Crusader.cpp
//  d3ce
//
//  Created by Artem Shimanski on 05.01.15.
//  Copyright (c) 2015 Artem Shimanski. All rights reserved.
//

#include "Crusader.h"
#include "Party.h"

using namespace d3ce;

Crusader::Crusader(std::shared_ptr<Engine> engine, Party* party) : Hero(engine, party) {
	setAttribute(AttributeStrengthFactorLevelID, AttributeNoneSubID, 3);
	setAttribute(AttributeDexterityFactorLevelID, AttributeNoneSubID, 1);
	setAttribute(AttributeIntelligenceFactorLevelID, AttributeNoneSubID, 1);
	setAttribute(AttributeVitalityFactorLevelID, AttributeNoneSubID, 2);
	
	setAttribute(AttributeStrengthID, AttributeNoneSubID, 10);
	setAttribute(AttributeDexterityID, AttributeNoneSubID, 8);
	setAttribute(AttributeIntelligenceID, AttributeNoneSubID, 8);
	setAttribute(AttributeVitalityID, AttributeNoneSubID, 9);
	
	setAttribute(AttributePrimaryDamageAttributeID, AttributeNoneSubID, PrimaryDamageAttributeStrength);
	setAttribute(AttributeClassDamageReductionPercentID, AttributeNoneSubID, 0.3);
	
	setAttribute(AttributeResourceTypePrimaryID, AttributeNoneSubID, AttributeFaithSubID);
	setAttribute(AttributeResourceMaxID, AttributeFaithSubID, 100);
	setAttribute(AttributeResourceRegenPerSecondID, AttributeFaithSubID, 2.5);
	setAttribute(AttributeHitpointsFactorResourceID, AttributeFaithSubID, 3.75);
}

Crusader::Crusader(const Crusader& other, Party* party) : Hero(other, party) {
	
}

Entity* Crusader::cloneIn(Entity* parent) {
	return new Crusader(*this, dynamic_cast<Party*>(parent));
}

ClassMask Crusader::getClass() const {
	return ClassMaskCrusader;
}

std::string Crusader::getClassName() const {
	return "Crusader";
}