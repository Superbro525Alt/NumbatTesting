// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#include "Loggers.h"

#include <networktables/NetworkTableValue.h>

using namespace loggers;

NTLogger::NTLogger(std::string name, std::string path, std::vector<NT_Table> tables)
    : name(name), tables(tables) {}

NTLogger::~NTLogger() {
  for (std::thread* thread : this->threads) {
    thread->join();
  }
}

std::string NTLogger::GetName() {
  return this->name;
}

std::vector<NT_Table> NTLogger::GetTables() {
  return this->tables;
}

void NTLogger::OnLogTick() {
  for (NT_Table table : this->tables) {
    std::thread thread = std::thread([table]() {
      for (std::string key : table->first.GetKeys()) {
        table->first.GetEntry(key).SetDefaultValue((table->second));
      }
    });
    threads.push_back(&thread);
  }
}
