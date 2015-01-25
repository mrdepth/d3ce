//
//  Hero.cpp
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Hero.h"
#include "Party.h"
#include "Aggregator.h"
#include <algorithm>

using namespace d3ce;

Hero::Hero(std::shared_ptr<Engine> engine, Party* party) : Entity(engine, party) {
	//setAttribute(AttributeCritDamagePercentTotalID, AttributeNoneSubID, 0.5);
	//setAttribute(AttributeCritPercentBonusTotalID, AttributeNoneSubID, 0.05);
	setAttribute(AttributeAttacksPerSecondID, AttributeNoneSubID, 1);
	setAttribute(AttributeCoreAttributesFromItemBonusMultiplierID, AttributeNoneSubID, 1);
	setAttribute(AttributeAttacksPerSecondPercentCapID, AttributeNoneSubID, 1);
	setAttribute(AttributeHitpointsFactorLevelID, AttributeNoneSubID, 4);
//	setAttribute(AttributeHitpointsFactorVitalityID, AttributeNoneSubID, 80);
	setAttribute(AttributeHitpointsMaxID, AttributeNoneSubID, 40);
}

Hero::~Hero() {
}

Hero::Hero(const Hero& other, Party* party) : Entity(other, party) {
	attributes_ = other.attributes_;
	std::vector<std::shared_ptr<Gear>>::const_iterator i, end = other.items_.end();
	for (i = other.items_.begin(); i != end; i++) {
		//Gear* item = dynamic_cast<Gear*>((*i)->cloneIn(this));
		//addItem(item);
		//item->setSlot((*i)->getSlot());
	}

	std::vector<Skill*>::const_iterator j, endj = other.skills_.end();
	for (j = other.skills_.begin(); j != endj; j++) {
		skills_.push_back(dynamic_cast<Skill*>((*j)->cloneIn(this)));
	}
}

std::shared_ptr<Gear> Hero::addItem(Hash itemHash) {
	return addItem(std::dynamic_pointer_cast<Gear>(Item::CreateItem(engine_, this, itemHash)));
}

std::shared_ptr<Gear> Hero::addItem(const std::string& nonNlsKey) {
	return addItem(std::dynamic_pointer_cast<Gear>(Item::CreateItem(engine_, this, nonNlsKey)));
}

std::shared_ptr<Gear> Hero::addItem(std::shared_ptr<Gear> item) {
	if (!item)
		return item;
	
	Hash quiverHash = hash("Quiver");
	Hash offhandHash = hash("Offhand");
	Hash shieldHash = hash("Shield");
	if (item->twoHanded()) {
		std::shared_ptr<Gear> offHand = getItem(Item::SlotOffHand);
		if (offHand && !offHand->conforms(quiverHash) && !offHand->conforms(shieldHash)) {
			throw SlotIsAlreadyFilledException(Item::SlotOffHand);
		}
		if (getItem(Item::SlotMainHand))
			throw SlotIsAlreadyFilledException(Item::SlotMainHand);
	}
	else if (!item->conforms(quiverHash) && !item->conforms(shieldHash) && item->conforms(offhandHash) && !slotIsEmpty(Item::SlotOffHand)) {
		throw SlotIsAlreadyFilledException(Item::SlotOffHand);
	}
	
	static std::vector<Item::Slot> slots = {Item::SlotHead, Item::SlotTorso, Item::SlotMainHand, Item::SlotOffHand, Item::SlotHands, Item::SlotWaist, Item::SlotFeet, Item::SlotShoulders, Item::SlotLegs, Item::SlotBracers, Item::SlotRightFinger, Item::SlotLeftFinger, Item::SlotNeck};

	Item::Slot firstSlot = Item::SlotUnknown;
	for (auto slot: slots) {
		if ((item->possibleSlots() & slot) == slot) {
			if (firstSlot == Item::SlotUnknown)
				firstSlot = slot;
			
			if (!getItem(slot)) {
				
				item->setSlot(slot);
				items_.push_back(item);
				
				Hash itemSetBonusHash = item->itemSetBonusHash();
				if (isValidHash(itemSetBonusHash)) {
					
					auto itemSetIterator = std::find_if(setBonuses_.begin(), setBonuses_.end(), [=](std::shared_ptr<ItemSet> a)->bool {
						return a->getSetBonusHashe() == itemSetBonusHash;
					});
					
					std::shared_ptr<ItemSet> itemSet;
					if (itemSetIterator == setBonuses_.end()) {
						itemSet = std::shared_ptr<ItemSet>(new ItemSet(engine_, this, itemSetBonusHash));
						setBonuses_.push_back(itemSet);
					}
					else
						itemSet = *itemSetIterator;
					itemSet->addItem(item);
				}
				return item;
			}
		}
	}
	
	throw SlotIsAlreadyFilledException(firstSlot);
}

void Hero::removeItem(std::shared_ptr<Gear> item) {
	if (item) {
		items_.erase(std::remove(items_.begin(), items_.end(), item));
		
		Hash itemSetBonusHash = item->itemSetBonusHash();
		if (isValidHash(itemSetBonusHash)) {
			auto itemSetIterator = std::find_if(setBonuses_.begin(), setBonuses_.end(), [=](std::shared_ptr<ItemSet> a)->bool {
				return a->getSetBonusHashe() == itemSetBonusHash;
			});
			
			if (itemSetIterator != setBonuses_.end())
				(*itemSetIterator)->removeItem(item);
		}
		
	}
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


std::shared_ptr<Gear> Hero::getItem(Item::Slot slot) const {
	std::vector<std::shared_ptr<Gear>>::const_iterator i, end = items_.end();
	for (i = items_.begin(); i != end; i++) {
		Item::Slot itemSlot = (*i)->getSlot();
		if (slot == itemSlot)// || (slot == Item::SlotOffHand && itemSlot == Item::SlotMainHand && (*i)->twoHanded()))
			return *i;
	}
	return NULL;
}

const std::vector<std::shared_ptr<Gear>>& Hero::getItems() const {
	return items_;
}

bool Hero::slotIsEmpty(Item::Slot slot) const {
	bool isEmpty = getItem(slot) == NULL;
	if (slot == Item::SlotOffHand && isEmpty) {
		std::shared_ptr<Gear> mainHand = getItem(Item::SlotMainHand);
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
	setAttribute(AttributeLevelID, AttributeNoneSubID, level);
}

void Hero::setParagonLevel(int level) {
	setAttribute(AttributeAltLevelID, AttributeNoneSubID, level);
}

int Hero::getLevel() const {
	return getAttribute(AttributeLevelID).value().max;
}

int Hero::getParagonLevel() const {
	return getAttribute(AttributeAltLevelID).value().max;
}

AttributeSubID Hero::getResourceTypePrimary() const {
	AttributesMap::const_iterator i = attributes_.find(std::make_pair(AttributeResourceTypePrimaryID, AttributeNoneSubID));
	if (i != attributes_.end())
		return static_cast<AttributeSubID>(static_cast<int>(i->second.min));
	else
		return AttributeNoneSubID;
}

AttributeSubID Hero::getResourceTypeSecondary() const {
	AttributesMap::const_iterator i = attributes_.find(std::make_pair(AttributeResourceTypeSecondaryID, AttributeNoneSubID));
	if (i != attributes_.end())
		return static_cast<AttributeSubID>(static_cast<int>(i->second.min));
	else
		return AttributeNoneSubID;
}

PrimaryDamageAttribute Hero::getPrimaryDamageAttribute() const {
	return static_cast<PrimaryDamageAttribute>(getAttribute(AttributePrimaryDamageAttributeID).value().max);
}

//Stats
Range Hero::getStrength() const {
	return getAttribute(AttributeStrengthTotalID);
}

Range Hero::getDexterity() const {
	return getAttribute(AttributeDexterityTotalID);
}

Range Hero::getIntelligence() const {
	return getAttribute(AttributeIntelligenceTotalID);
}

Range Hero::getVitality() const {
	return getAttribute(AttributeVitalityTotalID);
}

Resistance Hero::getResistances() const {
	Resistance resistances;
	resistances.physical = getAttribute(AttributeResistanceTotalID, AttributePhysicalSubID);
	resistances.fire = getAttribute(AttributeResistanceTotalID, AttributeFireSubID);
	resistances.lightning = getAttribute(AttributeResistanceTotalID, AttributeLightningSubID);
	resistances.cold = getAttribute(AttributeResistanceTotalID, AttributeColdSubID);
	resistances.poison = getAttribute(AttributeResistanceTotalID, AttributePoisonSubID);
	resistances.arcane = getAttribute(AttributeResistanceTotalID, AttributeArcaneSubID);
	resistances.holy = getAttribute(AttributeResistanceTotalID, AttributeHolySubID);
	return resistances;
}

Range Hero::getArmor() const {
	return getAttribute(AttributeArmorTotalID);
}

Range Hero::getDamageReductionFromArmor(int againstMosterLevel) const {
	if (againstMosterLevel < 0)
		againstMosterLevel = getLevel();

	Range armor = getArmor();
	return armor / (armor + 50.0 * againstMosterLevel);
}

Resistance Hero::getDamageReductionFromResistances(int againstMosterLevel) const {
	if (againstMosterLevel < 0)
		againstMosterLevel = getLevel();

	Resistance resistances = getResistances();
	resistances.physical = resistances.physical / (resistances.physical + 5 * againstMosterLevel);
	resistances.fire = resistances.fire / (resistances.fire + 5 * againstMosterLevel);
	resistances.lightning = resistances.lightning / (resistances.lightning + 5 * againstMosterLevel);
	resistances.cold = resistances.cold / (resistances.cold + 5 * againstMosterLevel);
	resistances.poison = resistances.poison / (resistances.poison + 5 * againstMosterLevel);
	resistances.arcane = resistances.arcane / (resistances.arcane + 5 * againstMosterLevel);
	resistances.holy = resistances.holy / (resistances.holy + 5 * againstMosterLevel);
	return resistances;
}

Range Hero::getAverageDamageReduction(int againstMosterLevel) const {
	if (againstMosterLevel < 0)
		againstMosterLevel = getLevel();
	
	Resistance resistances = getResistances();
	Range averageResistance = (resistances.physical + resistances.fire + resistances.lightning + resistances.cold + resistances.poison + resistances.arcane) / 6;
	Range damageReductionFromResistance = averageResistance / (averageResistance + 5 * againstMosterLevel);
	Range damageReductionFromArmor = getDamageReductionFromArmor();
	Range classDamageReduction = getAttribute(AttributeClassDamageReductionPercentID).value();

	Range damageReductionPhysical = getAttribute(AttributeDamageReductionTotalID, AttributePhysicalSubID).value();
	Range damageReductionFire = getAttribute(AttributeDamageReductionTotalID, AttributeFireSubID).value();
	Range damageReductionLightning = getAttribute(AttributeDamageReductionTotalID, AttributeLightningSubID).value();
	Range damageReductionCold = getAttribute(AttributeDamageReductionTotalID, AttributeColdSubID).value();
	Range damageReductionPoison = getAttribute(AttributeDamageReductionTotalID, AttributePoisonSubID).value();
	Range damageReductionArcane = getAttribute(AttributeDamageReductionTotalID, AttributeArcaneSubID).value();
	Range damageReductionAverageElemental = (damageReductionPhysical + damageReductionFire + damageReductionLightning + damageReductionCold + damageReductionPoison + damageReductionArcane) / 6;
	Range dodgeChance = getDodgeChance();
	
	Range situationalDamageReduction = (getDamageReductionFromElites() + getDamageReductionFromMelee() + getDamageReductionFromRanged()) / 3.0;
	
	return Range(1) - ((Range(1) - damageReductionFromResistance) * (Range(1) - damageReductionFromArmor) * (Range(1)-classDamageReduction) * (Range(1) - damageReductionAverageElemental) * (Range(1) - situationalDamageReduction) * (Range(1) - dodgeChance));
}

Range Hero::getBlockChance() const {
	return getAttribute(AttributeBlockChanceCappedTotalID).value();
}

Range Hero::getBlockAmmountMin() const {
	return getAttribute(AttributeBlockAmountTotalMinID).value();
}

Range Hero::getBlockAmmountMax() const {
	return getAttribute(AttributeBlockAmountTotalMaxID).value();
}

Range Hero::getDodgeChance() const {
	return getAttribute(AttributeDodgeChanceBonusID).value();
}

Range Hero::getCrowdControlReduction() const {
	return getAttribute(AttributeCrowdControlReductionID).value();
}

Range Hero::getDamageReductionFromMelee() const {
	return getAttribute(AttributeDamagePercentReductionFromMeleeID).value();
}

Range Hero::getDamageReductionFromRanged() const {
	return getAttribute(AttributeDamagePercentReductionFromRangedID).value();
}

Range Hero::getDamageReductionFromElites() const {
	return getAttribute(AttributeDamagePercentReductionFromElitesID).value();
}

Range Hero::getHitPoints() const {
	return getAttribute(AttributeHitpointsMaxTotalID).value();
}

Range Hero::getToughness() const {
	Range hp = getHitPoints();
	Range damageReduction = getAverageDamageReduction();
	return hp / (Range(1) - damageReduction);
}

Range Hero::getLifeRegen() const {
	return getAttribute(AttributeHitpointsRegenPerSecondTotalID).value();
}

Range Hero::getLifePerHit() const {
	return getAttribute(AttributeHitpointsOnHitID).value();
}

Range Hero::getLifePerKill() const {
	return getAttribute(AttributeHitpointsOnKillTotalID).value();
}

Range Hero::getLifeSteal() const {
	return getAttribute(AttributeStealHealthPercentID).value();
}

Range Hero::getLifeBonus() const {
	return getAttribute(AttributeHitpointsMaxPercentBonusID).value() + getAttribute(AttributeHitpointsMaxPercentBonusItemID).value();
}

Range Hero::getHealthGlobeBonus() const {
	return getAttribute(AttributeHealthGlobeBonusHealthID).value();
}

Range Hero::getHealing() const {
	Range lph = getLifePerHit();
	Range regen = getLifeRegen();
	Range lpk = getLifePerKill();
	Range aps = getAttackSpeed();
	AttributeSubID primaryResourceType = getResourceTypePrimary();
	Range lpr = getAttribute(AttributeSpendingResourceHealsPercentID, primaryResourceType);
	Range resourceRegen = getPrimaryResourceRegen();
	Range factor = getAttribute(AttributeHitpointsFactorResourceID, primaryResourceType);
	Range healing =  regen + lph * aps + lpk * 0.16;
	if (factor > 0)
		healing = healing + (aps + resourceRegen / factor) * lpr * factor;
	return healing;
}

Range Hero::getRecovery() const {
	return getHealing() / (Range(1) - getAverageDamageReduction());
}

Range Hero::getDamageBonusFromPrimaryDamageAttribute() const {
	return getAttribute(AttributeDamageBonusFromPrimaryDamageAttributeID).value();
}

Range Hero::getDPS() const {
	return getAttribute(AttributeDPSID).value();
}

Range Hero::getElementalDPS() const {
	Range value = 0;
	for (auto damageType: AttributeDamageTypeSubIDs)
		value = std::max(value, getAttribute(AttributeDamageDealtPercentBonusID, damageType).value());
	return getDPS() * (1 + value);
}

Range Hero::getEliteDPS() const {
	return getDPS() * (1 + getDamageBonusVsElites());
}

Range Hero::getEliteElementalDPS() const {
	return getElementalDPS() * (1 + getDamageBonusVsElites());
}

Range Hero::getCritChance() const {
	return getAttribute(AttributeCritPercentBonusTotalID).value();
}

Range Hero::getCritDamage() const {
	return getAttribute(AttributeCritDamagePercentTotalID).value();
}

Range Hero::getAttackSpeed() const {
	return getAttribute(AttributeAttacksPerSecondTotalID).value();
}

Range Hero::getAttackSpeedBonus() const {
	return getAttribute(AttributeAttacksPerSecondPercentID).value();
}

Range Hero::getMaxDamage() const {
	return getAttribute(AttributeDamageMinTotalAllID).value() + getAttribute(AttributeDamageDeltaTotalAllID).value();
}

Range Hero::getMinDamage() const {
	return getAttribute(AttributeDamageMinTotalAllID).value();
}

Range Hero::getDamageBonusVsElites() const {
	return getAttribute(AttributeDamagePercentBonusVsElitesID).value();
}

Range Hero::getSplashDamage() const {
	return getAttribute(AttributeSplashDamageEffectPercentID).value();
}

Range Hero::getPowerCooldownReduction() const {
	return getAttribute(AttributePowerCooldownReductionPercentAllID).value();
}

Range Hero::getThorns() const {
	Range value = 0;
	for (auto i: AttributeDamageTypeSubIDs) {
		value += getAttribute(AttributeThornsFixedID, i).value();
	}
	return value;
}

Range Hero::getMovementBonus() const {
	return getAttribute(AttributeMovementBonusTotalID).value();
}

Range Hero::getMagicFind() const {
	return getAttribute(AttributeMagicFindTotalID).value();
}

Range Hero::getGoldFind() const {
	return getAttribute(AttributeGoldFindTotalID).value();
}

Range Hero::getGoldPickUpRadius() const {
	return getAttribute(AttributeGoldPickUpRadiusID).value();
}

Range Hero::getExperienceBonus() const {
	return getAttribute(AttributeExperienceBonusPercentTotalID).value();
}

Range Hero::getExperiencePerKill() const {
	return getAttribute(AttributeExperienceBonusID).value();
}

Range Hero::getPrimaryResourceMax() const {
	AttributeSubID resourceType = getResourceTypePrimary();
	if (resourceType != AttributeNoneSubID)
		return getAttribute(AttributeResourceMaxTotalID, resourceType).value();
	else
		return 0;
}

Range Hero::getSecondaryResourceMax() const {
	AttributeSubID resourceType = getResourceTypeSecondary();
	if (resourceType != AttributeNoneSubID)
		return getAttribute(AttributeResourceMaxTotalID, resourceType).value();
	else
		return 0;
}

Range Hero::getPrimaryResourceRegen() const {
	AttributeSubID resourceType = getResourceTypePrimary();
	if (resourceType != AttributeNoneSubID)
		return getAttribute(AttributeResourceRegenTotalID, resourceType).value();
	else
		return 0;
}

Range Hero::getSecondaryResourceRegen() const {
	AttributeSubID resourceType = getResourceTypeSecondary();
	if (resourceType != AttributeNoneSubID)
		return getAttribute(AttributeResourceRegenTotalID, resourceType).value();
	else
		return 0;
}

Range Hero::getPrimaryResourceCostReduction() const {
	AttributeSubID resourceType = getResourceTypePrimary();
	if (resourceType != AttributeNoneSubID)
		return getAttribute(AttributeResourceCostReductionPercentTotalID, resourceType).value();
	else
		return 0;
}

Range Hero::getSecondaryResourceCostReduction() const {
	AttributeSubID resourceType = getResourceTypeSecondary();
	if (resourceType != AttributeNoneSubID)
		return getAttribute(AttributeResourceCostReductionPercentTotalID, resourceType).value();
	else
		return 0;
}

Range Hero::getPrimaryResourceOnCrit() const {
	AttributeSubID resourceType = getResourceTypePrimary();
	if (resourceType != AttributeNoneSubID)
		return getAttribute(AttributeResourceOnCritID, resourceType).value();
	else
		return 0;
}

Range Hero::getSecondaryResourceOnCrit() const {
	AttributeSubID resourceType = getResourceTypeSecondary();
	if (resourceType != AttributeNoneSubID)
		return getAttribute(AttributeResourceOnCritID, resourceType).value();
	else
		return 0;
}

Attribute Hero::getAttribute(AttributeID attributeID, AttributeSubID subID) const {
	auto items = MakeAggregator(engine_, items_.begin(), items_.end());
	auto setBonuses = MakeAggregator(engine_, setBonuses_.begin(), setBonuses_.end());
	auto skills = MakeAggregator(engine_, skills_.begin(), skills_.end());
	const Hero& hero = *this;
	Range value = 0;
	switch (attributeID) {
	case AttributeWalkingRateTotalID:
		value = hero[AttributeWalkingRateID][subID] * hero[AttributeMovementScalarTotalID][subID];
		break;
	case AttributeHitpointsTotalFromVitalityID:
		value = hero[AttributeVitalityTotalID][subID] * hero[AttributeHitpointsFactorVitalityID][subID];
		break;
	case AttributeThornsPercentTotalID:
		value = hero[AttributeThornsPercentID][subID] * hero[AttributeThornsPercentAllID][AttributeNoneSubID];
		break;
	case AttributeStrafingRateTotalID:
		value = hero[AttributeStrafingRateID][subID] * hero[AttributeMovementScalarTotalID][subID];
		break;
	case AttributeSprintingRateTotalID:
		value = hero[AttributeSprintingRateID][subID] * hero[AttributeMovementScalarTotalID][subID];
		break;
	case AttributeSkillTotalID:
		value = hero[AttributeSkillID][subID];
		break;
	case AttributeRunningRateTotalID:
		value = hero[AttributeRunningRateID][subID] * hero[AttributeMovementScalarTotalID][subID];
		break;
	case AttributeResourceRegenTotalID:
		value = hero[AttributeResourceRegenPerSecondID][subID] * (1 + hero[AttributeResourceRegenBonusPercentID][subID]) + hero[AttributeResourceRegenPercentPerSecondID][subID] * hero[AttributeResourceMaxTotalID][subID];
		break;
	case AttributeResourceMaxPercentBonusID:
		value = hero[AttributeResourcePercentID][subID];
		break;
	case AttributeResourceEffectiveMaxID:
		value = hero[AttributeResourceMaxTotalID][subID] - hero[AttributeResourceCapacityUsedID][subID];
		break;
	case AttributeResourceCostReductionTotalID:
		value = hero[AttributeResourceCostReductionAmountID][subID];
		break;
	case AttributeResistanceStunTotalID:
		value = hero[AttributeResistanceStunID][subID] + hero[AttributeResistanceStunRootFreezeID][subID];
		break;
	case AttributeResistanceRootTotalID:
		value = hero[AttributeResistanceRootID][subID] + hero[AttributeResistanceStunRootFreezeID][subID];
		break;
	case AttributeResistanceFreezeTotalID:
		value = hero[AttributeResistanceFreezeID][subID] + hero[AttributeResistanceStunRootFreezeID][subID];
		break;
	case AttributePowerCooldownReductionPercentAllCappedID:
		value = hero[AttributePowerCooldownReductionPercentAllID][subID];
		break;
	case AttributeMovementScalarTotalID:
		value = hero[AttributeMovementScalarCappedTotalID][subID] + hero[AttributeMovementScalarUncappedBonusID][subID];
		break;
	case AttributeMovementBonusTotalID:
		value = hero[AttributeMovementBonusRunSpeedID][subID];
		break;
	case AttributeMovementScalarCappedTotalID:
		value = std::min(hero[AttributeMovementScalarCapID][subID], hero[AttributeMovementScalarSubtotalID][subID]);
		break;
	case AttributeBlockChanceCappedTotalID:
		value = std::min(Range(1.0), hero[AttributeBlockChanceSubTotalID][subID] + hero[AttributeBlockChanceUncappedBonusID][subID]);
		break;
	case AttributeBlockChanceSubTotalID:
		value = std::min(Range(0.75), hero[AttributeBlockChanceID][subID] + hero[AttributeBlockChanceItemTotalID][subID]);
		break;
	case AttributeMagicFindCappedSubtotalID:
		value = std::min(hero[AttributeMagicFindAltLevelsTotalID][subID] + hero[AttributeMagicFindID][subID], Range(3.0));
		break;
	case AttributeEffectiveLevelID:
		value = std::max(hero[AttributeUpscaledLevelID][subID], hero[AttributeLevelID][subID]);
		break;
	case AttributeMovementScalarSubtotalID:
		value = std::max(Range(0.1), static_cast<Range>(hero[AttributeMovementScalarID][subID])) *
			(1 + hero[AttributeMovementBonusTotalID][subID]) *
			(1 - hero[AttributeMovementScalarReductionPercentID][subID] * (1 - std::min(Range(1.0), static_cast<Range>(hero[AttributeMovementScalarReductionResistanceID][subID]))));
		break;
	case AttributeAttacksPerSecondPercentSubtotalID:
		value = std::max(Range(0.1),
			(1 + std::min(hero[AttributeAttacksPerSecondPercentCapID][subID], hero[AttributeAttacksPerSecondPercentID][subID]) +
			hero[AttributeAttacksPerSecondPercentUncappedID][subID]/* + (hero[AttributeDualWieldID] > 0 ? 0.15 : 0)*/) *
			(1 - hero[AttributeAttacksPerSecondPercentReductionID][subID]));
		break;
	case AttributeAttacksPerSecondTotalID:
		value = std::max(Range(0.1),
			(((hero[AttributeAttacksPerSecondItemCurrentHandID][subID] > 0.0 ? hero[AttributeAttacksPerSecondItemCurrentHandID][subID] : hero[AttributeAttacksPerSecondID][subID]) +
			hero[AttributeAttacksPerSecondBonusID][subID]) + hero[AttributeAttacksPerSecondItemBonusID][subID]) *
			hero[AttributeAttacksPerSecondPercentSubtotalID][subID]);
		break;
	case AttributeResourceMaxTotalID:
		value = std::max((hero[AttributeResourceMaxID][subID] + ((hero[AttributeLevelID][AttributeNoneSubID] - 1) * hero[AttributeResourceFactorLevelID][subID]) + hero[AttributeResourceMaxBonusID][subID]) *
			(hero[AttributeResourceMaxPercentBonusID][subID] + 1), Range(0));
		break;
	case AttributeHitpointsMaxTotalID:
		value = std::max((hero[AttributeHitpointsMaxID][subID] + hero[AttributeHitpointsTotalFromLevelID][subID] + hero[AttributeHitpointsTotalFromVitalityID][subID] + hero[AttributeHitpointsMaxBonusID][subID]) *
			(hero[AttributeHitpointsMaxPercentBonusID][subID] + hero[AttributeHitpointsMaxPercentBonusItemID][subID] + 1),
			Range(1));
		break;
	case AttributeMagicFindTotalID:
		value = hero[AttributeMagicFindUncappedID][subID] + hero[AttributeMagicFindHandicapID][subID] + hero[AttributeMagicFindCappedSubtotalID][subID];
		break;
	case AttributeInitialCooldownMinTotalID:
		value = hero[AttributeInitialCooldownMinID][subID] / hero[AttributeAttacksPerSecondTotalID][subID];
		break;
	case AttributeInitialCooldownDeltaTotalID:
		value = hero[AttributeInitialCooldownDeltaID][subID] / hero[AttributeAttacksPerSecondTotalID][subID];
		break;
	case AttributeIncreasedHealthFromGlobesPercentTotalID:
		value = hero[AttributeIncreasedHealthFromGlobesPercentID][subID];
		break;
	case AttributeHitpointsOnKillTotalID:
		value = hero[AttributeHitpointsOnKillID][subID] * pin(1 - hero[AttributeHitpointsOnKillReductionPercentID][subID], 0, 1);
		break;
	case AttributeGetHitRecoveryID:
		value = hero[AttributeGetHitRecoveryBaseID][subID] + (hero[AttributeGetHitRecoveryPerLevelID][subID] * hero[AttributeLevelID][subID]);
		break;
	case AttributeGetHitMaxID:
		value = hero[AttributeGetHitMaxBaseID][subID] + (hero[AttributeGetHitMaxPerLevelID][subID] * hero[AttributeLevelID][subID]);
		break;
	case AttributeArmorTotalID:
		value = floor((hero[AttributeArmorID][subID] + hero[AttributeArmorItemTotalID][subID] + hero[AttributeStrengthTotalID][subID] + hero[AttributeDexterityTotalID][subID]) *
			(hero[AttributeArmorBonusPercentID][subID] + 1));
		break;
	case AttributeExperienceBonusPercentSuperScalarTotalID:
		value = hero[AttributeExperienceBonusPercentSuperScalarID][subID] + hero[AttributeExperienceBonusPercentCommunityBuffID][subID] + hero[AttributeExperienceBonusPercentIGRBuffID][subID] + hero[AttributeExperienceBonusPercentAnniversaryBuffID][subID];
		break;
	case AttributeExperienceBonusPercentTotalID:
		value = hero[AttributeExperienceBonusPercentID][subID] + hero[AttributeExperienceBonusPercentHandicapID][subID];
		break;
	case AttributeBonusHealthPercentPerSecondFromGlobesTotalID:
		value = hero[AttributeBonusHealthPercentPerSecondFromGlobesID][subID];
		break;
	case AttributeAttackCooldownMinTotalID:
		value = hero[AttributeAttackCooldownMinID][subID] / hero[AttributeAttacksPerSecondTotalID][subID];
		break;
	case AttributeAttackCooldownDeltaTotalID:
		value = hero[AttributeAttackCooldownDeltaID][subID] / hero[AttributeAttacksPerSecondTotalID][subID];
		break;
	case AttributeGoldFindAltLevelsTotalID:
	case AttributeMagicFindAltLevelsTotalID:
		value = hero[AttributeAltLevelID][subID] * 0.0;
		break;
	case AttributeResourceCostReductionPercentTotalID:
		value = 1.0 - ((1.0 - hero[AttributeResourceCostReductionPercentID][subID]) * (1.0 - hero[AttributeResourceCostReductionPercentAllID][AttributeNoneSubID]));
		break;
	case AttributeResistancePenetrationTotalID:
		value = (hero[AttributeResistancePenetrationID][subID] + hero[AttributeResistancePenetrationAllID][AttributeNoneSubID]) * (hero[AttributeResistancePenetrationPercentAllID][AttributeNoneSubID] + 1);
		break;
	case AttributeResistanceTotalID:
		value = (hero[AttributeResistanceID][subID] + hero[AttributeResistanceAllID][AttributeNoneSubID] + hero[AttributeResistanceFromIntelligenceID][AttributeNoneSubID]) *
			(hero[AttributeResistancePercentAllID][AttributeNoneSubID] + hero[AttributeResistancePercentID][subID] + 1);
		break;
	case AttributeHitpointsTotalFromLevelID:
		value = (hero[AttributeLevelID][subID] - 1) * hero[AttributeHitpointsFactorLevelID][subID];
		break;
	case AttributeResistanceFromIntelligenceID:
		value = hero[AttributeIntelligenceTotalID][subID] * 0.1;
		break;
	case AttributeHitpointsRegenPerSecondTotalID:
		value = (hero[AttributeHitpointsRegenPerSecondSubtotalID][subID] * pin(1 - hero[AttributeHitpointsRegenReductionPercentID][subID], 0, 1)) + hero[AttributeHitpointsRegenPerSecondHealthGlobeID][subID];
		break;
	case AttributeHitpointsRegenPerSecondSubtotalID:
		value = (hero[AttributeHitpointsRegenPerSecondID][subID] + hero[AttributeHitpointsRegenPerSecondBonusID][subID]) * (1 + hero[AttributeHitpointsRegenBonusPercentID][subID]);
		break;
	case AttributeDamageWeaponMinTotalCurrentHandID:
		value = hero[AttributeDualWieldHandID][AttributeNoneSubID] > 0 ? hero[AttributeDamageWeaponMinTotalOffHandID][subID] : hero[AttributeDamageWeaponMinTotalMainHandID][subID];
		break;
	case AttributeDamageWeaponDeltaTotalCurrentHandID:
		value = hero[AttributeDualWieldHandID][AttributeNoneSubID] > 0 ? hero[AttributeDamageWeaponDeltaTotalOffHandID][subID] : hero[AttributeDamageWeaponDeltaTotalMainHandID][subID];
		break;
	case AttributeWeaponCritChanceCurrentHandID:
		value = hero[AttributeDualWieldHandID][AttributeNoneSubID] > 0 ? hero[AttributeWeaponCritChanceOffHandID][subID] : hero[AttributeWeaponCritChanceMainHandID][subID];
		break;
	case AttributeAttacksPerSecondItemCurrentHandID:
		value = hero[AttributeDualWieldHandID][AttributeNoneSubID] > 0 ? hero[AttributeAttacksPerSecondItemOffHandID][subID] : hero[AttributeAttacksPerSecondItemMainHandID][subID];
		break;
	case AttributeCastingSpeedTotalID:
		value = (hero[AttributeCastingSpeedID][subID] + hero[AttributeCastingSpeedBonusID][subID]) * std::max(Range(0.1), 1 + hero[AttributeCastingSpeedPercentID][subID]);
		break;
	case AttributeBlockAmountTotalMaxID:
		value = (hero[AttributeBlockAmountID][subID] + hero[AttributeBlockAmountItemMinID][subID] + hero[AttributeBlockAmountItemDeltaID][subID] + hero[AttributeBlockAmountItemBonusID][subID]) *
			(1 + hero[AttributeBlockAmountBonusPercentID][subID]);
		break;
	case AttributeBlockAmountTotalMinID:
		value = (hero[AttributeBlockAmountID][subID] + hero[AttributeBlockAmountItemMinID][subID] + hero[AttributeBlockAmountItemBonusID][subID]) *
			(1 + hero[AttributeBlockAmountBonusPercentID][subID]);
		break;
	case AttributeVitalityTotalID:
		value = ((hero[AttributeVitalityTotalFromLevelID][subID] + hero[AttributeVitalityID][subID] + hero[AttributeStatsAllBonusID][subID] + hero[AttributeVitalityBonusID][subID]) +
			(hero[AttributeVitalityItemID][subID] * hero[AttributeCoreAttributesFromItemBonusMultiplierID][subID]) * (1 + hero[AttributeVitalityBonusPercentID][subID])) *
			(1 - hero[AttributeVitalityReductionPercentID][subID]);
		break;
	case AttributeStrengthTotalID:
		value = ((hero[AttributeStrengthTotalFromLevelID][subID] + hero[AttributeStrengthID][subID] + hero[AttributeStatsAllBonusID][subID] + hero[AttributeStrengthBonusID][subID]) +
			(hero[AttributeStrengthItemID][subID] * hero[AttributeCoreAttributesFromItemBonusMultiplierID][subID]) * (1 + hero[AttributeStrengthBonusPercentID][subID])) *
			(1 - hero[AttributeStrengthReductionPercentID][subID]);
		break;
	case AttributeIntelligenceTotalID:
		value = ((hero[AttributeIntelligenceTotalFromLevelID][subID] + hero[AttributeIntelligenceID][subID] + hero[AttributeStatsAllBonusID][subID] + hero[AttributeIntelligenceBonusID][subID]) +
			(hero[AttributeIntelligenceItemID][subID] * hero[AttributeCoreAttributesFromItemBonusMultiplierID][subID]) * (1 + hero[AttributeIntelligenceBonusPercentID][subID])) *
			(1 - hero[AttributeIntelligenceReductionPercentID][subID]);
		break;
	case AttributeDexterityTotalID:
		value = ((hero[AttributeDexterityTotalFromLevelID][subID] + hero[AttributeDexterityID][subID] + hero[AttributeStatsAllBonusID][subID] + hero[AttributeDexterityBonusID][subID]) +
			(hero[AttributeDexterityItemID][subID] * hero[AttributeCoreAttributesFromItemBonusMultiplierID][subID]) * (1 + hero[AttributeDexterityBonusPercentID][subID])) *
			(1 - hero[AttributeDexterityReductionPercentID][subID]);
		break;
	case AttributeGoldFindTotalID:
		value = ((1.0 + hero[AttributeGoldFindUncappedID][subID] + hero[AttributeGoldFindAltLevelsTotalID][subID] + hero[AttributeGoldFindID][subID] + hero[AttributeGoldFindCommunityBuffID][subID]) *
			(1 + hero[AttributeGoldFindHandicapID][subID])) - 1;
		break;


	case AttributeStrengthTotalFromLevelID:
		value = (hero[AttributeLevelID][subID] - 1) * hero[AttributeStrengthFactorLevelID][subID];
		break;
	case AttributeDexterityTotalFromLevelID:
		value = (hero[AttributeLevelID][subID] - 1) * hero[AttributeDexterityFactorLevelID][subID];
		break;
	case AttributeIntelligenceTotalFromLevelID:
		value = (hero[AttributeLevelID][subID] - 1) * hero[AttributeIntelligenceFactorLevelID][subID];
		break;
	case AttributeVitalityTotalFromLevelID:
		value = (hero[AttributeLevelID][subID] - 1) * hero[AttributeVitalityFactorLevelID][subID];
		break;

/*	case AttributeIntelligenceItemID:
	case AttributeStrengthItemID:
	case AttributeDexterityItemID:
	case AttributeVitalityItemID:
	case AttributeIntelligenceID:
	case AttributeStrengthID:
	case AttributeDexterityID:
	case AttributeVitalityID:
		value = Entity::getAttribute(attributeID, subID) + items[attributeID][subID] + setBonuses[attributeID][subID];
		break;*/
	case AttributeAttributeSetItemDiscountID:
		value = items[attributeID][subID];
		break;
	//from Gear
	case AttributeDamageDeltaTotalID:
		value = std::max(hero[AttributeDamageDeltaID][subID] - hero[AttributeDamageBonusMinID][subID] + hero[AttributeDamageWeaponDeltaTotalCurrentHandID][subID], Range(0));
		break;
	case AttributeDamageMinTotalID:
		value = hero[AttributeDamageMinSubtotalID][subID];
		break;
	case AttributeDamageMinSubtotalID:
		value = hero[AttributeDamageMinID][subID] + hero[AttributeDamageBonusMinID][subID] + hero[AttributeDamageWeaponMinTotalCurrentHandID][subID];
		break;

	//Calculations
	case AttributeHitpointsFactorVitalityID: {
		auto level = getLevel();
		//63-47
		//64-51
		//65-55
		//66-60
		//67-70
		if (level >= 66)
			value = 60 + 10 * (level - 66);
		else if (level >= 60)
			value = 35 + 4 * (level - 60);
		else if (level >= 35)
			value = level - 25;
		else
			value = 10;

/*		if (level >= 61)
			value = 35 + 5 * (level - 61);
		else if (level >= 35)
			value = level - 25;
		else
			value = 10;*/
		break;
	}
	case AttributeDualWieldHandID: {
		auto mainHand = getItem(Item::SlotMainHand);
		auto offHand = getItem(Item::SlotOffHand);
		value = !mainHand && offHand && offHand->isWeapon();
	   break;
	}
	case AttributeDualWieldID: {
		auto mainHand = getItem(Item::SlotMainHand);
		auto offHand = getItem(Item::SlotOffHand);
		value = mainHand && offHand && mainHand != offHand && offHand->isWeapon();
		break;
	}
	case AttributeDamageMinTotalAllID:
		for (auto subID : AttributeDamageTypeSubIDs)
			value += hero[AttributeDamageMinTotalID][subID];
		break;
	case AttributeDamageDeltaTotalAllID:
		for (auto subID : AttributeDamageTypeSubIDs)
			value += hero[AttributeDamageDeltaTotalID][subID];
		break;
	case AttributeDamageBonusFromPrimaryDamageAttributeID: {
		Range primaryDamageAttribute = hero[AttributePrimaryDamageAttributeID];
		switch (static_cast<PrimaryDamageAttribute>(primaryDamageAttribute.max)) {
			case PrimaryDamageAttributeIntelligence:
				value = hero[AttributeIntelligenceTotalID] / 100;
				break;
			case PrimaryDamageAttributeDexterity:
				value = hero[AttributeDexterityTotalID] / 100;
				break;
			case PrimaryDamageAttributeStrength:
				value = hero[AttributeStrengthTotalID] / 100;
				break;
		}
		break;
	}

	case AttributeDamageMinFullID:
		value = hero[AttributeDamageMinTotalID][subID] * (1 + hero[AttributeDamageBonusFromPrimaryDamageAttributeID]);
		break;
	case AttributeDamageDeltaFullID:
		value = hero[AttributeDamageDeltaTotalID][subID] * (1 + hero[AttributeDamageBonusFromPrimaryDamageAttributeID]);
		break;
	case AttributeDamageAverageFullID:
		value = hero[AttributeDamageMinFullID][subID] + hero[AttributeDamageDeltaFullID][subID] / 2;
		break;
	case AttributeDamageMinFullAllID:
		for (auto subID : AttributeDamageTypeSubIDs)
			value += hero[AttributeDamageMinFullID][subID];
		break;
	case AttributeDamageDeltaFullAllID:
		for (auto subID : AttributeDamageTypeSubIDs)
			value += hero[AttributeDamageDeltaFullID][subID];
		break;
	case AttributeDamageAverageFullAllID:
		value = hero[AttributeDamageMinFullAllID][subID] + hero[AttributeDamageDeltaFullAllID][subID] / 2;
		break;
	case AttributeCritDamagePercentTotalID:
		value = hero[d3ce::AttributeCritDamagePercentID][subID] + hero[d3ce::AttributeCritDamagePercentUncappedID][subID] + 0.5;
		break;
	case AttributeCritPercentBonusTotalID:
		value = hero[d3ce::AttributeCritPercentBonusUncappedID][subID] + hero[d3ce::AttributeCritPercentBonusCappedID][subID] + 0.05;
		break;

		//Damage
	case AttributeDamageDeltaTotalMainHandID:
		value = std::max(hero[AttributeDamageDeltaID][subID] - hero[AttributeDamageBonusMinID][subID] + hero[AttributeDamageWeaponDeltaTotalMainHandID][subID], Range(0));
		break;
	case AttributeDamageMinTotalMainHandID:
		value = hero[AttributeDamageMinSubtotalMainHandID][subID];
		break;
	case AttributeDamageMinSubtotalMainHandID:
		value = hero[AttributeDamageMinID][subID] + hero[AttributeDamageBonusMinID][subID] + hero[AttributeDamageWeaponMinTotalMainHandID][subID];
		break;
	case AttributeDamageDeltaTotalOffHandID:
		value = std::max(hero[AttributeDamageDeltaID][subID] - hero[AttributeDamageBonusMinID][subID] + hero[AttributeDamageWeaponDeltaTotalOffHandID][subID], Range(0));
		break;
	case AttributeDamageWeaponMinTotalMainHandID:
		value = items[AttributeDamageWeaponMinTotalMainHandID][subID];
		if (subID == AttributePhysicalSubID)
			 value = std::max(value, Range(2.5));
		break;
	case AttributeDamageMinTotalOffHandID:
		value = hero[AttributeDamageMinSubtotalOffHandID][subID];
		break;
	case AttributeDamageMinSubtotalOffHandID:
		value = hero[AttributeDamageMinID][subID] + hero[AttributeDamageBonusMinID][subID] + hero[AttributeDamageWeaponMinTotalOffHandID][subID];
		break;
	case AttributeAttacksPerSecondTotalMainHandID:
		value = std::max(Range(0.1),
			(((hero[AttributeAttacksPerSecondItemMainHandID][subID] > 0.0 ? hero[AttributeAttacksPerSecondItemMainHandID][subID] : hero[AttributeAttacksPerSecondID][subID]) +
			hero[AttributeAttacksPerSecondBonusID][subID]) + hero[AttributeAttacksPerSecondItemBonusID][subID]) *
			hero[AttributeAttacksPerSecondPercentSubtotalID][subID]);
		break;
	case AttributeAttacksPerSecondTotalOffHandID:
		value = std::max(Range(0.1),
			(((hero[AttributeAttacksPerSecondItemMainHandID][subID] > 0.0 ? hero[AttributeAttacksPerSecondItemOffHandID][subID] : hero[AttributeAttacksPerSecondID][subID]) +
			hero[AttributeAttacksPerSecondBonusID][subID]) + hero[AttributeAttacksPerSecondItemBonusID][subID]) *
			hero[AttributeAttacksPerSecondPercentSubtotalID][subID]);
		break;

	case AttributeDamageMinFullMainHandID:
		value = hero[AttributeDamageMinTotalMainHandID][subID] * (1 + hero[AttributeDamageBonusFromPrimaryDamageAttributeID]);
		break;
	case AttributeDamageDeltaFullMainHandID:
		value = hero[AttributeDamageDeltaTotalMainHandID][subID] * (1 + hero[AttributeDamageBonusFromPrimaryDamageAttributeID]);
		break;
	case AttributeDamageAverageFullMainHandID:
		value = hero[AttributeDamageMinFullMainHandID][subID] + hero[AttributeDamageDeltaFullMainHandID][subID] / 2;
		break;
	case AttributeDamageMinFullAllMainHandID:
		for (auto subID : AttributeDamageTypeSubIDs)
			value += hero[AttributeDamageMinFullMainHandID][subID];
		break;
	case AttributeDamageDeltaFullAllMainHandID:
		for (auto subID : AttributeDamageTypeSubIDs)
			value += hero[AttributeDamageDeltaFullMainHandID][subID];
		break;
	case AttributeDamageAverageFullAllMainHandID:
		value = hero[AttributeDamageMinFullAllMainHandID][subID] + hero[AttributeDamageDeltaFullAllMainHandID][subID] / 2;
		break;

	case AttributeDamageMinFullOffHandID:
		value = hero[AttributeDamageMinTotalOffHandID][subID] * (1 + hero[AttributeDamageBonusFromPrimaryDamageAttributeID]);
		break;
	case AttributeDamageDeltaFullOffHandID:
		value = hero[AttributeDamageDeltaTotalOffHandID][subID] * (1 + hero[AttributeDamageBonusFromPrimaryDamageAttributeID]);
		break;
	case AttributeDamageAverageFullOffHandID:
		value = hero[AttributeDamageMinFullOffHandID][subID] + hero[AttributeDamageDeltaFullOffHandID][subID] / 2;
		break;
	case AttributeDamageMinFullAllOffHandID:
		for (auto subID : AttributeDamageTypeSubIDs)
			value += hero[AttributeDamageMinFullOffHandID][subID];
		break;
	case AttributeDamageDeltaFullAllOffHandID:
		for (auto subID : AttributeDamageTypeSubIDs)
			value += hero[AttributeDamageDeltaFullOffHandID][subID];
		break;
	case AttributeDamageAverageFullAllOffHandID:
		value = hero[AttributeDamageMinFullAllOffHandID][subID] + hero[AttributeDamageDeltaFullAllOffHandID][subID] / 2;
		break;
	case AttributeDPSID:
		if (hero[AttributeDualWieldID] > 0)
			value = (hero[AttributeDamageAverageFullAllMainHandID] + hero[AttributeDamageAverageFullAllOffHandID]) / (1.0 / hero[AttributeAttacksPerSecondTotalMainHandID] + 1.0 / hero[AttributeAttacksPerSecondTotalOffHandID]) * 1.15;
		else
			value = hero[AttributeDamageAverageFullAllID] * hero[AttributeAttacksPerSecondTotalID];
		value *= (1 + hero[AttributeCritDamagePercentTotalID] * hero[AttributeCritPercentBonusTotalID]);
		break;
	default:
		value = Entity::getAttribute(attributeID, subID) + items[attributeID][subID] + setBonuses[attributeID][subID];
		break;
	}

	return Attribute(this, attributeID, subID, value);
}

