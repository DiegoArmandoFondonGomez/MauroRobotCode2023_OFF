#include "SuperStructureCommon.h"

frc2::CommandPtr ClosedCommand(SuperStructure* m_SuperStructure, Intake* m_Intake) {
	return frc2::cmd::Select<SuperStructurePosition>(
		[m_SuperStructure] { return m_SuperStructure->getPosition(); },
		std::pair{ SuperStructurePosition::Upper, frc2::cmd::Sequence(
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::Closed);}, { m_SuperStructure }),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 0.0, 100 });}, { m_SuperStructure }),
			frc2::cmd::Wait(1_s),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ -6, 0.0, 100 });}, { m_SuperStructure })
		) },
		std::pair{ SuperStructurePosition::Middle, frc2::cmd::Sequence(
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::Closed);}, { m_SuperStructure }),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 0.0, 100 });}, { m_SuperStructure }),
			frc2::cmd::Wait(1_s),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ -6, 0.0, 100 });}, { m_SuperStructure })
		) },
		std::pair{ SuperStructurePosition::IntakeOpen, frc2::cmd::Sequence(
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::Closed);}, { m_SuperStructure }),
			frc2::InstantCommand([m_Intake] {m_Intake->setVoltage(0_V);}, { m_Intake }),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ -6, 0.0, 100 });}, { m_SuperStructure })
		) },
		std::pair{ SuperStructurePosition::Opened, frc2::cmd::Sequence(
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::Closed);}, { m_SuperStructure }),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ -6, 0.0, 100 });}, { m_SuperStructure })
		) }
	);
}

frc2::CommandPtr OpenLowerWristsCommand(SuperStructure* m_SuperStructure) {
	return frc2::cmd::Select<SuperStructurePosition>(
		[m_SuperStructure] { return m_SuperStructure->getPosition(); },
		std::pair{ SuperStructurePosition::Closed, frc2::cmd::Sequence(
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::Opened);}, { m_SuperStructure }),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 0.0, 100.0 });}, { m_SuperStructure }).ToPtr()
		) }
	);

}

frc2::CommandPtr LowerCommand(SuperStructure* m_SuperStructure) {
	return frc2::cmd::Select<SuperStructurePosition>(
		[m_SuperStructure] { return m_SuperStructure->getPosition(); },
		std::pair{ SuperStructurePosition::Closed, frc2::cmd::Sequence(
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::Lower);}, { m_SuperStructure }),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ -6.0, 0.0, 26.0 });}, { m_SuperStructure }).ToPtr()
		) });
}

frc2::CommandPtr LowerCommandClosed(SuperStructure* m_SuperStructure) {
	return frc2::cmd::Select<SuperStructurePosition>(
		[m_SuperStructure] { return m_SuperStructure->getPosition(); },
		std::pair{ SuperStructurePosition::Lower, frc2::cmd::Sequence(
		frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::Closed);}, { m_SuperStructure }),
		frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ -6.0, 0.0, 100.0 });}, { m_SuperStructure }).ToPtr()
	) }
	);
}

frc2::CommandPtr MiddleCommand(SuperStructure* m_SuperStructure) {
	return frc2::cmd::Select<SuperStructurePosition>(
		[m_SuperStructure] { return m_SuperStructure->getPosition(); },
		std::pair{ SuperStructurePosition::Closed, frc2::cmd::Sequence(
					frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::Middle);}, { m_SuperStructure }),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 0.0, 100 });}, { m_SuperStructure }),
			frc2::cmd::Wait(0.8_s),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 11.5, -43.0 });}, { m_SuperStructure })
				) },
		std::pair{ SuperStructurePosition::Opened, frc2::cmd::Sequence(
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::Middle);}, { m_SuperStructure }),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 11.5, -43.0 });}, { m_SuperStructure })
				) },
		std::pair{ SuperStructurePosition::Upper, frc2::cmd::Sequence(
						frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::Middle);}, { m_SuperStructure }),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 21.5, 0.0 });}, { m_SuperStructure }),
			frc2::cmd::Wait(0.5_s),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 11.5, 0.0 });}, { m_SuperStructure }),
			frc2::cmd::Wait(0.3_s),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 11.5, -43.0 });}, { m_SuperStructure })
				) });
}

frc2::CommandPtr UpperCommand(SuperStructure* m_SuperStructure) {
	return frc2::cmd::Select<SuperStructurePosition>(
		[m_SuperStructure] { return m_SuperStructure->getPosition(); },

		std::pair{ SuperStructurePosition::Closed, frc2::cmd::Sequence(
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::Upper);}, { m_SuperStructure }),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 0.0, 100 });}, { m_SuperStructure }),
			frc2::cmd::Wait(0.8_s),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 21.5, 0.0 });}, { m_SuperStructure }),
			frc2::cmd::Wait(1_s),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 21.5, -43.0 });}, { m_SuperStructure })
		) },
		std::pair{ SuperStructurePosition::Opened, frc2::cmd::Sequence(
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::Upper);}, { m_SuperStructure }),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 21.5, 0.0 });}, { m_SuperStructure }),
			frc2::cmd::Wait(1_s),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 21.5, -43.0 });}, { m_SuperStructure })
		) },
		std::pair{ SuperStructurePosition::Middle, frc2::cmd::Sequence(
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::Upper);}, { m_SuperStructure }),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 11.5, 0.0 });}, { m_SuperStructure }),
			frc2::cmd::Wait(0.5_s),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 21.5, 0.0 });}, { m_SuperStructure }),
			frc2::cmd::Wait(0.3_s),
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 42.0, 21.5, -43.0 });}, { m_SuperStructure })
		) });
}

frc2::CommandPtr LoadingCommand(SuperStructure* m_SuperStructure) {
	return frc2::cmd::Sequence(
		frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 50.0, 0.0, 100 });}, { m_SuperStructure }),
		frc2::cmd::Wait(0.8_s),
		frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ 50.0, 1.0, -30.0 });}, { m_SuperStructure })
	);
}

frc2::CommandPtr GroundIntakeTrueCommand(SuperStructure* m_SuperStructure, Intake* m_Intake, units::volt_t voltage) {
	return frc2::cmd::Select<SuperStructurePosition>(
		[m_SuperStructure] { return m_SuperStructure->getPosition(); },

		std::pair{ SuperStructurePosition::Closed, frc2::cmd::Sequence(
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::IntakeOpen);}, { m_SuperStructure }),
			frc2::cmd::Parallel(
				frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ -2, 0.0, -31 });}, { m_SuperStructure }),
				frc2::InstantCommand([m_Intake, voltage] {m_Intake->setVoltage(voltage);}, { m_Intake })
			)
		) },
		std::pair{ SuperStructurePosition::IntakeOpen, frc2::cmd::Sequence(
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::IntakeOpen);}, { m_SuperStructure }),
			frc2::cmd::Parallel(
				frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ -2, 0.0, -31 });}, { m_SuperStructure }),
				frc2::InstantCommand([m_Intake, voltage] {m_Intake->setVoltage(voltage);}, { m_Intake })
			)
		) });
}

frc2::CommandPtr GroundIntakeFalseCommand(SuperStructure* m_SuperStructure, Intake* m_Intake) {
	return frc2::cmd::Sequence(
		frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::Closed);}, { m_SuperStructure }),
		frc2::InstantCommand([m_Intake] {m_Intake->setVoltage(0_V);}, { m_Intake }),
		frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({ -6, 0.0, 100 });}, { m_SuperStructure })
	);
}

frc2::CommandPtr SetGamePieceTrueCommand(Intake* m_Intake, units::volt_t voltage) {
	return frc2::InstantCommand([m_Intake, voltage] {m_Intake->setVoltage(voltage);}, { m_Intake }).ToPtr();
}

frc2::CommandPtr SetGamePieceFalseCommand(Intake* m_Intake) {
	return frc2::InstantCommand([m_Intake] {m_Intake->setVoltage(0_V);}, { m_Intake }).ToPtr();
}

frc2::CommandPtr GroundIntakeAuto(SuperStructure* m_SuperStructure, Intake* m_Intake, units::volt_t voltage) {
	return frc2::cmd::Select<SuperStructurePosition>(
		[m_SuperStructure] { return m_SuperStructure->getPosition(); },

		std::pair{ SuperStructurePosition::Closed, frc2::cmd::Sequence(
			frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setPosition(SuperStructurePosition::IntakeOpen);}, { m_SuperStructure }),
			frc2::cmd::Parallel(
				frc2::InstantCommand([m_SuperStructure] {m_SuperStructure->setTargetCoord({-2.5, 0.0, -22.0  });}, { m_SuperStructure }),
				frc2::InstantCommand([m_Intake, voltage] {m_Intake->setVoltage(voltage);}, { m_Intake })
			)
		) });
}