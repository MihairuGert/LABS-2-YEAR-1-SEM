#include "ExceptionMSG.h"

const char *ExceptionMSG::what() const noexcept {
    return message.c_str();
}
