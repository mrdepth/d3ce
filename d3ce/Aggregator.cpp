//
//  Gear.cpp
//  d3ce
//
//  Created by Artem Shimanski on 17.09.14.
//  Copyright (c) 2014 Artem Shimanski. All rights reserved.
//

#include "Aggregator.h"
#include <algorithm>

using namespace d3ce;

/*Aggregator::Aggregator(std::shared_ptr<Engine> engine, std::vector<std::shared_ptr<Entity>>::iterator begin, std::vector<std::shared_ptr<Entity>>::iterator end) : Entity(engine, NULL), entities_(begin, end) {

}

Aggregator::~Aggregator() {

}

void Aggregator::addEntity(std::shared_ptr<Entity> entity) {
	entities_.push_back(entity);
}

void Aggregator::removeEntity(std::shared_ptr<Entity> entity) {
	entities_.erase(std::remove(entities_.begin(), entities_.end(), entity));
}

Attribute Aggregator::getAttribute(AttributeID attributeID, AttributeSubID attributeSubID) const {
	Range value = 0;
	for (auto item : entities_)
		value = value + item->getAttribute(attributeID, attributeSubID);
	return Attribute(this, attributeID, attributeSubID, value);
}
*/