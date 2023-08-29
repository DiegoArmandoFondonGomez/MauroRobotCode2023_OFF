// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "SetSuperStructure.h"

SetSuperStructure::SetSuperStructure(SuperStructure* superStructure, SuperStructureState targetState) :
	m_SuperStructure(superStructure),
	m_targetState(targetState) {
	AddRequirements(m_SuperStructure);
}

// Called when the command is initially scheduled.
void SetSuperStructure::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SetSuperStructure::Execute() {
	m_SuperStructure->setTargetCoord(m_targetState);
}

// Called once the command ends or is interrupted.
void SetSuperStructure::End(bool interrupted) {}

// Returns true when the command should end.
bool SetSuperStructure::IsFinished() {
	return false;
}
