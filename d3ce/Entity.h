//
//  Entity.h
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Entity__
#define __d3ce__Entity__

#include <vector>
#include <map>
#include <string>
#include "Engine.h"
#include "Attribute.h"
#include "Environment.h"
#include "types.h"


namespace d3ce {

	typedef std::pair<AttributeID, AttributeSubID> AttributeKey;
	typedef std::map<AttributeKey, Range> AttributesMap;

	class Entity {
	public:
		/*class AttributeWrapper {
		public:
			AttributeWrapper(Entity* entity, const Attribute& attribute) : attribute_(attribute) {}
			Attribute& operator=(const Range &value) { entity_->setAttribute(attribute_.getAttributeID(), attribute_.getAttributeSubID(), value);}
			Attribute& operator=(const Attribute &other) { entity_->setAttribute(attribute_.getAttributeID(), attribute_.getAttributeSubID(), other.value()); }
			operator Attribute() {return attribute_;}
			operator Range() {return attribute_.value();}
		private:
			Attribute attribute_;
			Entity* entity_;
		};*/

		class AttributeWrapper {
		public:
			AttributeWrapper(Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID = AttributeNoneSubID) : entity_(entity), attributeID_(attributeID), attributeSubID_(attributeSubID) {}
			
			AttributeWrapper operator[](AttributeSubID attributeSubID) const {
				return AttributeWrapper(entity_, attributeID_, attributeSubID);
			}

			operator Attribute() const {
				return entity_->getAttribute(attributeID_, attributeSubID_);
			}

			operator Range() const {
				return entity_->getAttribute(attributeID_, attributeSubID_);
			}

			AttributeWrapper& operator=(const Range& value) {
				entity_->setAttribute(attributeID_, attributeSubID_, value);
				return *this;
			}

			AttributeWrapper& operator=(const AttributeWrapper& other) {
				entity_->setAttribute(attributeID_, attributeSubID_, other);
				return *this;
			}

		private:
			Entity* entity_;
			AttributeID attributeID_;
			AttributeSubID attributeSubID_;
		};

		class ConstAttributeWrapper {
		public:
			ConstAttributeWrapper(const Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID = AttributeNoneSubID) : entity_(entity), attributeID_(attributeID), attributeSubID_(attributeSubID) {}

			ConstAttributeWrapper operator[](AttributeSubID attributeSubID) const {
				return ConstAttributeWrapper(entity_, attributeID_, attributeSubID);
			}

			operator Attribute() const {
				return entity_->getAttribute(attributeID_, attributeSubID_);
			}

			operator Range() const {
				return entity_->getAttribute(attributeID_, attributeSubID_);
			}
		private:
			const Entity* entity_;
			AttributeID attributeID_;
			AttributeSubID attributeSubID_;
		};

		virtual ~Entity();
		std::shared_ptr<Engine> getEngine() const;

		virtual Attribute getAttribute(AttributeID attributeID, AttributeSubID attributeSubID = AttributeNoneSubID) const;
		Attribute getAttribute(const std::string& nonNlsKey) const;
		Entity* getParent() const;
		
		AttributeWrapper operator[](AttributeKey& key);
		AttributeWrapper operator[](AttributeID attributeID);
		AttributeWrapper operator[](const std::string& nonNlsKey);

		ConstAttributeWrapper operator[](AttributeKey& key) const;
		ConstAttributeWrapper operator[](AttributeID attributeID) const;
		ConstAttributeWrapper operator[](const std::string& nonNlsKey) const;

		void setAttribute(AttributeID attributeID, AttributeSubID attributeSubID, const Range& value);
	protected:
		Entity(const Entity& other, Entity* parent);
		Entity(std::shared_ptr<Engine> engine, Entity* parent = NULL);
		
		std::shared_ptr<Engine> engine_;
		Entity* parent_;
		AttributesMap attributes_;
		AttributeKey getKey(const std::string& nonNlsKey) const;

	};
	
}
#endif /* defined(__d3ce__Entity__) */
