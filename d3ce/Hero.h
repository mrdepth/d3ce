//
//  Hero.h
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Hero__
#define __d3ce__Hero__

#include "Entity.h"
#include "Item.h"
#include "Skill.h"
#include "Follower.h"
#include "Gear.h"
#include "ItemSet.h"

namespace d3ce {

	class Party;
	
	class Hero: public Entity {
	public:
		class SlotIsAlreadyFilledException : public std::exception {
		public:
			SlotIsAlreadyFilledException(Item::Slot slot) : slot(slot) {};
			Item::Slot slot;
		};

		virtual ~Hero();

		//virtual Attribute getAttribute(AttributeID attributeID, AttributeSubID attributeSubID = AttributeNoneSubID) const;

		std::shared_ptr<Gear> addItem(Hash itemHash);
		std::shared_ptr<Gear> addItem(const std::string& nonNlsKey);
		void removeItem(std::shared_ptr<Gear>);
		
		Skill* addSkill(const std::string& skillName);
		void removeSkill(Skill* skill);

		virtual ClassMask getClass() const = 0;
		
		std::shared_ptr<Gear> getItem(Item::Slot slot) const;
		const std::vector<std::shared_ptr<Gear>>& getItems() const;
		
		bool slotIsEmpty(Item::Slot slot) const;
		
		void setLevel(int level);
		void setParagonLevel(int level);
		int getLevel() const;
		int getParagonLevel() const;
		
		AttributeSubID getResourceTypePrimary() const;
		AttributeSubID getResourceTypeSecondary() const;
		
		//Stats
		Range getStrength() const;
		Range getDexterity() const;
		Range getIntelligence() const;
		Range getVitality() const;
		
		Resistance getResistances() const;
		Range getArmor() const;
		Range getDamageReductionFromArmor(int againstMosterLevel = -1) const;
		Resistance getDamageReductionFromResistances(int againstMosterLevel = -1) const;
		Range getAverageDamageReduction(int againstMosterLevel = -1) const;
		Range getBlockChance() const;
		Range getBlockAmmountMin() const;
		Range getBlockAmmountMax() const;
		Range getDodgeChance() const;
		
		Range getHitPoints() const;
		Range getEffectiveHitPoints() const;
		Range getLifeRegen() const;
		Range getLifePerHit() const;
		Range getLifePerKill() const;
		Range getLifeSteal() const;
		
		Range getDPS() const;
		Range getCritChance() const;
		Range getCritDamage() const;
		Range getAttackSpeed() const;
		Range getMaxDamage() const;
		Range getMinDamage() const;
		
		Range getMagicFind() const;
		Range getGoldFind() const;
		
		Range getPrimaryResourceEffectiveMax() const;
		Range getSecondaryResourceEffectiveMax() const;
		
		Range getPrimaryResourceRegen() const;
		Range getSecondaryResourceRegen() const;

		virtual Attribute getAttribute(AttributeID attributeID, AttributeSubID attributeSubID = AttributeNoneSubID) const;

	protected:
		virtual Environment environment();
		Hero(const Hero& other, Party* party);
		Hero(std::shared_ptr<Engine> engine, Party* party);

	private:
		std::vector<std::shared_ptr<Gear>> items_;
		std::vector<Skill*> skills_;
		std::vector<std::shared_ptr<ItemSet>> setBonuses_;
		Follower* follower_;

		std::shared_ptr<Gear> addItem(std::shared_ptr<Gear> item);
	};
}

#endif /* defined(__d3ce__Hero__) */
