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

using namespace d3ce;


int main(int argc, const char * argv[])
{
	//Engine engine("j:\\Users\\mr_depth\\Work\\My\\git\\D3Parser\\Data\\d3.sqlite");
	Engine engine("/Users/shimanski/Documents/git/D3Assistant/D3Assistant/Resources/d3.sqlite"); //Work
	
	//Engine engine("/Users/mr_depth/Work/My/git/D3Parser/Data/d3.sqlite"); // Home
	
	Party* p = new Party(&engine);
	Hero* wizard = p->addHero(ClassMaskWitchDoctor);
	wizard->getAttribute(AttributeLevelID)->setValue(60);
	wizard->getAttribute(AttributeAltLevelID)->setValue(28);
	
	auto dodge = wizard->getDodgeChance();
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
/*	wizard->removeItem(pants);
	wizard->removeItem(chest);
	wizard->removeItem(amulet);
	wizard->removeItem(boots);
	wizard->removeItem(belt);*/
	
	auto dps = wizard->getDPS();
	auto res = wizard->getAverageDamageReduction();
	
	wizard->addSkill("glass-cannon");
	wizard->addSkill("familiar-a");
	wizard->addSkill("magic-weapon-c");

	auto dps2 = wizard->getDPS();
	auto res2 = wizard->getAverageDamageReduction();

	Party* p2 = p->clone();
	Hero* h1 = p2->getHeroes().front();

	auto vit2 = h1->getVitality();
	
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

