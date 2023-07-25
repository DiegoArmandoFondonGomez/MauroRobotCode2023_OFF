// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc2/command/CommandScheduler.h>

void Robot::RobotInit() {
  m_container.setAllianceColor();

  m_led.SetLength(kLength);
  m_led.SetData(m_ledBuffer);
  m_led.Start();
}

void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}


void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {
  frc::DriverStation::Alliance allianceColor = frc::DriverStation::GetAlliance();

  if (allianceColor == frc::DriverStation::Alliance::kBlue) {
    for (int i = 0; i < kLength; i++) {
      m_ledBuffer[i].SetRGB(0, 0, 255);
    }
  } else if (allianceColor == frc::DriverStation::Alliance::kRed) {
    for (int i = 0; i < kLength; i++) {
      m_ledBuffer[i].SetRGB(255, 0, 0);
    }
  }
  m_led.SetData(m_ledBuffer);
}

void Robot::DisabledExit() {
  for (int i = 0; i < kLength; i++) {
    m_ledBuffer[i].SetRGB(255, 0, 255);
  }
  m_led.SetData(m_ledBuffer);
}


void Robot::AutonomousInit() {
  m_container.setAllianceColor();
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Schedule();
  }
}

void Robot::AutonomousPeriodic() {
  for (int i = 0; i < kLength; i++) {
    m_ledBuffer[i].SetRGB(255, 0, 255);
  }
  m_led.SetData(m_ledBuffer);
}

void Robot::AutonomousExit() {}

void Robot::TeleopInit() {
  m_container.setAllianceColor();
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
}

void Robot::TeleopPeriodic() {
  for (int i = 0; i < kLength; i++) {
    m_ledBuffer[i].SetRGB(255, 0, 255);
  }
  m_led.SetData(m_ledBuffer);
}

void Robot::TeleopExit() {
  for (int i = 0; i < kLength; i++) {
    m_ledBuffer[i].SetRGB(255, 0, 255);
  }
  m_led.SetData(m_ledBuffer);
}

void Robot::TestInit() {
  frc2::CommandScheduler::GetInstance().CancelAll();
}

void Robot::TestPeriodic() {}

void Robot::TestExit() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
