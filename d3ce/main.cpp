//
//  main.cpp
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#include <iostream>
#include "Range.h"
#include <map>
#include "Engine.h"
#include "Party.h"
#include "Wizard.h"
#include "WitchDoctor.h"

#include <tuple>
#include <initializer_list>

namespace d3ce2{
using namespace d3ce;

class Calculator {
public:
	virtual operator d3ce::Range () = 0;
};

class Value: public Calculator {
public:
	Value(Attribute* attribute): attribute_(attribute) {
	}

	virtual operator Range() {
		return attribute_->value();
	}
private:
	Attribute* attribute_;
};

class Const: public Calculator {
	Const(const Range& value): value_(value){};
	Const(double value): value_(value){};

	virtual operator Range() {
		return value_;
	}

private:
	Range value_;
};

template<typename T> class Expression: public Calculator {
public:
	Expression(const T& value): value_(value){};
	virtual operator Range() {
		return value_;
	}
private:
	const T value_;
};

template<typename T1, typename T2> class ExpressionAdd: public Calculator {
public:
	ExpressionAdd(const T1& arg1, const T2& arg2):arg1_(arg1), arg2_(arg2) {};
	operator Range() {
		return static_cast<Range>(arg1_) + static_cast<Range>(arg2_);
	}
private:
	T1 arg1_;
	T2 arg2_;
};

template<typename T1, typename T2> class ExpressionSub: public Calculator {
public:
	ExpressionSub(const T1& arg1, const T2& arg2):arg1_(arg1), arg2_(arg2) {};
	operator Range() {
		return static_cast<Range>(arg1_) - static_cast<Range>(arg2_);
	}
private:
	T1 arg1_;
	T2 arg2_;
};

template<typename T1, typename T2> class ExpressionMul: public Calculator {
public:
	ExpressionMul(const T1& arg1, const T2& arg2):arg1_(arg1), arg2_(arg2) {};
	operator Range() {
		return static_cast<Range>(arg1_) * static_cast<Range>(arg2_);
	}
private:
	T1 arg1_;
	T2 arg2_;
};

template<typename T1, typename T2> class ExpressionDiv: public Calculator {
public:
	ExpressionDiv(const T1& arg1, const T2& arg2):arg1_(arg1), arg2_(arg2) {};
	operator Range() {
		return static_cast<Range>(arg1_) / static_cast<Range>(arg2_);
	}
private:
	T1 arg1_;
	T2 arg2_;
};

template<typename T1, typename T2> ExpressionAdd<T1, T2> operator+ (const T1& arg1, const T2& arg2) {
	return ExpressionAdd<T1, T2>(arg1, arg2);
}

template<typename T1, typename T2> ExpressionSub<T1, T2> operator- (const T1& arg1, const T2& arg2) {
	return ExpressionSub<T1, T2>(arg1, arg2);
}

template<typename T1, typename T2> ExpressionMul<T1, T2> operator* (const T1& arg1, const T2& arg2) {
	return ExpressionMul<T1, T2>(arg1, arg2);
}

template<typename T1, typename T2> ExpressionDiv<T1, T2> operator/ (const T1& arg1, const T2& arg2) {
	return ExpressionDiv<T1, T2>(arg1, arg2);
}

};

int main(int argc, const char * argv[])
{
	{
		std::shared_ptr<d3ce::Engine> engine = d3ce::Engine::Create("D:\\mpq\\Work\\d3.sqlite ");
		//Engine engine("/Users/shimanski/Documents/git/D3Assistant/D3Assistant/Resources/d3.sqlite"); //Work

		//Engine engine("/Users/mr_depth/Work/My/git/D3Parser/Data/d3.sqlite"); // Home

		std::shared_ptr<d3ce::Party> p(new d3ce::Party(engine));

		/*{
			d3ce::Hero& monk = *p->addHero(d3ce::ClassMaskMonk);
			monk[d3ce::AttributeLevelID] = 60;
			monk[d3ce::AttributeAltLevelID] = 303;

			auto& mainHand = *monk.addItem("FistWeapon_1H_205");
			mainHand.setSlot(d3ce::Item::SlotMainHand);
			mainHand["Durability_Max"] = 377;
			mainHand["Resource_Max_Bonus#Spirit"] = 14;
			mainHand["Attacks_Per_Second_Item"] = 1.399999976158142;
			mainHand["Damage_Weapon_Bonus_Delta_X1#Physical"] = 84;
			mainHand["Dexterity_Item"] = 302;
			mainHand["Damage_Weapon_Min#Physical"] = 90;
			mainHand["Attacks_Per_Second_Item_Percent"] = 0.04;
			mainHand["Vitality_Item"] = 300;
			mainHand["Damage_Weapon_Delta#Physical"] = 120;
			mainHand["Damage_Weapon_Bonus_Min_X1#Physical"] = 408;


			auto& offHand = *monk.addItem("FistWeapon_1H_205");
			offHand.setSlot(d3ce::Item::SlotOffHand);
			offHand["Damage_Weapon_Min#Lightning"] = 376;
			offHand["Splash_Damage_Effect_Percent"] = 0.17;
			offHand["Attacks_Per_Second_Item"] = 1.399999976158142;
			offHand["Damage_Weapon_Delta#Lightning"] = 88;
			offHand["Damage_Weapon_Min#Physical"] = 90;
			offHand["Hitpoints_On_Kill"] = 1237;
			offHand["Damage_Weapon_Delta#Physical"] = 120;
			offHand["Spending_Resource_Heals_Percent#Spirit"] = 49;
			offHand["Durability_Max"] = 387;
			offHand["Experience_Bonus"] = 62;
			offHand["Power_Cooldown_Reduction_Percent_All"] = 0.07999999999999996;

			d3ce::Range aps = monk[d3ce::AttributeAttacksPerSecondTotalID];
			d3ce::Range dmg = monk[d3ce::AttributeDamageAverageFullAllMainHandID];
			d3ce::Range critChance = monk[d3ce::AttributeCritPercentBonusTotalID];
			d3ce::Range critDamage = monk[d3ce::AttributeCritDamagePercentTotalID];
			d3ce::Range apsMain = monk[d3ce::AttributeAttacksPerSecondTotalMainHandID];
			d3ce::Range apsOff = monk[d3ce::AttributeAttacksPerSecondTotalOffHandID];
			dmg = monk[d3ce::AttributeDPSID];
			dmg = dmg * aps * (1 + (critChance)* critDamage);//792078
			dmg = dmg;
		}*/


		d3ce::Hero& wizard = *p->addHero(d3ce::ClassMaskWizard);

		wizard[d3ce::AttributeLevelID] = 70;
		wizard[d3ce::AttributeAltLevelID] = 299;
		auto& mainHand = *wizard.addItem("Unique_Sword_1H_002_x1");
		mainHand.setSlot(d3ce::Item::SlotMainHand);
		mainHand["Damage_Weapon_Min#Poison"] = 1199;
		mainHand["Item_Binding_Level_Override"] = 2;
		mainHand["Item_Legendary_Item_Base_Item"] = -270935653;
		mainHand["Experience_Bonus"] = 151;
		mainHand["Durability_Max"] = 351;
		mainHand["Attacks_Per_Second_Item"] = 1.399999976158142;
		mainHand["Loot_2_0_Drop"] = 1;
		mainHand["Durability_Max_Before_Reforge"] = 351;
		mainHand["Damage_Weapon_Min#Physical"] = 168;
		mainHand["Damage_Weapon_Percent_All"] = 0.09;
		mainHand["Intelligence_Item"] = 694;
		mainHand["Weapon_On_Hit_Knockback_Proc_Chance"] = 0.018299999999999983;
		mainHand["Item_LegendaryItem_Level_Override"] = 70;
		mainHand["Sockets"] = 1;
		mainHand["Damage_Weapon_Delta#Poison"] = 289;
		mainHand["Damage_Weapon_Delta#Physical"] = 224;
		mainHand["Durability_Cur"] = 194;
		(*mainHand.addGem("Emerald_19"))["Crit_Damage_Percent"] = 1.3;

		auto& head = *wizard.addItem("Unique_Helm_014_x1");
		head["Item_Binding_Level_Override"] = 2;
		head["Resistance_All"] = 91;
		head["Vitality_Item"] = 686;
		head["Durability_Max"] = 282;
		head["Intelligence_Item"] = 669;
		head["Loot_2_0_Drop"] = 1;
		head["Experience_Bonus"] = 170;
		head["CrowdControl_Reduction"] = 0.30000000000000004;
		head["Armor_Item"] = 758;
		head["Durability_Max_Before_Reforge"] = 282;
		head["IsCrafted"] = 1;
		head["Durability_Cur"] = 282;
		head["Armor_Bonus_Item"] = 378;

		auto& torso = *wizard.addItem("Unique_Chest_Set_13_x1");
		torso["Durability_Cur"] = 287;
		torso["Experience_Bonus"] = 196;
		torso["Health_Globe_Bonus_Health"] = 27792;
		torso["Item_Legendary_Item_Base_Item"] = 1612259889;
		torso["Durability_Max_Before_Reforge"] = 288;
		torso["Loot_2_0_Drop"] = 1;
		torso["Vitality_Item"] = 487;
		torso["Durability_Max"] = 288;
		torso["Item_LegendaryItem_Level_Override"] = 70;
		torso["Crit_Percent_Bonus_Capped"] = 0.02;
		torso["Intelligence_Item"] = 419;
		torso["Sockets"] = 3;
		torso["Item_Binding_Level_Override"] = 2;
		for (int i = 0; i < 3; i++)
			(*torso.addGem("Diamond_18"))["Resistance_All"] = 74;

		auto& feet = *wizard.addItem("Unique_Boots_015_x1");
		feet["Power_Damage_Percent_Bonus#Wizard_ArcaneTorrent"] = 0.15;
		feet["Item_Level_Requirement_Reduction"] = 29;
		feet["Intelligence_Item"] = 442;
		feet["Vitality_Item"] = 442;
		feet["Durability_Cur"] = 434;
		feet["Armor_Item"] = 566.3333129882812;
		feet["IsCrafted"] = 1;
		feet["Resistance_All"] = 92;
		feet["Durability_Max"] = 446;
		feet["Experience_Bonus"] = 200;
		feet["Loot_2_0_Drop"] = 1;
		feet["Durability_Max_Before_Reforge"] = 446;
		feet["Item_Binding_Level_Override"] = 2;

		auto& hands = *wizard.addItem("Unique_Gloves_Set_13_x1");
		hands["Resistance#Lightning"] = 144;
		hands["Crit_Percent_Bonus_Capped"] = 0.08;
		hands["Loot_2_0_Drop"] = 1;
		hands["Durability_Max_Before_Reforge"] = 396;
		hands["Armor_Item"] = 514.3333129882812;
		hands["Durability_Cur"] = 384;
		hands["Durability_Max"] = 396;
		hands["Item_LegendaryItem_Level_Override"] = 2;
		hands["Item_Legendary_Item_Base_Item"] = -1533912119;
		hands["Gold_PickUp_Radius"] = 1;
		hands["Item_Binding_Level_Override"] = 2;
		hands["Crit_Damage_Percent"] = 0.47;
		hands["Intelligence_Item"] = 735;
		hands["Vitality_Item"] = 674;

		auto& shoulders = *wizard.addItem("Unique_Shoulder_008_x1");
		shoulders["Item_Binding_Level_Override"] = 2;
		shoulders["Resistance_All"] = 93;
		shoulders["Vitality_Item"] = 465;
		shoulders["Durability_Max"] = 276;
		shoulders["Intelligence_Item"] = 500;
		shoulders["Loot_2_0_Drop"] = 1;
		shoulders["Armor_Item"] = 644.6666870117188;
		shoulders["Durability_Max_Before_Reforge"] = 276;
		shoulders["IsCrafted"] = 1;
		shoulders["Thorns_Fixed#Physical"] = 3408;
		shoulders["Gold_Find"] = 0.33;
		shoulders["Durability_Cur"] = 0.47;
		shoulders["Armor_Bonus_Item"] = 378;

		auto& legs = *wizard.addItem("Unique_Pants_010_x1");
		legs["Durability_Max"] = 371;
		legs["Armor_Bonus_Item"] = 577;
		legs["Durability_Cur"] = 359;
		legs["Intelligence_Item"] = 472;
		legs["Item_Binding_Level_Override"] = 2;
		legs["Armor_Item"] = 722;
		legs["IsCrafted"] = 1;
		legs["Loot_2_0_Drop"] = 1;
		legs["Vitality_Item"] = 478;
		legs["Resistance#Fire"] = 153;
		legs["Gold_PickUp_Radius"] = 2;
		legs["Durability_Max_Before_Reforge"] = 371;
		legs["Sockets"] = 2;
		for (int i = 0; i < 2; i++)
			(*legs.addGem("Diamond_18"))["Resistance_All"] = 74;

		auto& bracers = *wizard.addItem("Unique_Bracer_106_x1");
		bracers["Intelligence_Item"] = 467;
		bracers["Loot_2_0_Drop"] = 1;
		bracers["Item_Power_Passive#ItemPassive_Unique_Ring_638_x1"] = 1;
		bracers["Armor_Item"] = 380.6666564941406;
		bracers["Damage_Dealt_Percent_Bonus#Lightning"] = 0.16;
		bracers["Gold_PickUp_Radius"] = 1;
		bracers["Durability_Max_Before_Reforge"] = 394;
		bracers["Item_Binding_Level_Override"] = 2;
		bracers["Durability_Cur"] = 382;
		bracers["Durability_Max"] = 394;
		bracers["Crit_Percent_Bonus_Capped"] = 0.06;
		bracers["Item_LegendaryItem_Level_Override"] = 70;
		bracers["Vitality_Item"] = 2;
		bracers["Item_Legendary_Item_Base_Item"] = -875942693;

		auto& offHand = *wizard.addItem("Unique_Orb_003_x1");
		offHand["Resource_Max_Bonus#Arcanum"] = 13;
		offHand["Item_Binding_Level_Override"] = 2;
		offHand["Thorns_Fixed#Physical"] = 1590;
		offHand["Crit_Percent_Bonus_Capped"] = 0.09;
		offHand["Damage_Dealt_Percent_Bonus#Fire"] = 0.07;
		offHand["Damage_Delta#Physical"] = 65;
		offHand["Item_LegendaryItem_Level_Override"] = 70;
		offHand["Item_Legendary_Item_Base_Item"] = 1905181658;
		offHand["Intelligence_Item"] = 710;
		offHand["Resource_On_Crit#Arcanum"] = 4;
		offHand["Loot_2_0_Drop"] = 1;
		offHand["Damage_Dealt_Percent_Bonus#Arcane"] = 0.09;
		offHand["Damage_Dealt_Percent_Bonus#Lightning"] = 0.07;
		offHand["Damage_Min#Physical"] = 348;

		auto& waist = *wizard.addItem("Unique_Belt_105_x1");
		waist["Intelligence_Item"] = 492;
		waist["Vitality_Item"] = 450;
		waist["Hitpoints_Max_Percent_Bonus_Item"] = 0.15;
		waist["Gold_Find"] = 0.33;
		waist["Durability_Max"] = 285;
		waist["Item_Legendary_Item_Base_Item"] = -733829184;
		waist["Armor_Item"] = 475;
		waist["Durability_Cur"] = 273;
		waist["Item_Power_Passive#ItemPassive_Unique_Ring_685_x1"] = 1.26;
		waist["Item_Binding_Level_Override"] = 2;
		waist["Loot_2_0_Drop"] = 1;
		waist["Armor_Bonus_Item"] = 396;
		waist["Item_LegendaryItem_Level_Override"] = 70;
		waist["Durability_Max_Before_Reforge"] = 285;

		auto& rightFinger = *wizard.addItem("Unique_Ring_107_x1");
		rightFinger["Thorns_Fixed#Physical"] = 1985;
		rightFinger["Item_Binding_Level_Override"] = 2;
		rightFinger["Attacks_Per_Second_Percent"] = 0.06;
		rightFinger["Sockets"] = 1;
		rightFinger["Attribute_Set_Item_Discount"] = 1;
		rightFinger["Intelligence_Item"] = 466;
		rightFinger["Loot_2_0_Drop"] = 1;
		rightFinger["Item_LegendaryItem_Level_Override"] = 70;
		rightFinger["Hitpoints_On_Hit"] = 7245;
		rightFinger["Item_Legendary_Item_Base_Item"] = 1146967350;
		{
			auto& gem = *rightFinger.addGem("Unique_Gem_011_x1");
			gem["Jewel_Rank"] = 1;
			gem["Item_Power_Passive#ItemPassive_Unique_Gem_011U_x1"] = 0.1;
			gem["Item_Binding_Level_Override"] = 2;
			gem["Item_Power_Passive#ItemPassive_Unique_Gem_011_x1"] = 3.1;
			gem["Loot_2_0_Drop"] = 1;
		}

		auto& leftFinger = *wizard.addItem("Unique_Ring_103_x1");
		leftFinger["Crit_Percent_Bonus_Capped"] = 0.055;
		leftFinger["Loot_2_0_Drop"] = 1;
		leftFinger["Item_Power_Passive#ItemPassive_Unique_Ring_665_x1"] = 0.84;
		leftFinger["Item_Legendary_Item_Base_Item"] = 1146967350;
		leftFinger["Gold_Find"] = 0.35;
		leftFinger["Damage_Delta#Physical"] = 73;
		leftFinger["Item_Binding_Level_Override"] = 2;
		leftFinger["Sockets"] = 1;
		leftFinger["Intelligence_Item"] = 461;
		leftFinger["Item_LegendaryItem_Level_Override"] = 70;
		leftFinger["Damage_Min#Physical"] = 71;
		{
			auto& gem = *leftFinger.addGem("Unique_Gem_004_x1");
			gem["Jewel_Rank"] = 21;
			gem["Item_Power_Passive#ItemPassive_Unique_Gem_004U_x1"] = 0.25;
			gem["Item_Binding_Level_Override"] = 2;
			gem["Item_Power_Passive#ItemPassive_Unique_Gem_004_x1"] = 3.1;
			gem["Loot_2_0_Drop"] = 8.1;
		}

		auto& neck = *wizard.addItem("Unique_Amulet_105_x1");
		neck["Loot_2_0_Drop"] = 1;
		neck["Item_Legendary_Item_Base_Item"] = 1682228656;
		neck["Item_Binding_Level_Override"] = 2;
		neck["Crit_Percent_Bonus_Capped"] = 0.1;
		neck["Crit_Damage_Percent"] = 0.81;
		neck["Item_Power_Passive#ItemPassive_Unique_Amulet_105_x1"] = 5;
		neck["Damage_Percent_Reduction_From_Melee"] = 0.06000000000000005;
		neck["Sockets"] = 1;
		neck["Intelligence_Item"] = 749;
		neck["Item_LegendaryItem_Level_Override"] = 70;
		{
			auto& gem = *neck.addGem("Unique_Gem_015_x1");
			gem["Jewel_Rank"] = 5;
			gem["Item_Power_Passive#ItemPassive_Unique_Gem_015U_x1"] = 0.005;
			gem["Item_Binding_Level_Override"] = 2;
			gem["Item_Power_Passive#ItemPassive_Unique_Gem_015_x1"] = 25;
			gem["Loot_2_0_Drop"] = 8.1;
		}

		d3ce::Range intil = wizard[d3ce::AttributeIntelligenceTotalID] + 120;
		d3ce::Range intillvl = wizard[d3ce::AttributeIntelligenceTotalFromLevelID] + 120;
		//intil = intil - intillvl;


		d3ce::Range min = mainHand[d3ce::AttributeDamageWeaponMinTotalID][d3ce::AttributePoisonSubID];
		d3ce::Range max = mainHand[d3ce::AttributeDamageWeaponMaxTotalID][d3ce::AttributePoisonSubID];
		d3ce::Range aps = wizard[d3ce::AttributeAttacksPerSecondTotalID];
		d3ce::Range avg = mainHand[d3ce::AttributeDamageWeaponAverageTotalAllID];
		d3ce::Range dmg = wizard[d3ce::AttributeDamageAverageFullAllID];
		d3ce::Range critChance = wizard[d3ce::AttributeCritPercentBonusTotalID];
		d3ce::Range critDamage = wizard[d3ce::AttributeCritDamagePercentTotalID];
		d3ce::Range apsPercent = wizard[d3ce::AttributeAttacksPerSecondPercentID];

		d3ce::Range AttributeAttacksPerSecondBonusIDv = wizard[d3ce::AttributeAttacksPerSecondBonusID];
		d3ce::Range AttributeAttacksPerSecondItemBonusIDv = wizard[d3ce::AttributeAttacksPerSecondItemBonusID];
		d3ce::Range AttributeAttacksPerSecondPercentSubtotalIDv = wizard[d3ce::AttributeAttacksPerSecondPercentSubtotalID];
		d3ce::Range AttributeAttacksPerSecondItemCurrentHandIDv = wizard[d3ce::AttributeAttacksPerSecondItemCurrentHandID];
		d3ce::Range armor = wizard[d3ce::AttributeArmorTotalID];
		d3ce::Range res = wizard[d3ce::AttributeResistanceTotalID][d3ce::AttributeFireSubID];
		dmg = wizard[d3ce::AttributeDPSID];
		aps = aps * (1 + apsPercent);
		critChance = critChance + 0.05;
		critDamage = critDamage + 0.24;
		dmg = dmg * aps * (1 + (critChance)* critDamage);//792078
		min = avg * aps;
	}

	/*auto dodge = wizard->getDodgeChance();
	auto max = wizard->getPrimaryResourceEffectiveMax();
	auto regen = wizard->getPrimaryResourceRegen();
	
	Gear& mainHand = *wizard->addItem("Unique_Mace_1H_001_104");
//	mainHand["Damage_Weapon_Min#Physical"]->setValue(129);
	mainHand["Damage_Dealt_Percent_Bonus#Fire"]->setValue(0.16);
	mainHand["Damage_Weapon_Delta#Fire"]->setValue(386);
	mainHand["Damage_Type_Percent_Bonus#Fire"]->setValue(0.06);
	mainHand["Damage_Weapon_Percent_Bonus#Physical"]->setValue(0.37);
	mainHand["Damage_Weapon_Delta#Physical"]->setValue(109);
	mainHand["Damage_Weapon_Min#Fire"]->setValue(293);
	//mainHand["Attacks_Per_Second_Item"]->setValue(1.2999999523162842);
	mainHand[AttributeDamageWeaponMinID][AttributePhysicalSubID]->setValue(129);
	mainHand[AttributeAttacksPerSecondItemID]->setValue(1.2999999523162842);
	
	float perfection = mainHand.perfection();
	
	auto maxDamage = mainHand[AttributeDamageWeaponMaxTotalAllID]->value();
	auto minDamage = mainHand[AttributeDamageWeaponMinTotalAllID]->value();
	auto wdps = mainHand[AttributeDPSID]->value();
//	auto dps = mainHand[AttributeDamageWeaponAverageID]->value() * mainHand[AttributeDamageWeapon];

	auto belt = wizard->addItem("Unique_Belt_015");
	auto boots = wizard->addItem("Unique_Boots_019");
	auto amulet = wizard->addItem("Unique_Amulet_016");
	auto chest = wizard->addItem("Unique_ChestArmor_028");
	auto pants = wizard->addItem("Unique_Pants_013");
	pants->getAttribute(AttributeDamageWeaponMinID, AttributePhysicalSubID)->setValue(10);
	pants->getAttribute(AttributeDamageWeaponDeltaID, AttributePhysicalSubID)->setValue(100);
	
	auto dps = wizard->getDPS();
	auto res = wizard->getAverageDamageReduction();
	
	wizard->addSkill("glass-cannon");
	wizard->addSkill("familiar-a");
	wizard->addSkill("magic-weapon-c");

	auto dps2 = wizard->getDPS();
	auto res2 = wizard->getAverageDamageReduction();

	Party* p2 = p->clone();
	Hero* h1 = p2->getHeroes().front();

	auto vit2 = h1->getVitality();*/
	
/*	wizard->getAttribute(AttributeLevelID)->setValue(60);
	wizard->getAttribute(AttributeAltLevelID)->setValue(28);
	
	Gear* offHand = wizard->addItem("Unique_Orb_003_104");
	offHand->getAttribute("Crit_Percent_Bonus_Capped")->setValue(0.085);
	offHand->getAttribute("Damage_Delta#Physical")->setValue(16);
	offHand->getAttribute("Damage_Min#Physical")->setValue(71);
	offHand->getAttribute("Intelligence_Item")->setValue(162);
	offHand->getAttribute("Damage_Type_Percent_Bonus#Arcane")->setValue(0.05);
	offHand->getAttribute("Damage_Type_Percent_Bonus#Fire")->setValue(0.05);
	offHand->getAttribute("Damage_Type_Percent_Bonus#Lightning")->setValue(0.05);

	Gear* mainHand = wizard->addItem("Unique_Orb_003_104");
	mainHand->getAttribute("Damage_Weapon_Min#Physical")->setValue(160);
	mainHand->getAttribute("Damage_Weapon_Bonus_Min#Physical")->setValue(291);
	mainHand->getAttribute("Damage_Weapon_Delta#Physical")->setValue(136);
	mainHand->getAttribute("Attacks_Per_Second_Item_Bonus")->setValue(0.24);
	mainHand->getAttribute("Attacks_Per_Second_Item")->setValue(1.2);
	mainHand->getAttribute("Attacks_Per_Second_Item_Percent")->setValue(0.05);
	mainHand->getAttribute("Damage_Weapon_Bonus_Delta#Physical")->setValue(362);
	mainHand->getAttribute("Damage_Weapon_Percent_Bonus#Physical")->setValue(0.39);
	mainHand->getAttribute("Intelligence_Item")->setValue(154);
	auto dps = wizard->getDPS();

//	staff->removeGem(gem);
//	intel = wizard->getAttribute(AttributeIntelligenceTotalID)->getValue();
//	wizard->removeItem(staff);
//	intel = wizard->getAttribute(AttributeIntelligenceTotalID)->getValue();
	
	Party* p2 = p->clone();
	Hero* h1 = p->getHeroes().front();
	
	auto intel2 = h1->getAttribute(AttributeIntelligenceTotalID)->getValue();
	delete p2;
	delete p;*/
    return 0;
}

