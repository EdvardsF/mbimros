#pragma once

#include <string>
#include <vector>

template<typename T>
struct Field; // forward declare Field<T>

class Serializable {
public:
    void addField(const std::string& name, const std::string& value);

    template<typename T>
    void addField(const Field<T>& f);

    std::string to_string() const;

protected:
    std::vector<std::pair<std::string, std::string>> printableFields;
};
