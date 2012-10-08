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
		class SlotIsAlreadyFilledException : public std::exception {};

		virtual ~Hero();
		
		Gear* addItem(Hash itemHash);
		Gear* addItem(const std::string& nonNlsKey);
		void removeItem(Gear* item);
		
		Skill* addSkill(const std::string& skillName);
		void removeSkill(Skill* skill);

		virtual ClassMask getClass() = 0;
		
		Gear* getItem(Item::Slot slot);
		std::vector<Gear*> getItems();
		
		bool slotIsEmpty(Item::Slot slot);
		
		void setLevel(int level);
		void setParagonLevel(int level);
		int getLevel();
		int getParagonLevel();
		
		AttributeSubID getResourceTypePrimary();
		AttributeSubID getResourceTypeSecondary();
		
		//Stats
		Range getStrength();
		Range getDexterity();
		Range getIntelligence();
		Range getVitality();
		
		Resistance getResistances();
		Range getArmor();
		Range getDamageReductionFromArmor(int againstMosterLevel = -1);
		Resistance getDamageReductionFromResistances(int againstMosterLevel = -1);
		Range getAverageDamageReduction(int againstMosterLevel = -1);
		Range getBlockChance();
		Range getBlockAmmountMin();
		Range getBlockAmmountMax();
		Range getDodgeChance();
		
		Range getHitPoints();
		Range getLifeRegen();
		Range getLifePerHit();
		Range getLifePerKill();
		Range getLifeSteal();
		
		Range getDPS();
		Range getCritChance();
		Range getCritDamage();
		Range getAttackSpeed();
		Range getMaxDamage();
		Range getMinDamage();
		
		Range getMagicFind();
		Range getGoldFind();
		
		Range getPrimaryResourceEffectiveMax();
		Range getSecondaryResourceEffectiveMax();
		
		Range getPrimaryResourceRegen();
		Range getSecondaryResourceRegen();
	protected:
		virtual Environment environment();
		Hero(const Hero& other, Party* party);
		Hero(Engine* engine, Party* party);

	private:
		std::vector<Gear*> items_;
		std::vector<Skill*> skills_;
		std::map<Hash, ItemSet*> setBonuses_;
		Follower* follower_;

		Gear* addItem(Gear* item);
	};
}

#endif /* defined(__d3ce__Hero__) */
