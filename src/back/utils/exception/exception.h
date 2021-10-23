#ifndef PROJECT_PYPP_EXCEPTION_H
#define PROJECT_PYPP_EXCEPTION_H

#include <exception>
#include <string>

namespace pypp {

class Exception : public std::exception {
public:
    explicit Exception();

    explicit Exception(const char *message);

    explicit Exception(std::string message);

    Exception(const Exception &e);

    ~Exception() override;

    const char * what() const noexcept override;

protected:
    std::string _ = "Base exception thrown";
};

}

#endif //PROJECT_PYPP_EXCEPTION_H
