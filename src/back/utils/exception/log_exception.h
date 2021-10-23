#ifndef PROJECT_PYPP_LOG_EXCEPTION_H
#define PROJECT_PYPP_LOG_EXCEPTION_H

#include <string>
#include "exception.h"

namespace pypp {

class LogException : public Exception {
public:
    explicit LogException();

    explicit LogException(const char *message);

    explicit LogException(std::string message);

    LogException(const Exception &e);

    ~LogException() override;

    const char * what() const noexcept override;

protected:
    std::string _ = "Log exception thrown";
};

}

#endif //PROJECT_PYPP_LOG_EXCEPTION_H
