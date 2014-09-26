//
//  Entity.cpp
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Entity.h"
#include "Attribute.h"
#include <algorithm>
#include <sstream>

#include <iostream>
using namespace d3ce;

Entity::Entity(std::shared_ptr<Engine> engine, Entity* parent) : engine_(engine), parent_(parent) {
}

Entity::Entity(const Entity& other, Entity* parent) : engine_(other.engine_), parent_(parent) {
}

Entity::~Entity() {

}

Attribute Entity::getAttribute(AttributeID attributeID, AttributeSubID attributeSubID) const {
	AttributeKey key = std::make_pair(attributeID, attributeSubID);
	AttributesMap::const_iterator i = attributes_.find(key);
	Range value = 0;
	if (i != attributes_.end())
		value = i->second;
	return Attribute(this, attributeID, attributeSubID, value);
}

Attribute Entity::getAttribute(const std::string& nonNlsKey) const {
	auto key = getKey(nonNlsKey);
	return getAttribute(key.first, key.second);
}

Entity* Entity::getParent() const {
	return parent_;
}

Entity::AttributeWrapper Entity::operator[](AttributeKey& key) {
	return AttributeWrapper(this, key.first, key.second);
}

Entity::AttributeWrapper Entity::operator[](AttributeID attributeID) {
	return AttributeWrapper(this, attributeID);
}

Entity::AttributeWrapper Entity::operator[](const std::string& nonNlsKey) {
	auto key = getKey(nonNlsKey);
	return AttributeWrapper(this, key.first, key.second);
}

Entity::ConstAttributeWrapper Entity::operator[](AttributeKey& key) const {
	return ConstAttributeWrapper(this, key.first, key.second);
	//return getAttribute(key.first, key.second);
}

Entity::ConstAttributeWrapper Entity::operator[](AttributeID attributeID) const {
	return ConstAttributeWrapper(this, attributeID);
	//return getAttribute(attributeID);
}

Entity::ConstAttributeWrapper Entity::operator[](const std::string& nonNlsKey) const {
	Attribute attribute = getAttribute(nonNlsKey);
	return ConstAttributeWrapper(this, attribute.getAttributeID(), attribute.getAttributeSubID());
	//return getAttribute(nonNlsKey);
}

void Entity::setAttribute(AttributeID attributeID, AttributeSubID attributeSubID, const Range& value) {
	attributes_[std::make_pair(attributeID, attributeSubID)] = value;
}

AttributeKey Entity::getKey(const std::string& nonNlsKey) const {
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
			attributeSubID = AttributePhysicalSubID;
		else if (attributeSubKey == "Fire")
			attributeSubID = AttributeFireSubID;
		else if (attributeSubKey == "Lightning")
			attributeSubID = AttributeLightningSubID;
		else if (attributeSubKey == "Cold")
			attributeSubID = AttributeColdSubID;
		else if (attributeSubKey == "Poison")
			attributeSubID = AttributePoisonSubID;
		else if (attributeSubKey == "Arcane")
			attributeSubID = AttributeArcaneSubID;
		else if (attributeSubKey == "Holy")
			attributeSubID = AttributeHolySubID;
		else if (attributeSubKey == "Mana")
			attributeSubID = AttributeManaSubID;
		else if (attributeSubKey == "Arcanum")
			attributeSubID = AttributeArcanumSubID;
		else if (attributeSubKey == "Fury")
			attributeSubID = AttributeFurySubID;
		else if (attributeSubKey == "Spirit")
			attributeSubID = AttributeSpiritSubID;
		else if (attributeSubKey == "Hatred")
			attributeSubID = AttributeHatredSubID;
		else if (attributeSubKey == "Discripline")
			attributeSubID = AttributeDisciplineSubID;
		else if (attributeSubKey == "Undead")
			attributeSubID = AttributeUndeadSubID;
		else if (attributeSubKey == "Demon")
			attributeSubID = AttributeDemonSubID;
		else if (attributeSubKey == "Beast")
			attributeSubID = AttributeBeastSubID;
		else if (attributeSubKey == "Human")
			attributeSubID = AttributeHumanSubID;
		else {
			//			std::cout<< "Unknown " << attributeSubKey;
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
		sqlite3_finalize(stmt);
		return std::make_pair(attributeID, attributeSubID);
	}
	else
		sqlite3_finalize(stmt);
	throw std::invalid_argument("nonNlsKey");
}