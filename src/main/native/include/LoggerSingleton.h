// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#pragma once

#include <frc/smartdashboard/SendableChooser.h>

#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace loggers {
enum class MetaData {
  kProjectName,
  // kBuildDate,
  kGitHash,
  // kGitDate,
  kGitBranch,
};

struct StoredMetaData {
  std::string projectName;
  std::string gitHash;
  std::string gitBranch;
};

class SingletonLogger {
 public:
  static SingletonLogger* GetInstance();
  void RecordMetadata(MetaData field, std::string value);

  void RobotInit();
  void RobotPeriodic();
  void AutonomousInit();
  void AutonomousPeriodic();
  void TeleopInit();
  void TeleopPeriodic();

 private:
  std::vector<MetaData> m_loggedMetaData;
  StoredMetaData m_storedMetaData;
  frc::SendableChooser<std::string> m_chooser;
  std::vector<std::pair<std::string, std::pair<std::function<void()>, std::function<void()>>>> autos;
  std::string m_autoSelected;
};
}  // namespace loggers
