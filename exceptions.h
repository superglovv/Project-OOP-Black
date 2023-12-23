#include <iostream>
#include <stdexcept>

class BaseException : public std::exception {
public:
    explicit BaseException(const char* message) noexcept : customMessage(message) {}

    [[nodiscard]] const char* what() const noexcept override {
        return customMessage.c_str();
    }

private:
    std::string customMessage;
};

class InvalidBet : public BaseException {
public:
    InvalidBet() noexcept : BaseException("!!! Bet amount must not be higher than available credits !!!") {}
};

class InvalidMove : public BaseException {
public:
    InvalidMove() noexcept : BaseException("!!! You can only choose '0' to hit or '1' to stay !!!") {}
};