//
//  Attribute.cpp
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Attribute.h"
#include "Entity.h"

using namespace d3ce;

Attribute::Attribute(const Entity* entity, AttributeID attributeID, AttributeSubID attributeSubID, const Range& value): entity_(entity), attributeID_(attributeID), attributeSubID_(attributeSubID), value_(value) {
}


/*Attribute::Attribute(AttributeID attributeID, AttributeSubID attributeSubID, const Environment& environment, const Range& value) : attributeID_(attributeID), attributeSubID_(attributeSubID), environment_(environment), initialValue_(value) {
	switch(attributeID_) {
			
		//Primary Attributes
			
		case AttributeArmorBonusItemID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeArmorItemTotalID, ptr(V(*this))));
			break;
		case AttributeArmorItemID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeArmorItemTotalID, ptr(V(*this))));
			break;
		case AttributeArmorItemPercentID:
			modifiers_.push_back(new ModifierPostBoost(environment.self, AttributeArmorItemTotalID, ptr(V(*this))));
			break;
		case AttributeArmorID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeArmorTotalID, ptr(V(*this))));
			break;
		case AttributeArmorItemTotalID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeArmorTotalID, ptr(V(*this))));
			break;
		case AttributeArmorBonusPercentID:
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeArmorTotalID, ptr(V(*this))));
			break;
			
		case AttributeCoreAttributesFromItemBonusMultiplierID:
			modifiers_.push_back(new ModifierPreMul(environment.self, AttributeStrengthItemID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPreMul(environment.self, AttributeDexterityItemID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPreMul(environment.self, AttributeIntelligenceItemID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPreMul(environment.self, AttributeVitalityItemID, ptr(V(*this))));
			break;
		case AttributeStatsAllBonusID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeStrengthTotalID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDexterityTotalID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeIntelligenceTotalID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeVitalityTotalID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeAttackTotalID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributePrecisionBonusID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDefenseTotalID, ptr(V(*this))));
			break;
			
		case AttributeStrengthTotalID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeArmorTotalID, ptr(V(*this))));
			break;
		case AttributeStrengthID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeStrengthTotalID, ptr(V(*this))));
			break;
		case AttributeStrengthBonusID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeStrengthTotalID, ptr(V(*this))));
			break;
		case AttributeStrengthItemID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeStrengthTotalID, ptr(V(*this))));
			break;
		case AttributeStrengthBonusPercentID:
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeStrengthTotalID, ptr(V(*this))));
			break;
		case AttributeStrengthReductionPercentID:
			modifiers_.push_back(new ModifierPostReduce(environment.hero, AttributeStrengthTotalID, ptr(V(*this))));
			break;
		case AttributeStrengthTotalFromLevelID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeStrengthTotalID, ptr(V(*this))));
			break;
			
		case AttributeDexterityTotalID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDodgeChanceFromDexterityID, ptr(min(V(*this), V(100)) * V(0.00100))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDodgeChanceFromDexterityID, ptr(min(max(V(*this) - V(100), V(0)), V(400)) * V(0.00025))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDodgeChanceFromDexterityID, ptr(min(max(V(*this) - V(500), V(0)), V(500)) * V(0.00020))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDodgeChanceFromDexterityID, ptr(min(max(V(*this) - V(1000), V(0)), V(7000)) * V(0.00010))));
			break;
		case AttributeDexterityID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDexterityTotalID, ptr(V(*this))));
			break;
		case AttributeDexterityBonusID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDexterityTotalID, ptr(V(*this))));
			break;
		case AttributeDexterityItemID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDexterityTotalID, ptr(V(*this))));
			break;
		case AttributeDexterityBonusPercentID:
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDexterityTotalID, ptr(V(*this))));
			break;
		case AttributeDexterityReductionPercentID:
			modifiers_.push_back(new ModifierPostReduce(environment.hero, AttributeDexterityTotalID, ptr(V(*this))));
			break;
		case AttributeDexterityTotalFromLevelID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDexterityTotalID, ptr(V(*this))));
			break;

		case AttributeIntelligenceTotalID:
			modifiers_.push_back(new ModifierPostMul(environment.hero, AttributeResistanceFromIntelligenceID, ptr(V(*this))));
			break;
		case AttributeIntelligenceID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeIntelligenceTotalID, ptr(V(*this))));
			break;
		case AttributeIntelligenceBonusID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeIntelligenceTotalID, ptr(V(*this))));
			break;
		case AttributeIntelligenceItemID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeIntelligenceTotalID, ptr(V(*this))));
			break;
		case AttributeIntelligenceBonusPercentID:
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeIntelligenceTotalID, ptr(V(*this))));
			break;
		case AttributeIntelligenceReductionPercentID:
			modifiers_.push_back(new ModifierPostReduce(environment.hero, AttributeIntelligenceTotalID, ptr(V(*this))));
			break;
		case AttributeIntelligenceTotalFromLevelID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeIntelligenceTotalID, ptr(V(*this))));
			break;

		case AttributeVitalityTotalID:
			modifiers_.push_back(new ModifierPostMul(environment.hero, AttributeHitpointsTotalFromVitalityID, ptr(V(*this))));
			break;
		case AttributeVitalityID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeVitalityTotalID, ptr(V(*this))));
			break;
		case AttributeVitalityBonusID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeVitalityTotalID, ptr(V(*this))));
			break;
		case AttributeVitalityItemID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeVitalityTotalID, ptr(V(*this))));
			break;
		case AttributeVitalityBonusPercentID:
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeVitalityTotalID, ptr(V(*this))));
			break;
		case AttributeVitalityReductionPercentID:
			modifiers_.push_back(new ModifierPostReduce(environment.hero, AttributeVitalityTotalID, ptr(V(*this))));
			break;
		case AttributeVitalityTotalFromLevelID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeVitalityTotalID, ptr(V(*this))));
			break;
			
		//Level Attributes

		case AttributeLevelID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeLevelTotalID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostMul(environment.hero, AttributeHitpointsTotalFromLevelID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPreAssign(environment.hero, AttributeHitpointsFactorVitalityID, ptr(max(V(*this) - V(25), V(10)))));
			//modifiers_.push_back(new ModifierPreAssign(environment.hero, AttributeHitpointsFactorVitalityID, new ExpressionMax(new ExpressionSub(new ExpressionAttribute(this), new ExpressionConst(25)), new ExpressionConst(10))));
			break;
		case AttributeAltLevelID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeLevelTotalID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostMul(environment.hero, AttributeGoldFindAltLevelsTotalID, ptr(V(*this))));
			//modifiers_.push_back(new ModifierPostMul(environment.hero, AttributeMagicFindAltLevelsTotalID, ptr(V(*this))));
			break;
		case AttributeLevelTotalID:
			modifiers_.push_back(new ModifierPostMul(environment.hero, AttributeStrengthTotalFromLevelID, ptr(V(*this) - V(1))));
			modifiers_.push_back(new ModifierPostMul(environment.hero, AttributeDexterityTotalFromLevelID, ptr(V(*this) - V(1))));
			modifiers_.push_back(new ModifierPostMul(environment.hero, AttributeIntelligenceTotalFromLevelID, ptr(V(*this) - V(1))));
			modifiers_.push_back(new ModifierPostMul(environment.hero, AttributeVitalityTotalFromLevelID, ptr(V(*this) - V(1))));
			break;

		//Hitpoints

		case AttributeHitpointsMaxTotalID:
			modifiers_.push_back(new ModifierPreAssign(environment.hero, AttributeHitpointsMaxTotalID, ptr(V(36))));
			break;
		case AttributeHitpointsFactorVitalityID:
			modifiers_.push_back(new ModifierPreAssign(environment.hero, AttributeHitpointsTotalFromVitalityID, ptr(V(*this))));
			break;
		case AttributeHitpointsTotalFromVitalityID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeHitpointsMaxTotalID, ptr(V(*this))));
			break;
		case AttributeHitpointsTotalFromLevelID:
			modifiers_.push_back(new ModifierPreAssign(environment.hero, AttributeHitpointsTotalFromLevelID, ptr(V(4))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeHitpointsMaxTotalID, ptr(V(*this))));
			break;
		case AttributeHitpointsMaxBonusID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeHitpointsMaxTotalID, ptr(V(*this))));
			break;
		case AttributeHitpointsMaxPercentBonusItemID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeHitpointsMaxPercentBonusID, ptr(V(*this))));
			break;
		case AttributeHitpointsMaxPercentBonusID:
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeHitpointsMaxTotalID, ptr(V(*this))));
			break;

		//Weapon Damage

		case AttributeDamageWeaponMinID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponMaxID, attributeSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponMinTotalID, attributeSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponAverageID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeDamageWeaponDeltaID:
		{
			modifiers_.push_back(new ModifierPreAssign(environment.self, AttributeDamageWeaponDeltaSubTotalID, attributeSubID,
													   ptr(min(V(*this), max(V(*this) - V(*(*environment.self)[AttributeDamageWeaponBonusMinID][attributeSubID]), V(1))))));
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponMaxID, attributeSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponAverageID, attributeSubID, ptr(V(*this) / V(2))));
			break;
		}
		case AttributeDamageWeaponBonusMinID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponMinTotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeDamageWeaponBonusDeltaID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponDeltaTotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeDamageWeaponPercentBonusID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponPercentTotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeDamageWeaponPercentAllID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponPercentTotalID, AttributePhysicalSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponPercentTotalID, AttributeFireSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponPercentTotalID, AttributeLightningSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponPercentTotalID, AttributeColdSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponPercentTotalID, AttributePoisonSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponPercentTotalID, AttributeArcaneSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponPercentTotalID, AttributeHolySubID, ptr(V(*this))));
			break;

		case AttributeDamageWeaponDeltaSubTotalID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponDeltaTotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeDamageWeaponDeltaTotalID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponMaxTotalID, attributeSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponDeltaTotalAllID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamageDeltaSubTotalID, attributeSubID, ptr(V(*this) / V(*(*environment.hero)[AttributeHeldWeaponsInHandsID]))));
			break;
		case AttributeDamageWeaponMinTotalID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponMaxTotalID, attributeSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponMinTotalAllID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponAverageTotalID, attributeSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamageMinSubtotalID, attributeSubID, ptr(V(*this) / V(*(*environment.hero)[AttributeHeldWeaponsInHandsID]))));
			break;
		case AttributeDamageWeaponMaxTotalID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponMaxTotalAllID, ptr(V(*this))));
			break;
		case AttributeDamageWeaponPercentTotalID:
			modifiers_.push_back(new ModifierPostBoost(environment.self, AttributeDamageWeaponDeltaTotalID, attributeSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostBoost(environment.self, AttributeDamageWeaponMinTotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeDamageWeaponMinTotalAllID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponAverageTotalAllID, ptr(V(*this))));
			break;
		case AttributeDamageWeaponDeltaTotalAllID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDamageWeaponAverageTotalAllID, ptr(V(*this) / V(2))));
			break;

		case AttributeDamageWeaponAverageTotalAllID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeDPSID, ptr(V(*this))));
			break;
		case AttributeHeldWeaponsInHandsID:
		{
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeAttacksPerSecondPercentID, ptr(If(V(*this) == V(2), V(0.15), V(0.0)))));
			modifiers_.push_back(new ModifierPostDiv(environment.self, AttributeAttacksPerSecondSubTotalID, ptr(max(V(*this), V(1)))));
			break;
		}
		case AttributeWeapon2HID:
			modifiers_.push_back(new ModifierPreAssign(environment.hero, AttributeHeld2HandedWeaponID, ptr(V(1))));
		case AttributeWeapon1HID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeHeldWeaponsInHandsID, ptr(V(1))));
			break;

		//Hero Damage
		case AttributePrimaryDamageAttributeID:
		{
			/*modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDPSID,
													   ptr(
														   If(V(*this) == V(PrimaryDamageAttributeDexterity),
															  V(*(*environment.hero)[AttributeDexterityTotalID]),
															  If(V(*this) == V(PrimaryDamageAttributeStrength),
																 V(*(*environment.hero)[AttributeStrengthTotalID]),
																 V(*(*environment.hero)[AttributeIntelligenceTotalID])
																 )
															  ) / V(100))));*/
												 /* for (AttributeSubID i : {AttributePhysicalSubID, AttributeFireSubID, AttributeLightningSubID, AttributeColdSubID, AttributePoisonSubID, AttributeArcaneSubID, AttributeHolySubID}) {
				modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageMinTotalID, i,
														   ptr(
															   If(V(*this) == V(PrimaryDamageAttributeDexterity),
																  V(*(*environment.hero)[AttributeDexterityTotalID]),
																  If(V(*this) == V(PrimaryDamageAttributeStrength),
																	 V(*(*environment.hero)[AttributeStrengthTotalID]),
																	 V(*(*environment.hero)[AttributeIntelligenceTotalID])
																	 )
																  ) / V(100))));
				modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageDeltaTotalID, i,
														   ptr(
															   If(V(*this) == V(PrimaryDamageAttributeDexterity),
																  V(*(*environment.hero)[AttributeDexterityTotalID]),
																  If(V(*this) == V(PrimaryDamageAttributeStrength),
																	 V(*(*environment.hero)[AttributeStrengthTotalID]),
																	 V(*(*environment.hero)[AttributeIntelligenceTotalID])
																	 )
																  ) / V(100))));
			}

			break;
		}
		case AttributeDamageMinID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamageMinSubtotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeDamageMinSubtotalID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamageMinTotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeDamageDeltaID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamageDeltaSubTotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeDamageBonusMinID:
			modifiers_.push_back(new ModifierSub(environment.hero, AttributeDamageDeltaSubTotalID, attributeSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamageMinSubtotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeDamageDeltaSubTotalID:
			modifiers_.push_back(new ModifierPreAssign(environment.hero, AttributeDamageDeltaTotalID, attributeSubID, ptr(max(V(*this), V(0)))));
			break;
		case AttributeDamageTypePercentBonusID:
		{
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamageMinTotalID, attributeSubID, ptr(V(*this) * V(*(*environment.hero)[AttributeDamageMinSubtotalID][AttributePhysicalSubID]))));
			if (attributeSubID != AttributePhysicalSubID) {
				modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamageMinTotalID, attributeSubID, ptr(V(*this) * V(*(*environment.hero)[AttributeDamageMinSubtotalID][attributeSubID]))));
			}
			break;
		}
		case AttributeDamageMinTotalID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamageMinTotalAllID, ptr(V(*this))));
			break;
		case AttributeDamageDeltaTotalID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamageDeltaTotalAllID, ptr(V(*this))));
			break;
		case AttributeDamageMinTotalAllID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamageAverageTotalAllID, ptr(V(*this))));
			break;
		case AttributeDamageDeltaTotalAllID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamageAverageTotalAllID, ptr(V(*this) / V(2))));
			break;
		case AttributeDamageAverageTotalAllID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDPSID, ptr(V(*this))));
			break;
								 
			
		//Attack Speed
		case AttributeAttacksPerSecondItemID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeAttacksPerSecondItemSubtotalID, ptr(V(*this))));
			break;
		case AttributeAttacksPerSecondItemPercentID:
			modifiers_.push_back(new ModifierPostBoost(environment.self, AttributeAttacksPerSecondItemSubtotalID, ptr(V(*this))));
			break;
		case AttributeAttacksPerSecondItemSubtotalID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeAttacksPerSecondItemTotalID, ptr(V(*this))));
			break;
		case AttributeAttacksPerSecondItemBonusID:
			modifiers_.push_back(new ModifierAdd(environment.self, AttributeAttacksPerSecondItemTotalID, ptr(V(*this))));
			//modifiers_.push_back(new ModifierAdd(environment.hero, AttributeAttacksPerSecondTotalID, ptr(V(*this))));
			break;
		case AttributeAttacksPerSecondBonusID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeAttacksPerSecondTotalID, ptr(V(*this))));
			break;
		case AttributeAttacksPerSecondItemTotalID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeAttacksPerSecondSubTotalID, ptr(V(1) / V(*this))));
			modifiers_.push_back(new ModifierPostMul(environment.self, AttributeDPSID, ptr(V(*this))));
			break;
		case AttributeAttacksPerSecondSubTotalID:
		{
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeAttacksPerSecondTotalID, ptr(
				If(V(*this) == V(0),
					V(*(*environment.hero)[AttributeAttacksPerSecondID]),
					V(1) / V(*this)))));
			break;
		}
		case AttributeAttacksPerSecondPercentID:
			//modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeAttacksPerSecondTotalID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeAttacksPerSecondPercentTotalID, ptr(V(*this))));
			break;
		case AttributeAttacksPerSecondPercentTotalID:
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeAttacksPerSecondTotalID, ptr(V(*this))));
			break;
		case AttributeAttacksPerSecondTotalID:
			modifiers_.push_back(new ModifierPostMul(environment.hero, AttributeDPSID, ptr(V(*this))));
			break;
			
		//Crit Damage
		case AttributeCritPercentBonusCappedID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeCritPercentBonusTotalID, ptr(V(*this))));
			break;
		case AttributeCritDamagePercentID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeCritDamagePercentTotalID, ptr(V(*this))));
			break;
		case AttributeCritPercentBonusTotalID:
			modifiers_.push_back(new ModifierPreAssign(environment.hero, AttributeCritDamageFactorID, ptr(V(*this))));
			break;
		case AttributeCritDamagePercentTotalID:
			modifiers_.push_back(new ModifierPostMul(environment.hero, AttributeCritDamageFactorID, ptr(V(*this))));
			break;
		case AttributeCritDamageFactorID:
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDPSID, ptr(V(*this))));
			break;
			
		//Resistances
		case AttributeResistanceFromIntelligenceID:
			modifiers_.push_back(new ModifierPreAssign(environment.hero, AttributeResistanceFromIntelligenceID, ptr(V(0.1))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributePhysicalSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributeFireSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributeLightningSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributeColdSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributePoisonSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributeArcaneSubID, ptr(V(*this))));
			break;
		case AttributeResistanceAllID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributePhysicalSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributeFireSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributeLightningSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributeColdSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributePoisonSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributeArcaneSubID, ptr(V(*this))));
			break;
		case AttributeResistancePercentAllID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributeFireSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributeLightningSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributeColdSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributePoisonSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, AttributeArcaneSubID, ptr(V(*this))));
			break;
		case AttributeResistancePercentID:
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeResistanceSubTotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeResistanceSubTotalID:
			modifiers_.push_back(new ModifierPreAssign(environment.hero, AttributeResistanceTotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeResistanceID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResistanceSubTotalID, attributeSubID, ptr(V(*this))));
			break;
			
		//Dodge

		case AttributeDodgeChanceFromDexterityID:
		case AttributeDodgeChanceBonusID:
			modifiers_.push_back(new ModifierPostMul(environment.hero, AttributePierceChanceID, ptr(V(1) - V(*this))));
			break;
		case AttributePierceChanceID:
			modifiers_.push_back(new ModifierPreAssign(environment.hero, AttributePierceChanceID, ptr(V(1))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDodgeChanceTotalID, attributeSubID, ptr(V(1) - V(*this))));
			break;

		//Life regen
			
		case AttributeHitpointsRegenPerSecondID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeHitpointsRegenPerSecondTotalID, ptr(V(*this))));
			break;
		case AttributeHitpointsOnHitID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeHitpointsOnHitTotalID, ptr(V(*this))));
			break;
		case AttributeHitpointsOnKillID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeHitpointsOnKillTotalID, ptr(V(*this))));
			break;
		case AttributeStealHealthPercentID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeStealHealthPercentTotalID, ptr(V(*this))));
			break;
			
		//Magic&Golf find
		case AttributeMagicFindID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeMagicFindCappedSubtotalID, ptr(V(*this))));
			break;
		case AttributeGoldFindID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeGoldFindCappedSubtotalID, ptr(V(*this))));
			break;
		case AttributeGoldFindAltLevelsTotalID:
			modifiers_.push_back(new ModifierPreAssign(environment.hero, AttributeGoldFindAltLevelsTotalID, ptr(V(0.03))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeMagicFindCappedSubtotalID, ptr(V(*this))));
			break;
		case AttributeMagicFindAltLevelsTotalID:
			modifiers_.push_back(new ModifierPreAssign(environment.hero, AttributeMagicFindAltLevelsTotalID, ptr(V(0.03))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeGoldFindCappedSubtotalID, ptr(V(*this))));
			break;
		case AttributeMagicFindCappedSubtotalID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeMagicFindTotalID, ptr(max(V(*this), V(0.03)))));
			break;
		case AttributeGoldFindCappedSubtotalID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeGoldFindTotalID, ptr(max(V(*this), V(0.03)))));
			break;
		case AttributeMagicFindUncappedID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeMagicFindTotalID, ptr(V(*this))));
			break;
		case AttributeGoldFindUncappedID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeGoldFindTotalID, ptr(V(*this))));
			break;
			
		//Block
		case AttributeBlockChanceID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeBlockChanceTotalID, ptr(V(*this))));
			break;
		case AttributeBlockChanceItemID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeBlockChanceTotalID, ptr(V(*this))));
			break;
		case AttributeBlockAmountID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeBlockAmountTotalMinID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeBlockAmountTotalMaxID, ptr(V(*this))));
			break;
		case AttributeBlockAmountItemMinID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeBlockAmountTotalMinID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeBlockAmountTotalMaxID, ptr(V(*this))));
			break;
		case AttributeBlockAmountItemBonusID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeBlockAmountTotalMinID, ptr(V(*this))));
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeBlockAmountTotalMaxID, ptr(V(*this))));
			break;
		case AttributeBlockAmountItemDeltaID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeBlockAmountTotalMaxID, ptr(V(*this))));
			break;
		case AttributeBlockAmountBonusPercentID:
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeBlockAmountTotalMinID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeBlockAmountTotalMaxID, ptr(V(*this))));
			break;
			
		//Resource
		case AttributeResourceMaxID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResourceMaxTotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeResourceMaxBonusID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResourceMaxTotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeResourceFactorLevelID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResourceMaxTotalID, attributeSubID,
												 ptr((V(*(*environment.hero)[AttributeLevelID]) - V(1)) * V(*this))));
			break;
		case AttributeResourceMaxPercentBonusID:
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeResourceMaxTotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeResourceRegenPerSecondID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResourceRegenSubTotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeResourceRegenSubTotalID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResourceRegenTotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeResourceRegenBonusPercentID:
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeResourceRegenSubTotalID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeResourceRegenPercentPerSecondID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResourceRegenTotalID, attributeSubID,
												 ptr(V(*this) * V(*(*environment.hero)[AttributeResourceMaxTotalID][attributeSubID]) )));
			break;
		case AttributeResourceMaxTotalID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResourceEffectiveMaxID, attributeSubID, ptr(V(*this))));
			break;
		case AttributeResourceCapacityUsedID:
			modifiers_.push_back(new ModifierSub(environment.hero, AttributeResourceEffectiveMaxID, attributeSubID, ptr(V(*this))));
			break;
			
		//Skills
		case AttributeArmorBonusSkillPercentID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeArmorBonusPercentID, ptr(V(*this))));
			break;
		case AttributeDamagePercentAllFromSkillsID:
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageMinTotalID, AttributePhysicalSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageMinTotalID, AttributeFireSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageMinTotalID, AttributeLightningSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageMinTotalID, AttributeColdSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageMinTotalID, AttributePoisonSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageMinTotalID, AttributeArcaneSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageMinTotalID, AttributeHolySubID, ptr(V(*this))));

			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageDeltaTotalID, AttributePhysicalSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageDeltaTotalID, AttributeFireSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageDeltaTotalID, AttributeLightningSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageDeltaTotalID, AttributeColdSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageDeltaTotalID, AttributePoisonSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageDeltaTotalID, AttributeArcaneSubID, ptr(V(*this))));
			modifiers_.push_back(new ModifierPostBoost(environment.hero, AttributeDamageDeltaTotalID, AttributeHolySubID, ptr(V(*this))));
			break;
		case AttributeDamageBonusSkillPercentID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamagePercentAllFromSkillsID, ptr(V(*this))));
			break;
		case AttributeArmorFromVitalityFactorID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeArmorTotalID, ptr(V(*(*environment.hero)[AttributeVitalityTotalID]) * V(*this))));
			break;
		case AttributeArmorFromDexterityFactorID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeArmorTotalID, ptr(V(*(*environment.hero)[AttributeDexterityTotalID]) * V(*this))));
			break;
		case AttributeDamagePercentBonusFromSwordsID:
		{
			Hero* hero = dynamic_cast<Hero*>(environment_.hero);
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamagePercentAllFromSkillsID,
				ptr(If(conforms(hero, Item::SlotMainHand, V(hash("Sword"))), V(*this), If(conforms(hero, Item::SlotMainHand, V(hash("Sword2H"))), V(*this), V(0))))));
			break;
		}
		case AttributeDamagePercentBonusFromDaggersID:
		{
			Hero* hero = dynamic_cast<Hero*>(environment_.hero);
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamagePercentAllFromSkillsID,
				ptr(If(conforms(hero, Item::SlotMainHand, V(hash("Dagger"))), V(*this), V(0)))));
			break;
		}
		case AttributeCritPercentBonusFromMacesID:
		{
			Hero* hero = dynamic_cast<Hero*>(environment_.hero);
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeCritPercentBonusCappedID,
				ptr(If(conforms(hero, Item::SlotMainHand, V(hash("Mace"))), V(*this), If(conforms(hero, Item::SlotMainHand, V(hash("Mace2H"))), V(*this), V(0))))));
			break;
		}
		case AttributeCritPercentBonusFromAxesID:
		{
			Hero* hero = dynamic_cast<Hero*>(environment_.hero);
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeCritPercentBonusCappedID,
				ptr(If(conforms(hero, Item::SlotMainHand, V(hash("Axe"))), V(*this), If(conforms(hero, Item::SlotMainHand, V(hash("Axe2H"))), V(*this), V(0))))));
			break;
		}
		case AttributeAttacksPerSecondPercentBonusFromPolearmsID:
		{
			Hero* hero = dynamic_cast<Hero*>(environment_.hero);
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeAttacksPerSecondPercentID,
				ptr(If(conforms(hero, Item::SlotMainHand, V(hash("Polearm"))), V(*this), V(0)))));
			break;
		}
		case AttributeAttacksPerSecondPercentBonusFromSpearsID:
		{
			Hero* hero = dynamic_cast<Hero*>(environment_.hero);
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeAttacksPerSecondPercentID,
				ptr(If(conforms(hero, Item::SlotMainHand, V(hash("Spear"))), V(*this), V(0)))));
			break;
		}
		case AttributeDamagePercentBonusFromBowID:
		{
			Hero* hero = dynamic_cast<Hero*>(environment_.hero);
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeDamagePercentAllFromSkillsID,
				ptr(If(conforms(hero, Item::SlotMainHand, V(hash("Bow"))), V(*this), V(0)))));
			break;
		}
		case AttributeCritDamagePercentBonusFromCrossbowID:
		{
			Hero* hero = dynamic_cast<Hero*>(environment_.hero);
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeCritDamagePercentID,
				ptr(If(conforms(hero, Item::SlotMainHand, V(hash("Crossbow"))), V(*this), V(0)))));
			break;
		}
		case AttributeCritPercentBonusFromHandXbowID:
		{
			Hero* hero = dynamic_cast<Hero*>(environment_.hero);
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeCritPercentBonusCappedID,
				ptr(If(conforms(hero, Item::SlotMainHand, V(hash("HandXbow"))), V(*this), V(0)))));
			break;
		}
		case AttributeDodgeChanceBonusFromDualWieldingID:
			modifiers_.push_back(new ModifierPostMul(environment.hero, AttributePierceChanceID,
													 ptr(If(V(*(*environment.hero)[AttributeHeldWeaponsInHandsID]) == V(2), V(1.0) - V(*this), V(1.0)))));
			break;
		case AttributeResourceRegenBonusPercentFrom2HandedWeaponID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeResourceRegenBonusPercentID, AttributeSpiritSubID,
													 ptr(If(V(*(*environment.hero)[AttributeHeld2HandedWeaponID]), V(*this), V(0)))));
			break;
		case AttributeDodgeChanceBonusFromCritPercentFactorID:
			modifiers_.push_back(new ModifierPostMul(environment.hero, AttributePierceChanceID,
													 ptr(V(1) - V(*(*environment.hero)[AttributeCritPercentBonusTotalID]) * V(*this))));
			break;
		case AttributeResistanceFlatID:
		{
			Entity& hero = *environment.hero;
			
			/*for (AttributeSubID i = AttributePhysicalSubID; i <= AttributeHolySubID; i++) {
				modifiers_.push_back(new ModifierPostAssign(environment.hero, AttributeResistanceTotalID, i,
															ptr(
																max(max(max(V(*hero[AttributeResistanceSubTotalID][AttributePhysicalSubID]), V(*hero[AttributeResistanceSubTotalID][AttributeFireSubID])),
																		max(V(*hero[AttributeResistanceSubTotalID][AttributeLightningSubID]), V(*hero[AttributeResistanceSubTotalID][AttributeColdSubID]))),
																	max(V(*hero[AttributeResistanceSubTotalID][AttributeHolySubID]),
																		max(V(*hero[AttributeResistanceSubTotalID][AttributePoisonSubID]), V(*hero[AttributeResistanceSubTotalID][AttributeArcaneSubID]))))
																)));
			}*/
/*
		}
		case AttributeHitpointsRegenPercentPerSecondID:
			modifiers_.push_back(new ModifierAdd(environment.hero, AttributeHitpointsRegenPerSecondTotalID, ptr(V(*this) * V(*(*environment.hero)[AttributeHitpointsMaxTotalID]))));
			break;
		default:
			break;
	};
}

Attribute::~Attribute() {
	std::vector<Modifier*>::iterator i, end = modifiers_.end();
	for (i = modifiers_.begin(); i != end; i++)
		delete *i;
}

Range Attribute::value() {
	std::vector<Modifier*> modifiers = environment_.self->getAttributeModifiers(this);
	if (modifiers.size() > 0) {
//		std::sort(modifiers.begin(), modifiers.end(), PriorityCompare());
		std::vector<Modifier*>::iterator i, end = modifiers.end();
		
		Range value = initialValue_;
		for (i = modifiers.begin(); i != end; i++) {
			value = (*i)->apply(value);
		}
		return value;
	}
	else
		return initialValue_;
}

Range Attribute::getInitialValue() {
	return initialValue_;
}

void Attribute::setValue(const Range& value) {
	initialValue_ = value;
}

void Attribute::applyModifiers() {
	std::vector<Modifier*>::iterator i, end = modifiers_.end();
	for (i = modifiers_.begin(); i != end; i++) {
		(*i)->entity_->addModifier(*i);
	}
}

void Attribute::removeModifiers() {
	std::vector<Modifier*>::iterator i, end = modifiers_.end();
	for (i = modifiers_.begin(); i != end; i++) {
		(*i)->entity_->removeModifier(*i);
	}
}*/
