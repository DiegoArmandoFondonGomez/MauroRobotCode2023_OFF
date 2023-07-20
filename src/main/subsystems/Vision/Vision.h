// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "OvertureLib/subsystems/VisionManager/VisionManager.h"
#include "main/subsystems/Chassis/Chassis.h"

class Vision {
public:
  Vision(Chassis* chassis);
private:
  photonlib::PhotonCamera camera{ "IMX219" };
  frc::AprilTagFieldLayout tagLayout{ frc::LoadAprilTagLayoutField(frc::AprilTagField::k2023ChargedUp) };
  frc::Transform3d cameraToRobot{ {33.02_cm, 0_cm, 14.3_cm}, {0_deg, 0_deg, 0_deg} };
};
