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

void UGameUtility::SetValue(UPARAM(ref)FWeaponColorAttribute& WeaponColorAttributeObject, float Value, EColorTypes ColorType)
{
	switch (ColorType)
	{
	case EColorTypes::CT_Red:
		WeaponColorAttributeObject.ValueRed = Value;
		break;
	case EColorTypes::CT_Blue:
		WeaponColorAttributeObject.ValueBlue = Value;
		break;
	case EColorTypes::CT_None:
		WeaponColorAttributeObject.ValueGlobal = Value;
		break;
	}
}

void UGameUtility::SetFloat(UPARAM(ref)FColorFloatGroup& ColorFloatGroupObject, float Value, EColorTypes ColorType)
{
	switch (ColorType)
	{
	case EColorTypes::CT_Red:
		ColorFloatGroupObject.Red = Value;
		break;
	case EColorTypes::CT_Blue:
		ColorFloatGroupObject.Blue = Value;
		break;
	}
}

float UGameUtility::GetFloat(UPARAM(ref)FColorFloatGroup& ColorFloatGroupObject, EColorTypes ColorType)
{
	switch (ColorType)
	{
	case EColorTypes::CT_Red:
		return ColorFloatGroupObject.Red;
	case EColorTypes::CT_Blue:
		return ColorFloatGroupObject.Blue;
	}

	return 0.0f;
}
