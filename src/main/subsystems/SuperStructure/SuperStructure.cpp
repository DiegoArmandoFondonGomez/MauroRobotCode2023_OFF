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
	m_lowerLeft.setFollow(m_lowerRight.GetDeviceID(), true);

	m_elevatorRight.setSupplyCurrentLimit(true, 20, 30, 0.5);
	m_elevatorRight.zeroPosition();
	m_elevatorRight.setSensorToMechanism(ELEVATOR_GEAR_BOX_REDUCTION);

	m_elevatorLeft.setSupplyCurrentLimit(true, 20, 30, 0.5);
	m_elevatorLeft.setSensorToMechanism(ELEVATOR_GEAR_BOX_REDUCTION);
	m_elevatorLeft.setFollow(m_elevatorRight.GetDeviceID(), true);

	m_upperMotor.setSupplyCurrentLimit(true, 20, 30, 0.5);
	m_upperMotor.setSensorPosition(14.4);
	m_upperMotor.setSensorToMechanism(UPPER_GEAR_BOX_REDUCTION);

	// COnfigure Motion Magic and PID
	m_lowerRight.setPIDValues(300.0, 0.0, 1.0, 0.0, 0.0);
	m_lowerRight.configureMotionMagic(2000.0, 1800.0, 0.0);

	m_elevatorRight.setPIDValues(12, 0, 0, 0.0, 0.0);
	m_elevatorRight.configureMotionMagic(20.0, 20.0, 0);

	m_upperMotor.setPIDValues(37, 0.0, 0.0, 0.0, 0.0);
	m_upperMotor.configureMotionMagic(100.0, 150, 0.0);

	setTargetCoord({ -8, 0, 100 });
}

void SuperStructure::setTargetCoord(SuperStructureState targetCoord) {
	m_TargetState = targetCoord;
}

double SuperStructure::getLowerAngle() {
	return m_lowerRight.getPosition() * 360;
}

double SuperStructure::getUpperAngle() {
	return m_upperMotor.getPosition() * 360;
}

double SuperStructure::getElevatorDistance() {
	return m_elevatorRight.getPosition() * M_PI;
}

SuperStructurePosition SuperStructure::getPosition() {
	return position;
}

void SuperStructure::setPosition(SuperStructurePosition pos) {
	position = pos;
}

SuperStructureState SuperStructure::getCurrentState() {
	SuperStructureState state;
	state.lowerAngle = getLowerAngle();
	state.elevatorDistance = getElevatorDistance();
	state.upperAngle = getUpperAngle();
	return state;
}

void SuperStructure::setFalconTargetPos(SuperStructureState targetState) {
	m_lowerRight.setMotionMagicPosition(convertAngleToFalconPos(targetState.lowerAngle), lowerFF * cos(targetState.lowerAngle), false);
	m_elevatorRight.setMotionMagicPosition(convertDistanceToFalconPos(targetState.elevatorDistance), elevatorFF * cos(targetState.lowerAngle), false);
	m_upperMotor.setMotionMagicPosition(convertAngleToFalconPos(targetState.upperAngle), upperFF * cos(upperAngleFFCalculation(targetState.upperAngle)), false);
}

double SuperStructure::convertAngleToFalconPos(double angle) {
	return angle / 360;
}

double SuperStructure::convertDistanceToFalconPos(double distance) {
	return distance / M_PI;
}

double SuperStructure::upperAngleFFCalculation(double angle) {
	double rawVal = angle;
	rawVal = frc::InputModulus(rawVal, -180.0, 180.0);
	double angleToLower = rawVal;

	return angleToLower + getLowerAngle();
}

// This method will be called once per scheduler run
void SuperStructure::Periodic() {
	setFalconTargetPos(m_TargetState);

	// frc::SmartDashboard::PutNumber("Target Lower Angle", m_TargetState.lowerAngle);
	// frc::SmartDashboard::PutNumber("Target Upper Angle", m_TargetState.upperAngle);
	// frc::SmartDashboard::PutNumber("Target Elevator Distance", m_TargetState.elevatorDistance);

	// // Debugging
	// SuperStructureState currentState = getCurrentState();
	// frc::SmartDashboard::PutNumber("Lower Angle", currentState.lowerAngle);
	// frc::SmartDashboard::PutNumber("Upper Angle", currentState.upperAngle);
	// frc::SmartDashboard::PutNumber("Elevator Distance", currentState.elevatorDistance);

	// frc::SmartDashboard::PutNumber("Position", position);
}
