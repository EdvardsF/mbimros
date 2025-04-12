#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <functional>

template<typename T>
struct Field;

class Serializable {
public:
    void addField(const std::string& name, const std::string& value);

    std::string to_string() const;

    template<typename T>
    void bindField(Field<T>& f) {
        f.bind(this);
    }

    template<typename T>
    void addField(const Field<T>& f);

    template<typename T>
    void addField(const Field<T>& f, std::function<std::string(T)> enumToString);

protected:
    std::vector<std::pair<std::string, std::string>> printableFields;
};

template<typename T>
void Serializable::addField(const Field<T>& f) {
    printableFields.emplace_back(f.name, std::to_string(f.value));
}

template<typename T>
void Serializable::addField(const Field<T>& f, std::function<std::string(T)> enumToString) {
    printableFields.emplace_back(f.name, enumToString(f.value));
}
