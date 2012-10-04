//
//  Range.cpp
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Range.h"

using namespace d3ce;

Range::Range() : min(0), max(0) {
	
}

Range::Range(double value) : min(value), max(value) {
	
}

Range::Range(double min, double max) : min(min), max(max) {
	
}

Range Range::operator+(const Range& other) const {
	return Range(min + other.min, max + other.max);
}

Range Range::operator-(const Range& other) const {
	return Range(min - other.min, max - other.max);
}

Range Range::operator*(const Range& other) const {
	return Range(min * other.min, max * other.max);
}

Range Range::operator/(const Range& other) const {
	return Range(min / other.min, max / other.max);
}

bool Range::operator>(const Range& other) const {
	return min > other.min && max > other.max;
}

bool Range::operator<(const Range& other) const {
	return min < other.min && max < other.max;
}

bool Range::operator>=(const Range& other) const {
	return min >= other.min && max >= other.max;
}

bool Range::operator<=(const Range& other) const {
	return min <= other.min && max <= other.max;
}

bool Range::operator==(const Range& other) const {
	return min == other.min && max == other.max;
}

bool Range::operator!=(const Range& other) const {
	return min != other.min || max != other.max;
}

Range Range::operator()(double from) {
	return Range(from);
}