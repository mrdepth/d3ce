//
//  Party.cpp
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Party.h"
#include "Barbarian.h"
#include "DemonHunter.h"
#include "Monk.h"
#include "WitchDoctor.h"
#include "Wizard.h"
#include <algorithm>

using namespace d3ce;

Party::Party(Engine* engine) : Entity(engine) {
	
}

Party::Party(const Party& other) : Entity(other){
	std::vector<Hero*>::const_iterator i, end = other.heroes_.end();
	for (i = other.heroes_.begin(); i != end; i++)
		heroes_.push_back(dynamic_cast<Hero*>((*i)->cloneIn(this)));
}

Hero* Party::addHero(ClassMask classMask) {
	Hero* hero;
	switch (classMask) {
		case ClassMaskBarbarian:
			hero = new Barbarian(engine_, this);
			break;
		case ClassMaskDemonHunter:
			hero = new DemonHunter(engine_, this);
			break;
		case ClassMaskMonk:
			hero = new Monk(engine_, this);
			break;
		case ClassMaskWitchDoctor:
			hero = new WitchDoctor(engine_, this);
			break;
		case ClassMaskWizard:
			hero = new Wizard(engine_, this);
			break;
		default:
			break;
	}
	if (hero)
		heroes_.push_back(hero);
	return hero;
}

void Party::removeHero(Hero* hero) {
	heroes_.erase(std::remove(heroes_.begin(), heroes_.end(), hero));
	delete hero;
}


Environment Party::environment() {
	return Environment (this, NULL, this);
}

Party* Party::clone() {
	return dynamic_cast<Party*>(cloneIn(NULL));
}

Entity* Party::cloneIn(Entity* parent) {
	return new Party(*this);
}

const std::vector<Hero*>& Party::getHeroes() {
	return heroes_;
}