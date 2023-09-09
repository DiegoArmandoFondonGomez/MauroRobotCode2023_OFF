// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/Commands.h>

RobotContainer::RobotContainer() {
	pathChooser.SetDefaultOption("Null-None", nullptr);
	pathChooser.AddOption("LoadingScore", loadingScore.get());
	pathChooser.AddOption("CenterBalance", centerBalance.get());
	pathChooser.AddOption("BarrierScore", barrierScore.get());
	frc::SmartDashboard::PutData("Auto Chooser", &pathChooser);
	ConfigureBindings();
}

void RobotContainer::setAllianceColor() {
	ledManager.setLEDAllianceColor();
	vision.setAlliancesColor();
}

void RobotContainer::ConfigureBindings() {
	chassis.SetDefaultCommand(Drive(&chassis, &driver));


	// Configure the button bindings
	resetNavxButton.OnTrue(frc2::InstantCommand{ [this]() {chassis.resetNavx();} }.ToPtr());
	autoBalance.WhileTrue(AutoBalance(&chassis).ToPtr());

	dropCone.OnTrue(SetGamePieceTrueCommand(&intake, -3_V));
	dropCone.OnFalse(SetGamePieceFalseCommand(&intake));

	dropCube.OnTrue(SetGamePieceTrueCommand(&intake, 3_V));
	dropCube.OnFalse(SetGamePieceFalseCommand(&intake));

	closedPosition.OnTrue(ClosedCommand(&superStructure));
	openLowerWrists.OnTrue(OpenLowerWristsCommand(&superStructure));

	lowerPosition.OnTrue(LowerCommand(&superStructure));
	lowerPosition.OnFalse(LowerCommandClosed(&superStructure));

	middlePosition.OnTrue(MiddleCommand(&superStructure));
	middlePosition.OnFalse(ClosedCommand(&superStructure));

	upperPosition.OnTrue(UpperCommand(&superStructure));
	upperPosition.OnFalse(ClosedCommand(&superStructure));

	// loadingPosition.OnTrue(LoadingCommand(&superStructure));
	// loadingPosition.OnFalse(ClosedCommand(&superStructure));

	intakeCone.OnTrue(GroundIntakeTrueCommand(&superStructure, &intake, 7_V));
	intakeCone.OnFalse(GroundIntakeFalseCommand(&superStructure, &intake));

	intakeCube.OnTrue(GroundIntakeTrueCommand(&superStructure, &intake, -4_V));
	intakeCube.OnFalse(GroundIntakeFalseCommand(&superStructure, &intake));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
	return pathChooser.GetSelected();
}
