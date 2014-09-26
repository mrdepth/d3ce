#pragma once
#include "Entity.h"
#include <iterator>

namespace d3ce {

	template<typename T>
	class Aggregator: public Entity
	{
	public:
		Aggregator(std::shared_ptr<Engine> engine, const T& begin, const T& end) : Entity(engine), begin_(begin), end_(end) {};
		//virtual ~Aggregator();
		//void addEntity(std::shared_ptr<T> entity);
		//void removeEntity(std::shared_ptr<T> entity);
		virtual Attribute getAttribute(AttributeID attributeID, AttributeSubID attributeSubID = AttributeNoneSubID) const {
			Range value = 0;
			for (T item = begin_; item < end_; item++)
				value = value + (*item)->getAttribute(attributeID, attributeSubID);
			return Attribute(this, attributeID, attributeSubID, value);
		}
	private:
		T begin_;
		T end_;
	};

	template<typename T> Aggregator<T> MakeAggregator(std::shared_ptr<Engine> engine, const T& begin, const T& end) {
		return Aggregator<T>(engine, begin, end);
	}
}