#include "Autonomous.h"

frc2::CommandPtr LoadingSocre(SuperStructure* m_SuperStructure, Intake* m_Intake, Chassis* m_Chassis) {
    //Get Alliance Color
    frc::DriverStation::Aliance allianceColor = frc::DriverStation::GetAlliance();

    //Get Trajectories
    pathplanner::PathPlannerTrajectory trajectoryOne = pathplanner::PathPlanner::loadPath("LoadingFirstPiece", { 2_mps, 2_mps_sq });

    //Get Initial Pose
    frc::Pose2d initialPose = pathplanner::PathPlannerTrajectory::transformTrajectoryForAlliance(trajectoryOne, allianceColor).getInitialPose();

    return frc2::cmd::Sequence(

        frc2::InstantCommand([m_Chassis, initialPose]() {m_Chassis->resetOdometry({ initialPose.X(), initialPose.Y(), 180_deg });}).ToPtr(),
        SwerveTrajectories(m_Chassis, trajectoryOne, { 1,0,0 }, { -1,0,0 }, { 1.27,0,0 }).asProxy()

    );
}