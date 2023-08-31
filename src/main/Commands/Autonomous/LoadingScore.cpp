#include "Autonomous.h"

frc2::CommandPtr LoadingScore(SuperStructure* m_SuperStructure, Intake* m_Intake, Chassis* m_Chassis) {
    //Get Alliance Color
    frc::DriverStation::Alliance allianceColor = frc::DriverStation::GetAlliance();

    frc2::InstantCommand([m_swerveChassis = m_Chassis]() {m_swerveChassis->resetOdometry({ 1.80_m, 4.71_m, {180_deg} });}).ToPtr();

    //Get Trajectories
    pathplanner::PathPlannerTrajectory loadingfirstpiece = pathplanner::PathPlanner::loadPath("LoadingFirstPiece", { 3.5_mps, 3.5_mps_sq });
    pathplanner::PathPlannerTrajectory loadingsecondpiece = pathplanner::PathPlanner::loadPath("LoadingSecondPiece", { 3.5_mps, 3.5_mps_sq });

    //Get Initial Pose
    frc::Pose2d initialPose = pathplanner::PathPlannerTrajectory::transformTrajectoryForAlliance(loadingfirstpiece, allianceColor).getInitialPose();

    return frc2::cmd::Sequence(

        //Putting Pre-loaded Piece
        frc2::cmd::Sequence(
            frc2::InstantCommand([m_Chassis, initialPose]() {m_Chassis->resetOdometry({ initialPose.X(), initialPose.Y(), 180_deg });}).ToPtr(),
            UpperCommand(m_SuperStructure),
            SetGamePieceTrueCommand(m_Intake, 3.0_V),
            frc2::WaitCommand(0.5_s),
            SetGamePieceFalseCommand(m_Intake),
            ClosedCommand(m_SuperStructure),
            frc2::WaitCommand(3.0_s)
        ),

        //LoadingFirstPiece
        frc2::cmd::Parallel(
            frc2::cmd::Sequence(
                SwerveTrajectories(m_Chassis, loadingfirstpiece, { 1,0,0 }, { -1,0,0 }, { 1.27,0,0 }).AsProxy(),
                frc2::WaitCommand(2.0_s)
            )


            /* Eat piece while moving
            frc2::cmd::Sequence(
                frc2::WaitCommand(2.0_s),
                GroundIntakeTrueCommand(m_SuperStructure, m_Intake, 3.0_V),
                frc2::WaitCommand(2.0_s),
                GroundIntakeFalseCommand(m_SuperStructure, m_Intake)
            )
            */
        ),


        //Putting First Piece
        frc2::cmd::Sequence(
            UpperCommand(m_SuperStructure),
            SetGamePieceTrueCommand(m_Intake, 3.0_V),
            frc2::WaitCommand(0.5_s),
            SetGamePieceFalseCommand(m_Intake),
            ClosedCommand(m_SuperStructure),
            frc2::WaitCommand(3.0_s)
        ),

        //LoadingSecondPiece
        frc2::cmd::Parallel(
            frc2::cmd::Sequence(
                SwerveTrajectories(m_Chassis, loadingsecondpiece, { 1,0,0 }, { -1,0,0 }, { 1.27,0,0 }).AsProxy(),
                frc2::WaitCommand(2.0_s)
            )

            /* Eat piece while moving
            frc2::cmd::Sequence(
                frc2::WaitCommand(2.0_s),
                GroundIntakeTrueCommand(m_SuperStructure, m_Intake, 3.0_V),
                frc2::WaitCommand(2.0_s),
                GroundIntakeFalseCommand(m_SuperStructure, m_Intake)
            )
            */
        ),

        //Putting Second Piece
        frc2::cmd::Sequence(
            GroundIntakeTrueCommand(m_SuperStructure, m_Intake, 3.0_V),
            frc2::WaitCommand(0.5_s),
            GroundIntakeFalseCommand(m_SuperStructure, m_Intake),
            frc2::WaitCommand(3.0_s)
        )
    );
}