// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "AutoBalance.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

AutoBalance::AutoBalance(SwerveChassis* swerveChassis) : m_swerveChassis(swerveChassis) {
	// Use addRequirements() here to declare subsystem dependencies.
	AddRequirements({ m_swerveChassis });
}

// Called when the command is initially scheduled.
void AutoBalance::Initialize() {
	xController.SetTolerance(7);
	// rController.SetTolerance(5);
}

// Called repeatedly when this Command is scheduled to run
void AutoBalance::Execute() {

	units::meters_per_second_t xOutput{ xController.Calculate(m_swerveChassis->getRoll(), 0) };
	units::radians_per_second_t rOutput{ rController.Calculate(m_swerveChassis->getYaw(), 180) };

	if (m_swerveChassis->getYaw() > 180) {
		rOutput = -rOutput;
	}

	m_swerveChassis->driveFieldRelative({ xOutput, 0_mps, rOutput });

}
// Called once the command ends or is interrupted.
void AutoBalance::End(bool interrupted) {
	m_swerveChassis->driveFieldRelative({ 0_mps, 0_mps, 0_rad_per_s });

}

// Returns true when the command should end.
bool AutoBalance::IsFinished() {
	return xController.AtSetpoint() && rController.AtSetpoint();
}
