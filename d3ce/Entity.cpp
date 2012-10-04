//
//  Entity.cpp
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Entity.h"
#include "Modifier.h"
#include "Attribute.h"
#include <algorithm>
#include <sstream>

#include <iostream>
using namespace d3ce;

class PriorityCompare : public std::binary_function<Modifier*, Modifier*, bool> {
public:
	bool operator()(Modifier* a, Modifier* b) {
		return a->priority() < b->priority();
	}
};

Entity::Entity(Engine* engine, Entity* parent) : engine_(engine), parent_(parent) {
}

Entity::Entity(const Entity& other, Entity* parent) : engine_(other.engine_), parent_(parent) {
}

Entity::~Entity() {
	AttributesMap::iterator i, end = attributes_.end();
	for (i = attributes_.begin(); i != end; i++) {
		i->second->removeModifiers();
		delete i->second;
	}
}

void Entity::copyAttributes(const Entity& other) {
	AttributesMap::const_iterator i, end = other.attributes_.end();
	for (i = other.attributes_.begin(); i != end; i++)
		getAttribute(i->first.first, i->first.second)->setValue(i->second->getInitialValue());
}


void Entity::addModifier(Modifier* modifier) {
	std::vector<Modifier*>::iterator i = std::upper_bound(modifiers_.begin(), modifiers_.end(), modifier, PriorityCompare());
	modifiers_.insert(i, modifier);
	getAttribute(modifier->attributeID_, modifier->attributeSubID_);
}

void Entity::removeModifier(Modifier* modifier) {
	modifiers_.erase(std::remove(modifiers_.begin(), modifiers_.end(), modifier));
}

Attribute* Entity::getAttribute(AttributeID attributeID, AttributeSubID attributeSubID) {
	AttributeKey key = std::make_pair(attributeID, attributeSubID);
	AttributesMap::iterator i = attributes_.find(key);
	if (i == attributes_.end()) {
		Attribute* attribute = new Attribute(attributeID, attributeSubID, environment(), Range());
		attributes_[key] = attribute;
		attribute->applyModifiers();
		return attribute;
	}
	else
		return i->second;
}

Attribute* Entity::getAttribute(const std::string& nonNlsKey) {
	std::string::size_type pos = nonNlsKey.find('#');
	std::string attributeKey;
	std::string attributeSubKey;
	
	if (pos != std::string::npos) {
		attributeKey = nonNlsKey.substr(0, pos);
		attributeSubKey = nonNlsKey.substr(pos + 1);
	}
	else
		attributeKey = nonNlsKey;
	
	AttributeSubID attributeSubID = AttributeNoneSubID;
	if (attributeSubKey.length() > 0) {
		if (attributeSubKey == "Physical")
			attributeSubID = 0;
		else if (attributeSubKey == "Fire")
			attributeSubID = 1;
		else if (attributeSubKey == "Lightning")
			attributeSubID = 2;
		else if (attributeSubKey == "Cold")
			attributeSubID = 3;
		else if (attributeSubKey == "Poison")
			attributeSubID = 4;
		else if (attributeSubKey == "Arcane")
			attributeSubID = 5;
		else if (attributeSubKey == "Holy")
			attributeSubID = 6;
		else if (attributeSubKey == "Mana")
			attributeSubID = 0;
		else if (attributeSubKey == "Arcanum")
			attributeSubID = 1;
		else if (attributeSubKey == "Fury")
			attributeSubID = 2;
		else if (attributeSubKey == "Spirit")
			attributeSubID = 3;
		else if (attributeSubKey == "Hatred")
			attributeSubID = 5;
		else if (attributeSubKey == "Discripline")
			attributeSubID = 6;
		else if (attributeSubKey == "Undead")
			attributeSubID = 0;
		else if (attributeSubKey == "Demon")
			attributeSubID = 1;
		else if (attributeSubKey == "Beast")
			attributeSubID = 2;
		else if (attributeSubKey == "Human")
			attributeSubID = 3;
		else {
			std::cout<< "Unknown " << attributeSubKey;
		}
	}
	
	std::stringstream sql;
	sql << "SELECT rawAttributeID FROM rawAttribute WHERE nonNlsKey =  \"" << attributeKey << "\"";
	
	sqlite3* db = engine_->getDb();
	sqlite3_stmt* stmt = NULL;
	sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
	int result = sqlite3_step(stmt);
	
	Attribute* attribute = NULL;
	if (result == SQLITE_ROW)
	{
		AttributeID attributeID = static_cast<AttributeID>(sqlite3_column_int(stmt, 0));
		attribute = getAttribute(attributeID, attributeSubID);
	}
	sqlite3_finalize(stmt);
	return attribute;
}

std::vector<Modifier*> Entity::getAttributeModifiers(Attribute* attribute) {
	std::vector<Modifier*> result;
	std::vector<Modifier*>::iterator i, end = modifiers_.end();
	AttributeID attributeID = attribute->getAttributeID();
	AttributeSubID attributeSubID = attribute->getAttributeSubID();
	
	for (i = modifiers_.begin(); i != end; i++) {
		if ((*i)->attributeID_ == attributeID && (*i)->attributeSubID_ == attributeSubID) {
			result.push_back(*i);
		}
	}
	return result;
}

Entity* Entity::getParent() {
	return parent_;
}

Attribute* Entity::operator[](AttributeKey& key) {
	return getAttribute(key.first, key.second);
}

Entity::AttributeContainer Entity::operator[](AttributeID attributeID) {
	return AttributeContainer(this, attributeID);
}

Attribute* Entity::operator[](const std::string& nonNlsKey) {
	return getAttribute(nonNlsKey);
}
