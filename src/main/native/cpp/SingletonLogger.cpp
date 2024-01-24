// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#include <frc/smartdashboard/SmartDashboard.h>

#include <functional>

#include "LoggerSingleton.h"

loggers::SingletonLogger* singleton_logger_instance;

loggers::SingletonLogger* loggers::SingletonLogger::GetInstance() {
  if (singleton_logger_instance != nullptr) {
    singleton_logger_instance = new SingletonLogger();
  }
  return singleton_logger_instance;
}

void loggers::SingletonLogger::RecordMetadata(MetaData field, std::string value) {
  switch (field) {
    case MetaData::kProjectName:
      m_storedMetaData.projectName = value;
      break;
    case loggers::MetaData::kGitHash:
      m_storedMetaData.gitHash = value;
      break;
    case loggers::MetaData::kGitBranch:
      m_storedMetaData.gitBranch = value;
  }
}

void loggers::SingletonLogger::RobotInit() {
  for (std::pair<std::string, std::pair<std::function<void()>, std::function<void()>>> i : autos) {
    m_chooser.AddOption(i.first, i.first);
  }
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

void loggers::SingletonLogger::RobotPeriodic() {}

void loggers::SingletonLogger::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();

  for (std::pair<std::string, std::pair<std::function<void()>, std::function<void()>>> i : autos) {
    if (m_autoSelected == i.first) {
      i.second.first();
    }
  }
}

void loggers::SingletonLogger::AutonomousPeriodic() {
  m_autoSelected = m_chooser.GetSelected();

  for (std::pair<std::string, std::pair<std::function<void()>, std::function<void()>>> i : autos) {
    if (m_autoSelected == i.first) {
      i.second.second();
    }
  }
}

void loggers::SingletonLogger::TeleopInit() {}
void loggers::SingletonLogger::TeleopPeriodic() {}
