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
#include "Modifier.h"
#include "Environment.h"
#include "types.h"

namespace d3ce {
	
	typedef std::pair<AttributeID, AttributeSubID> AttributeKey;
	typedef std::map<AttributeKey, Attribute*> AttributesMap;

	class Entity {
	public:
		class AttributeContainer {
		public:
			AttributeContainer(Entity* entity, AttributeID attributeID) : entity_(entity), attributeID_(attributeID) {}
			
			Attribute* operator[](AttributeSubID attributeSubID) {
				return entity_->getAttribute(attributeID_, attributeSubID);
			}
			
			Attribute* operator->() {
				return entity_->getAttribute(attributeID_);
			}
			
			Attribute& operator*() {
				return *entity_->getAttribute(attributeID_);
			}
		private:
			Entity* entity_;
			AttributeID attributeID_;
		};
		
		virtual ~Entity();
		virtual Entity* cloneIn(Entity* parent) = 0;

		void addModifier(Modifier* modifier);
		void removeModifier(Modifier* modifier);
		Attribute* getAttribute(AttributeID attributeID, AttributeSubID attributeSubID = AttributeNoneSubID);
		Attribute* getAttribute(const std::string& nonNlsKey);
		std::vector<Modifier*> getAttributeModifiers(Attribute* attribute);
		Entity* getParent();
		
		Attribute* operator[](AttributeKey& key);
		AttributeContainer operator[](AttributeID attributeID);
		Attribute* operator[](const std::string& nonNlsKey);
	protected:
		Entity(const Entity& other, Entity* parent);
		Entity(Engine* engine, Entity* parent = NULL);
		
		Engine* engine_;
		Entity* parent_;
		AttributesMap attributes_;
		std::vector<Modifier*> modifiers_;

		virtual Environment environment() = 0;
		void copyAttributes(const Entity& other);
	};
	
}
#endif /* defined(__d3ce__Entity__) */
