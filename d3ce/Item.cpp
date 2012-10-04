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

using namespace d3ce;

Item* Item::CreateItem(Engine* engine, Entity* parent, Hash itemHash) {
	std::stringstream sql;
	sql << "SELECT itemHash, nonNlsKey, itemTypeHash, itemSetBonusHash FROM item where itemHash =  " << itemHash;
	return CreateItemFromRequest(engine, parent, sql.str());
}

Item* Item::CreateItem(Engine* engine, Entity* parent, const std::string& nonNlsKey) {
	std::stringstream sql;
	sql << "SELECT itemHash, nonNlsKey, itemTypeHash, itemSetBonusHash FROM item where nonNlsKey =  \"" << nonNlsKey << "\"";
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
		sqlite3_finalize(stmt);
		
		
		std::stringstream sql;
		sql << "SELECT nonNlsKey, parentItemTypeHash, flags, slot1, slot2, slot3, slot4, bitMask1 FROM itemType where itemTypeHash = " << itemTypeHash;
		
		stmt = NULL;
		sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW)
		{
			std::string itemTypeName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
			Hash parentItemTypeHash = sqlite3_column_int(stmt, 1);
			int flags = sqlite3_column_int(stmt, 2);
			int slots[] = {sqlite3_column_int(stmt, 3), sqlite3_column_int(stmt, 4), sqlite3_column_int(stmt, 5), sqlite3_column_int(stmt, 6)};
			int bitMask = sqlite3_column_int(stmt, 7);
			
			std::vector<Hash> itemTypesTree;
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

Item::Item(const Item& other, Entity* parent) : Entity(other, parent), itemTypesTree_(other.itemTypesTree_), possibleSlots_(other.possibleSlots_) {
	slot_ = other.slot_;
	itemHash_ = other.itemHash_;
	flags_ = other.flags_;
	bitMask_ = other.bitMask_;
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

Environment Item::environment() {
	Entity* hero = getParent();
	Entity* party = hero->getParent();
	return Environment(this, hero, party);
}
