// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "SuperStructure.h"
#include <frc/MathUtil.h>
#include <frc/DriverStation.h>

SuperStructure::SuperStructure() {
	// Configure Motors
	m_lowerRight.setSupplyCurrentLimit(true, 20, 30, 0.5);
	m_lowerRight.setSensorPosition(-5.12);
	m_lowerRight.setSensorToMechanism(LOWER_GEAR_BOX_REDUCTION);

	m_lowerLeft.setSupplyCurrentLimit(true, 20, 30, 0.5);
	m_lowerLeft.setSensorToMechanism(LOWER_GEAR_BOX_REDUCTION);
	m_lowerLeft.setFollow(m_lowerRight.getMotorController()->GetDeviceID(), true);

	m_elevatorRight.setSupplyCurrentLimit(true, 20, 30, 0.5);
	m_elevatorRight.zeroPosition();
	m_elevatorRight.setSensorToMechanism(ELEVATOR_GEAR_BOX_REDUCTION);

	m_elevatorLeft.setSupplyCurrentLimit(true, 20, 30, 0.5);
	m_elevatorLeft.setSensorToMechanism(ELEVATOR_GEAR_BOX_REDUCTION);
	m_elevatorLeft.setFollow(m_elevatorRight.getMotorController()->GetDeviceID(), true);

	m_upperMotor.setSupplyCurrentLimit(true, 20, 30, 0.5);
	m_upperMotor.setSensorPosition(14.0);
	m_upperMotor.setSensorToMechanism(UPPER_GEAR_BOX_REDUCTION);

	// COnfigure Motion Magic and PID
	m_lowerRight.setPIDValues(0.0, 0.0, 0.0, 0.0, 0.0);
	m_lowerRight.configureMotionMagic(0.0, 0.0, 3.0);

	m_elevatorRight.setPIDValues(0.0, 0.0, 0.0, 0.0, 0.0);
	m_elevatorRight.configureMotionMagic(0.0, 0.0, 3.0);

	m_upperMotor.setPIDValues(8, 0.0, 0.0, 0.0, 0.0);
	m_upperMotor.configureMotionMagic(10.0, 15.0, 3.0);

	setTargetCoord({ getLowerAngle(), getElevatorDistance(), getUpperAngle() });
}

void SuperStructure::setTargetCoord(SuperStructureState targetCoord) {
	m_TargetState = targetCoord;
}

double SuperStructure::getLowerAngle() {
	return m_lowerRight.getPosition() * 360;
}

double SuperStructure::getUpperAngle() {
	// double rawVal = (-m_upperMotor.getPosition()) * 360.0;
	// rawVal = frc::InputModulus(rawVal, -180.0, 180.0);
	// double angleToLower = rawVal;

	// return angleToLower + getLowerAngle();

	return m_upperMotor.getPosition() * 360;
}

double SuperStructure::getElevatorDistance() {
	return m_elevatorRight.getPosition() * M_PI;
}

SuperStructureState SuperStructure::getCurrentState() {
	SuperStructureState state;
	state.lowerAngle = getLowerAngle();
	state.elevatorDistance = getElevatorDistance();
	state.upperAngle = getUpperAngle();
	return state;
}

void SuperStructure::setFalconTargetPos(SuperStructureState targetState) {
	m_lowerRight.setMotionMagicPosition(convertAngleToFalconPos(targetState.lowerAngle), lowerFF, false);
	m_elevatorRight.setMotionMagicPosition(convertDistanceToFalconPos(targetState.elevatorDistance), elevatorFF, false);
	m_upperMotor.setMotionMagicPosition(convertAngleToFalconPos(targetState.upperAngle), upperFF, false);
}

double SuperStructure::convertAngleToFalconPos(double angle) {
	return angle / 360;
}

double SuperStructure::convertDistanceToFalconPos(double distance) {
	return distance / M_PI;
}

// This method will be called once per scheduler run
void SuperStructure::Periodic() {
	setFalconTargetPos(m_TargetState);

	frc::SmartDashboard::PutNumber("Target Lower Angle", m_TargetState.lowerAngle);
	frc::SmartDashboard::PutNumber("Target Upper Angle", m_TargetState.upperAngle);
	frc::SmartDashboard::PutNumber("Target Elevator Distance", m_TargetState.elevatorDistance);

	// Debugging
	SuperStructureState currentState = getCurrentState();
	frc::SmartDashboard::PutNumber("Lower Angle", currentState.lowerAngle);
	frc::SmartDashboard::PutNumber("Upper Angle", currentState.upperAngle);
	frc::SmartDashboard::PutNumber("Elevator Distance", currentState.elevatorDistance);
}
