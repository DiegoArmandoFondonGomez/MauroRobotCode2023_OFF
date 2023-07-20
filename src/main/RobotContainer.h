// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "subsystems/Chassis/Chassis.h"
#include "subsystems/Vision/Vision.h"

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

  // Auto
  frc::SendableChooser<frc2::Command*> pathChooser;
};
