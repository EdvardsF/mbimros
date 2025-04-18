#pragma once

#include <exception>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

class MBIMBaseException : public std::exception {
private:
    std::string message;

public:
    explicit MBIMBaseException(const std::string& msg);
    virtual ~MBIMBaseException() = default;

    const char* what() const noexcept override;
    virtual std::string type() const;

    friend std::ostream& operator<<(std::ostream& os, const MBIMBaseException& ex);
    const std::string& getMessage() const;
};

class MBIMBaseWarning {
private:
    std::string message;

public:
    explicit MBIMBaseWarning(const std::string& msg);
    virtual ~MBIMBaseWarning();

    virtual std::string type() const;
    const std::string& getMessage() const;

    static void registerWarning(std::unique_ptr<MBIMBaseWarning> warning);
    static const std::vector<std::unique_ptr<MBIMBaseWarning>>& getWarnings();
    static void clearWarnings();

    friend std::ostream& operator<<(std::ostream& os, const MBIMBaseWarning& ex);

private:
    static std::vector<std::unique_ptr<MBIMBaseWarning>>& warnings();

};
