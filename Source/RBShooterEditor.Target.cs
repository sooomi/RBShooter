// Copyright (c) 2019 PSQ Grupp 4 =)

using UnrealBuildTool;
using System.Collections.Generic;

public class RBShooterEditorTarget : TargetRules
{
	public RBShooterEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "RBShooter" } );
	}
}
