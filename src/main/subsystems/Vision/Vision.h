// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "OvertureLib/subsystems/VisionManager/VisionManager.h"
#include "main/subsystems/Chassis/Chassis.h"

class Vision : public VisionManager {
public:
	Vision(Chassis* chassis);
private:
	photonlib::PhotonCamera camera{ "IMX219" };
	frc::AprilTagFieldLayout tagLayout{ frc::LoadAprilTagLayoutField(frc::AprilTagField::k2023ChargedUp) };
	frc::Transform3d cameraToRobot{ {33.02_cm, 0.25_in, 4_in}, {0_deg, 0_deg, 0_deg} };
};
