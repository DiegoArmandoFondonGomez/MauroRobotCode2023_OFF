#include "SuperStructureCommon.h"

frc2::CommandPtr ClosedCommand(SuperStructure* m_SuperStructure) {
	return frc2::cmd::Sequence(
		frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 0.0, 100 });}, { m_SuperStructure }),
		frc2::cmd::Wait(0.8_s),
		frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ -6, 0.0, 100 });}, { m_SuperStructure })
	);
}

frc2::CommandPtr OpenLowerWristsCommand(SuperStructure* m_SuperStructure) {
	return frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 0.0, 100.0 });}, { m_SuperStructure }).ToPtr();
}

frc2::CommandPtr LowerCommand(SuperStructure* m_SuperStructure) {
	return frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ -6.0, 0.0, 26.0 });}, { m_SuperStructure }).ToPtr();
}

frc2::CommandPtr LowerCommandClosed(SuperStructure* m_SuperStructure) {
	return frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ -6.0, 0.0, 100.0 });}, { m_SuperStructure }).ToPtr();
}

frc2::CommandPtr MiddleCommand(SuperStructure* m_SuperStructure) {
	return frc2::cmd::Sequence(
		frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 0.0, 100 });}, { m_SuperStructure }),
		frc2::cmd::Wait(0.8_s),
		frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 11.5, -43.0 });}, { m_SuperStructure })
	);
}

frc2::CommandPtr UpperCommand(SuperStructure* m_SuperStructure) {
	return frc2::cmd::Sequence(
		frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 0.0, 100 });}, { m_SuperStructure }),
		frc2::cmd::Wait(0.8_s),
		frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 21.5, 0.0 });}, { m_SuperStructure }),
		frc2::cmd::Wait(1_s),
		frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 21.5, -43.0 });}, { m_SuperStructure })
	);
}

frc2::CommandPtr LoadingCommand(SuperStructure* m_SuperStructure) {
	return frc2::cmd::Sequence(
		frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 50.0, 0.0, 100 });}, { m_SuperStructure }),
		frc2::cmd::Wait(0.8_s),
		frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 50.0, 1.0, -30.0 });}, { m_SuperStructure })
	);
}

frc2::CommandPtr GroundIntakeTrueCommand(SuperStructure* m_SuperStructure, Intake* m_Intake, units::volt_t voltage) {
	return frc2::cmd::Parallel(
		SetSuperStructure(m_SuperStructure, SuperStructureState(-2.5, 0.0, -32.0)),
		frc2::InstantCommand([m_Intake, voltage] {m_Intake->setVoltage(voltage);}, { m_Intake })
	);
}

frc2::CommandPtr GroundIntakeFalseCommand(SuperStructure* m_SuperStructure, Intake* m_Intake) {
	return frc2::cmd::Sequence(
		frc2::InstantCommand([m_Intake] {m_Intake->setVoltage(0_V);}, { m_Intake }),
		SetSuperStructure(m_SuperStructure, SuperStructureState(-2.5, 0.0, 100))
	);
}

frc2::CommandPtr SetGamePieceTrueCommand(Intake* m_Intake, units::volt_t voltage) {
	return frc2::InstantCommand([m_Intake, voltage] {m_Intake->setVoltage(voltage);}, { m_Intake }).ToPtr();
}

frc2::CommandPtr SetGamePieceFalseCommand(Intake* m_Intake) {
	return frc2::InstantCommand([m_Intake] {m_Intake->setVoltage(0_V);}, { m_Intake }).ToPtr();
}