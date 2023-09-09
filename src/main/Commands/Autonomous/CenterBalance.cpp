#include "Autonomous.h"

frc2::CommandPtr CenterBalance(SuperStructure* m_SuperStructure, Intake* m_Intake, Chassis* m_Chassis, Vision* m_Vision) {
	//Get Alliance Color
	frc::DriverStation::Alliance allianceColor = frc::DriverStation::GetAlliance();

	//Get Trajectories
	pathplanner::PathPlannerTrajectory CenterBalance = pathplanner::PathPlanner::loadPath("CenterBalance", { 2.5_mps, 2.5_mps_sq });

	// Transform Trajectories for Alliance Color
	CenterBalance = pathplanner::PathPlannerTrajectory::transformTrajectoryForAlliance(CenterBalance, allianceColor);

	//Get Initial Pose
	frc::Pose2d initialPose = pathplanner::PathPlannerTrajectory::transformTrajectoryForAlliance(CenterBalance, allianceColor).getInitialPose();

	return frc2::cmd::Sequence(

		frc2::InstantCommand([m_Chassis, initialPose]() {m_Chassis->resetOdometry({ initialPose.X(), initialPose.Y(), 180_deg });}).ToPtr(),
		MiddleCommand(m_SuperStructure),
		frc2::WaitCommand(0.5_s),
		SetGamePieceTrueCommand(m_Intake, -6.0_V),
		frc2::WaitCommand(0.3_s),
		SetGamePieceFalseCommand(m_Intake),
		ClosedCommand(m_SuperStructure),

		SwerveTrajectories(m_Chassis, CenterBalance, { 1,0,0 }, { 0,0,0 }, { 1.27,0,0 }).AsProxy(),
		AutoBalance(m_Chassis)
	);
};