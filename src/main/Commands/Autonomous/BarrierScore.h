#include "Autonomous.h"

frc2::CommandPtr BarrierScore(SuperStructure* m_SuperStructure, Intake* m_Intake, Chassis* m_Chassis) {
	//Get Alliance Color
	frc::DriverStation::Alliance allianceColor = frc::DriverStation::GetAlliance();

	//Get Trajectories
	pathplanner::PathPlannerTrajectory barrierFirstPiece = pathplanner::PathPlanner::loadPath("BarrierFirstPiece", { 3.5_mps, 3.5_mps_sq });

	// Transform Trajectories for Alliance Color
	barrierFirstPiece = pathplanner::PathPlannerTrajectory::transformTrajectoryForAlliance(barrierFirstPiece, allianceColor);

	//Get Initial Pose
	frc::Pose2d initialPose = pathplanner::PathPlannerTrajectory::transformTrajectoryForAlliance(barrierFirstPiece, allianceColor).getInitialPose();

	return frc2::cmd::Sequence(

		UpperCommand(m_SuperStructure),
		SetGamePieceTrueCommand(m_Intake, 6.0_V),
		frc2::WaitCommand(0.5_s),
		SetGamePieceFalseCommand(m_Intake),
		ClosedCommand(m_SuperStructure),

		frc2::cmd::Parallel(
			SwerveTrajectories(m_Chassis, barrierFirstPiece, { 1,0,0 }, { -1,0,0 }, { 1.27,0,0 }).AsProxy(),

			frc2::cmd::Sequence(
				frc2::WaitCommand(2.35_s),
				GroundIntakeTrueCommand(m_SuperStructure, m_Intake, -6.0_V),
				frc2::WaitCommand(1.5_s),
				GroundIntakeFalseCommand(m_SuperStructure, m_Intake)
			)
		)

	);
};