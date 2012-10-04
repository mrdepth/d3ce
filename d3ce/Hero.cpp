//
//  Hero.cpp
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Hero.h"
#include "Party.h"
#include <algorithm>

using namespace d3ce;

Hero::Hero(Engine* engine, Party* party) : Entity(engine, party) {
}

Hero::~Hero() {
	std::vector<Gear*>::iterator i, end = items_.end();
	for (i = items_.begin(); i != end; i++) {
		delete *i;
	}
}

Hero::Hero(const Hero& other, Party* party) : Entity(other, party) {
	copyAttributes(other);
	std::vector<Gear*>::const_iterator i, end = other.items_.end();
	for (i = other.items_.begin(); i != end; i++) {
		Gear* item = dynamic_cast<Gear*>((*i)->cloneIn(this));
		addItem(item);
		item->setSlot((*i)->getSlot());
	}

	std::vector<Skill*>::const_iterator j, endj = other.skills_.end();
	for (j = other.skills_.begin(); j != endj; j++) {
		skills_.push_back(dynamic_cast<Skill*>((*j)->cloneIn(this)));
	}
}

Gear* Hero::addItem(Hash itemHash) {
	return addItem(dynamic_cast<Gear*>(Item::CreateItem(engine_, this, itemHash)));
}

Gear* Hero::addItem(const std::string& nonNlsKey) {
	return addItem(dynamic_cast<Gear*>(Item::CreateItem(engine_, this, nonNlsKey)));
}

Gear* Hero::addItem(Gear* item) {
	if (!item)
		return item;
	
	if (item->twoHanded() && (!slotIsEmpty(Item::SlotMainHand) || !(slotIsEmpty(Item::SlotOffHand)))) {
		throw SlotIsAlreadyFilledException();
	}
	
	std::vector<Item::Slot>::const_iterator i, end = item->possibleSlots().end();
	
	for (i = item->possibleSlots().begin(); i != end; i++) {
		std::vector<Gear*>::iterator j, endj = items_.end();
		bool isEmpty = true;
		for (j = items_.begin(); j != endj; j++) {
			if ((*j)->getSlot() == *i) {
				isEmpty = false;
				break;
			}
		}
		if (isEmpty) {
			item->setSlot(*i);
			items_.push_back(item);
			
			Hash itemSetBonusHash = item->itemSetBonusHash();
			if (isValidHash(itemSetBonusHash)) {
				std::map<Hash, ItemSet*>::iterator itemSetIterator = setBonuses_.find(itemSetBonusHash);
				ItemSet* itemSet;
				if (itemSetIterator == setBonuses_.end())
					setBonuses_[itemSetBonusHash] = itemSet = new ItemSet(engine_, this, itemSetBonusHash);
				else
					itemSet = itemSetIterator->second;
				itemSet->addItem(item);
			}
			
			return item;
		}
		else {
			continue;
		}
	}
	delete item;
	throw SlotIsAlreadyFilledException();
}

void Hero::removeItem(Gear* item) {
	items_.erase(std::remove(items_.begin(), items_.end(), item));
	
	Hash itemSetBonusHash = item->itemSetBonusHash();
	if (isValidHash(itemSetBonusHash)) {
		std::map<Hash, ItemSet*>::iterator itemSetIterator = setBonuses_.find(itemSetBonusHash);
		if (itemSetIterator != setBonuses_.end())
			itemSetIterator->second->removeItem(item);
	}

	delete item;
}

Skill* Hero::addSkill(const std::string& skillName) {
	Skill* skill = new Skill(engine_, this, skillName);
	skills_.push_back(skill);
	return skill;
}

void Hero::removeSkill(Skill* skill) {
	skills_.erase(std::remove(skills_.begin(), skills_.end(), skill));
	delete skill;
}


Gear* Hero::getItem(Item::Slot slot) {
	std::vector<Gear*>::iterator i, end = items_.end();
	for (i = items_.begin(); i != end; i++)
		if ((*i)->getSlot() == slot)
			return *i;
	return NULL;
}

std::vector<Gear*> Hero::getItems() {
	return items_;
}

bool Hero::slotIsEmpty(Item::Slot slot) {
	bool isEmpty = getItem(slot) == NULL;
	if (slot == Item::SlotOffHand && isEmpty) {
		Gear* mainHand = getItem(Item::SlotMainHand);
		if (mainHand && mainHand->twoHanded())
			return false;
		else
			return true;
	}
	else
		return isEmpty;
}

Environment Hero::environment() {
	return Environment(this, this, getParent());
}

void Hero::setLevel(int level) {
	getAttribute(AttributeLevelID)->setValue(level);
}

void Hero::setParagonLevel(int level) {
	getAttribute(AttributeAltLevelID)->setValue(level);
}

int Hero::getLevel() {
	return getAttribute(AttributeLevelID)->value().max;
}

int Hero::getParagonLevel() {
	return getAttribute(AttributeAltLevelID)->value().max;
}

//Stats
Range Hero::getStrength() {
	return getAttribute(AttributeStrengthTotalID)->value();
}

Range Hero::getDexterity() {
	return getAttribute(AttributeDexterityTotalID)->value();
}

Range Hero::getIntelligence() {
	return getAttribute(AttributeIntelligenceTotalID)->value();
}

Range Hero::getVitality() {
	return getAttribute(AttributeVitalityTotalID)->value();
}

Resistance Hero::getResistances() {
	Resistance resistances;
	resistances.physical = getAttribute(AttributeResistanceTotalID, AttributePhysicalSubID)->value();
	resistances.fire = getAttribute(AttributeResistanceTotalID, AttributeFireSubID)->value();
	resistances.lightning = getAttribute(AttributeResistanceTotalID, AttributeLightningSubID)->value();
	resistances.cold = getAttribute(AttributeResistanceTotalID, AttributeColdSubID)->value();
	resistances.poison = getAttribute(AttributeResistanceTotalID, AttributePoisonSubID)->value();
	resistances.arcane = getAttribute(AttributeResistanceTotalID, AttributeArcaneSubID)->value();
	resistances.holy = getAttribute(AttributeResistanceTotalID, AttributeHolySubID)->value();
	return resistances;
}

Range Hero::getArmor() {
	return getAttribute(AttributeArmorTotalID)->value();
}

Range Hero::getDamageReductionFromArmor(int againstMosterLevel) {
	if (againstMosterLevel < 0)
		againstMosterLevel = getLevel();

	Range armor = getArmor();
	return armor / (armor + 50.0 * againstMosterLevel);
}

Range Hero::getAverageDamageReduction(int againstMosterLevel) {
	if (againstMosterLevel < 0)
		againstMosterLevel = getLevel();
	
	Resistance resistances = getResistances();
	Range averageResistance = (resistances.physical + resistances.fire + resistances.lightning + resistances.cold + resistances.poison + resistances.arcane) / 6;
	Range damageReductionFromResistance = averageResistance / (averageResistance + 5 * againstMosterLevel);
	Range damageReductionFromArmor = getDamageReductionFromArmor();
	Range classDamageReduction = getAttribute(AttributeClassDamageReductionPercentID)->value();

	Range damageReductionPhysical = getAttribute(AttributeDamageReductionTotalID, AttributePhysicalSubID)->value();
	Range damageReductionFire = getAttribute(AttributeDamageReductionTotalID, AttributeFireSubID)->value();
	Range damageReductionLightning = getAttribute(AttributeDamageReductionTotalID, AttributeLightningSubID)->value();
	Range damageReductionCold = getAttribute(AttributeDamageReductionTotalID, AttributeColdSubID)->value();
	Range damageReductionPoison = getAttribute(AttributeDamageReductionTotalID, AttributePoisonSubID)->value();
	Range damageReductionArcane = getAttribute(AttributeDamageReductionTotalID, AttributeArcaneSubID)->value();
	Range damageReductionAverageElemental = (damageReductionPhysical + damageReductionFire + damageReductionLightning + damageReductionCold + damageReductionPoison + damageReductionArcane) / 6;
	
	return Range(1) - ((Range(1) - damageReductionFromResistance) * (Range(1) - damageReductionFromArmor) * (Range(1)-classDamageReduction) * (Range(1) - damageReductionAverageElemental));
}

Range Hero::getBlockChance() {
	return getAttribute(AttributeBlockChanceTotalID)->value();
}

Range Hero::getBlockAmmountMin() {
	return getAttribute(AttributeBlockAmountTotalMinID)->value();
}

Range Hero::getBlockAmmountMax() {
	return getAttribute(AttributeBlockAmountTotalMaxID)->value();
}

Range Hero::getDodgeChance() {
	return getAttribute(AttributeDodgeChanceTotalID)->value();
}

Range Hero::getHitPoints() {
	return getAttribute(AttributeHitpointsMaxTotalID)->value();
}

Range Hero::getLifeRegen() {
	return getAttribute(AttributeHitpointsRegenPerSecondTotalID)->value();
}

Range Hero::getLifePerHit() {
	return getAttribute(AttributeHitpointsOnHitTotalID)->value();
}

Range Hero::getLifePerKill() {
	return getAttribute(AttributeHitpointsOnKillTotalID)->value();
}

Range Hero::getDPS() {
	return getAttribute(AttributeDPSID)->value();
}

Range Hero::getCritChance() {
	return getAttribute(AttributeCritPercentBonusTotalID)->value();
}

Range Hero::getCritDamage() {
	return getAttribute(AttributeCritDamagePercentTotalID)->value();
}

Range Hero::getAttackSpeed() {
	return getAttribute(AttributeAttacksPerSecondTotalID)->value();
}

Range Hero::getMaxDamage() {
	return getAttribute(AttributeDamageMinTotalAllID)->value() + getAttribute(AttributeDamageDeltaTotalAllID)->value();
}

Range Hero::getMinDamage() {
	return getAttribute(AttributeDamageMinTotalAllID)->value();
}

Range Hero::getMagicFind() {
	return getAttribute(AttributeMagicFindTotalID)->value();
}

Range Hero::getGoldFind() {
	return getAttribute(AttributeGoldFindTotalID)->value();
}
