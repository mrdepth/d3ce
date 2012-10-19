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
		sql << "SELECT modCode, modParam1, min, max FROM itemModifier WHERE itemHash = " << itemHash_;
		requests.push_back(sql.str());
		
		sql.str(std::string());
		sql << "SELECT modCode, modParam1, min, max FROM affixModifier as a, affix as b, affixGroupAssociation as c, itemAffix as d, itemTypeAffix as e where a.affixHash=c.affixHash and c.affixGroupHash=d.affixGroupHash and b.affixHash=c.affixHash and b.affixLevel=d.affixLevel and e.affixHash=c.affixHash and e.itemTypeHash in ("
			<< itemTypes << ") and d.itemHash = " << itemHash_;
//		sql << "SELECT modCode, modParam1, min, max FROM affixModifier as a, affix as b, affixGroupAssociation as c, itemAffix as d where a.affixHash=c.affixHash and c.affixGroupHash=d.affixGroupHash and b.affixHash=c.affixHash and b.affixLevel=d.affixLevel and d.itemHash=" << itemHash_;
		requests.push_back(sql.str());

		if (flags_ & LegendaryFlag) {
			sql.str(std::string());
			sql << "SELECT modCode, modParam1, min, max FROM affixModifier as a, affix as b, affixGroupAssociation as c, itemAffix as d, legendaryItemTypeAffix as e where a.affixHash=c.affixHash and c.affixGroupHash=d.affixGroupHash and b.affixHash=c.affixHash and b.affixLevel=d.affixLevel and e.affixHash=c.affixHash and e.itemTypeHash in ("
			<< itemTypes << ") and d.itemHash = " << itemHash_;
			requests.push_back(sql.str());
		}

		sql.str(std::string());
		sql << "SELECT modCode, modParam1, min, max FROM affixModifier as a, affixGroupAssociation as b, itemType as c, affix as d where a.affixHash=b.affixHash and b.affixGroupHash=c.inherentAffixGroupHash and d.affixHash = b.affixHash and d.affixLevel <= "
		<< itemLevel_ << " and c.itemTypeHash in (" << itemTypes << ");";
		requests.push_back(sql.str());
		
		sql.str(std::string());
		sql << "SELECT modCode, modParam1, min, max FROM affixModifier as a, itemTypeAffix as b, affix as c where a.affixHash=b.affixHash and c.affixHash = b.affixHash and c.affixLevel <= "
		<< itemLevel_ << " and b.itemTypeHash in (" << itemTypes << ");";
		requests.push_back(sql.str());
		
		if (flags_ & LegendaryFlag) {
			sql.str(std::string());
			sql << "SELECT modCode, modParam1, min, max FROM affixModifier as a, legendaryItemTypeAffix as b, affix as c where a.affixHash=b.affixHash and c.affixHash = b.affixHash and c.affixLevel <= "
			<< itemLevel_ << " and b.itemTypeHash in (" << itemTypes << ");";
			requests.push_back(sql.str());
		}
		
		std::vector<std::string>::iterator j, endj = requests.end();
		for (j = requests.begin(); j != endj; j++) {
			sqlite3_stmt* stmt = NULL;
			sqlite3_prepare_v2(db, j->c_str(), -1, &stmt, NULL);
			
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				AttributeID modCode = static_cast<AttributeID>(sqlite3_column_int(stmt, 0));
				AttributeSubID modParam = static_cast<AttributeSubID>(sqlite3_column_int(stmt, 1));
				Range value = Range(sqlite3_column_double(stmt, 2), sqlite3_column_double(stmt, 3));
				AttributeKey key = std::make_pair(modCode, modParam);
				Range& range = possibleModifiers_[key];
				range.max = fabs(value.max) > fabs(range.max) ? value.max : range.max;
				range.min = fabs(value.min) < fabs(range.min) ? value.min : range.min;
			}
			sqlite3_finalize(stmt);
		}
	}
	return possibleModifiers_;
}

Environment Item::environment() {
	Entity* hero = getParent();
	Entity* party = hero->getParent();
	return Environment(this, hero, party);
}
