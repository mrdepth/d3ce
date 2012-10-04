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

namespace d3ce {
	class Party;
	
	bool isValidHash(Hash hash);
	Hash hash(const std::string& string);

	class Engine {
	public:
		class SqliteException : public std::exception {};
		
		Engine(const char* databasePath);
		~Engine(void);
		
		sqlite3* getDb();
		
	private:
		sqlite3* db_;
		Party* party_;
	};
	
};

#endif /* defined(__d3ce__Engine__) */