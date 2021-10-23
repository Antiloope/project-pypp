#ifndef PROJECT_PYPP_LOG_H
#define PROJECT_PYPP_LOG_H

#include <string>

namespace pypp {

class Log {
public:
    static void initLogFile();

    enum LogType {
        error_t = 0,
        warning_t,
        info_t
    };

    static void write(const char *, LogType);
    static void write(const std::string&, LogType);
    static void write(const std::exception&, LogType);
    static std::string getLogFilePath();
private:
    static void _write(const std::string&, LogType);
};

}

#endif //PROJECT_PYPP_LOG_H
