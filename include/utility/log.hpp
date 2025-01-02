#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <string>

class Log {
  public:
    enum LogLevel {
      INFO,
      WARN,
      ERROR
    };

    template <typename ...T>
    static void debug(const T &...objs) {
      print(std::cout, objs...);
    }
    
    template <typename ...T>
    static void info(const T &...objs) {
      std::cout << "\x1b[32m[Info]\x1b[39m ";
      print(std::cout, objs...);
    }

    template <typename ...T>
    static void warn(const T &...objs) {
      std::cout << "\x1b[33m[Warn]\x1b[39m ";
      print(std::cout, objs...);
    }

    template <typename ...T>
    static void error(const T &...objs) {
      std::cout << "\x1b[31m[Error]\x1b[39m ";
      print(std::cout, objs...);
      std::exit(EXIT_FAILURE);
    }

  private:
    template <typename Stream, typename First, typename ...Rest>
    static void print(Stream &os, const First &first, const Rest &...rest) {
      os << first;
      ((os << ' ' << rest), ...);
      os << std::endl;
    }
};

#endif
