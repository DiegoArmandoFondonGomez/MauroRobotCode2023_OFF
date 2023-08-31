// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "CharacterizationChassis.h"

CharacterizationChassis::CharacterizationChassis() {
	setModulePositions(&modulePos);
	setModulesRatios(turnRatio, driveRatio, wheelDiameter);
	setModules(&frontLeftModule, &frontRightModule, &backLeftModule, &backRightModule);
	setRotatorPID(53, 0, 0);
	setFeedForward(0.74656_V, 2.1143_V, 0.80794_V);
}

// This method will be called once per scheduler run
void CharacterizationChassis::Periodic() {
	updateOdometry();
	shuffleboardPeriodic();
}
