//
//  Range.cpp
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Range.h"

using namespace d3ce;

Range d3ce::pin(const Range& value, const Range& min, const Range& max) {
	return value > max ? max : value < min ? min : value;
}

Range d3ce::floor(const Range& value) {
	return Range(::floor(value.min), ::floor(value.max));
}

Range::Range() : min(0), max(0) {
	
}

Range::Range(double value) : min(value), max(value) {
	
}

Range::Range(double min, double max) : min(min), max(max) {
	
}

/*Range Range::operator+(const Range& other) const {
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
}*/

Range& Range::operator+=(const Range& other) {
	min += other.min;
	max += other.max;
	return *this;
}

Range& Range::operator-=(const Range& other) {
	min -= other.min;
	max -= other.max;
	return *this;
}

Range& Range::operator*=(const Range& other) {
	min *= other.min;
	max *= other.max;
	return *this;
}

Range& Range::operator/=(const Range& other) {
	min /= other.min;
	max /= other.max;
	return *this;
}

Range d3ce::operator+(const Range& arg1, const Range& arg2) {
	return Range(arg1.min + arg2.min, arg1.max + arg2.max);
}

Range d3ce::operator-(const Range& arg1, const Range& arg2) {
	return Range(arg1.min - arg2.min, arg1.max - arg2.max);
}

Range d3ce::operator*(const Range& arg1, const Range& arg2) {
	return Range(arg1.min * arg2.min, arg1.max * arg2.max);
}

Range d3ce::operator/(const Range& arg1, const Range& arg2) {
	return Range(arg1.min / arg2.min, arg1.max / arg2.max);
}

bool d3ce::operator>(const Range& arg1, const Range& arg2) {
	return arg1.min > arg2.min && arg1.max > arg2.max;
}

bool d3ce::operator<(const Range& arg1, const Range& arg2) {
	return arg1.min < arg2.min && arg1.max < arg2.max;
}

bool d3ce::operator>=(const Range& arg1, const Range& arg2) {
	return arg1.min >= arg2.min && arg1.max >= arg2.max;
}

bool d3ce::operator<=(const Range& arg1, const Range& arg2) {
	return arg1.min >= arg2.min && arg1.max >= arg2.max;
}

bool d3ce::operator==(const Range& arg1, const Range& arg2) {
	return arg1.min == arg2.min && arg1.max == arg2.max;
}

bool d3ce::operator!=(const Range& arg1, const Range& arg2) {
	return arg1.min != arg2.min && arg1.max != arg2.max;
}


/*Range::operator bool() {
	return min != 0 && max != 0;
}*/

std::string Range::toString(int precision) {
	char format[16];
	sprintf(format, "%%.%df", precision);
	
	char string[16];
	sprintf(string, format, max);
	return string;
}
