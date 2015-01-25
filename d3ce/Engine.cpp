//
//  Engine.cpp
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Engine.h"
#include "Party.h"

using namespace d3ce;

std::shared_ptr<Engine> Engine::Create(const char* databasePath) {
	std::shared_ptr<Engine> ptr(new Engine(databasePath));
	return ptr;
}

bool d3ce::isValidHash(Hash hash) {
	return hash != -1 && hash != 0;
}

Hash d3ce::hash(const std::string& string) {
	Hash hash = 0;
	size_t n = string.size();
	const char* s = string.c_str();
	for (int i = 0; i < n; i++)
		hash = (hash * 0x21) + tolower(s[i]);
	return hash;
}

Engine::Engine(const char* databasePath) {
	int result = sqlite3_open(databasePath, &db_);
	if (result != SQLITE_OK)
		throw SqliteException();
}

Engine::~Engine(void) {
}

sqlite3* Engine::getDb() {
	return db_;
}

void Engine::exec(const std::string sql, std::function<bool (sqlite3_stmt* stmt)> callback) {
	sqlite3_stmt* stmt = NULL;
	sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, NULL);
	if (stmt) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			if (callback && !callback(stmt))
				break;
		}
		sqlite3_finalize(stmt);
	}
}