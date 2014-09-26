//
//  Gear.cpp
//  d3ce
//
//  Created by Artem Shimanski on 28.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Gear.h"
#include <algorithm>
#include <sstream>
#include <math.h>
#include "Aggregator.h"

using namespace d3ce;

Gear::Gear(std::shared_ptr<Engine> engine, Entity* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, Hash itemSetBonusHash, int flags, int bitMask, const std::vector<Slot>& possibleSlots) : Item(engine, parent, itemHash, itemTypesTree, flags, bitMask, possibleSlots) {
	itemSetBonusHash_ = itemSetBonusHash;
}

Gear::Gear(const Gear& other, Entity* parent) : Item(other, parent) {
	//copyAttributes(other);
	itemSetBonusHash_ = other.itemSetBonusHash_;
	std::vector<std::shared_ptr<Gem>>::const_iterator i, end = other.gems_.end();
	//for (i = other.gems_.begin(); i != end; i++)
		//gems_.push_back(dynamic_cast<Gem*>((*i)->cloneIn(this)));

}

Gear::~Gear() {
}

bool Gear::twoHanded() const {
	return false;
}

std::shared_ptr<Gem> Gear::addGem(Hash itemHash) {
	std::shared_ptr<Gem> gem = std::dynamic_pointer_cast<Gem>(Item::CreateItem(engine_, this, itemHash));
	gems_.push_back(gem);
	return gem;
}

std::shared_ptr<Gem> Gear::addGem(const std::string& nonNlsKey) {
	std::shared_ptr<Gem> gem = std::dynamic_pointer_cast<Gem>(Item::CreateItem(engine_, this, nonNlsKey));
	gems_.push_back(gem);
	return gem;
}


void Gear::removeGem(std::shared_ptr<Gem> gem) {
	gems_.erase(std::remove(gems_.begin(), gems_.end(), gem));
}

const std::vector<std::shared_ptr<Gem>>& Gear::getGems() const {
	return gems_;
}

Hash Gear::itemSetBonusHash() const {
	return itemSetBonusHash_;
}

float Gear::perfection() const {
	const std::map<AttributeKey, Range>& modifiers = possibleModifiers();
	float perfection = 0;
	int n = 0;
	AttributesMap::const_iterator i, end = attributes_.end();

	for (i = attributes_.begin(); i != end; i++) {
		std::map<AttributeKey, Range>::const_iterator j = modifiers.find(i->first);
		if (j != modifiers.end()) {
			Range value = i->second;
			if (value.max == 0.0)
				continue;
			Range perfect = j->second;
			float v = 0;
			if ((perfect.max - perfect.min) != 0)
				v = fabs(value.max - perfect.min) / (perfect.max - perfect.min);
			else if (perfect.max != 0)
				v = 1;
			if (v <= 1.0) {
				perfection += v;
				n++;
			}
		}
	}
	return n > 0 ? perfection / n : 0;
}

bool Gear::isWeapon() const {
	return false;
}


Attribute Gear::getAttribute(AttributeID attributeID, AttributeSubID subID) const {
	auto gems = MakeAggregator(engine_, gems_.begin(), gems_.end());
	const Gear& gear = *this;
	Range value;
	switch (attributeID) {
	case AttributeWeaponRangedID:
		value = pin(gear[AttributeThrowingAxeID][subID] + gear[AttributeBowAnyID][subID], 0, 1);
		break;
	case AttributeSwordAnyID:
		value = pin(gear[AttributeSwordID][subID] + gear[AttributeSword2HID][subID], 0, 1);
		break;
	case AttributeMaceAnyID:
		value = pin(gear[AttributeMaceID][subID] + gear[AttributeMace2HID][subID], 0, 1);
		break;
	case AttributeStaffAnyID:
		value = pin(gear[AttributeColdStaffID][subID] + gear[AttributeFireStaffID][subID] + gear[AttributeLightningStaffID][subID] + gear[AttributePoisonStaffID][subID], 0, 1);
		break;
	case AttributeClubAnyID:
		value = pin(gear[AttributeClubID][subID] + gear[AttributeClub2HID][subID], 0, 1);
		break;
	case AttributeBowAnyID:
		value = pin(gear[AttributeBowID][subID] + gear[AttributeCrossbowID][subID], 0, 1);
		break;
	case AttributeAxeAnyID:
		value = pin(gear[AttributeAxeID][subID] + gear[AttributeAxe2HID][subID], 0, 1);
		break;
	case AttributeWeapon2HID:
		value = pin(gear[AttributeAxe2HID][subID] + gear[AttributeBowAnyID][subID] + gear[AttributeClub2HID][subID] + gear[AttributeMace2HID][subID] + gear[AttributeSword2HID][subID] +
			gear[AttributePolearmID][subID] + gear[AttributeStaffAnyID][subID], 0, 1);
		break;
	case AttributeWeapon1HID:
		value = pin(gear[AttributeAxeID][subID] + gear[AttributeClubID][subID] + gear[AttributeDaggerID][subID] + gear[AttributeMaceID][subID] + gear[AttributeSwordID][subID] + gear[AttributeWandID][subID], 0, 1);
		break;
	case AttributeWeaponMeleeID:
		value = pin(gear[AttributeAxeID][subID] + gear[AttributeAxe2HID][subID] + gear[AttributeClubAnyID][subID] + gear[AttributeDaggerID][subID] + gear[AttributeMaceAnyID][subID] +
			gear[AttributeSwordAnyID][subID] + gear[AttributePolearmID][subID] + gear[AttributeSpearID][subID] + gear[AttributeWandID][subID] + gear[AttributeStaffAnyID][subID], 0, 1);
		break;
	case AttributeDamageDeltaTotalID:
		value = std::max(gear[AttributeDamageDeltaID][subID] - gear[AttributeDamageBonusMinID][subID] + gear[AttributeDamageWeaponDeltaTotalCurrentHandID][subID], Range(0));
		break;
	case AttributeDamageWeaponDeltaTotalID:
		value = std::max((gear[AttributeDamageWeaponDeltaSubTotalID][subID] + gear[AttributeDamageWeaponBonusDeltaID][subID] + gear[AttributeDamageWeaponBonusDeltaX1ID][subID]) *
			(1 + gear[AttributeDamageWeaponPercentTotalID][subID]), Range(0));
		break;
	case AttributeArmorItemSubTotalID:
		value = floor((gear[AttributeArmorItemID][subID] + gear[AttributeArmorBonusItemID][subID]) * (gear[AttributeArmorItemPercentID][subID] + 1));
		break;
	case AttributeDamageWeaponPercentTotalID:
		value = gear[AttributeDamageWeaponPercentBonusID][subID] + gear[AttributeDamageWeaponPercentAllID][AttributeNoneSubID];
		break;
	case AttributeDamageMinTotalID:
		value = gear[AttributeDamageMinSubtotalID][subID];
		break;
	case AttributeDamageMinSubtotalID:
		value = gear[AttributeDamageMinID][subID] + gear[AttributeDamageBonusMinID][subID] + gear[AttributeDamageWeaponMinTotalCurrentHandID][subID];
		break;
	case AttributeBlockChanceItemTotalID:
		value = gear[AttributeBlockChanceTotalID][subID] + gear[AttributeBlockChanceBonusItemID][subID];
		break;
	case AttributeAttacksPerSecondItemTotalOffHandID:
		value = gear[AttributeAttacksPerSecondItemOffHandID][subID] + gear[AttributeAttacksPerSecondItemBonusID][subID];
		break;
	case AttributeAttacksPerSecondItemTotalMainHandID:
		value = gear[AttributeAttacksPerSecondItemMainHandID][subID] + gear[AttributeAttacksPerSecondItemBonusID][subID];
		break;
	case AttributeAttacksPerSecondItemSubtotalID:
		value = gear[AttributeAttacksPerSecondItemID][subID] * (1 + gear[AttributeAttacksPerSecondItemPercentID][subID]);
		break;
	case AttributeDamageWeaponMinTotalOffHandID:
		value = gear[AttributeHeldInOffHandID][AttributeNoneSubID] != 0 ? gear[AttributeDamageWeaponMinTotalID][subID] : Range(0);
		break;
	case AttributeDamageWeaponDeltaTotalOffHandID:
		value = gear[AttributeHeldInOffHandID][AttributeNoneSubID] != 0 ? gear[AttributeDamageWeaponDeltaTotalID][subID] : Range(0);
		break;
	case AttributeDamageWeaponMinTotalMainHandID:
		value = gear[AttributeHeldInOffHandID][AttributeNoneSubID] != 0 ? Range(0) : gear[AttributeDamageWeaponMinTotalID][subID];
		break;
	case AttributeDamageWeaponDeltaTotalMainHandID:
		value = gear[AttributeHeldInOffHandID][AttributeNoneSubID] != 0 ? Range(0) : gear[AttributeDamageWeaponDeltaTotalID][subID];
		break;
	case AttributeAttacksPerSecondItemOffHandID:
		value = gear[AttributeHeldInOffHandID][AttributeNoneSubID] != 0 ? gear[AttributeAttacksPerSecondItemSubtotalID][subID] : Range(0);
		break;
	case AttributeAttacksPerSecondItemMainHandID:
		value = gear[AttributeHeldInOffHandID][AttributeNoneSubID] != 0 ? Range(0) : gear[AttributeAttacksPerSecondItemSubtotalID][subID];
		break;
	case AttributeWeaponCritChanceOffHandID:
		value = gear[AttributeHeldInOffHandID][AttributeNoneSubID] != 0 ? gear[AttributeWeaponCritChanceID][subID] : Range(0);
		break;
	case AttributeWeaponCritChanceMainHandID:
		value = gear[AttributeHeldInOffHandID][AttributeNoneSubID] != 0 ? Range(0) : gear[AttributeWeaponCritChanceID][subID];
		break;
	case AttributeDamageWeaponAverageTotalAllID:
		value = gear[AttributeDamageWeaponMinTotalAllID][subID] + gear[AttributeDamageWeaponDeltaTotalAllID][subID] / 2;
		break;
	case AttributeDamageWeaponMinTotalAllID:
		value = gear[AttributeDamageWeaponMinTotalID][AttributePhysicalSubID] + gear[AttributeDamageWeaponMinTotalID][AttributeFireSubID] + gear[AttributeDamageWeaponMinTotalID][AttributeColdSubID] +
			gear[AttributeDamageWeaponMinTotalID][AttributeLightningSubID] + gear[AttributeDamageWeaponMinTotalID][AttributePoisonSubID] + gear[AttributeDamageWeaponMinTotalID][AttributeArcaneSubID] +
			gear[AttributeDamageWeaponMinTotalID][AttributeHolySubID];
		break;
	case AttributeDamageWeaponMaxTotalID:
		value = gear[AttributeDamageWeaponMinTotalID][subID] + gear[AttributeDamageWeaponDeltaTotalID][subID];
		break;
	case AttributeDamageWeaponAverageTotalID:
		value = gear[AttributeDamageWeaponMinTotalID][subID] + gear[AttributeDamageWeaponDeltaTotalID][subID] / 2;
		break;
	case AttributeDamageWeaponMaxID:
		value = gear[AttributeDamageWeaponMinID][subID] + gear[AttributeDamageWeaponDeltaID][subID];
		break;
	case AttributeDamageWeaponMinTotalID:
		value = (gear[AttributeDamageWeaponMinID][subID] + gear[AttributeDamageWeaponBonusMinID][subID] + gear[AttributeDamageWeaponBonusMinX1ID][subID] + gear[AttributeDamageWeaponBonusFlatID][subID]) *
			(1 + gear[AttributeDamageWeaponPercentTotalID][subID]);
		break;
	case AttributeDamageWeaponAverageID:
		value = gear[AttributeDamageWeaponMinID][subID] + gear[AttributeDamageWeaponDeltaID][subID] / 2;
		break;
	case AttributeDamageWeaponMaxTotalAllID:
		value = gear[AttributeDamageWeaponMaxTotalID][AttributePhysicalSubID] + gear[AttributeDamageWeaponMaxTotalID][AttributeFireSubID] + gear[AttributeDamageWeaponMaxTotalID][AttributeColdSubID] +
			gear[AttributeDamageWeaponMaxTotalID][AttributeLightningSubID] + gear[AttributeDamageWeaponMaxTotalID][AttributePoisonSubID] + gear[AttributeDamageWeaponMaxTotalID][AttributeArcaneSubID] +
			gear[AttributeDamageWeaponMaxTotalID][AttributeHolySubID];
		break;
	case AttributeDamageWeaponDeltaTotalAllID:
		value = gear[AttributeDamageWeaponDeltaTotalID][AttributePhysicalSubID] + gear[AttributeDamageWeaponDeltaTotalID][AttributeFireSubID] + gear[AttributeDamageWeaponDeltaTotalID][AttributeColdSubID] +
			gear[AttributeDamageWeaponDeltaTotalID][AttributeLightningSubID] + gear[AttributeDamageWeaponDeltaTotalID][AttributePoisonSubID] + gear[AttributeDamageWeaponDeltaTotalID][AttributeArcaneSubID] +
			gear[AttributeDamageWeaponDeltaTotalID][AttributeHolySubID];
		break;
	case AttributeDamageWeaponDeltaSubTotalID:
		value = gear[AttributeDamageWeaponDeltaID][subID] > 1 ? std::max(Range(1), gear[AttributeDamageWeaponDeltaID][subID] - gear[AttributeDamageWeaponBonusMinID][subID]) : gear[AttributeDamageWeaponDeltaID][subID];
		break;
	case AttributeDamageAverageTotalAllID:
		value = gear[AttributeDamageMinTotalAllID][subID] + gear[AttributeDamageDeltaTotalAllID][subID] / 2;
		break;
	case AttributeDamageMinTotalAllID:
		value = gear[AttributeDamageMinTotalID][AttributePhysicalSubID] + gear[AttributeDamageMinTotalID][AttributeFireSubID] + gear[AttributeDamageMinTotalID][AttributeColdSubID] +
			gear[AttributeDamageMinTotalID][AttributeLightningSubID] + gear[AttributeDamageMinTotalID][AttributePoisonSubID] + gear[AttributeDamageMinTotalID][AttributeArcaneSubID] +
			gear[AttributeDamageMinTotalID][AttributeHolySubID];
		break;
	case AttributeDamageDeltaTotalAllID:
		value = gear[AttributeDamageDeltaTotalID][AttributePhysicalSubID] + gear[AttributeDamageDeltaTotalID][AttributeFireSubID] + gear[AttributeDamageDeltaTotalID][AttributeColdSubID] +
			gear[AttributeDamageDeltaTotalID][AttributeLightningSubID] + gear[AttributeDamageDeltaTotalID][AttributePoisonSubID] + gear[AttributeDamageDeltaTotalID][AttributeArcaneSubID] +
			gear[AttributeDamageDeltaTotalID][AttributeHolySubID];
		break;
	case AttributeAttacksPerSecondItemTotalID:
		value = gear[AttributeAttacksPerSecondItemSubtotalID][subID] + gear[AttributeAttacksPerSecondItemBonusID][subID];
		break;
	case AttributeArmorItemTotalID:
		value = gear[AttributeArmorItemID][subID] > 0 ? std::max(Range(1), static_cast<Range>(gear[AttributeArmorItemSubTotalID][subID])) : gear[AttributeArmorItemSubTotalID][subID];
		break;
	case AttributeHeldInOffHandID:
		value = slot_ == SlotOffHand;
		break;
	case AttributeGoldFindID:
	case AttributeMagicFindID:
	case AttributeExperienceBonusID:
	case AttributeResistanceAllID:
	case AttributeHitpointsMaxPercentBonusItemID:
	case AttributePowerCooldownReductionPercentAllID:
	case AttributeDamageWeaponBonusFlatID:
	case AttributeCritDamagePercentID:
	case AttributeThornsFixedID:
	case AttributeHitpointsOnHitID:
	case AttributeDamagePercentBonusVsElitesID:
	case AttributeStrengthItemID:
	case AttributeDexterityItemID:
	case AttributeIntelligenceItemID:
	case AttributeVitalityItemID:
		value = Item::getAttribute(attributeID, subID) + gems[attributeID][subID];
		break;
	default:
		value = Item::getAttribute(attributeID, subID);
	}
	return Attribute(this, attributeID, subID, value);
}