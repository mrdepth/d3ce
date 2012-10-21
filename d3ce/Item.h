//
//  Item.h
//  d3ce
//
//  Created by Artem Shimanski on 24.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef __d3ce__Item__
#define __d3ce__Item__

#include "Entity.h"

namespace d3ce {

	class Item: public Entity {
	public:
		enum Slot {
			SlotHead = 0x01,
			SlotTorso = 0x02,
			SlotOffHand = 0x03,
			SlotMainHand = 0x04,
			SlotHands = 0x05,
			SlotWaist = 0x06,
			SlotFeet = 0x07,
			SlotShoulders = 0x08,
			SlotLegs = 0x09,
			SlotBracers = 0x0a,
			SlotRightFinger = 0x0b,
			SlotLeftFinger = 0x0c,
			SlotNeck = 0x0d,
			
			SlotFollowerOffHand = 0x15,
			SlotFollowerMainHand = 0x16,
			SlotFollowerSpecial = 0x17,
			SlotFollowerNeck = 0x18,
			SlotFollowerRightFinger = 0x19,
			SlotFollowerLeftFinger = 0x1a,
			
			SlotSocket = 0x100
		};
		
		static const int LegendaryFlag = 0x01;
		
		class UnknownItemHashException : public std::exception {};
		class UnknownItemTypeHashException : public std::exception {};

		
		static Item* CreateItem(Engine* engine, Entity* parent, Hash itemHash);
		static Item* CreateItem(Engine* engine, Entity* parent, const std::string& nonNlsKey);
		Slot getSlot();
		void setSlot(Slot slot);
		
		const std::vector<Slot>& possibleSlots();
		const std::vector<Hash>& itemTypesTree();

		bool conforms(Hash hash);
		
		const std::map<AttributeKey, Range> possibleModifiers();
		
	protected:
		Hash itemHash_;
		std::vector<Hash> itemTypesTree_;
		int flags_;
		int bitMask_;
		int itemLevel_;
		
		std::vector<Slot> possibleSlots_;
		Slot slot_;
		std::map<AttributeKey, Range> possibleModifiers_;
		
		Item(const Item& other, Entity* parent);
		Item(Engine* engine, Entity* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, int flags, int bitMask, const std::vector<Slot>& possibleSlots);
		virtual Environment environment();
		
	private:
		static Item* CreateItemFromRequest(Engine* engine, Entity* parent, const std::string& sqlRequest);
	};
	
}

#endif /* defined(__d3ce__Item__) */
