#include "log_exception.h"
#include <utility>
#include "../log.h"

using namespace pypp;
using namespace std;

LogException::LogException() : Exception() {
    Log::write(_, Log::error_t);
}

LogException::LogException(const char * message) : Exception(message), _(message) {
    Log::write(_, Log::error_t);
}

LogException::LogException(string message) : Exception(message), _(std::move(message)) {
    Log::write(_, Log::error_t);
}

LogException::LogException(const Exception& e) : Exception(e.what()), _(e.what()) {
    Log::write(_, Log::error_t);
}

const char * LogException::what() const noexcept {
    return _.c_str();
}

LogException::~LogException() = default;