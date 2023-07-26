// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "SuperStructureState.h"
#include <OvertureLib/MotorControllers/OverTalonFX/OverTalonFX.h>
#include <OvertureLib/MotorControllers/ControllerNeutralMode/ControllerNeutralMode.h>

class SuperStructure: public frc2::SubsystemBase {
public:
  SuperStructure();
  void setTargetCoord(SuperStructureState TargetCoord);
  double getLowerAngle();
  double getUpperAngle();
  double getElevatorDistance();
  SuperStructureState getTargetState();
  void Periodic() override;

private:
  void setFalconTargetPos(SuperStructureState targetState);
  double convertAngleToFalconPos(double angle);
  double convertDistanceToFalconPos(double distance);

  //constrant
  // const double LOWER_GEAR_BOX_REDUCTION = 230.4;
  // const double ELEVATOR_GEAR_BOX_REDUCTION = 3;
  //const double UPPER_GEAR_BOX_REDUCTION = 50.4;

  const double LOWER_GEAR_BOX_REDUCTION = 230.4;
  const double ELEVATOR_GEAR_BOX_REDUCTION = 3;
  const double UPPER_GEAR_BOX_REDUCTION = 50.4;


  // LowerMotors modificar el ID, Coast -> Brake y OverCANivore a Roborio
  OverTalonFX m_lowerRight{ 8, ControllerNeutralMode::Coast, false, LOWER_GEAR_BOX_REDUCTION, "OverCANivore" };
  OverTalonFX m_lowerLeft{ 6, ControllerNeutralMode::Coast, false, LOWER_GEAR_BOX_REDUCTION, "OverCANivore" };

  // Elevator Motors
  OverTalonFX m_elevatorRight{ 7, ControllerNeutralMode::Coast, false, ELEVATOR_GEAR_BOX_REDUCTION, "OverCANivore" };
  OverTalonFX m_elevatorLeft{ 5, ControllerNeutralMode::Coast, false, ELEVATOR_GEAR_BOX_REDUCTION, "OverCANivore" };

  // Upper Motors
  OverTalonFX m_upperMotor{ 4, ControllerNeutralMode::Coast, false, UPPER_GEAR_BOX_REDUCTION, "OverCANivore" };

  // State
  SuperStructureState m_TargetState{ 0.0, 0.0, 0.0 };

  //Motion Magic Feed Forward
  double lowerFF = 0.0;
  double elevatorFF = 0.0;
  double upperFF = 0.0;


};
