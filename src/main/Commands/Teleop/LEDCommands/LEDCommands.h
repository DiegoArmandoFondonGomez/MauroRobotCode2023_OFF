#pragma once

#include <frc2/command/InstantCommand.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/CommandPtr.h>

#include "main/subsystems/LEDManager/LEDManager.h"
#include "main/subsystems/LEDManager/LEDState.h"

frc2::CommandPtr SetConeLED(LEDManager* m_LEDManager);
frc2::CommandPtr SetCubeLED(LEDManager* m_LEDManager);
frc2::CommandPtr SetLEDOverture(LEDManager* m_LEDManager);
frc2::CommandPtr SetLEDPieceLoaded(LEDManager* m_LEDManager);
frc2::CommandPtr SetLEDOff(LEDManager* m_LEDManager);