//
//  Expression.h
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Expression__
#define __d3ce__Expression__

#include "Range.h"
#include "Attribute.h"
#include "Hero.h"

namespace d3ce {
	class Expression {
	public:
		virtual ~Expression() {};
		virtual Range value() = 0;
	};

	template<typename T> class Value : public Expression {
	public:
		Value(const T& value) : value_(value) {};
		virtual Range value() {
			return value_.value();
		}
		const T& rep() const {
			return value_;
		}
		T rep() {
			return value_;
		}
	private:
		T value_;
	};

	class AttributeWrapper {
	public:
		AttributeWrapper(Attribute& attribute) : attribute_(attribute) {};
		AttributeWrapper(const AttributeWrapper& other) : attribute_(other.attribute_) {};
		Range value() {
			return attribute_.value();
		}
	private:
		Attribute& attribute_;
	};

	/*template<> class Value<AttributeWrapper> : public Expression {
	public:
		Value(Attribute& value) : value_(value) {};
		virtual Range value() {
			return value_.value();
		}
		Attribute& rep() {
			return value_;
		}
	private:
		Attribute& value_;
	};*/

	template<typename T1, typename T2> class ExpressionAdd {
	public:
		ExpressionAdd(const T1& arg1, const T2& arg2) : arg1_(arg1), arg2_(arg2) {};
		Range value() {
			return arg1_.value() + arg2_.value();
		}
	private:
		T1 arg1_;
		T2 arg2_;
	};

	template<typename T1, typename T2> class ExpressionSub {
	public:
		ExpressionSub(const T1& arg1, const T2& arg2) : arg1_(arg1), arg2_(arg2) {};
		Range value() {
			return arg1_.value() - arg2_.value();
		}
	private:
		T1 arg1_;
		T2 arg2_;
	};

	template<typename T1, typename T2> class ExpressionMul {
	public:
		ExpressionMul(const T1& arg1, const T2& arg2) : arg1_(arg1), arg2_(arg2) {};
		Range value() {
			return arg1_.value() * arg2_.value();
		}
	private:
		T1 arg1_;
		T2 arg2_;
	};

	template<typename T1, typename T2> class ExpressionDiv {
	public:
		ExpressionDiv(const T1& arg1, const T2& arg2) : arg1_(arg1), arg2_(arg2) {};
		Range value() {
			return arg1_.value() / arg2_.value();
		}
	private:
		T1 arg1_;
		T2 arg2_;
	};

	template<typename T1, typename T2> class ExpressionMax {
	public:
		ExpressionMax(const T1& arg1, const T2& arg2) : arg1_(arg1), arg2_(arg2) {};
		Range value() {
			Range a = arg1_.value();
			Range b = arg2_.value();
			return Range(std::max(a.min, b.min), std::max(a.max, b.max));
		}
	private:
		T1 arg1_;
		T2 arg2_;
	};

	template<typename T1, typename T2> class ExpressionMin {
	public:
		ExpressionMin(const T1& arg1, const T2& arg2) : arg1_(arg1), arg2_(arg2) {};
		Range value() {
			Range a = arg1_.value();
			Range b = arg2_.value();
			return Range(std::min(a.min, b.min), std::min(a.max, b.max));
		}
	private:
		T1 arg1_;
		T2 arg2_;
	};

	template<typename T1, typename T2> class ExpressionEq {
	public:
		ExpressionEq(const T1& arg1, const T2& arg2) : arg1_(arg1), arg2_(arg2) {};
		Range value() {
			return arg1_.value() == arg2_.value();
		}
	private:
		T1 arg1_;
		T2 arg2_;
	};

	template<typename T1, typename T2, typename T3> class ExpressionIf {
	public:
		ExpressionIf(const T1& condition, const T2& thenValue, const T3& elseValue) : condition_(condition), thenValue_(thenValue), elseValue_(elseValue) {};
		Range value() {
			return condition_.value().min ? thenValue_.value() : elseValue_.value();
		}
	private:
		T1 condition_;
		T2 thenValue_;
		T3 elseValue_;
	};

	template<typename T> class ExpressionSlotConformsTo {
	public:
		ExpressionSlotConformsTo(Hero* hero, Item::Slot slot, const T& itemType) : hero_(hero), slot_(slot), itemType_(itemType) {};
		Range value() {
			Item* item = hero_->getItem(slot_);
			if (item)
				return item->conforms(static_cast<Hash>(itemType_.value().min));
			else
				return false;
		}
	private:
		Hero* hero_;
		Item::Slot slot_;
		T itemType_;
	};

	template<typename T1, typename T2> Value<ExpressionAdd<T1, T2> > operator+(const Value<T1>& arg1, const Value<T2>& arg2) {
		return Value<ExpressionAdd<T1, T2> > (ExpressionAdd<T1, T2>(arg1.rep(), arg2.rep()));
	}

	template<typename T1, typename T2> Value<ExpressionSub<T1, T2> > operator-(const Value<T1>& arg1, const Value<T2>& arg2) {
		return Value<ExpressionSub<T1, T2> > (ExpressionSub<T1, T2>(arg1.rep(), arg2.rep()));
	}

	template<typename T1, typename T2> Value<ExpressionMul<T1, T2> > operator*(const Value<T1>& arg1, const Value<T2>& arg2) {
		return Value<ExpressionMul<T1, T2> > (ExpressionMul<T1, T2>(arg1.rep(), arg2.rep()));
	}

	template<typename T1, typename T2> Value<ExpressionDiv<T1, T2> > operator/(const Value<T1>& arg1, const Value<T2>& arg2) {
		return Value<ExpressionDiv<T1, T2> > (ExpressionDiv<T1, T2>(arg1.rep(), arg2.rep()));
	}

	template<typename T1, typename T2> Value<ExpressionEq<T1, T2> > operator==(const Value<T1>& arg1, const Value<T2>& arg2) {
		return Value<ExpressionEq<T1, T2> > (ExpressionEq<T1, T2>(arg1.rep(), arg2.rep()));
	}

}
#endif /* defined(__d3ce__Expression__) */
