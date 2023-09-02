#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/CommandPtr.h>
#include <pathplanner/lib/PathPlannerTrajectory.h>
#include <pathplanner/lib/PathPLanner.h>

#include "main/subsystems/Chassis/Chassis.h"
#include "main/subsystems/Intake/Intake.h"
#include "main/subsystems/SuperStructure/SuperStructure.h"
#include "main/subsystems/Vision/Vision.h"

#include "main/Commands/Common/SuperStructureCommon/SuperStructureCommon.h"
#include "main/Commands/Teleop/LEDCommands/LEDCommands.h"
#include "OvertureLib/Commands/Autonomous/AutoBalance/AutoBalance.h"
#include "OvertureLib/Commands/Autonomous/SwerveTrajectories/SwerveTrajectories.h"

frc2::CommandPtr LoadingScore(SuperStructure* m_SuperStructure, Intake* m_Intake, Chassis* m_Chassis, Vision* m_Vision);
frc2::CommandPtr CenterBalance(SuperStructure* m_SuperStructure, Intake* m_Intake, Chassis* m_Chassis, Vision* m_Vision);
frc2::CommandPtr BarrierScore(SuperStructure* m_SuperStructure, Intake* m_Intake, Chassis* m_Chassis, Vision* m_Vision);
