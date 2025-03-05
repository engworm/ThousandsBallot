#ifndef CHRONOTIMER_HPP
#define CHRONOTIMER_HPP

#include <cstdint>
#include <chrono>
#include "utility/log.hpp"

class ChronoTimer {
using clock = std::chrono::system_clock;
using milliseconds = std::chrono::milliseconds;

public:
  ChronoTimer() : m_start(clock::time_point::min()) {}

  void clear() {
    this->m_start = clock::time_point::min();
  }

  void start() {
    this->m_start = clock::system_clock::now();
  }

  bool is_started() const {
    return (m_start.time_since_epoch() != clock::duration(0));
  }

  uint32_t get_ms() const {
    if (is_started()) {
      clock::duration diff;
      diff = clock::now() - m_start;
      return (uint32_t)(duration_cast<milliseconds>(diff).count());
    } else {
      Log::error("ChronoTimer is not started");
      return 0;
    }
  }

private:
  clock::time_point m_start;
};

#endif