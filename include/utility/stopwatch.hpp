#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <cstdint>
#include "utility/chronotimer.hpp"

template <typename T>
class StopWatch : T {
  using BaseTimer = T;

public:
  explicit StopWatch(bool start) {
    if (start) {
      this->start();
    }
  }

  explicit StopWatch(std::ostream &os, char const* activity = "StopWatch", bool start = true) 
    : os(os), activity(activity), lap(0) {
      if (start) {
        this->start();
      }
  }

  StopWatch() : os(std::cout), activity("StopWatch"), lap(0) {}

  void start() {
    BaseTimer::start();
  }

  void start(char const* messg) {
    os << activity << " " << messg << std::endl;
    BaseTimer::start();
  }

  uint32_t lap_get() {
    uint32_t current_lap = this->get_ms();
    uint32_t lap_time = current_lap - lap;
    lap = current_lap;
    return lap_time;
  }

  void show_with_flush(char const *mssg) {
    uint32_t ms = this->get_ms();
    std::cout << activity << mssg << ms << "ms" << std::endl;
  };

  uint32_t stop(char const *event = "stop") {
    uint32_t ms = this->get_ms();
    os << activity << " " << event << " " << ms << "ms" << std::endl;
    BaseTimer::clear();
    return ms;
  }

private:
  char const *activity;
  uint32_t lap;
  std::ostream& os;
};

#endif