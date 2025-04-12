#include <iostream>
#include <fstream>
#include <string>
#include <regex>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Can't open file");

    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

int main() {
    std::cout << readFile("mbim_log.txt");
    return 0;
}
