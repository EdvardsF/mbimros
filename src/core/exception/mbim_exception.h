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
    virtual ~MBIMException() = default;

    const char* what() const noexcept override;
    virtual std::string type() const;

    friend std::ostream& operator<<(std::ostream& os, const MBIMException& ex);
    const std::string& getMessage() const;
};

class MBIMWarning {
private:
    std::string message;

public:
    explicit MBIMWarning(const std::string& msg);
    virtual ~MBIMWarning();

    virtual std::string type() const;
    const std::string& getMessage() const;

    static void registerWarning(const MBIMWarning& warning);
    static const std::vector<MBIMWarning>& getWarnings();
    static void clearWarnings();

    friend std::ostream& operator<<(std::ostream& os, const MBIMWarning& ex);

private:
    static std::vector<MBIMWarning>& warnings();
};
