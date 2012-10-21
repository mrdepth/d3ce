//
//  Item.cpp
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Item.h"
#include "Hero.h"
#include "Party.h"
#include "Weapon.h"
#include "Armor.h"
#include "OffHand.h"
#include "Gem.h"
#include <sstream>
#include <math.h>
#include <iostream>

using namespace d3ce;

Item* Item::CreateItem(Engine* engine, Entity* parent, Hash itemHash) {
	std::stringstream sql;
	sql << "SELECT itemHash, nonNlsKey, itemTypeHash, itemSetBonusHash, itemLevel, flags FROM item where itemHash =  " << itemHash;
	return CreateItemFromRequest(engine, parent, sql.str());
}

Item* Item::CreateItem(Engine* engine, Entity* parent, const std::string& nonNlsKey) {
	std::stringstream sql;
	sql << "SELECT itemHash, nonNlsKey, itemTypeHash, itemSetBonusHash, itemLevel, flags FROM item where nonNlsKey =  \"" << nonNlsKey << "\"";
	return CreateItemFromRequest(engine, parent, sql.str());
}

Item* Item::CreateItemFromRequest(Engine* engine, Entity* parent, const std::string& sqlRequest) {
	sqlite3* db = engine->getDb();
	
	sqlite3_stmt* stmt = NULL;
	sqlite3_prepare_v2(db, sqlRequest.c_str(), -1, &stmt, NULL);
	int result = sqlite3_step(stmt);
	
	if (result == SQLITE_ROW)
	{

		Hash itemHash = sqlite3_column_int(stmt, 0);
		std::string itemName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		Hash itemTypeHash = sqlite3_column_int(stmt, 2);
		Hash itemSetBonusHash = sqlite3_column_int(stmt, 3);
		int itemLevel = sqlite3_column_int(stmt, 4);
		int flags = sqlite3_column_int(stmt, 5);
		sqlite3_finalize(stmt);
		
		std::vector<Hash> itemTypesTree;
		itemTypesTree.push_back(itemTypeHash);
		
//		if (flags & LegendaryFlag)
//			itemTypesTree.push_back(hash("LegendaryOnly"));
		
		std::stringstream sql;
		sql << "SELECT nonNlsKey, parentItemTypeHash, flags, slot1, slot2, slot3, slot4, bitMask1 FROM itemType where itemTypeHash = " << itemTypeHash;
		
		stmt = NULL;
		sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW)
		{
			std::string itemTypeName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
			Hash parentItemTypeHash = sqlite3_column_int(stmt, 1);
			int slots[] = {sqlite3_column_int(stmt, 3), sqlite3_column_int(stmt, 4), sqlite3_column_int(stmt, 5), sqlite3_column_int(stmt, 6)};
			int bitMask = sqlite3_column_int(stmt, 7);
			
			itemTypesTree.push_back(parentItemTypeHash);
			
			if (flags & ItemTypeGemFlag) {
				slots[0] = SlotSocket;
			}
			
			sqlite3_finalize(stmt);
			
			while (isValidHash(parentItemTypeHash)) {
				sql.str(std::string());
				sql << "SELECT parentItemTypeHash FROM itemType where itemTypeHash = " << parentItemTypeHash;
				stmt = NULL;
				sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
				result = sqlite3_step(stmt);
				Hash hash = result == SQLITE_ROW ? sqlite3_column_int(stmt, 0) : -1;
				sqlite3_finalize(stmt);
				if (isValidHash(hash)) {
					parentItemTypeHash = hash;
					itemTypesTree.push_back(parentItemTypeHash);
				}
				else
					break;
			}
			
			std::vector<Slot> possibleSlots;
			for (int i = 0; i < 4; i++) {
				if (slots[i] > 0)
					possibleSlots.push_back(static_cast<Slot>(slots[i]));
			}
			
			Item* item;
			switch(parentItemTypeHash) {
				case ItemTypeArmorHash:
				case ItemTypeJewelryHash:
					item = new Armor(engine, parent, itemHash, itemTypesTree, itemSetBonusHash, flags, bitMask, possibleSlots);
					break;
				case ItemTypeWeaponHash:
					item = new Weapon(engine, parent, itemHash, itemTypesTree, itemSetBonusHash, flags, bitMask, possibleSlots);
					break;
				case ItemTypeOffHandHash:
					item = new OffHand(engine, parent, itemHash, itemTypesTree, itemSetBonusHash, flags, bitMask, possibleSlots);
					break;
				case ItemTypeSocketableHash:
					item = new Gem(engine, dynamic_cast<Item*>(parent), itemHash, itemTypesTree, flags, bitMask, possibleSlots);
					break;
				default:
					throw UnknownItemTypeHashException();
			};
			item->itemLevel_ = itemLevel;
			return item;
		}
		else {
			sqlite3_finalize(stmt);
			throw UnknownItemTypeHashException();
		}
	}
	else
	{
		sqlite3_finalize(stmt);
		throw UnknownItemHashException();
	}
	return NULL;
}

Item::Item(Engine* engine, Entity* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, int flags, int bitMask, const std::vector<Slot>& possibleSlots) : Entity(engine, parent), itemTypesTree_(itemTypesTree), possibleSlots_(possibleSlots){
	itemHash_ = itemHash;
	flags_ = flags;
	bitMask_ = bitMask;
}

Item::Item(const Item& other, Entity* parent) : Entity(other, parent), itemTypesTree_(other.itemTypesTree_), possibleSlots_(other.possibleSlots_), possibleModifiers_(other.possibleModifiers_) {
	slot_ = other.slot_;
	itemHash_ = other.itemHash_;
	flags_ = other.flags_;
	bitMask_ = other.bitMask_;
	itemLevel_ = other.itemLevel_;
}


Item::Slot Item::getSlot() {
	return slot_;
}

void Item::setSlot(Slot slot) {
	slot_ = slot;
}

const std::vector<Item::Slot>&  Item::possibleSlots() {
	return possibleSlots_;
}

const std::vector<Hash>& Item::itemTypesTree() {
	return itemTypesTree_;
}

bool Item::conforms(Hash hash) {
	std::vector<Hash>::iterator i, end = itemTypesTree_.end();
	for (i = itemTypesTree_.begin(); i != end; i++) {
		if (*i == hash)
			return true;
	}
	return false;
}

const std::map<AttributeKey, Range> Item::possibleModifiers() {
	if (possibleModifiers_.size() == 0) {
		std::map<AttributeKey, Range> itemModifiers;
		std::map<AttributeKey, std::map<int, Range> > affixModifiers;
		
		sqlite3* db = engine_->getDb();
		
		std::stringstream itemTypesStream;
		
		std::vector<Hash>::iterator i, end = itemTypesTree_.end();
		bool first = true;
		for (i = itemTypesTree_.begin(); i != end; i++) {
			if (!first)
				itemTypesStream << ',';
			itemTypesStream << *i;
			first = false;
		}
		
		std::string itemTypes = itemTypesStream.str();
		
		std::vector<std::string> requests;
		
		std::stringstream sql;
		
		Hash itemHash = itemHash_;
		
		sqlite3_stmt* stmt = NULL;
		while (isValidHash(itemHash)) {
			sql << "SELECT baseItemHash, durabilityMin, durabilityDelta, damageWeaponMinMin, damageWeaponMinDelta, damageWeaponDeltaMin, damageWeaponDeltaDelta, armorMin, armorDelta FROM item WHERE itemHash = " << itemHash;
			sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
			
			if (sqlite3_step(stmt) == SQLITE_ROW) {
				itemHash = sqlite3_column_int(stmt, 0);
				Range durability;
				Range damageMin;
				Range damageDelta;
				Range armor;
				durability.min = sqlite3_column_double(stmt, 1);
				durability.max = durability.min + sqlite3_column_double(stmt, 2);
				damageMin.min = sqlite3_column_double(stmt, 3);
				damageMin.max = damageMin.min + sqlite3_column_double(stmt, 4);
				damageDelta.min = sqlite3_column_double(stmt, 5);
				damageDelta.max = damageDelta.min + sqlite3_column_double(stmt, 6);
				armor.min = sqlite3_column_double(stmt, 7);
				armor.max = armor.min + sqlite3_column_double(stmt, 8);
				if (durability.max != 0)
					affixModifiers[std::make_pair(AttributeDurabilityMaxID, AttributeNoneSubID)][0] = durability;
				if (damageMin.max != 0)
					affixModifiers[std::make_pair(AttributeDamageWeaponMinID, AttributePhysicalSubID)][0] = damageMin;
				if (damageDelta.max != 0)
					affixModifiers[std::make_pair(AttributeDamageWeaponDeltaID, AttributePhysicalSubID)][0] = damageDelta;
				if (armor.max != 0)
					affixModifiers[std::make_pair(AttributeArmorItemID, AttributeNoneSubID)][0] = armor;
			}
			else
				itemHash = -1;
			
			sqlite3_finalize(stmt);
			sql.str(std::string());
			stmt = NULL;
		}
		
		sql << "SELECT modCode, modParam1, min, max FROM itemModifier WHERE itemHash = " << itemHash_;

		sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
			
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			AttributeID modCode = static_cast<AttributeID>(sqlite3_column_int(stmt, 0));
			AttributeSubID modParam = static_cast<AttributeSubID>(sqlite3_column_int(stmt, 1));
			Range value = Range(sqlite3_column_double(stmt, 2), sqlite3_column_double(stmt, 3));
			if (value.min > value.max)
				std::swap(value.min, value.max);
			AttributeKey key = std::make_pair(modCode, modParam);
			itemModifiers[key] = value;
		}
		sqlite3_finalize(stmt);

		sql.str(std::string());
		sql << "SELECT modCode, modParam1, min, max, propertyType FROM affixModifier as a, affix as b, itemTypeAffix as c WHERE a.affixHash=b.affixHash and b.affixHash=c.affixHash and b.affixLevel <= "
			<< 63 << " and c.itemTypeHash in (" << itemTypes << ")";

		if (flags_ & LegendaryFlag) {
			sql << " UNION SELECT modCode, modParam1, min, max, propertyType FROM affixModifier as a, affix as b, legendaryItemTypeAffix  as c WHERE a.affixHash=b.affixHash and b.affixHash=c.affixHash and b.affixLevel <= "
				<< 63 << " and c.itemTypeHash in (" << itemTypes << ")";
		}

		stmt = NULL;
		sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
		std::cout << sql.str();
			
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			AttributeID modCode = static_cast<AttributeID>(sqlite3_column_int(stmt, 0));
			AttributeSubID modParam = static_cast<AttributeSubID>(sqlite3_column_int(stmt, 1));
			Range value = Range(sqlite3_column_double(stmt, 2), sqlite3_column_double(stmt, 3));
			if (value.min > value.max)
				std::swap(value.min, value.max);
			
			int propertyType = sqlite3_column_int(stmt, 4);
			AttributeKey key = std::make_pair(modCode, modParam);
			if (affixModifiers[key].find(propertyType) == affixModifiers[key].end())
				affixModifiers[key][propertyType] = value;
			else {
				Range& range = affixModifiers[key][propertyType];
				range.max = std::max(range.max, value.max);
				range.min = std::min(range.min, value.min);
			}
		}
		sqlite3_finalize(stmt);

		{
			std::map<AttributeKey, Range>::iterator i, end= itemModifiers.end();
			for (i = itemModifiers.begin(); i != end; i++) {
				possibleModifiers_[i->first] = i->second;
			}
		}

		{
			std::map<AttributeKey, std::map<int, Range> >::iterator i, end= affixModifiers.end();
			for (i = affixModifiers.begin(); i != end; i++) {
				std::map<int, Range>::iterator j, endj = i->second.end();
				for (j = i->second.begin(); j != endj; j++) {
					Range& value = j->second;
					if (possibleModifiers_.find(i->first) != possibleModifiers_.end()) {
						Range& range = possibleModifiers_[i->first];
						range.min = std::min(range.min, value.min);
						if (value.max > 0)
							range.max += value.max;
						if (value.min < 0)
							range.min += value.min;
					}
					else
						possibleModifiers_[i->first] = value;
				}
			}
		}
	}
	return possibleModifiers_;
}

Environment Item::environment() {
	Entity* hero = getParent();
	Entity* party = hero->getParent();
	return Environment(this, hero, party);
}
