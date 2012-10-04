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
		ClassMaskBarbarian = 0x0100,
		ClassMaskWizard = 0x0200,
		ClassMaskWitchDoctor = 0x0400,
		ClassMaskDemonHunter = 0x0800,
		ClassMaskMonk = 0x2000
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
