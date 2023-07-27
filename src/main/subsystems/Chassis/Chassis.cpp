// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Chassis.h"

Chassis::Chassis() {
	setModulePositions(&modulePos);
	setModules(&frontLeftModule, &frontRightModule, &backLeftModule, &backRightModule);
	setModulesRatios(turnRatio, driveRatio, wheelDiameter);
	setRotatorPID(58, 0, 0);
	// setDrivePID(5, 0, 0);
	setFeedForward(0.74656_V, 2.1143_V, 0.80794_V);
}

//This method will be called once per schedule run
void Chassis::Periodic() {
	updateOdometry();
	shuffleboardPeriodic();
}
