#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>

class Log {
  public:
    enum LogLevel {
      INFO,
      WARN,
      ERROR
    };
    
    template <typename ...T>
    static void print(LogLevel level, const T &...objs) {
      auto print_with_space = [](const auto &first, const auto &...rest) {
        std::cout << first;
        ((std::cout << ' ' << rest), ...);
      };

      switch (level) {
        case INFO:
          print_with_space(objs...);
          std::cout << std::endl;
          break;
        case WARN:
          print_with_space(objs...);
          std::cout << std::endl;
          break;
        case ERROR:
          print_with_space(objs...);
          std::cerr << std::endl;
          break;
        default:
          break;
      }
    }
};

#endif
