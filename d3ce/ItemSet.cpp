//
//  ItemSet.cpp
//  d3ce
//
//  Created by mr_depth on 30.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "ItemSet.h"
#include <sstream>
#include <algorithm>

using namespace d3ce;

ItemSet::ItemSet(Engine* engine, Entity* parent, Hash setBonusHash) : Entity(engine, parent) {
	sqlite3* db = engine->getDb();
	std::stringstream sql;
	sql << "SELECT itemSetBonusHash, numOfSet FROM itemSetBonus WHERE parentHash=" << setBonusHash;
	
	sqlite3_stmt* stmt = NULL;
	sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
	
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		Bonus bonus;
		bonus.setBonusHash = sqlite3_column_int(stmt, 0);
		bonus.numOfSet = sqlite3_column_int(stmt, 1);
		if (bonus.numOfSet > 0)
			bonuses_.push_back(bonus);
	}
	sqlite3_finalize(stmt);
}

ItemSet::ItemSet(const ItemSet& other, Entity* parent) : Entity(other, parent) {
	std::vector<SetBonus*>::iterator i, end = setBonuses_.end();
	for (i = setBonuses_.begin(); i != end; i++)
		delete *i;
}

ItemSet::~ItemSet() {
	
}

Entity* ItemSet::cloneIn(Entity* parent) {
	return new ItemSet(*this, parent);
}

void ItemSet::addItem(Gear* item) {
	items_.push_back(item);
	update();
}

void ItemSet::removeItem(Gear* item) {
	items_.erase(std::remove(items_.begin(), items_.end(), item));
	update();
}

void ItemSet::update() {
	size_t numOfSet = items_.size();
	
	{
		std::vector<SetBonus*>::iterator i, end = setBonuses_.end();
		for (i = setBonuses_.begin(); i != end; i++) {
			if ((*i)->numOfSet() > numOfSet) {
				delete *i;
				setBonuses_.erase(i);
			}
		}
	}
	
	std::vector<Bonus>::iterator i, end = bonuses_.end();
	for (i = bonuses_.begin(); i != end; i++) {
		if (i->numOfSet <= numOfSet) {
			std::vector<SetBonus*>::iterator j, endj = setBonuses_.end();
			bool find = false;
			for (j = setBonuses_.begin(); j != endj; j++) {
				if ((*j)->setBonusHash() == i->setBonusHash) {
					find = true;
					break;
				}
			}
			if (!find)
				setBonuses_.push_back(new SetBonus(engine_, parent_, i->setBonusHash, setBonusHash_, i->numOfSet));
		}
	}
}

Environment ItemSet::environment() {
	Entity* hero = this->getParent();
	return Environment(this, hero, hero->getParent());
}