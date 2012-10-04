//
//  Skill.cpp
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include "Skill.h"

using namespace d3ce;

const Hash SkillEnergyArmorHash = hash("energy-armor");
const Hash SkillEnergyArmorAHash = hash("energy-armor-a");
const Hash SkillEnergyArmorEHash = hash("energy-armor-e");

const Hash SkillMagicWeaponHash = hash("magic-weapon");
const Hash SkillMagicWeaponCHash = hash("magic-weapon-c");

const Hash SkillGlassCannonHash = hash("glass-cannon");
const Hash SkillGalvanizingWardHash = hash("galvanizing-ward");
const Hash SkillFamiliarAHash = hash("familiar-a");

const Hash SkillRuthlessHash = hash("ruthless");
const Hash SkillNervesOfSteelHash = hash("nerves-of-steel");
const Hash SkillWeaponsMasterHash = hash("weapons-master");
const Hash SkillBerserkerRageHash = hash("berserker-rage");
const Hash SkillSuperstitionHash = hash("superstition");
const Hash SkillToughAsNailsHash = hash("tough-as-nails");
const Hash SkillBrawlerHash = hash("brawler");

const Hash SkillSteadyAimHash = hash("steady-aim");
const Hash SkillArcheryHash = hash("archery");

const Hash SkillSeizeTheInitiativeHash = hash("seize-the-initiative");
const Hash SkillTheGuardiansPathHash = hash("the-guardians-path");
const Hash SkillSixthSenseHash = hash("sixth-sense");
const Hash SkillOneWithEverythingHash = hash("one-with-everything");



Skill::Skill(Engine* engine, Entity* parent, const std::string& skillName) : Entity(engine, parent), skillname_(skillName) {
	Hash skillNameHash = hash(skillName);
	//Wizard
	if (skillNameHash == SkillEnergyArmorHash) {
		getAttribute(AttributeArmorBonusSkillPercentID)->setValue(0.65);
	}
	else if (skillNameHash == SkillEnergyArmorAHash) {
		getAttribute(AttributeArmorBonusSkillPercentID)->setValue(0.65);
		getAttribute(AttributeResistancePercentAllID)->setValue(0.40);
	}
	else if (skillNameHash == SkillEnergyArmorEHash) {
		getAttribute(AttributeArmorBonusSkillPercentID)->setValue(0.65);
		getAttribute(AttributeCritPercentBonusCappedID)->setValue(0.05);
	}
	else if (skillNameHash == SkillMagicWeaponHash) {
		getAttribute(AttributeDamageBonusSkillPercentID)->setValue(0.10);
	}
	else if (skillNameHash == SkillMagicWeaponCHash) {
		getAttribute(AttributeDamageBonusSkillPercentID)->setValue(0.15);
	}
	else if (skillNameHash == SkillGlassCannonHash) {
		getAttribute(AttributeDamageBonusSkillPercentID)->setValue(0.15);
		getAttribute(AttributeResistancePercentAllID)->setValue(-0.10);
	}
	else if (skillNameHash == SkillGalvanizingWardHash) {
		getAttribute(AttributeHitpointsRegenPerSecondID)->setValue(310);
	}
	else if (skillNameHash == SkillFamiliarAHash) {
		getAttribute(AttributeDamageBonusSkillPercentID)->setValue(0.12);
	}
	//Barbarian
	else if (skillNameHash == SkillRuthlessHash) {
		getAttribute(AttributeCritPercentBonusCappedID)->setValue(0.05);
		getAttribute(AttributeCritDamagePercentID)->setValue(0.50);
	}
	else if (skillNameHash == SkillNervesOfSteelHash) {
		getAttribute(AttributeArmorFromVitalityFactorID)->setValue(1);
	}
	else if (skillNameHash == SkillWeaponsMasterHash) {
		getAttribute(AttributeDamagePercentBonusFromSwordsID)->setValue(0.15);
		getAttribute(AttributeDamagePercentBonusFromDaggersID)->setValue(0.15);
		getAttribute(AttributeCritPercentBonusFromMacesID)->setValue(0.10);
		getAttribute(AttributeCritPercentBonusFromAxesID)->setValue(0.10);
		getAttribute(AttributeAttacksPerSecondPercentBonusFromPolearmsID)->setValue(0.10);
		getAttribute(AttributeAttacksPerSecondPercentBonusFromSpearsID)->setValue(0.10);
	}
	else if (skillNameHash == SkillBerserkerRageHash) {
		getAttribute(AttributeDamageBonusSkillPercentID)->setValue(0.25);
	}
	else if (skillNameHash == SkillSuperstitionHash) {
		getAttribute(AttributeDamageReductionTotalID, AttributeFireSubID)->setValue(0.20);
		getAttribute(AttributeDamageReductionTotalID, AttributeLightningSubID)->setValue(0.20);
		getAttribute(AttributeDamageReductionTotalID, AttributeColdSubID)->setValue(0.20);
		getAttribute(AttributeDamageReductionTotalID, AttributePoisonSubID)->setValue(0.20);
		getAttribute(AttributeDamageReductionTotalID, AttributeArcaneSubID)->setValue(0.20);
		getAttribute(AttributeDamageReductionTotalID, AttributeHolySubID)->setValue(0.20);
	}
	else if (skillNameHash == SkillToughAsNailsHash) {
		getAttribute(AttributeArmorBonusSkillPercentID)->setValue(0.25);
		getAttribute(AttributeThornsPercentID)->setValue(0.50);
	}
	else if (skillNameHash == SkillBrawlerHash) {
		getAttribute(AttributeDamageBonusSkillPercentID)->setValue(0.30);
	}
	//Demon Hunter
	else if (skillNameHash == SkillSteadyAimHash) {
		getAttribute(AttributeDamageBonusSkillPercentID)->setValue(0.20);
	}
	else if (skillNameHash == SkillArcheryHash) {
		getAttribute(AttributeDamagePercentBonusFromBowID, AttributeFireSubID)->setValue(0.15);
		getAttribute(AttributeCritDamagePercentBonusFromCrossbowID, AttributeLightningSubID)->setValue(0.50);
		getAttribute(AttributeCritPercentBonusFromHandXbowID, AttributeColdSubID)->setValue(0.10);
	}
	//Monk
	else if (skillNameHash == SkillSeizeTheInitiativeHash) {
		getAttribute(AttributeArmorFromDexterityFactorID)->setValue(1);
	}
	else if (skillNameHash == SkillTheGuardiansPathHash) {
		getAttribute(AttributeDodgeChanceBonusFromDualWieldingID)->setValue(1);
	}
	else if (skillNameHash == SkillSixthSenseHash) {
		getAttribute(AttributeDodgeChanceBonusFromCritPercentFactorID)->setValue(0.30);
	}
	else if (skillNameHash == SkillOneWithEverythingHash) {
		getAttribute(AttributeResistanceFlatID)->setValue(0.30);
	}
}

Skill::Skill(const Skill& other, Entity* parent) : Entity(other, parent), skillname_(other.skillname_) {
	
}

Entity* Skill::cloneIn(Entity* parent) {
	return new Skill(*this, parent);
}

const std::string& Skill::skillName() {
	return skillname_;
}


Environment Skill::environment() {
	Entity* hero = getParent();
	return Environment(this, hero, hero->getParent());
}
