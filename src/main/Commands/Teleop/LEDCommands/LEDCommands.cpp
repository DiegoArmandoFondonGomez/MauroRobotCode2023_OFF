#include "LEDCommands.h"

frc2::CommandPtr SetConeLED(LEDManager* m_LEDManager) {
    return frc2::InstantCommand([m_LEDManager = m_LEDManager] {m_LEDManager->setLEDStripState(LEDState::Cone);}, { m_LEDManager }).ToPtr();
}

frc2::CommandPtr SetCubeLED(LEDManager* m_LEDManager) {
    return frc2::InstantCommand([m_LEDManager = m_LEDManager] {m_LEDManager->setLEDStripState(LEDState::Cube);}, { m_LEDManager }).ToPtr();
}

frc2::CommandPtr SetLEDOverture(LEDManager* m_LEDManager) {
    return frc2::InstantCommand([m_LEDManager = m_LEDManager] {m_LEDManager->setLEDStripState(LEDState::Overture);}, { m_LEDManager }).ToPtr();
}

frc2::CommandPtr SetLEDPieceLoaded(LEDManager* m_LEDManager) {
    return frc2::InstantCommand([m_LEDManager = m_LEDManager] {m_LEDManager->setLEDStripState(LEDState::PieceLoaded);}, { m_LEDManager }).ToPtr();
}

frc2::CommandPtr SetLEDOff(LEDManager* m_LEDManager) {
    return frc2::InstantCommand([m_LEDManager = m_LEDManager] {m_LEDManager->setLEDStripState(LEDState::Off);}, { m_LEDManager }).ToPtr();
}