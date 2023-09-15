#pragma once

#include <frc2/command/InstantCommand.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/Commands.h>

#include "main/subsystems/SuperStructure/SuperStructure.h"
#include "main/Commands/Common/SetSuperStructure/SetSuperStructure.h"
#include "main/subsystems/Intake/Intake.h"

frc2::CommandPtr ClosedCommand(SuperStructure* m_superStructure, Intake* m_Intake);
frc2::CommandPtr OpenLowerWristsCommand(SuperStructure* m_superStructure);
frc2::CommandPtr LowerCommand(SuperStructure* m_superStructure);
frc2::CommandPtr LowerCommandClosed(SuperStructure* m_superStructure);
frc2::CommandPtr MiddleCommand(SuperStructure* m_superStructure);
frc2::CommandPtr UpperCommand(SuperStructure* m_superStructure);
frc2::CommandPtr LoadingCommand(SuperStructure* m_superStructure);
frc2::CommandPtr GroundIntakeTrueCommand(SuperStructure* m_superStructure, Intake* m_Intake, units::volt_t voltage);
frc2::CommandPtr GroundIntakeFalseCommand(SuperStructure* m_superStructure, Intake* m_Intake);
frc2::CommandPtr SetGamePieceTrueCommand(Intake* m_Intake, units::volt_t voltage);
frc2::CommandPtr SetGamePieceFalseCommand(Intake* m_Intake);

frc2::CommandPtr GroundIntakeAuto(SuperStructure* m_superStructure, Intake* m_Intake, units::volt_t voltage);

