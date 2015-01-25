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

WitchDoctor::WitchDoctor(std::shared_ptr<Engine> engine, Party* party) : Hero(engine, party) {
	setAttribute(AttributeStrengthFactorLevelID, AttributeNoneSubID, 1);
	setAttribute(AttributeDexterityFactorLevelID, AttributeNoneSubID, 1);
	setAttribute(AttributeIntelligenceFactorLevelID, AttributeNoneSubID, 3);
	setAttribute(AttributeVitalityFactorLevelID, AttributeNoneSubID, 2);

	setAttribute(AttributeStrengthID, AttributeNoneSubID, 8);
	setAttribute(AttributeDexterityID, AttributeNoneSubID, 8);
	setAttribute(AttributeIntelligenceID, AttributeNoneSubID, 10);
	setAttribute(AttributeVitalityID, AttributeNoneSubID, 9);

	setAttribute(AttributePrimaryDamageAttributeID, AttributeNoneSubID, PrimaryDamageAttributeIntelligence);

	setAttribute(AttributeResourceTypePrimaryID, AttributeNoneSubID, AttributeManaSubID);
	setAttribute(AttributeResourceMaxID, AttributeManaSubID, 150);
	setAttribute(AttributeResourceRegenPerSecondID, AttributeManaSubID, 10);
	setAttribute(AttributeResourceFactorLevelID, AttributeManaSubID, 10);
}

WitchDoctor::WitchDoctor(const WitchDoctor& other, Party* party) : Hero(other, party) {
	
}

Entity* WitchDoctor::cloneIn(Entity* parent) {
	return new WitchDoctor(*this, dynamic_cast<Party*>(parent));
}

ClassMask WitchDoctor::getClass() const {
	return ClassMaskWitchDoctor;
}

std::string WitchDoctor::getClassName() const {
	return "WitchDoctor";
}