// Copyright (c) 2019 PSQ Grupp 4 =)

using UnrealBuildTool;
using System.Collections.Generic;

public class RBShooterTarget : TargetRules
{
	public RBShooterTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "RBShooter" } );
	}
}
