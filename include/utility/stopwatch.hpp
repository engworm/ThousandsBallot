#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <cstdint>
#include "utility/chronotimer.hpp"
#include "utility/log.hpp"

template <typename T>
class StopWatch : T {
  using BaseTimer = T;

public:
  explicit StopWatch(bool start) {
    if (start) {
      this->start();
    }
  };

  StopWatch(std::ostream &log, char const* activity = "StopWatch", bool start = true) 
    : log(log), activity(activity), lap(0) {
      if (start) {
        this->start();
      }
  };

  StopWatch() : log(std::cout), activity("StopWatch"), lap(0) {};

  uint32_t lap_get() {
    uint32_t current_lap = this->get_ms();
    uint32_t lap_time = current_lap - lap;
    lap = current_lap;
    return lap_time;
  }

  void show(char const *mssg) {
    uint32_t ms = this->get_ms();
    Log::info(mssg, ms);
  };

  uint32_t stop(char const *event = "stop") {
    uint32_t ms = this->get_ms();
    log << activity << " " << event << " " << ms << "ms" << std::endl;
    BaseTimer::clear();
    return ms;
  };

private:
  char const *activity;
  uint32_t lap;
  std::ostream& log;
};

#endif