// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/Commands.h>

RobotContainer::RobotContainer() {
	pathChooser.AddOption("LoadingScore", loadingScore.get());
	frc::SmartDashboard::PutData("Auto Chooser", &pathChooser);
	ConfigureBindings();
}

void RobotContainer::setAllianceColor() {
	// vision.setAlliancesColor();
}

void RobotContainer::ConfigureBindings() {
	chassis.SetDefaultCommand(Drive(&chassis, &driver));


	// Configure the button bindings
	resetNavxButton.OnTrue(frc2::InstantCommand{ [this]() {chassis.resetNavx();} }.ToPtr());
	setConeLED.OnTrue(SetConeLED(&ledManager));
	setCubeLED.OnTrue(SetCubeLED(&ledManager));
	setLEDOff.OnTrue(SetLEDOff(&ledManager));


	// closedPosition.OnTrue(ClosedCommand(&superStructure));
	// openLowerWrists.OnTrue(OpenLowerWristsCommand(&superStructure));

	// lowerPosition.OnTrue(LowerCommand(&superStructure));
	// lowerPosition.OnFalse(ClosedCommand(&superStructure));

	// middlePosition.OnTrue(MiddleCommand(&superStructure));
	// middlePosition.OnFalse(LongClosedCommand(&superStructure));

	// upperPosition.OnTrue(UpperCommand(&superStructure));
	// upperPosition.OnFalse(LongClosedCommand(&superStructure));

	// loadingPosition.OnTrue(LoadingCommand(&superStructure));
	// loadingPosition.OnFalse(LongClosedCommand(&superStructure));

	groundIntake.OnTrue(GroundIntakeTrueCommand(nullptr, &intake));
	groundIntake.OnFalse(GroundIntakeFalseCommand(nullptr, &intake));

	setGamePiece.OnTrue(SetGamePieceTrueCommand(&intake));
	setGamePiece.OnFalse(SetGamePieceFalseCommand(&intake));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
	return pathChooser.GetSelected();
}
