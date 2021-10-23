#include "exception.h"

#include <utility>

using namespace pypp;
using namespace std;

Exception::Exception() : exception() {}

Exception::Exception(const char * message) : exception(), _(message) {}

Exception::Exception(string message) : exception(), _(std::move(message)) {}

Exception::Exception (const Exception& e) : exception(), _(e.what()) {}

const char * Exception::what() const noexcept {
    return _.c_str();
}

Exception::~Exception() = default;