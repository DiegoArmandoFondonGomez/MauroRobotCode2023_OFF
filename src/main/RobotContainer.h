// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/Trigger.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/XboxController.h>

#include "subsystems/Chassis/Chassis.h"
#include "subsystems/Vision/Vision.h"
#include "subsystems/SuperStructure/SuperStructure.h"
#include "subsystems/Intake/Intake.h"
#include "subsystems/LEDManager/LEDManager.h"

#include "OvertureLib/Commands/Teleop/Drive/Drive.h"
#include "Commands/Common/SuperStructureCommon/SuperStructureCommon.h"
#include "Commands/Teleop/LEDCommands/LEDCommands.h"
#include "Commands/Autonomous/Autonomous.h"

class RobotContainer {
public:
	RobotContainer();
	void setAllianceColor();
	frc2::Command* GetAutonomousCommand();

private:
	void ConfigureBindings();

	// Subsystems
	Chassis chassis;
	Vision vision{ &chassis };
	SuperStructure superStructure;
	Intake intake;
	LEDManager ledManager;

	//controllers
	frc::XboxController driver{ 0 };
	frc::XboxController mechanisms{ 1 };

	// Driver commands
	frc2::Trigger resetNavxButton{ [this] {return driver.GetBackButton();} };
	frc2::Trigger setConeLED{ [this] {return driver.GetLeftBumper();} };
	frc2::Trigger setCubeLED{ [this] {return driver.GetRightBumper();} };
	frc2::Trigger setLEDOff{ [this] {return driver.GetBButton();} };
	frc2::Trigger dropCube{ [this] {return driver.GetLeftTriggerAxis();} };
	frc2::Trigger dropCone{ [this] {return driver.GetRightTriggerAxis();} };

	// Mechanisms commands
	frc2::Trigger closedPosition{ [this] {return mechanisms.GetRightBumper();} };
	frc2::Trigger openLowerWrists{ [this] {return mechanisms.GetLeftBumper();} };
	frc2::Trigger lowerPosition{ [this] {return mechanisms.GetAButton();} };
	frc2::Trigger middlePosition{ [this] {return mechanisms.GetBButton();} };
	frc2::Trigger upperPosition{ [this] {return mechanisms.GetYButton();} };
	frc2::Trigger loadingPosition{ [this] {return mechanisms.GetXButton();} };
	frc2::Trigger intakeCone{ [this] {return mechanisms.GetRightTriggerAxis();} };
	frc2::Trigger intakeCube{ [this] {return mechanisms.GetLeftTriggerAxis();} };


	// Auto
	frc::SendableChooser<frc2::Command*> pathChooser;
	frc2::CommandPtr loadingScore = LoadingScore(&superStructure, &intake, &chassis, &vision);
};
