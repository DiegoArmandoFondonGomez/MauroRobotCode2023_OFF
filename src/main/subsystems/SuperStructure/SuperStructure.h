// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "SuperStructureState.h"
#include <OvertureLib/MotorControllers/OverTalonFX/OverTalonFX.h>
#include <OvertureLib/MotorControllers/ControllerNeutralMode/ControllerNeutralMode.h>

class SuperStructure : public frc2::SubsystemBase {
public:
	SuperStructure();
	void setTargetCoord(SuperStructureState TargetCoord);
	double getLowerAngle();
	double getUpperAngle();
	double getElevatorDistance();
	std::string getPosition();
	void setPosition(std::string pos);
	SuperStructureState getCurrentState();
	void zeroLowerMotors();
	void Periodic() override;

private:
	void setFalconTargetPos(SuperStructureState targetState);
	double convertAngleToFalconPos(double angle);
	double convertDistanceToFalconPos(double distance);
	double upperAngleFFCalculation(double angle);

	//constant
	const double LOWER_GEAR_BOX_REDUCTION = 230.4;
	const double ELEVATOR_GEAR_BOX_REDUCTION = 3;
	const double UPPER_GEAR_BOX_REDUCTION = 51.84;


	// LowerMotors
	OverTalonFX m_lowerRight{ 20, ControllerNeutralMode::Brake, true, LOWER_GEAR_BOX_REDUCTION, "rio" };
	OverTalonFX m_lowerLeft{ 21, ControllerNeutralMode::Brake, true, LOWER_GEAR_BOX_REDUCTION, "rio" };

	// Elevator Motors
	OverTalonFX m_elevatorRight{ 22, ControllerNeutralMode::Brake, true, ELEVATOR_GEAR_BOX_REDUCTION, "rio" };
	OverTalonFX m_elevatorLeft{ 23, ControllerNeutralMode::Brake, true, ELEVATOR_GEAR_BOX_REDUCTION, "rio" };

	// Upper Motors
	OverTalonFX m_upperMotor{ 24, ControllerNeutralMode::Brake, false, UPPER_GEAR_BOX_REDUCTION, "rio" };

	// State
	SuperStructureState m_TargetState{ getCurrentState() };
	std::string position = "closed";

	//Motion Magic Feed Forward
	double lowerFF = 0.1;
	double elevatorFF = 1.3;
	double upperFF = 0.27;


};
