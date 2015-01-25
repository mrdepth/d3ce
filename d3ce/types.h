//
//  types.h
//  d3ce
//
//  Created by Artem Shimanski on 27.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef d3ce_types_h
#define d3ce_types_h
#include "Range.h"

namespace d3ce {
	
	typedef int Hash;
	
	struct Resistance {
		Range physical;
		Range fire;
		Range lightning;
		Range cold;
		Range poison;
		Range arcane;
		Range holy;
	};

	enum ClassMask {
		classMaskUnknown = 0x0,
		ClassMaskBarbarian = 0x0100,
		ClassMaskWizard = 0x0200,
		ClassMaskWitchDoctor = 0x0400,
		ClassMaskDemonHunter = 0x0800,
		ClassMaskMonk = 0x2000,
		ClassMaskCrusader = 0x20000,
		ClassMaskAnyClass = ClassMaskBarbarian | ClassMaskWizard | ClassMaskWitchDoctor |ClassMaskDemonHunter | ClassMaskMonk | ClassMaskCrusader
	};
	
	enum SlotIdentifier {
		SlotIdentifierUnknown = 0x0,
		SlotIdentifierHead = 0x01,
		SlotIdentifierTorso = 0x02,
		SlotIdentifierOffHand = 0x03,
		SlotIdentifierMainHand = 0x04,
		SlotIdentifierHands = 0x05,
		SlotIdentifierWaist = 0x06,
		SlotIdentifierFeet = 0x07,
		SlotIdentifierShoulders = 0x08,
		SlotIdentifierLegs = 0x09,
		SlotIdentifierBracers = 0x0a,
		SlotIdentifierRightFinger = 0x0b,
		SlotIdentifierLeftFinger = 0x0c,
		SlotIdentifierNeck = 0x0d,
		
		SlotIdentifierFollowerOffHand = 0x15,
		SlotIdentifierFollowerMainHand = 0x16,
		SlotIdentifierFollowerSpecial = 0x17,
		SlotIdentifierFollowerNeck = 0x18,
		SlotIdentifierFollowerRightFinger = 0x19,
		SlotIdentifierFollowerLeftFinger = 0x1a,
		
		SlotIdentifierSocket = 0x100
	};
	
	const int ItemTypeGemFlag = 0x08;
	
	const Hash ItemTypeArmorHash = 119253633;
	const Hash ItemTypeJewelryHash = -740765630;
	const Hash ItemTypeWeaponHash = 485534122;
	const Hash ItemTypeOffHandHash = 1440677334;
	const Hash ItemTypeSocketableHash = -792466723;
	
	const int Weapon1HandedMask = 0x0200;
	const int Weapon2HandedMask = 0x0400;
}

#endif
