#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>

struct MatchInfo {
    std::string matchText;
    size_t start;
    size_t end;
    int line;
};

// Reads a file into a string
std::string readFile(const std::string& filename);

// Extracts individual mbim lines (hex blocks) from log text
std::vector<MatchInfo> parseMbimLines(const std::string& logText);

// Combines adjacent mbim line matches into full message blocks
std::vector<MatchInfo> parseMbimBlocks(std::vector<MatchInfo>& parsedLines);
