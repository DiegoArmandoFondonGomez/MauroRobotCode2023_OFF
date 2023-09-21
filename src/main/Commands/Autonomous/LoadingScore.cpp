#include "Autonomous.h"

frc2::CommandPtr LoadingScore(SuperStructure* m_SuperStructure, Intake* m_Intake, Chassis* m_Chassis, Vision* m_vision) {
	//Get Alliance Color
	frc::DriverStation::Alliance allianceColor = frc::DriverStation::GetAlliance();

	//Get Trajectories
	pathplanner::PathPlannerTrajectory loadingfirstpiece = pathplanner::PathPlanner::loadPath("LoadingFirstPieceAlt", { 3.0_mps, 3_mps_sq });
	pathplanner::PathPlannerTrajectory loadingsecondpiece = pathplanner::PathPlanner::loadPath("LoadingSecondPiece", { 4_mps, 4_mps_sq });

	// Transform Trajectories for Alliance Color
	frc::Pose2d initialPose = pathplanner::PathPlannerTrajectory::transformTrajectoryForAlliance(loadingfirstpiece, allianceColor).getInitialPose();
	//Get Initial Pose

	return frc2::cmd::Sequence(

		//Putting Pre-loaded Piece
		frc2::InstantCommand([m_Chassis, initialPose]() {m_Chassis->resetOdometry({ initialPose.X(), initialPose.Y(), 180_deg });}).ToPtr(),
		UpperCommand(m_SuperStructure),
		frc2::WaitCommand(0.5_s),
		SetGamePieceTrueCommand(m_Intake, -4.0_V),
		frc2::WaitCommand(0.3_s),
		SetGamePieceFalseCommand(m_Intake),
		ClosedCommand(m_SuperStructure, m_Intake),

		//LoadingFirstPiece
		frc2::cmd::Parallel(
			SwerveTrajectories(m_Chassis, loadingfirstpiece, { 1,0,0 }, { 4,0,0 }, { 1.27,0,0 }).AsProxy(),

			// Eat piece while moving
			frc2::cmd::Sequence(
				frc2::WaitCommand(1.1_s),
				GroundIntakeTrueCommand(m_SuperStructure, m_Intake, -4.0_V),
				frc2::WaitCommand(1.2_s),
				GroundIntakeFalseCommand(m_SuperStructure, m_Intake)
			)
		),

		//Putting First Piece
		UpperCommand(m_SuperStructure),
		SetGamePieceTrueCommand(m_Intake, 4.0_V),
		frc2::WaitCommand(0.5_s),
		SetGamePieceFalseCommand(m_Intake),
		ClosedCommand(m_SuperStructure, m_Intake),

		// //LoadingSecondPiece
		frc2::cmd::Parallel(
			SwerveTrajectories(m_Chassis, loadingsecondpiece, { 1,0,0 }, { 0,0,0 }, { 1.27,0,0 }).AsProxy(),

			// 	// Eat piece while moving
			frc2::cmd::Sequence(
				frc2::WaitCommand(0.8_s),
				GroundIntakeTrueCommand(m_SuperStructure, m_Intake, -4.0_V),
				frc2::WaitCommand(1.5_s),
				GroundIntakeFalseCommand(m_SuperStructure, m_Intake)
			)
		)
	);
}