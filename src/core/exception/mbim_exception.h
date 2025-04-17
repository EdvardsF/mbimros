#pragma once

#include <exception>
#include <string>
#include <vector>
#include <iostream>

class MBIMException : public std::exception {
private:
    std::string message;

public:
    explicit MBIMException(const std::string& msg);

    const char* what() const noexcept override;

    friend std::ostream& operator<<(std::ostream& os, const MBIMException& ex);

    virtual std::string type() const;
};

class MBIMWarning {
private:
    std::string message;

public:
    explicit MBIMWarning(const std::string& msg);

    virtual std::string type() const;

    const std::string& getMessage() const;

    static const std::vector<MBIMWarning>& getWarnings();

    static void clearWarnings();

    friend std::ostream& operator<<(std::ostream& os, const MBIMWarning& warn);

private:
    static std::vector<MBIMWarning>& warnings();
};