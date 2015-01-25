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
		enum Slot: int32_t {
			SlotUnknown = 0,
			SlotHead = 1 << 0,
			SlotTorso = 1 << 1,
			SlotOffHand = 1 << 2,
			SlotMainHand = 1 << 3,
			SlotHands = 1 << 4,
			SlotWaist = 1 << 5,
			SlotFeet = 1 << 6,
			SlotShoulders = 1 << 7,
			SlotLegs = 1 << 8,
			SlotBracers = 1 << 9,
			SlotRightFinger = 1 << 10,
			SlotLeftFinger = 1 << 11,
			SlotNeck = 1 << 12,

			SlotAny = SlotHead | SlotTorso | SlotOffHand | SlotMainHand | SlotHands | SlotWaist | SlotFeet | SlotShoulders | SlotLegs | SlotBracers | SlotRightFinger | SlotLeftFinger | SlotNeck,
			
			SlotFollowerOffHand = 1 << 16,
			SlotFollowerMainHand = 1 << 17,
			SlotFollowerSpecial = 1 << 18,
			SlotFollowerNeck = 1 << 19,
			SlotFollowerRightFinger = 1 << 20,
			SlotFollowerLeftFinger = 1 << 21,
			
			SlotSocket = 1 << 30
		};
		
		
		static const int LegendaryFlag = 0x01;
		
		class UnknownItemHashException : public std::exception {};
		class UnknownItemTypeHashException : public std::exception {};

		
		static std::shared_ptr<Item> CreateItem(std::shared_ptr<Engine> engine, Entity* parent, Hash itemHash);
		static std::shared_ptr<Item> CreateItem(std::shared_ptr<Engine> engine, Entity* parent, const std::string& nonNlsKey);
		Slot getSlot() const;
		void setSlot(Slot slot);
		int32_t getClassMask() const;
		
		const Slot possibleSlots();
		const std::vector<Hash>& itemTypesTree();

		bool conforms(Hash hash);
		
		const std::map<AttributeKey, Range> possibleModifiers() const;
		
	protected:
		Hash itemHash_;
		std::vector<Hash> itemTypesTree_;
		int flags_;
		int bitMask_;
		int itemLevel_;
		
		Slot possibleSlots_;
		Slot slot_;
		mutable std::map<AttributeKey, Range> possibleModifiers_;
		
		Item(const Item& other, Entity* parent);
		Item(std::shared_ptr<Engine> engine, Entity* parent, Hash itemHash, const std::vector<Hash>& itemTypesTree, int flags, int bitMask, Slot possibleSlots);
		virtual Environment environment();
		
	private:
		static std::shared_ptr<Item> CreateItemFromRequest(std::shared_ptr<Engine> engine, Entity* parent, const std::string& sqlRequest);
	};
	
}

#endif /* defined(__d3ce__Item__) */
