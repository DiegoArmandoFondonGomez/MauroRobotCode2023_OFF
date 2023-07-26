// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "LEDManager.h"

LEDManager::LEDManager() {
    m_led.SetLength(kLength);
    m_led.SetData(m_ledBuffer);
    m_led.Start();
}

void LEDManager::setColor(frc::Color color) {
    for (int i = 0; i < kLength; i++) {
        m_ledBuffer[i].SetLED(color);
    }
}

void LEDManager::setLEDStripState(LEDState state) {
    ledState = state;
}

void LEDManager::chase(frc::Color color, int tailkLength) {
    for (auto i = 0; i < kLength; i++) {
        int distance = std::abs(firstPixel - i);
        double modifier = ((tailkLength + 1) - distance) / tailkLength;
        modifier = modifier > 0 ? modifier : 0;
        auto pixelColor = frc::Color(
            color.red * modifier,
            color.green * modifier,
            color.blue * modifier
        );
        m_ledBuffer[i].SetLED(pixelColor);

    }
    firstPixel = (firstPixel + 1) % kLength;
}

void LEDManager::linearPulse(frc::Color color, units::second_t cycle) {
    units::second_t time = frc::Timer::GetFPGATimestamp();
    double loop = fabs(remainder(time.value(), cycle.value()));
    double magnitude = (2 * loop) / cycle.value();
    auto pixelColor = frc::Color(
        color.red * magnitude,
        color.green * magnitude,
        color.red * magnitude
    );
    setColor(pixelColor);
}

void LEDManager::sinusoidalPulse(frc::Color color, units::time::second_t cycle) {
    units::second_t time = frc::Timer::GetFPGATimestamp();
    double loop = fabs(remainder(time.value(), cycle.value()));
    double t = (2 * loop) / cycle.value();
    double magnitude = (cos(t + std::numbers::pi) + 1) / 2;
    auto pixelColor = frc::Color(
        color.red * magnitude,
        color.green * magnitude,
        color.red * magnitude
    );
    setColor(pixelColor);
}

void LEDManager::Periodic() {
    switch (ledState) {
    case LEDState::Overture:
        color = frc::Color::kDarkViolet;
        setColor(color);
        break;
    case LEDState::Cone:
        color = frc::Color{ 255, 190, 0 };
        setColor(color);
        break;
    case LEDState::Cube:
        color = frc::Color::kPurple;
        setColor(color);
        break;
    case LEDState::PieceLoaded:
        color = frc::Color::kMediumSpringGreen;
        setColor(color);
        break;
    case LEDState::Chase:
        chase(frc::Color::kDarkViolet, 10);
        break;
    case LEDState::LinearPulse:
        linearPulse(frc::Color::kDarkViolet, 1_s);
        break;
    case LEDState::SinusoidalPulse:
        sinusoidalPulse(frc::Color::kDarkViolet, 1_s);
        break;
    case LEDState::Off:
        color = frc::Color::kBlack;
        setColor(color);
        break;
    }

    m_led.SetData(m_ledBuffer);
}
