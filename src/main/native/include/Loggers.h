// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#pragma once

#include <networktables/NetworkTable.h>

#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace loggers {
using NT_Table = std::shared_ptr<std::pair<nt::NetworkTable, nt::Value>>;

class Logger {
 public:
  virtual void OnLogTick() = 0;
  virtual std::string GetName() = 0;

 private:
  virtual std::vector<std::thread*> GetThreads() = 0;
};

class NTLogger : public Logger {
 public:
  NTLogger(std::string name, std::string path, std::vector<NT_Table> tables);

  ~NTLogger();

  void OnLogTick();

  std::string GetName();
  std::vector<NT_Table> GetTables();

 private:
  std::string name;
  std::vector<NT_Table> tables;
  std::vector<std::thread*> threads;
};

class JsonLogger : public Logger {};

class WPILogger : public Logger {};
}  // namespace loggers
