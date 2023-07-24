// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Wrists.h"
#include <frc/MathUtil.h>

Wrists::Wrists() {
    // Configure Motors
    m_lowerRight.setSupplyCurrentLimit(true, 20, 30, 0.5);
    m_lowerRight.zeroPosition();

    m_lowerLeft.setSupplyCurrentLimit(true, 20, 30, 0.5);
    m_lowerLeft.setFollow(m_lowerRight.getMotorController()->GetDeviceID(), true);

    m_upperMotor.setSupplyCurrentLimit(true, 20, 30, 0.5);
    m_upperMotor.zeroPosition();

    // COnfigure Motion Magic and PID
    m_lowerRight.setPIDValues(0.0, 0.0, 0.0, 0.0, 0.0);
    m_lowerRight.configureMotionMagic(0.0, 0.0, 0.0);

    m_upperMotor.setPIDValues(0.0, 0.0, 0.0, 0.0, 0.0);
    m_upperMotor.configureMotionMagic(0.0, 0.0, 0.0);
}

void Wrists::setUpperTargetCoord(double upperTarget) {
    upperAngle = upperTarget;
}

void Wrists::setLowerTargetCoord(double lowerTarget) {
    lowerAngle = lowerTarget;
}

double Wrists::getLowerAngle() {
    return m_lowerRight.getPosition() * 360.0;
}

double Wrists::getUpperAngle() {
    double rawVal = (-m_upperMotor.getPosition()) * 360.0;
    rawVal = frc::InputModulus(rawVal, -180.0, 180.0);
    double angleToLower = rawVal;

    return angleToLower + getLowerAngle();
}

void Wrists::setUpperFalconTargetPos(double upperTarget) {
    m_upperMotor.setMotionMagicPosition(upperTarget, upperFF, true);
}

void Wrists::setLowerFalconTargetPos(double lowerTarget) {
    m_lowerRight.setMotionMagicPosition(lowerTarget, lowerFF, true);
}

double Wrists::convertAngleToLowerFalconPos(double angle) {
    return angle / 360 * LOWER_GEAR_BOX_REDUCTION;
}
double Wrists::convertAngleToUpperFalconPos(double angle) {
    double targetAngle = angle - getLowerAngle();
    return targetAngle / 360 * UPPER_GEAR_BOX_REDUCTION;
}

// This method will be called once per scheduler run
void Wrists::Periodic() {
    frc::SmartDashboard::PutNumber("Lower Angle", getLowerAngle());
    // Pendiente
}
