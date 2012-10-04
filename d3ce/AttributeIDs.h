//
//  AttributeIDs.h
//  d3ce
//
//  Created by Artem Shimanski on 25.09.12.
//  Copyright (c) 2012 Artem Shimanski. All rights reserved.
//

#ifndef d3ce_AttributeIDs_h
#define d3ce_AttributeIDs_h

//select "Attribute" || replace(replace(replace(a.nonNlsKey, "_", ""), "#", ""), " ", "") || "ID = " || a.rawAttributeID || "," from rawAttribute as a;

namespace d3ce {
	typedef int AttributeSubID;
	const AttributeSubID AttributeNoneSubID = -1;
	
	const AttributeSubID AttributePhysicalSubID = 0;
	const AttributeSubID AttributeFireSubID = 1;
	const AttributeSubID AttributeLightningSubID = 2;
	const AttributeSubID AttributeColdSubID = 3;
	const AttributeSubID AttributePoisonSubID = 4;
	const AttributeSubID AttributeArcaneSubID = 5;
	const AttributeSubID AttributeHolySubID = 6;

	const AttributeSubID AttributeManaSubID = 0;
	const AttributeSubID AttributeArcanumSubID = 1;
	const AttributeSubID AttributeFurySubID = 2;
	const AttributeSubID AttributeSpiritSubID = 3;
	const AttributeSubID AttributeHatredSubID = 5;
	const AttributeSubID AttributeDisciplineSubID = 6;

	const AttributeSubID AttributeUndeadSubID = 0;
	const AttributeSubID AttributeDemonSubID = 1;
	const AttributeSubID AttributeBeastSubID = 2;
	const AttributeSubID AttributeHumanSubID = 3;
	
	const int PrimaryDamageAttributeStrength = 0;
	const int PrimaryDamageAttributeDexterity = 1;
	const int PrimaryDamageAttributeIntelligence = 2;

	typedef enum {
		AttributeAxeBadDataID = 0,
		AttributeAttributeTimerID = 1,
		AttributeAttributePoolID = 2,
		AttributeDeathCountID = 3,
		AttributeDualWieldHandID = 4,
		AttributeDualWieldHandNextID = 5,
		AttributeDualWieldHandsSwappedID = 6,
		AttributeRespawnGameTimeID = 7,
		AttributeBackpackSlotsID = 8,
		AttributeSharedStashSlotsID = 9,
		AttributeStrengthID = 10,
		AttributeDexterityID = 11,
		AttributeIntelligenceID = 12,
		AttributeVitalityID = 13,
		AttributeStrengthTotalID = 14,
		AttributeDexterityTotalID = 15,
		AttributeIntelligenceTotalID = 16,
		AttributeVitalityTotalID = 17,
		AttributeStrengthBonusID = 18,
		AttributeDexterityBonusID = 19,
		AttributeIntelligenceBonusID = 20,
		AttributeVitalityBonusID = 21,
		AttributeStrengthBonusPercentID = 22,
		AttributeDexterityBonusPercentID = 23,
		AttributeIntelligenceBonusPercentID = 24,
		AttributeVitalityBonusPercentID = 25,
		AttributeStrengthReductionPercentID = 26,
		AttributeDexterityReductionPercentID = 27,
		AttributeIntelligenceReductionPercentID = 28,
		AttributeVitalityReductionPercentID = 29,
		AttributePrimaryDamageAttributeID = 30,
		AttributeAttackID = 31,
		AttributePrecisionID = 32,
		AttributeDefenseID = 33,
		AttributeAttackTotalID = 34,
		AttributePrecisionTotalID = 35,
		AttributeDefenseTotalID = 36,
		AttributeAttackBonusID = 37,
		AttributePrecisionBonusID = 38,
		AttributeDefenseBonusID = 39,
		AttributeAttackBonusPercentID = 40,
		AttributePrecisionBonusPercentID = 41,
		AttributeDefenseBonusPercentID = 42,
		AttributeAttackReductionPercentID = 43,
		AttributePrecisionReductionPercentID = 44,
		AttributeDefenseReductionPercentID = 45,
		AttributeArmorID = 46,
		AttributeArmorBonusPercentID = 47,
		AttributeArmorItemID = 48,
		AttributeArmorBonusItemID = 49,
		AttributeArmorItemPercentID = 50,
		AttributeArmorItemSubTotalID = 51,
		AttributeArmorItemTotalID = 52,
		AttributeArmorTotalID = 53,
		AttributeExperienceGrantedID = 54,
		AttributeExperienceNextID = 55,
		AttributeAltExperienceNextID = 56,
		AttributeGoldGrantedID = 57,
		AttributeGoldID = 58,
		AttributeGoldFindID = 59,
		AttributeGoldFindUncappedID = 60,
		AttributeGoldFindAltLevelsTotalID = 61,
		AttributeGoldFindCappedSubtotalID = 62,
		AttributeGoldFindTotalID = 63,
		AttributeLevelID = 64,
		AttributeLevelCapID = 65,
		AttributeAltLevelID = 66,
		AttributeMagicFindID = 67,
		AttributeMagicFindUncappedID = 68,
		AttributeMagicFindAltLevelsTotalID = 69,
		AttributeMagicFindCappedSubtotalID = 70,
		AttributeMagicFindTotalID = 71,
		AttributeMagicAndGoldFindSuppressedID = 72,
		AttributeTreasureFindID = 73,
		AttributeResourceCostReductionAmountID = 74,
		AttributeResourceCostReductionTotalID = 75,
		AttributeResourceSetPointBonusID = 76,
		AttributeFasterHealingPercentID = 77,
		AttributeSpendingResourceHealsPercentID = 78,
		AttributeBonusHealingReceivedPercentID = 79,
		AttributeReducedHealingReceivedPercentID = 80,
		AttributeExperienceBonusID = 81,
		AttributeExperienceBonusPercentID = 82,
		AttributeHealthGlobeBonusChanceID = 83,
		AttributeHealthGlobeBonusMultChanceID = 84,
		AttributeHealthGlobeBonusHealthID = 85,
		AttributeIncreasedHealthFromGlobesPercentID = 86,
		AttributeIncreasedHealthFromGlobesPercentTotalID = 87,
		AttributeBonusHealthPercentPerSecondFromGlobesID = 88,
		AttributeBonusHealthPercentPerSecondFromGlobesTotalID = 89,
		AttributeManaGainedFromGlobesPercentID = 90,
		AttributeManaGainedFromGlobesID = 91,
		AttributeResistanceID = 92,
		AttributeResistancePercentID = 93,
		AttributeResistanceTotalID = 94,
		AttributeResistanceAllID = 95,
		AttributeResistancePercentAllID = 96,
		AttributeResistanceFromIntelligenceID = 97,
		AttributeClassDamageReductionPercentID = 98,
		AttributeSkillID = 99,
		AttributeSkillTotalID = 100,
		AttributeTeamIDID = 101,
		AttributeTeamOverrideID = 102,
		AttributeInvulnerableID = 103,
		AttributeLoadingID = 104,
		AttributeLoadingPlayerACDID = 105,
		AttributeLoadingPowerSNOID = 106,
		AttributeLoadingAnimTagID = 107,
		AttributeLoadingNewGameID = 108,
		AttributeAutoPortingToSavePointID = 109,
		AttributeNoDamageID = 110,
		AttributeNoAutoPickupID = 111,
		AttributeLightRadiusPercentBonusID = 112,
		AttributeHitpointsCurID = 113,
		AttributeHitpointsFactorLevelID = 114,
		AttributeHitpointsFactorVitalityID = 115,
		AttributeHitpointsTotalFromVitalityID = 116,
		AttributeHitpointsTotalFromLevelID = 117,
		AttributeHitpointsGrantedID = 118,
		AttributeHitpointsGrantedDurationID = 119,
		AttributeHitpointsMaxID = 120,
		AttributeHitpointsMaxBonusID = 121,
		AttributeHitpointsMaxTotalID = 122,
		AttributeHitpointsPercentID = 123,
		AttributeHitpointsRegenPerSecondID = 124,
		AttributeHitpointsMaxPercentBonusID = 125,
		AttributeHitpointsMaxPercentBonusItemID = 126,
		AttributeHitpointsHealedTargetID = 127,
		AttributeResourceTypePrimaryID = 128,
		AttributeResourceTypeSecondaryID = 129,
		AttributeResourceCurID = 130,
		AttributeResourceMaxID = 131,
		AttributeResourceMaxBonusID = 132,
		AttributeResourceMaxTotalID = 133,
		AttributeResourceFactorLevelID = 134,
		AttributeResourceGrantedID = 135,
		AttributeResourceGrantedDurationID = 136,
		AttributeResourcePercentID = 137,
		AttributeResourceRegenPerSecondID = 138,
		AttributeResourceRegenBonusPercentID = 139,
		AttributeResourceRegenTotalID = 140,
		AttributeResourceMaxPercentBonusID = 141,
		AttributeResourceCapacityUsedID = 142,
		AttributeResourceEffectiveMaxID = 143,
		AttributeResourceRegenPercentPerSecondID = 144,
		AttributeResourceDegenerationStopPointID = 145,
		AttributeMovementScalarID = 146,
		AttributeWalkingRateID = 147,
		AttributeRunningRateID = 148,
		AttributeSprintingRateID = 149,
		AttributeStrafingRateID = 150,
		AttributeWalkingRateTotalID = 151,
		AttributeRunningRateTotalID = 152,
		AttributeLastRunningRateID = 153,
		AttributeSprintingRateTotalID = 154,
		AttributeStrafingRateTotalID = 155,
		AttributeMovementBonusTotalID = 156,
		AttributeMovementScalarSubtotalID = 157,
		AttributeMovementScalarCappedTotalID = 158,
		AttributeMovementScalarUncappedBonusID = 159,
		AttributeMovementScalarTotalID = 160,
		AttributeMovementBonusRunSpeedID = 161,
		AttributeCastingSpeedID = 162,
		AttributeCastingSpeedBonusID = 163,
		AttributeCastingSpeedTotalID = 164,
		AttributeAlwaysHitsID = 165,
		AttributeHitChanceID = 166,
		AttributeAttacksPerSecondItemID = 167,
		AttributeAttacksPerSecondItemPercentID = 168,
		AttributeAttacksPerSecondItemSubtotalID = 169,
		AttributeAttacksPerSecondItemBonusID = 170,
		AttributeAttacksPerSecondItemTotalID = 171,
		AttributeAttacksPerSecondID = 172,
		AttributeAttacksPerSecondBonusID = 173,
		AttributeAttacksPerSecondTotalID = 174,
		AttributeAttacksPerSecondPercentID = 175,
		AttributeAICooldownReductionPercentID = 176,
		AttributePowerCooldownReductionPercentID = 177,
		AttributeDamageDeltaID = 178,
		AttributeDamageDeltaTotalID = 179,
		AttributeDamageMinID = 180,
		AttributeDamageBonusMinID = 181,
		AttributeDamageMinTotalID = 182,
		AttributeDamageDeltaTotalAllID = 183,
		AttributeDamageMinTotalAllID = 184,
		AttributeDamageAverageTotalAllID = 185,
		AttributeDamageMinSubtotalID = 186,
		AttributeDamagePercentAllFromSkillsID = 187,
		AttributeDamageWeaponDeltaID = 188,
		AttributeDamageWeaponDeltaSubTotalID = 189,
		AttributeDamageWeaponMaxID = 190,
		AttributeDamageWeaponMaxTotalID = 191,
		AttributeDamageWeaponMaxTotalAllID = 192,
		AttributeDamageWeaponDeltaTotalID = 193,
		AttributeDamageWeaponDeltaTotalAllID = 194,
		AttributeDamageWeaponBonusDeltaID = 195,
		AttributeDamageWeaponMinID = 196,
		AttributeDamageWeaponMinTotalID = 197,
		AttributeDamageWeaponMinTotalAllID = 198,
		AttributeDamageWeaponAverageID = 199,
		AttributeDamageWeaponAverageTotalID = 200,
		AttributeDamageWeaponAverageTotalAllID = 201,
		AttributeDamageWeaponBonusMinID = 202,
		AttributeDamageWeaponPercentBonusID = 203,
		AttributeDamageWeaponPercentAllID = 204,
		AttributeDamageWeaponPercentTotalID = 205,
		AttributeDamageTypePercentBonusID = 206,
		AttributeDamageDealtPercentBonusID = 207,
		AttributeDamagePercentBonusWitchdoctorID = 208,
		AttributeDamagePercentBonusWizardID = 209,
		AttributeCritPercentBaseID = 210,
		AttributeCritPercentBonusCappedID = 211,
		AttributeCritPercentBonusUncappedID = 212,
		AttributeCritPercentCapID = 213,
		AttributeCritDamagePercentID = 214,
		AttributeCritEffectTimeID = 215,
		AttributePierceChanceID = 216,
		AttributeDamageAbsorbPercentID = 217,
		AttributeDamageReductionTotalID = 218,
		AttributeDamageReductionCurrentID = 219,
		AttributeDamageReductionLastTickID = 220,
		AttributeBlockChanceID = 221,
		AttributeBlockChanceTotalID = 222,
		AttributeBlockChanceBonusItemID = 223,
		AttributeBlockChanceItemID = 224,
		AttributeBlockChanceItemTotalID = 225,
		AttributeBlockAmountID = 226,
		AttributeBlockAmountBonusPercentID = 227,
		AttributeBlockAmountTotalMinID = 228,
		AttributeBlockAmountTotalMaxID = 229,
		AttributeBlockAmountItemMinID = 230,
		AttributeBlockAmountItemDeltaID = 231,
		AttributeBlockAmountItemBonusID = 232,
		AttributeDodgeChanceBonusID = 233,
		AttributeDodgeChanceBonusMeleeID = 234,
		AttributeDodgeChanceBonusRangedID = 235,
		AttributeGetHitCurrentID = 236,
		AttributeGetHitMaxBaseID = 237,
		AttributeGetHitMaxPerLevelID = 238,
		AttributeGetHitMaxID = 239,
		AttributeGetHitRecoveryBaseID = 240,
		AttributeGetHitRecoveryPerLevelID = 241,
		AttributeGetHitRecoveryID = 242,
		AttributeGetHitDamageID = 243,
		AttributeGetHitDamageScalarID = 244,
		AttributeLastDamageMainActorID = 245,
		AttributeLastACDAttackedID = 246,
		AttributeIgnoresCriticalHitsID = 247,
		AttributeImmunityID = 248,
		AttributeUntargetableID = 249,
		AttributeImmobolizeID = 250,
		AttributeImmuneToKnockbackID = 251,
		AttributePowerImmobilizeID = 252,
		AttributeStunChanceID = 253,
		AttributeStunLengthID = 254,
		AttributeStunRecoveryID = 255,
		AttributeStunRecoverySpeedID = 256,
		AttributeStunnedID = 257,
		AttributeStunImmuneID = 258,
		AttributePoisonLengthReductionID = 259,
		AttributePoisonedID = 260,
		AttributeBleedingID = 261,
		AttributeBleedDurationID = 262,
		AttributeChilledID = 263,
		AttributeFreezeLengthReductionID = 264,
		AttributeFreezeImmuneID = 265,
		AttributeWebbedID = 266,
		AttributeSlowID = 267,
		AttributeFireAuraID = 268,
		AttributeLightningAuraID = 269,
		AttributeColdAuraID = 270,
		AttributePoisonAuraID = 271,
		AttributeBlindID = 272,
		AttributeEnragedID = 273,
		AttributeSlowdownImmuneID = 274,
		AttributeGethitImmuneID = 275,
		AttributeSuffocationPerSecondID = 276,
		AttributeSuffocationUnitValueID = 277,
		AttributeThornsPercentID = 278,
		AttributeThornsPercentAllID = 279,
		AttributeThornsPercentTotalID = 280,
		AttributeThornsFixedID = 281,
		AttributeStealHealthPercentID = 282,
		AttributeStealManaPercentID = 283,
		AttributeResourceOnHitID = 284,
		AttributeResourceOnKillID = 285,
		AttributeResourceOnCritID = 286,
		AttributeHitpointsOnHitID = 287,
		AttributeHitpointsOnKillID = 288,
		AttributeDamageToManaID = 289,
		AttributeLastProcTimeID = 290,
		AttributeDamagePowerDeltaID = 291,
		AttributeDamagePowerMinID = 292,
		AttributeRopeOverlayID = 293,
		AttributeGeneralCooldownID = 294,
		AttributePowerCooldownID = 295,
		AttributePowerCooldownStartID = 296,
		AttributeProcCooldownID = 297,
		AttributeEmoteCooldownID = 298,
		AttributeProjectileSpeedID = 299,
		AttributeProjectileSpeedIncreasePercentID = 300,
		AttributeDestroyWhenPathBlockedID = 301,
		AttributeSkillToggledStateID = 302,
		AttributeActID = 303,
		AttributeDifficultyID = 304,
		AttributeLastDamageAmountID = 305,
		AttributeInKnockbackID = 306,
		AttributeAmplifyDamageTypePercentID = 307,
		AttributeAmplifyDamagePercentID = 308,
		AttributeDurabilityCurID = 309,
		AttributeDurabilityMaxID = 310,
		AttributeDurabilityLastDamageID = 311,
		AttributeItemQualityLevelID = 312,
		AttributeItemQualityLevelIdentifiedID = 313,
		AttributeItemCostPercentBonusID = 314,
		AttributeItemEquippedID = 315,
		AttributeRequirementID = 316,
		AttributeRequirementsEasePercentID = 317,
		AttributeRequirementWhenEquippedID = 318,
		AttributeSocketsID = 319,
		AttributeSocketsFilledID = 320,
		AttributeStatsAllBonusID = 321,
		AttributeItemBoundToACDID = 322,
		AttributeItemLockedToACDID = 323,
		AttributeItemBindingLevelOverrideID = 324,
		AttributeItemStackQuantityHiID = 325,
		AttributeItemStackQuantityLoID = 326,
		AttributeRunSpeedGrantedID = 327,
		AttributeRunSpeedDurationID = 328,
		AttributeIdentifyCostID = 329,
		AttributeSeedID = 330,
		AttributeIsCraftedID = 331,
		AttributeDyeTypeID = 332,
		AttributeEnchantAffixID = 333,
		AttributeEnchantRangeValID = 334,
		AttributeHighlySalvageableID = 335,
		AttributeItemUnlockTimeHiID = 336,
		AttributeItemUnlockTimeLoID = 337,
		AttributeAlwaysPlaysGetHitID = 338,
		AttributeHiddenID = 339,
		AttributeRActorFadeGroupID = 340,
		AttributeQuestRangeID = 341,
		AttributeAttackCooldownMinID = 342,
		AttributeAttackCooldownDeltaID = 343,
		AttributeInitialCooldownMinTotalID = 344,
		AttributeInitialCooldownDeltaTotalID = 345,
		AttributeAttackCooldownMinTotalID = 346,
		AttributeAttackCooldownDeltaTotalID = 347,
		AttributeClosingCooldownMinTotalID = 348,
		AttributeClosingCooldownDeltaTotalID = 349,
		AttributeQuestMonsterID = 350,
		AttributeQuestMonsterEffectID = 351,
		AttributeTreasureClassID = 352,
		AttributeRemovesBodyOnDeathID = 353,
		AttributeInitialCooldownMinID = 354,
		AttributeInitialCooldownDeltaID = 355,
		AttributeKnockbackWeightID = 356,
		AttributeUntargetableByPetsID = 357,
		AttributeDamageStateCurrentID = 358,
		AttributeDamageStateMaxID = 359,
		AttributeIsPlayerDecoyID = 360,
		AttributeCustomTargetWeightID = 361,
		AttributeGizmoStateID = 362,
		AttributeGizmoChargesID = 363,
		AttributeChestOpenID = 364,
		AttributeDoorLockedID = 365,
		AttributeDoorTimerID = 366,
		AttributeGizmoDisabledByScriptID = 367,
		AttributeGizmoOperatorACDIDID = 368,
		AttributeTriggeringCountID = 369,
		AttributeGatePositionID = 370,
		AttributeGateVelocityID = 371,
		AttributeGizmoHasBeenOperatedID = 372,
		AttributePetOwnerID = 373,
		AttributePetCreatorID = 374,
		AttributePetTypeID = 375,
		AttributeDropsNoLootID = 376,
		AttributeGrantsNoXPID = 377,
		AttributeHirelingClassID = 378,
		AttributeSummonedBySNOID = 379,
		AttributeIsNPCID = 380,
		AttributeNPCIsOperatableID = 381,
		AttributeNPCIsEscortingID = 382,
		AttributeNPCHasInteractOptionsID = 383,
		AttributeConversationIconID = 384,
		AttributeCalloutCooldownID = 385,
		AttributeBanterCooldownID = 386,
		AttributeConversationHeardCountID = 387,
		AttributeLastTickShopEnteredID = 388,
		AttributeIsHelperID = 389,
		AttributeAxeID = 390,
		AttributeAxe2HID = 391,
		AttributeThrowingAxeID = 392,
		AttributeAxeAnyID = 393,
		AttributeBowID = 394,
		AttributeCrossbowID = 395,
		AttributeBowAnyID = 396,
		AttributeClubID = 397,
		AttributeClub2HID = 398,
		AttributeClubAnyID = 399,
		AttributeDaggerID = 400,
		AttributeMaceID = 401,
		AttributeMace2HID = 402,
		AttributeMaceAnyID = 403,
		AttributeSwordID = 404,
		AttributeSword2HID = 405,
		AttributeSwordAnyID = 406,
		AttributePolearmID = 407,
		AttributeSpearID = 408,
		AttributeWandID = 409,
		AttributeColdStaffID = 410,
		AttributeFireStaffID = 411,
		AttributeLightningStaffID = 412,
		AttributePoisonStaffID = 413,
		AttributeStaffAnyID = 414,
		AttributeWeapon1HID = 415,
		AttributeWeapon2HID = 416,
		AttributeWeaponMeleeID = 417,
		AttributeWeaponRangedID = 418,
		AttributeQuiverID = 419,
		AttributeReincarnationBuffID = 420,
		AttributeDeadBodyAnimTagID = 421,
		AttributeSpawnedbyACDIDID = 422,
		AttributeSummonedByACDIDID = 423,
		AttributeSummonerIDID = 424,
		AttributeBannerACDIDID = 425,
		AttributeBreakableShieldHPID = 426,
		AttributeCurrentWeaponClassID = 427,
		AttributeWeaponsSheathedID = 428,
		AttributeHeldInOffHandID = 429,
		AttributeAttacksPerSecondItemMainHandID = 430,
		AttributeAttacksPerSecondItemOffHandID = 431,
		AttributeAttacksPerSecondItemTotalMainHandID = 432,
		AttributeAttacksPerSecondItemTotalOffHandID = 433,
		AttributeDamageWeaponMinTotalMainHandID = 434,
		AttributeDamageWeaponMinTotalOffHandID = 435,
		AttributeDamageWeaponDeltaTotalMainHandID = 436,
		AttributeDamageWeaponDeltaTotalOffHandID = 437,
		AttributeAttacksPerSecondItemCurrentHandID = 438,
		AttributeDamageWeaponMinTotalCurrentHandID = 439,
		AttributeDamageWeaponDeltaTotalCurrentHandID = 440,
		AttributeHasSpecialDeathAnimTagID = 441,
		AttributeDeathTypeOverrideID = 442,
		AttributeInCombatID = 443,
		AttributeInConversationID = 444,
		AttributeLastTickPotionUsedID = 445,
		AttributePotionDilutionPercentID = 446,
		AttributeOutOfCombatHealthRegenPercentID = 447,
		AttributeOutOfCombatManaRegenPercentID = 448,
		AttributePotionDilutionDurationID = 449,
		AttributePotionDilutionScalarID = 450,
		AttributeFearedID = 451,
		AttributeFearImmuneID = 452,
		AttributeLastDamageACDID = 453,
		AttributeAttachedToACDID = 454,
		AttributeAttachmentACDID = 455,
		AttributeNormalAttackReplacementPowerSNOID = 456,
		AttributeDamageTypeOverrideID = 457,
		AttributeMinionCountBonusPercentID = 458,
		AttributeChampionTeleportNextTickID = 459,
		AttributeChampionTeleportTimeMinInSecondsID = 460,
		AttributeChampionTeleportTimeDeltaInSecondsID = 461,
		AttributeChampionCloneNextTickID = 462,
		AttributeChampionCloneTimeMinInSecondsID = 463,
		AttributeChampionCloneTimeDeltaInSecondsID = 464,
		AttributeChampionCloneHitpointBonusPercentID = 465,
		AttributeChampionCloneDamageBonusPercentID = 466,
		AttributeChampionGhostlyNextTickID = 467,
		AttributeChampionGhostlyInactiveTimeMinInSecondsID = 468,
		AttributeChampionGhostlyInactiveTimeDeltaInSecondsID = 469,
		AttributeChampionGhostlyActiveTimeMinInSecondsID = 470,
		AttributeChampionGhostlyActiveTimeDeltaInSecondsID = 471,
		AttributeChampionGhostlySavedDodgeChanceID = 472,
		AttributeChampionGhostlyID = 473,
		AttributeBaseElementID = 474,
		AttributeProjectileAmountBonusPercentID = 475,
		AttributeProjectileReflectChanceID = 476,
		AttributeAttackFearChanceID = 477,
		AttributeAttackFearTimeMinID = 478,
		AttributeAttackFearTimeDeltaID = 479,
		AttributeBuffVisualEffectID = 480,
		AttributeBuffIconStartTick0ID = 481,
		AttributeBuffIconStartTick1ID = 482,
		AttributeBuffIconStartTick2ID = 483,
		AttributeBuffIconStartTick3ID = 484,
		AttributeBuffIconStartTick4ID = 485,
		AttributeBuffIconStartTick5ID = 486,
		AttributeBuffIconStartTick6ID = 487,
		AttributeBuffIconStartTick7ID = 488,
		AttributeBuffIconEndTick0ID = 489,
		AttributeBuffIconEndTick1ID = 490,
		AttributeBuffIconEndTick2ID = 491,
		AttributeBuffIconEndTick3ID = 492,
		AttributeBuffIconEndTick4ID = 493,
		AttributeBuffIconEndTick5ID = 494,
		AttributeBuffIconEndTick6ID = 495,
		AttributeBuffIconEndTick7ID = 496,
		AttributeCouldHaveRagdolledID = 497,
		AttributeAmbientDamageEffectLastTimeID = 498,
		AttributeScaleBonusID = 499,
		AttributeDeletedOnServerID = 500,
		AttributeScriptedFadeTimeID = 501,
		AttributeDoesNoDamageID = 502,
		AttributeDoesFakeDamageID = 503,
		AttributeSlowTimeDebuffID = 504,
		AttributeBlocksProjectilesID = 505,
		AttributeFrozenID = 506,
		AttributeFreezeDamagePercentBonusID = 507,
		AttributeBuffActiveID = 508,
		AttributeDualWieldBothAttackChanceID = 509,
		AttributeSummonExpirationTickID = 510,
		AttributeSummonCountID = 511,
		AttributeUninterruptibleID = 512,
		AttributeQueueDeathID = 513,
		AttributeCantStartDisplayedPowersID = 514,
		AttributeWizardSlowtimeProxyACDID = 515,
		AttributeDPSID = 516,
		AttributeResurrectionPowerID = 517,
		AttributeFreezeDamageID = 518,
		AttributeFreezeCapacityID = 519,
		AttributeThawRateID = 520,
		AttributeChilledDurBonusPercentID = 521,
		AttributeDOTDPSID = 522,
		AttributeDamageCapPercentID = 523,
		AttributeItemTimeSoldID = 524,
		AttributeForcedHirelingPowerID = 525,
		AttributeIsRootedID = 526,
		AttributeRootTargetACDID = 527,
		AttributeRootAutoDecayPerSecondID = 528,
		AttributeRootUnitValueID = 529,
		AttributeRootTotalTicksID = 530,
		AttributeHideAffixesID = 531,
		AttributeRuneAID = 532,
		AttributeRuneBID = 533,
		AttributeRuneCID = 534,
		AttributeRuneDID = 535,
		AttributeRuneEID = 536,
		AttributeResistanceStunID = 537,
		AttributeResistanceStunTotalID = 538,
		AttributeResistanceRootID = 539,
		AttributeResistanceRootTotalID = 540,
		AttributeResistanceFreezeID = 541,
		AttributeResistanceFreezeTotalID = 542,
		AttributeResistanceStunRootFreezeID = 543,
		AttributeCrowdControlReductionID = 544,
		AttributeDisplaysTeamEffectID = 545,
		AttributeCannotBeAddedToAITargetListID = 546,
		AttributeSkillKitID = 547,
		AttributeImmuneToCharmID = 548,
		AttributeImmuneToBlindID = 549,
		AttributeDamageShieldID = 550,
		AttributeSilencedID = 551,
		AttributeDiseasedID = 552,
		AttributeGuardObjectACDIDID = 553,
		AttributeFollowTargetACDIDID = 554,
		AttributeFollowTargetTypeID = 555,
		AttributeForcedEnemyACDIDID = 556,
		AttributeNPCTalkTargetANNID = 557,
		AttributeNPCConvTargetANNID = 558,
		AttributeScriptTargetACDIDID = 559,
		AttributeLookTargetServerANNID = 560,
		AttributeLookTargetBroadcastIntensityID = 561,
		AttributeLookTargetBroadcastRadiusID = 562,
		AttributeStealthedID = 563,
		AttributeGemQualityID = 564,
		AttributeItemBuffIconID = 565,
		AttributeScrollDurationID = 566,
		AttributeGizmoActorSNOToSpawnID = 567,
		AttributeGizmoActorToSpawnScaleID = 568,
		AttributeDeathReplacementPowerSNOID = 569,
		AttributeAttachmentHandledByClientID = 570,
		AttributeAIInSpecialStateID = 571,
		AttributeAIUsedScriptedSpawnAnimID = 572,
		AttributeAISpawnedByInactiveMarkerID = 573,
		AttributeHeadstonePlayerANNID = 574,
		AttributeResourceCostReductionPercentID = 575,
		AttributeResistancePenetrationID = 576,
		AttributeResistancePenetrationTotalID = 577,
		AttributeResistancePenetrationAllID = 578,
		AttributeResistancePenetrationPercentAllID = 579,
		AttributeFuryEffectLevelID = 580,
		AttributeHealthPotionBonusHealPercentID = 581,
		AttributeFreeCastID = 582,
		AttributeFreeCastAllID = 583,
		AttributeMovementScalarReductionPercentID = 584,
		AttributeMovementScalarReductionResistanceID = 585,
		AttributeDamageAbsorbPercentAllID = 586,
		AttributeWorldSeedID = 587,
		AttributeKillCountRecordID = 588,
		AttributeObjectDestructionRecordID = 589,
		AttributeSingleAttackRecordID = 590,
		AttributeEnvironmentAttackRecordID = 591,
		AttributeRootImmuneID = 592,
		AttributeMonsterPlayGetHitBonusID = 593,
		AttributeStoredContactFrameID = 594,
		AttributeBuffIconCount0ID = 595,
		AttributeBuffIconCount1ID = 596,
		AttributeBuffIconCount2ID = 597,
		AttributeBuffIconCount3ID = 598,
		AttributeBuffIconCount4ID = 599,
		AttributeBuffIconCount5ID = 600,
		AttributeBuffIconCount6ID = 601,
		AttributeBuffIconCount7ID = 602,
		AttributeObserverID = 603,
		AttributeResurrectAsObserverID = 604,
		AttributeComboLevelID = 605,
		AttributeComboTimeLastMoveID = 606,
		AttributeBurrowedID = 607,
		AttributeDeathReplacementEffectGroupSNOID = 608,
		AttributeCheckpointResurrectionAllowedGameTimeID = 609,
		AttributeCheckpointResurrectionForcedGameTimeID = 610,
		AttributeControllingTimedEventSNOID = 611,
		AttributeCastingSpeedPercentID = 612,
		AttributeUsingBossbarID = 613,
		AttributePowerBuff0VisualEffectID = 614,
		AttributePowerBuff1VisualEffectID = 615,
		AttributePowerBuff2VisualEffectID = 616,
		AttributePowerBuff3VisualEffectID = 617,
		AttributePowerBuff4VisualEffectID = 618,
		AttributePowerBuff5VisualEffectID = 619,
		AttributePowerBuff6VisualEffectID = 620,
		AttributePowerBuff7VisualEffectID = 621,
		AttributeStoreSNOID = 622,
		AttributeBusyID = 623,
		AttributeAfkID = 624,
		AttributeLastActionTimestampID = 625,
		AttributePortalNextTimeID = 626,
		AttributeRepairDiscountPercentID = 627,
		AttributeResourceDegenerationPreventedID = 628,
		AttributeOperatableID = 629,
		AttributeLookOverrideID = 630,
		AttributeSpawnerConcurrentCountIDID = 631,
		AttributeDisabledID = 632,
		AttributeSkillOverrideID = 633,
		AttributeSkillOverrideActiveID = 634,
		AttributeSkillOverrideEndedID = 635,
		AttributeSkillOverrideEndedActiveID = 636,
		AttributeIsPowerProxyID = 637,
		AttributeForceNoDeathAnimationID = 638,
		AttributePlayerWeaponClassAnimOverrideID = 639,
		AttributeOperatableStoryGizmoID = 640,
		AttributePowerBuff0VisualEffectNoneID = 641,
		AttributePowerBuff0VisualEffectAID = 642,
		AttributePowerBuff0VisualEffectBID = 643,
		AttributePowerBuff0VisualEffectCID = 644,
		AttributePowerBuff0VisualEffectDID = 645,
		AttributePowerBuff0VisualEffectEID = 646,
		AttributePowerBuff1VisualEffectNoneID = 647,
		AttributePowerBuff1VisualEffectAID = 648,
		AttributePowerBuff1VisualEffectBID = 649,
		AttributePowerBuff1VisualEffectCID = 650,
		AttributePowerBuff1VisualEffectDID = 651,
		AttributePowerBuff1VisualEffectEID = 652,
		AttributePowerBuff2VisualEffectNoneID = 653,
		AttributePowerBuff2VisualEffectAID = 654,
		AttributePowerBuff2VisualEffectBID = 655,
		AttributePowerBuff2VisualEffectCID = 656,
		AttributePowerBuff2VisualEffectDID = 657,
		AttributePowerBuff2VisualEffectEID = 658,
		AttributePowerBuff3VisualEffectNoneID = 659,
		AttributePowerBuff3VisualEffectAID = 660,
		AttributePowerBuff3VisualEffectBID = 661,
		AttributePowerBuff3VisualEffectCID = 662,
		AttributePowerBuff3VisualEffectDID = 663,
		AttributePowerBuff3VisualEffectEID = 664,
		AttributePowerBuff4VisualEffectNoneID = 665,
		AttributePowerBuff4VisualEffectAID = 666,
		AttributePowerBuff4VisualEffectBID = 667,
		AttributePowerBuff4VisualEffectCID = 668,
		AttributePowerBuff4VisualEffectDID = 669,
		AttributePowerBuff4VisualEffectEID = 670,
		AttributePowerBuff5VisualEffectNoneID = 671,
		AttributePowerBuff5VisualEffectAID = 672,
		AttributePowerBuff5VisualEffectBID = 673,
		AttributePowerBuff5VisualEffectCID = 674,
		AttributePowerBuff5VisualEffectDID = 675,
		AttributePowerBuff5VisualEffectEID = 676,
		AttributePowerBuff6VisualEffectNoneID = 677,
		AttributePowerBuff6VisualEffectAID = 678,
		AttributePowerBuff6VisualEffectBID = 679,
		AttributePowerBuff6VisualEffectCID = 680,
		AttributePowerBuff6VisualEffectDID = 681,
		AttributePowerBuff6VisualEffectEID = 682,
		AttributePowerBuff7VisualEffectNoneID = 683,
		AttributePowerBuff7VisualEffectAID = 684,
		AttributePowerBuff7VisualEffectBID = 685,
		AttributePowerBuff7VisualEffectCID = 686,
		AttributePowerBuff7VisualEffectDID = 687,
		AttributePowerBuff7VisualEffectEID = 688,
		AttributeWalkPassabilityPowerSNOID = 689,
		AttributePassabilityPowerSNOID = 690,
		AttributeFlippyIDID = 691,
		AttributeSummoningMachineNumCastersID = 692,
		AttributeSummoningMachineSpawnCountID = 693,
		AttributeSummoningMachineNextSpawnTicksID = 694,
		AttributeSummoningMachineSpawnTeamID = 695,
		AttributeScreenAttackRadiusConstantID = 696,
		AttributeDamageDoneReductionPercentID = 697,
		AttributeSetItemCountID = 698,
		AttributeSpawnerCountdownPercentID = 699,
		AttributeAttackSlowID = 700,
		AttributePowerDisabledID = 701,
		AttributeWeaponEffectOverrideID = 702,
		AttributeDebuffDurationReductionPercentID = 703,
		AttributeUsesPvPPowerTagsID = 704,
		AttributeTraitID = 705,
		AttributeLastACDAttackedByID = 706,
		AttributeGoldPickUpRadiusID = 707,
		AttributeClientOnlyEffectID = 708,
		AttributeHasDoppelgangerClonedID = 709,
		AttributeResourceGainBonusPercentID = 710,
		AttributeLoopingAnimationStartTimeID = 711,
		AttributeLoopingAnimationEndTimeID = 712,
		AttributeLoopingAnimationSuppressItemTooltipsID = 713,
		AttributeHealEffectLastPlayedTickID = 714,
		AttributeResourceEffectLastPlayedtickID = 715,
		AttributeThornsEffectLastPlayedtickID = 716,
		AttributePVPKillsID = 717,
		AttributePVPDeathsID = 718,
		AttributePVPAssistsID = 719,
		AttributePVPProgressionPointsGainedID = 720,
		AttributePVPCurrentKillStreakID = 721,
		AttributePVPCurrentDeathStreakID = 722,
		AttributePVPLongestKillStreakID = 723,
		AttributePVPLongestDeathStreakID = 724,
		AttributeTurnRateScalarID = 725,
		AttributeTurnAccelScalarID = 726,
		AttributeTurnDeccelScalarID = 727,
		AttributeNoHealthDropID = 728,
		AttributeLeaderID = 729,
		AttributeIsContentRestrictedActorID = 730,
		AttributeInBossEncounterID = 731,
		AttributeGodID = 732,
		AttributeMinimapActiveID = 733,
		AttributeMinimapIconOverrideID = 734,
		AttributeMinimapDisableArrowID = 735,
		AttributeLastBlockedACDID = 736,
		AttributeLastBlockedTimeID = 737,
		AttributeDeactivateLureID = 738,
		AttributeWeaponsHiddenID = 739,
		AttributeActorUpdatesAttributesFromOwnerID = 740,
		AttributeTauntTargetACDID = 741,
		AttributeUIOnlyPercentDamageIncreaseID = 742,
		AttributeProjectileEffectSNOID = 743,
		AttributeOnHitFearProcChanceID = 744,
		AttributeOnHitStunProcChanceID = 745,
		AttributeOnHitBlindProcChanceID = 746,
		AttributeOnHitFreezeProcChanceID = 747,
		AttributeOnHitChillProcChanceID = 748,
		AttributeOnHitSlowProcChanceID = 749,
		AttributeOnHitImmobilizeProcChanceID = 750,
		AttributeOnHitKnockbackProcChanceID = 751,
		AttributeOnHitBleedProcChanceID = 752,
		AttributeOnHitBleedProcDamageBaseID = 753,
		AttributeOnHitBleedProcDamageDeltaID = 754,
		AttributeDamagePercentReductionFromRangedID = 755,
		AttributeDamagePercentReductionFromMeleeID = 756,
		AttributeDamagePercentReductionTurnsIntoHealID = 757,
		AttributeDamagePercentReductionFromElitesID = 758,
		AttributeDamagePercentReductionFromTypeID = 759,
		AttributeDamagePercentBonusVsMonsterTypeID = 760,
		AttributeDamagePercentBonusVsElitesID = 761,
		AttributeItemManipulationTimeoutID = 762,
		AttributePickedUpTimeID = 763,
		AttributeUnequippedTimeID = 764,
		AttributeLastACDKilledTimeID = 765,
		AttributeCannotDieDuringID = 766,
		AttributeWeaponOnHitFearProcChanceID = 767,
		AttributeWeaponOnHitStunProcChanceID = 768,
		AttributeWeaponOnHitBlindProcChanceID = 769,
		AttributeWeaponOnHitFreezeProcChanceID = 770,
		AttributeWeaponOnHitChillProcChanceID = 771,
		AttributeWeaponOnHitSlowProcChanceID = 772,
		AttributeWeaponOnHitImmobilizeProcChanceID = 773,
		AttributeWeaponOnHitKnockbackProcChanceID = 774,
		AttributeWeaponOnHitBleedProcChanceID = 775,
		AttributeWeaponOnHitBleedProcDamageBaseID = 776,
		AttributeWeaponOnHitBleedProcDamageDeltaID = 777,
		AttributeWeaponOnHitFearProcChanceMainHandID = 778,
		AttributeWeaponOnHitFearProcChanceOffHandID = 779,
		AttributeWeaponOnHitFearProcChanceCurrentHandID = 780,
		AttributeWeaponOnHitStunProcChanceMainHandID = 781,
		AttributeWeaponOnHitStunProcChanceOffHandID = 782,
		AttributeWeaponOnHitStunProcChanceCurrentHandID = 783,
		AttributeWeaponOnHitBlindProcChanceMainHandID = 784,
		AttributeWeaponOnHitBlindProcChanceOffHandID = 785,
		AttributeWeaponOnHitBlindProcChanceCurrentHandID = 786,
		AttributeWeaponOnHitFreezeProcChanceMainHandID = 787,
		AttributeWeaponOnHitFreezeProcChanceOffHandID = 788,
		AttributeWeaponOnHitFreezeProcChanceCurrentHandID = 789,
		AttributeWeaponOnHitChillProcChanceMainHandID = 790,
		AttributeWeaponOnHitChillProcChanceOffHandID = 791,
		AttributeWeaponOnHitChillProcChanceCurrentHandID = 792,
		AttributeWeaponOnHitSlowProcChanceMainHandID = 793,
		AttributeWeaponOnHitSlowProcChanceOffHandID = 794,
		AttributeWeaponOnHitSlowProcChanceCurrentHandID = 795,
		AttributeWeaponOnHitImmobilizeProcChanceMainHandID = 796,
		AttributeWeaponOnHitImmobilizeProcChanceOffHandID = 797,
		AttributeWeaponOnHitImmobilizeProcChanceCurrentHandID = 798,
		AttributeWeaponOnHitKnockbackProcChanceMainHandID = 799,
		AttributeWeaponOnHitKnockbackProcChanceOffHandID = 800,
		AttributeWeaponOnHitKnockbackProcChanceCurrentHandID = 801,
		AttributeWeaponOnHitBleedProcChanceMainHandID = 802,
		AttributeWeaponOnHitBleedProcChanceOffHandID = 803,
		AttributeWeaponOnHitBleedProcChanceCurrentHandID = 804,
		AttributeWeaponOnHitBleedProcDamageBaseMainHandID = 805,
		AttributeWeaponOnHitBleedProcDamageBaseOffHandID = 806,
		AttributeWeaponOnHitBleedProcDamageBaseCurrentHandID = 807,
		AttributeWeaponOnHitBleedProcDamageDeltaMainHandID = 808,
		AttributeWeaponOnHitBleedProcDamageDeltaOffHandID = 809,
		AttributeWeaponOnHitBleedProcDamageDeltaCurrentHandID = 810,
		AttributePowerDamagePercentBonusID = 811,
		AttributePowerResourceReductionID = 812,
		AttributePowerCooldownReductionID = 813,
		AttributePowerDurationIncreaseID = 814,
		AttributePowerCritPercentBonusID = 815,
		AttributeWeaponCritChanceID = 816,
		AttributeWeaponCritChanceMainHandID = 817,
		AttributeWeaponCritChanceOffHandID = 818,
		AttributeWeaponCritChanceCurrentHandID = 819,
		AttributeStrengthItemID = 820,
		AttributeDexterityItemID = 821,
		AttributeIntelligenceItemID = 822,
		AttributeVitalityItemID = 823,
		AttributeItemLevelRequirementReductionID = 824,
		AttributeItemDurabilityPercentBonusID = 825,
		AttributeItemIndestructibleID = 826,
		AttributeCoreAttributesFromItemBonusMultiplierID = 827,
		AttributeWaitingToAcceptResurrectionID = 828,
		AttributeGhostedID = 829,
		AttributeSpecialInventoryHasSoldID = 830,
		AttributeIGRBuffPollNextTimeID = 831,
		AttributePowerChannelLockoutTimeID = 832,
		AttributePowerBuff0LockoutTimeID = 833,
		AttributePowerBuff1LockoutTimeID = 834,
		AttributePowerBuff2LockoutTimeID = 835,
		AttributePowerBuff3LockoutTimeID = 836,
		AttributePowerBuff4LockoutTimeID = 837,
		AttributePowerBuff5LockoutTimeID = 838,
		AttributePowerBuff6LockoutTimeID = 839,
		AttributePowerBuff7LockoutTimeID = 840,
		AttributeKnownByOwnerID = 841,
		AttributeNeverDeactivatesID = 842,
		AttributeAccountUnderReviewID = 843,
		AttributeProjectileDetonateTimeID = 844,
		AttributeItemPowerPassiveID = 845,
		AttributeLastHealthDropIntervalID = 846,
		
		//User defined
		AttributeLevelTotalID = 1000,
		AttributeStrengthTotalFromLevelID,
		AttributeDexterityTotalFromLevelID,
		AttributeIntelligenceTotalFromLevelID,
		AttributeVitalityTotalFromLevelID,
		AttributeClassWizardID,
		AttributeClassWitchDoctorID,
		AttributeClassMonkID,
		AttributeClassDemonHunterID,
		AttributeClassBarbarianID,

		AttributeDamageDeltaSubTotalID,
		AttributeHeldWeaponsInHandsID,
		AttributeAttacksPerSecondSubTotalID,
		
		AttributeCritPercentBonusTotalID,
		AttributeCritDamagePercentTotalID,
		AttributeCritDamageFactorID,
		
		AttributeHitpointsRegenPerSecondTotalID,
		AttributeHitpointsOnHitTotalID,
		AttributeHitpointsOnKillTotalID,
		
		AttributeArmorBonusSkillPercentID,
		AttributeDamageBonusSkillPercentID,

		AttributeDodgeChanceTotalID,
		AttributeDodgeChanceFromDexterityID,

		AttributeAttacksPerSecondPercentTotalID,

		AttributeArmorFromVitalityFactorID,
		AttributeArmorFromDexterityFactorID,

		AttributeDamagePercentBonusFromSwordsID,
		AttributeDamagePercentBonusFromDaggersID,
		AttributeCritPercentBonusFromMacesID,
		AttributeCritPercentBonusFromAxesID,
		AttributeAttacksPerSecondPercentBonusFromPolearmsID,
		AttributeAttacksPerSecondPercentBonusFromSpearsID,

		AttributeDamagePercentBonusFromBowID,
		AttributeCritDamagePercentBonusFromCrossbowID,
		AttributeCritPercentBonusFromHandXbowID,
		
		AttributeDodgeChanceBonusFromDualWieldingID,
		AttributeDodgeChanceBonusFromCritPercentFactorID,

		AttributeResistanceSubTotalID,
		
		AttributeResistanceFlatID

	} AttributeID;

}
#endif
