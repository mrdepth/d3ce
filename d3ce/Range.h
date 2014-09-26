//
//  Range.h
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Range__
#define __d3ce__Range__
#include <string>

namespace d3ce {
	
	class Range {
	public:
		Range();
		Range(double value);
		Range(double min, double max);
		/*Range operator+(const Range& other) const;
		Range operator-(const Range& other) const;
		Range operator*(const Range& other) const;
		Range operator/(const Range& other) const;
		bool operator>(const Range& other) const;
		bool operator<(const Range& other) const;
		bool operator>=(const Range& other) const;
		bool operator<=(const Range& other) const;
		bool operator==(const Range& other) const;
		bool operator!=(const Range& other) const;*/

		Range& operator+=(const Range& other);
		Range& operator-=(const Range& other);
		Range& operator*=(const Range& other);
		Range& operator/=(const Range& other);

		double min;
		double max;
		
		//operator bool();
		
		std::string toString(int precision = 0);
	};

	Range operator+(const Range& arg1, const Range& arg2);
	Range operator-(const Range& arg1, const Range& arg2);
	Range operator*(const Range& arg1, const Range& arg2);
	Range operator/(const Range& arg1, const Range& arg2);
	bool operator>(const Range& arg1, const Range& arg2);
	bool operator<(const Range& arg1, const Range& arg2);
	bool operator>=(const Range& arg1, const Range& arg2);
	bool operator<=(const Range& arg1, const Range& arg2);
	bool operator==(const Range& arg1, const Range& arg2);
	bool operator!=(const Range& arg1, const Range& arg2);

	Range pin(const Range& value, const Range& min, const Range& max);
	Range floor(const Range& value);
}

#endif /* defined(__d3ce__Range__) */
