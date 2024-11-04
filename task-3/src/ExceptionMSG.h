#pragma once
#include <exception>
#include <string>

class ExceptionMSG : public std::exception{
    std::string message;
public:
    explicit ExceptionMSG(const char* msg) : message(msg) {}
    const char* what() const noexcept override;
};
