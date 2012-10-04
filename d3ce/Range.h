//
//  Range.h
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Range__
#define __d3ce__Range__

namespace d3ce {
	
	class Range {
	public:
		Range();
		Range(double value);
		Range(double min, double max);
		Range operator+(const Range& other) const;
		Range operator-(const Range& other) const;
		Range operator*(const Range& other) const;
		Range operator/(const Range& other) const;
		bool operator>(const Range& other) const;
		bool operator<(const Range& other) const;
		bool operator>=(const Range& other) const;
		bool operator<=(const Range& other) const;
		bool operator==(const Range& other) const;
		bool operator!=(const Range& other) const;
		
		double min;
		double max;
		
		Range operator()(double from);

		Range value() {
			return *this;
		};
	};
}

#endif /* defined(__d3ce__Range__) */