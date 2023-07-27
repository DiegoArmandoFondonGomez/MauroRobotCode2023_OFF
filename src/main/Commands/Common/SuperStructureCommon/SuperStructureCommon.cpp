#include "SuperStructureCommon.h"

frc2::CommandPtr ClosedCommand(SuperStructure* m_SuperStructure) {
    return SetSuperStructure(m_SuperStructure, SuperStructureState(0.0, 0.0, 0.0)).ToPtr();
}

frc2::CommandPtr LongClosedCommand(SuperStructure* m_SuperStructure) {
    return frc2::SequentialCommandGroup(
        SetSuperStructure(m_SuperStructure, SuperStructureState(0.0, 0.0, 0.0)),
        frc2::WaitCommand(0.5_s),
        SetSuperStructure(m_SuperStructure, SuperStructureState(0.0, 0.0, 0.0))
    ).ToPtr();
}

frc2::CommandPtr OpenLowerWristsCommand(SuperStructure* m_SuperStructure) {
    return SetSuperStructure(m_SuperStructure, SuperStructureState(0.0, 0.0, 0.0)).ToPtr();
}

frc2::CommandPtr LowerCommand(SuperStructure* m_SuperStructure) {
    return SetSuperStructure(m_SuperStructure, SuperStructureState(0.0, 0.0, 0.0)).ToPtr();
}

frc2::CommandPtr MiddleCommand(SuperStructure* m_SuperStructure) {
    return SetSuperStructure(m_SuperStructure, SuperStructureState(0.0, 0.0, 0.0)).ToPtr();
}

frc2::CommandPtr UpperCommand(SuperStructure* m_SuperStructure) {
    return frc2::SequentialCommandGroup(
        SetSuperStructure(m_SuperStructure, SuperStructureState(0.0, 0.0, 0.0)),
        frc2::WaitCommand(0.5_s),
        SetSuperStructure(m_SuperStructure, SuperStructureState(0.0, 0.0, 0.0))
    ).ToPtr();
}

frc2::CommandPtr LoadingCommand(SuperStructure* m_SuperStructure) {
    return SetSuperStructure(m_SuperStructure, SuperStructureState(0.0, 0.0, 0.0)).ToPtr();
}

frc2::CommandPtr GroundIntakeTrueCommand(SuperStructure* m_SuperStructure, Intake* m_Intake) {
    return frc2::ParallelCommandGroup(
        SetSuperStructure(m_SuperStructure, SuperStructureState(0.0, 0.0, 0.0)),
        frc2::InstantCommand([m_Intake = m_Intake] {m_Intake->setVoltage(8_V);}, { m_Intake })
    ).ToPtr();
}

frc2::CommandPtr GroundIntakeFalseCommand(SuperStructure* m_SuperStructure, Intake* m_Intake) {
    return frc2::ParallelCommandGroup(
        SetSuperStructure(m_SuperStructure, SuperStructureState(0.0, 0.0, 0.0)),
        frc2::InstantCommand([m_Intake = m_Intake] {m_Intake->setVoltage(0_V);}, { m_Intake })
    ).ToPtr();
}

frc2::CommandPtr SetGamePieceTrueCommand(Intake* m_Intake) {
    return frc2::InstantCommand([m_Intake = m_Intake] {m_Intake->setVoltage(-8_V);}, { m_Intake }).ToPtr();
}

frc2::CommandPtr SetGamePieceFalseCommand(Intake* m_Intake) {
    return frc2::InstantCommand([m_Intake = m_Intake] {m_Intake->setVoltage(0_V);}, { m_Intake }).ToPtr();
}