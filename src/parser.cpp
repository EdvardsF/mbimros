#include "parser.h"
#include <algorithm>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Can't open file");

    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

std::vector<MatchInfo> parseMbimLines(const std::string& logText) {
    std::vector<MatchInfo> results; 

    std::regex pattern(R"(mbim:\s*((?:[0-9a-f]{8}\s?)+))");
    std::smatch match;

    std::string::const_iterator searchStart = logText.cbegin();
    while (std::regex_search(searchStart, logText.cend(), match, pattern)) {
        size_t abs_start = match.position(1) + std::distance(logText.cbegin(), searchStart);
        size_t abs_end = abs_start + match.length(1);

        int line_number = 1;
        for (size_t i = 0; i < abs_start; ++i) {
            if (logText[i] == '\n') {
                ++line_number;
            }
        }
        
        std::string hex = match[1].str();
        hex.erase(std::remove_if(hex.begin(), hex.end(),
                [](unsigned char c) { return c == ' ' || c == '\n'; }),
                hex.end());

        results.push_back(MatchInfo{
            hex,
            abs_start,
            abs_end,
            line_number
        });

        searchStart = match.suffix().first;
    }

    return results;
}

std::vector<MatchInfo> parseMbimBlocks(std::vector<MatchInfo>& parsedLines) {
    std::vector<MatchInfo> mbimBlocks;
    MatchInfo currentMbimBlock;

    if (parsedLines.empty()) return mbimBlocks;

    int currentLine = parsedLines[0].line;
    currentMbimBlock = parsedLines[0];

    for (size_t i = 1; i < parsedLines.size(); ++i) {
        const MatchInfo& lineMatch = parsedLines[i];

        if (lineMatch.line == currentLine + 1 || lineMatch.line == currentLine) {
            currentMbimBlock.matchText += lineMatch.matchText;
            currentMbimBlock.end = lineMatch.end;
            currentLine = lineMatch.line;
        } else {
            mbimBlocks.push_back(currentMbimBlock);
            currentMbimBlock = lineMatch;
            currentLine = lineMatch.line;
        }
    }

    mbimBlocks.push_back(currentMbimBlock);
    return mbimBlocks;
}
