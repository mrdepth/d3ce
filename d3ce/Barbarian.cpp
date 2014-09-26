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

Barbarian::Barbarian(std::shared_ptr<Engine> engine, Party* party) : Hero(engine, party) {
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

	setAttribute(AttributeResourceTypePrimaryID, AttributeNoneSubID, AttributeFurySubID);
	setAttribute(AttributeResourceMaxID, AttributeFurySubID, 100);
	setAttribute(AttributeResourceRegenPerSecondID, AttributeFurySubID, -2);
}

Barbarian::Barbarian(const Barbarian& other, Party* party) : Hero(other, party) {
	
}

Entity* Barbarian::cloneIn(Entity* parent) {
	return new Barbarian(*this, dynamic_cast<Party*>(parent));
}

ClassMask Barbarian::getClass() const {
	return ClassMaskBarbarian;
}