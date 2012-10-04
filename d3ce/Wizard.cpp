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
	getAttribute(AttributeClassWizardID)->setValue(1);
	getAttribute(AttributePrimaryDamageAttributeID)->setValue(PrimaryDamageAttributeIntelligence);
}

Wizard::Wizard(const Wizard& other, Party* party) : Hero(other, party) {
	
}

Entity* Wizard::cloneIn(Entity* parent) {
	return new Wizard(*this, dynamic_cast<Party*>(parent));
}

ClassMask Wizard::getClass() {
	return ClassMaskWizard;
}