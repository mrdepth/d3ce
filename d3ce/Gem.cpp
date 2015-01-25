//
//  Gem.cpp
//  d3ce
//
//  Created by Artem Shimanski on 28.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Gem.h"
#include <sstream>

using namespace d3ce;

Gem::Gem(std::shared_ptr<Engine> engine, Item* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, int flags, int bitMask, Slot possibleSlots) : Item(engine, parent, itemHash, itemTypesTree, flags, bitMask, possibleSlots) {
	const std::vector<Hash>& parentItemTypesTree = parent->itemTypesTree();
	std::vector<Hash>::const_iterator i, end = parentItemTypesTree.end();
	
	sqlite3* db = engine->getDb();
	std::stringstream sql;
	sql << "SELECT socketedEffectHash, itemTypeHash from socketedEffect where itemHash=" << itemHash << " AND itemTypeHash <> 109305";
	
	sqlite3_stmt* stmt = NULL;
	sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
	
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		Hash socketedEffectHash = sqlite3_column_int(stmt, 0);
		Hash itemTypeHash = sqlite3_column_int(stmt, 1);
		
		for (i = parentItemTypesTree.begin(); i != end; i++) {
			if (*i == itemTypeHash) {
				sqlite3_finalize(stmt);
				sql.str(std::string());
				
				sql << "SELECT modCode, modParam1, min, max FROM socketedEffectModifier where socketedEffectHash=" << socketedEffectHash;
				sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
				
				while (sqlite3_step(stmt) == SQLITE_ROW) {
					AttributeID modCode = static_cast<AttributeID>(sqlite3_column_int(stmt, 0));
					AttributeSubID param = static_cast<AttributeSubID>(sqlite3_column_int(stmt, 1));
					Range value;
					value.min = sqlite3_column_double(stmt, 2);
					value.max = sqlite3_column_double(stmt, 3);
					setAttribute(modCode, param, value);
				}
				
				sqlite3_finalize(stmt);
				return;
			}
		}
	}
	sqlite3_finalize(stmt);
	
	sql.str(std::string());
	
	sql << "SELECT socketedEffectHash from socketedEffect where itemHash=" << itemHash << " AND itemTypeHash=109305";
	sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
	
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		Hash socketedEffectHash = sqlite3_column_int(stmt, 0);
		
		for (i = parentItemTypesTree.begin(); i != end; i++) {
			sqlite3_finalize(stmt);
			sql.str(std::string());
			
			sql << "SELECT modCode, modParam1, min, max FROM socketedEffectModifier where socketedEffectHash=" << socketedEffectHash;
			sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
			
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				AttributeID modCode = static_cast<AttributeID>(sqlite3_column_int(stmt, 0));
				AttributeSubID param = static_cast<AttributeSubID>(sqlite3_column_int(stmt, 1));
				Range value;
				value.min = sqlite3_column_double(stmt, 2);
				value.max = sqlite3_column_double(stmt, 3);
				setAttribute(modCode, param, value);
			}
			
			sqlite3_finalize(stmt);
			return;
		}
	}
	sqlite3_finalize(stmt);
}

Gem::Gem(const Gem& other, Entity* parent) : Item(other, parent) {
	//copyAttributes(other);
}

Entity* Gem::cloneIn(Entity* parent) {
	return new Gem(*this, parent);
}

Environment Gem::environment() {
	Entity* hero = parent_->getParent();
	return Environment(parent_, hero, hero->getParent());
}