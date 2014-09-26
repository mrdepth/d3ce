//
//  SetBonus.cpp
//  d3ce
//
//  Created by mr_depth on 30.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "SetBonus.h"
#include <sstream>

using namespace d3ce;

SetBonus::SetBonus(std::shared_ptr<Engine> engine, Entity* parent, Hash setBonusHash, Hash parentHash, int numOfSet) : Entity(engine, parent), setBonusHash_(setBonusHash), parentHash_(parentHash), numOfSet_(numOfSet){
	sqlite3* db = engine->getDb();
	std::stringstream sql;
	sql << "SELECT modCode, modParam1, min, max FROM itemSetBonusModifier WHERE itemSetBonusHash=" << setBonusHash;
	
	sqlite3_stmt* stmt = NULL;
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
}

SetBonus::SetBonus(const SetBonus& other, Entity* parent) : Entity(other, parent) {
	numOfSet_ = other.numOfSet_;
	setBonusHash_ = other.setBonusHash_;
	parentHash_ = other.parentHash_;
}

Entity* SetBonus::cloneIn(Entity* parent) {
	return new SetBonus(*this, parent);
}

int SetBonus::numOfSet() {
	return numOfSet_;
}

Hash SetBonus::setBonusHash() {
	return setBonusHash_;
}

Environment SetBonus::environment() {
	Entity* hero = getParent();
	return Environment(this, hero, hero->getParent());
}