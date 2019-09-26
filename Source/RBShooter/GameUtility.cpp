// Copyright (c) 2019 PSQ Grupp 4 =)


#include "GameUtility.h"

void UGameUtility::IncrementKillCount(FKillCount& KillCountObject, int32 Amount /*= 1*/, EColorTypes Type /*= EColorTypes::CT_None*/)
{
	if (Type != EColorTypes::CT_None)
	{
		switch (Type)
		{
		case EColorTypes::CT_Red:
			KillCountObject.KillCountRed += Amount;
			break;
		case EColorTypes::CT_Blue:
			KillCountObject.KillCountBlue += Amount;
			break;
		}

		KillCountObject.KillCountTotal += Amount;
	}
}

void UGameUtility::DecrementKillCount(FKillCount& KillCountObject, int32 Amount /*= 1*/, EColorTypes Type /*= EColorTypes::CT_None*/)
{
	if (Type != EColorTypes::CT_None)
	{
		switch (Type)
		{
		case EColorTypes::CT_Red:
			KillCountObject.KillCountRed -= Amount;
			break;
		case EColorTypes::CT_Blue:
			KillCountObject.KillCountBlue -= Amount;
			break;
		}

		KillCountObject.KillCountTotal -= Amount;
	}
}

void UGameUtility::ResetKillcount(FKillCount& KillCountObject)
{
	KillCountObject.KillCountRed = 0;
	KillCountObject.KillCountBlue = 0;
	KillCountObject.KillCountTotal = 0;
}
