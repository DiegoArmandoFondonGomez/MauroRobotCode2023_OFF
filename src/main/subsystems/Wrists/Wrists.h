// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include <OvertureLib/MotorControllers/OverTalonFX/OverTalonFX.h>
#include <OvertureLib/MotorControllers/ControllerNeutralMode/ControllerNeutralMode.h>

class Wrists: public frc2::SubsystemBase {
public:
  Wrists();
  void setUpperTargetCoord(double upperTarget);
  void setLowerTargetCoord(double lowerTarget);
  double getLowerAngle();
  double getUpperAngle();
  void Periodic() override;

private:
  void setUpperFalconTargetPos(double upperTarget);
  void setLowerFalconTargetPos(double lowerTarget);
  double convertAngleToUpperFalconPos(double angle);
  double convertAngleToLowerFalconPos(double angle);

  // Constrants
  const double LOWER_GEAR_BOX_REDUCTION = 230.4;
  const double UPPER_GEAR_BOX_REDUCTION = 50.4;

  // Lower Motors
  OverTalonFX m_lowerRight{ 20, ControllerNeutralMode::Brake, false, LOWER_GEAR_BOX_REDUCTION, "rio" };
  OverTalonFX m_lowerLeft{ 21, ControllerNeutralMode::Brake, false, LOWER_GEAR_BOX_REDUCTION, "rio" };

  // UpperMotors
  OverTalonFX m_upperMotor{ 22, ControllerNeutralMode::Brake, false, UPPER_GEAR_BOX_REDUCTION, "rio" };

  // State
  double lowerAngle = 0.0;
  double upperAngle = 0.0;

  // Motion Magic Feed Forward
  double lowerFF = 0.0;
  double upperFF = 0.0;
};
