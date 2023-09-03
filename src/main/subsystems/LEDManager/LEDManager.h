// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/AddressableLED.h>
#include <frc/PWM.h>
#include <frc/Timer.h>
#include <frc/DriverStation.h>

#include "LEDState.h"

class LEDManager : public frc2::SubsystemBase {
public:
	LEDManager();

	void setColor(frc::Color color);
	void setLEDAllianceColor();
	void setLEDStripState(LEDState state);
	void Periodic() override;

private:
	void chase(frc::Color color, int tailLength);
	void linearPulse(frc::Color color, units::second_t cycle);
	void sinusoidalPulse(frc::Color color, units::second_t cycle);

	static const int kLength = 200;
	int firstPixel = 0;
	frc::AddressableLED m_led{ 0 };
	std::array<frc::AddressableLED::LEDData, kLength> m_ledBuffer;

	LEDState ledState = LEDState::AllianceColor;
	frc::Color color = frc::Color::kWhite;
};
