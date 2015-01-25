//
//  Engine.h
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Engine__
#define __d3ce__Engine__

#ifdef WIN32
#include "ThirdParty/sqlite3.h"
#else
#include <sqlite3.h>
#endif
#include <exception>
#include "types.h"
#include <string>
#include <memory>
#include <functional>

namespace d3ce {
	class Party;
	
	bool isValidHash(Hash hash);
	Hash hash(const std::string& string);

	class Engine {
	public:
		class SqliteException : public std::exception {};
		static std::shared_ptr<Engine> Create(const char* databasePath);
		~Engine(void);
		
		sqlite3* getDb();
		
		void exec(const std::string sql, std::function<bool (sqlite3_stmt* stmt)> callback);
		
	private:
		sqlite3* db_;
		Engine(const char* databasePath);
	};
	
};

#endif /* defined(__d3ce__Engine__) */