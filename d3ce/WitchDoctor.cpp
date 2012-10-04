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
	getAttribute(AttributeClassWitchDoctorID)->setValue(1);
	getAttribute(AttributePrimaryDamageAttributeID)->setValue(PrimaryDamageAttributeIntelligence);
}

WitchDoctor::WitchDoctor(const WitchDoctor& other, Party* party) : Hero(other, party) {
	
}

Entity* WitchDoctor::cloneIn(Entity* parent) {
	return new WitchDoctor(*this, dynamic_cast<Party*>(parent));
}

ClassMask WitchDoctor::getClass() {
	return ClassMaskWitchDoctor;
}