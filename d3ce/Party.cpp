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

Party::Party(std::shared_ptr<Engine> engine) : Entity(engine) {
	
}

Party::Party(const Party& other) : Entity(other){
	//std::vector<Hero*>::const_iterator i, end = other.heroes_.end();
	//for (i = other.heroes_.begin(); i != end; i++)
	//	heroes_.push_back(dynamic_cast<Hero*>((*i)->cloneIn(this)));
}

std::shared_ptr<Hero> Party::addHero(ClassMask classMask) {
	std::shared_ptr<Hero> hero;
	switch (classMask) {
		case ClassMaskBarbarian:
			hero.reset(new Barbarian(engine_, this));
			break;
		case ClassMaskDemonHunter:
			hero.reset(new DemonHunter(engine_, this));
			break;
		case ClassMaskMonk:
			hero.reset(new Monk(engine_, this));
			break;
		case ClassMaskWitchDoctor:
			hero.reset(new WitchDoctor(engine_, this));
			break;
		case ClassMaskWizard:
			hero.reset(new Wizard(engine_, this));
			break;
		default:
			break;
	}
	if (hero)
		heroes_.push_back(hero);
	return hero;
}

void Party::removeHero(std::shared_ptr<Hero> hero) {
	heroes_.erase(std::remove(heroes_.begin(), heroes_.end(), hero));
}


Environment Party::environment() {
	return Environment (this, NULL, this);
}

Entity* Party::cloneIn(Entity* parent) {
	return new Party(*this);
}

const std::vector<std::shared_ptr<Hero>>& Party::getHeroes() {
	return heroes_;
}