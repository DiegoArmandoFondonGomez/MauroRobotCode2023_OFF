// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/smartdashboard/SmartDashboard.h>

#include <OvertureLib/subsystems/Swerve/SwerveChassis/SwerveChassis.h>
#include <OvertureLib/subsystems/Swerve/SwerveModule/SwerveModule.h>
#include <OvertureLib/Commands/Teleop/Drive/Drive.h>

class Chassis: public SwerveChassis {
public:
  Chassis();

  void Periodic() override;

private:
  SwerveModule backRightModule{ 8, 7, 14, 118.916015625, "BackRightModule", "OverCANivore" };
  SwerveModule backLeftModule{ 6, 5, 13, -155.7421875, "BackLeftModule", "OverCANivore" };
  SwerveModule frontLeftModule{ 4, 3, 12, 106.611328125, "FrontLeftModule", "OverCANivore" };
  SwerveModule frontRightModule{ 2, 1, 11, 132.978515625, "FrontRightModule", "OverCANivore" };

  std::array<frc::Translation2d, 4> modulePos{
   frc::Translation2d(10.36_in, 10.36_in),   //Front Left
       frc::Translation2d(10.36_in, -10.36_in),   //Front Right
       frc::Translation2d(-10.36_in, -10.36_in),   //Back Right
       frc::Translation2d(-10.36_in, 10.36_in),   //Back Left
  };

  double turnRatio = 150 / 7;
  double driveRatio = 6.75;
  double wheelDiameter = 0.10033;
};
