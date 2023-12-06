// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <wpi/MemoryBuffer.h>
#include <frc/Filesystem.h>

RobotContainer::RobotContainer() {
	pathplanner::NamedCommands::registerCommand("AutoBalance", AutoBalance(&chassis).ToPtr());
	pathplanner::NamedCommands::registerCommand("IntakeCube", GroundIntakeTrueCommand(&superStructure, &intake, -4_V));
	pathplanner::NamedCommands::registerCommand("Close", ClosedCommand(&superStructure, &intake));
	pathplanner::NamedCommands::registerCommand("SetCube", SetGamePieceTrueCommand(&intake, 5_V));
	pathplanner::NamedCommands::registerCommand("StopIntake", SetGamePieceFalseCommand(&intake));
	pathplanner::NamedCommands::registerCommand("LowerPosition", LowerCommand(&superStructure));
	pathplanner::NamedCommands::registerCommand("CloseLower", LowerCommandClosed(&superStructure));

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
		return  frc2::cmd::None();
	}
	const std::string filePath = frc::filesystem::GetDeployDirectory() + "/pathplanner/autos/" + autoChooser.GetSelected() + ".auto";

	std::error_code error_code;
	std::unique_ptr<wpi::MemoryBuffer> fileBuffer = wpi::MemoryBuffer::GetFile(filePath, error_code);

	if (fileBuffer == nullptr || error_code) {
		throw std::runtime_error("Cannot open file: " + filePath);
	}

	wpi::json json = wpi::json::parse(fileBuffer->GetCharBuffer());
	return pathplanner::AutoBuilder::getAutoCommandFromJson(json);
}
