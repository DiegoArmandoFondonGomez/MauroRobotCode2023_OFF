// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() {
	pathplanner::NamedCommands::registerCommand("AutoBalance", AutoBalance(&chassis).ToPtr());

	autoChooser.SetDefaultOption("None, null, nada", "None");
	autoChooser.AddOption("CenterBalance", "CenterBalance");

	frc::SmartDashboard::PutData("Auto Chooser", &autoChooser);
	ConfigureBindings();
}

void RobotContainer::setAllianceColor() {
	ledManager.setLEDAllianceColor();
	// vision.setAlliancesColor();
}

void RobotContainer::ConfigureBindings() {
	chassis.SetDefaultCommand(Drive(&chassis, &driver));


	// Configure the button bindings
	resetAngleButton.OnTrue(frc2::InstantCommand{ [this]() {chassis.resetAngle();} }.ToPtr());
	autoBalance.WhileTrue(AutoBalance(&chassis).ToPtr());

	dropCone.OnTrue(SetGamePieceTrueCommand(&intake, -4_V));
	dropCone.OnFalse(SetGamePieceFalseCommand(&intake));

	dropCube.OnTrue(SetGamePieceTrueCommand(&intake, 3_V));
	dropCube.OnFalse(SetGamePieceFalseCommand(&intake));

	closedPosition.OnTrue(ClosedCommand(&superStructure, &intake));
	openLowerWrists.OnTrue(OpenLowerWristsCommand(&superStructure));

	lowerPosition.OnTrue(LowerCommand(&superStructure));
	lowerPosition.OnFalse(LowerCommandClosed(&superStructure));

	middlePosition.OnTrue(MiddleCommand(&superStructure));

	upperPosition.OnTrue(UpperCommand(&superStructure));

	intakeCone.OnTrue(ConeIntakeTrueCommand(&superStructure, &intake, 7_V));

	intakeCube.OnTrue(GroundIntakeTrueCommand(&superStructure, &intake, -4_V));
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
	std::string autoName = autoChooser.GetSelected();
	if (autoName == "None") {
		return frc2::CommandPtr(nullptr);
	}
	return pathplanner::PathPlannerAuto(autoName).ToPtr();
}
