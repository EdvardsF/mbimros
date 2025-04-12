#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>

struct MatchInfo {
    std::string matchText;
    size_t start;
    size_t end;
    int line;
};

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
        // Get start and end position of the match
        size_t abs_start = match.position(1) + std::distance(logText.cbegin(), searchStart);
        size_t abs_end = abs_start + match.length(1);

        // Count the line number of the match
        int line_number = 1;
        for (size_t i = 0; i < abs_start; ++i) {
            if (logText[i] == '\n') {
                ++line_number;
            }
        }
        
        // Erase new lines and spaces
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

        // Move the search start position
        searchStart = match.suffix().first;
    }

    return results;
}

std::vector<MatchInfo> parseMbimBlocks(std::vector<MatchInfo>& parsedLines) {
    std::vector<MatchInfo> mbimBlocks;
    MatchInfo currentMbimBlock;

    int currentLine = parsedLines[0].line;
    for (MatchInfo lineMatch: parsedLines) {
        if (lineMatch.line == currentLine + 1 || lineMatch.line == currentLine) {
            // Mbim data is followd in the next or current line
            currentMbimBlock.matchText += lineMatch.matchText;
            currentMbimBlock.end = lineMatch.end;
            currentLine++;
        } else {
            // Mbim match not in the next line, thus a new block
            mbimBlocks.push_back(currentMbimBlock);
            currentMbimBlock = lineMatch;
            currentLine = lineMatch.line;
        }
    }
    mbimBlocks.push_back(currentMbimBlock);
    return mbimBlocks;
}



int main() {
    std::string fileContents = readFile("mbim_log.txt");    
    std::vector<MatchInfo> parsedLines = parseMbimLines(fileContents);
    std::vector<MatchInfo> parsedBlocks = parseMbimBlocks(parsedLines);

    for (MatchInfo match: parsedBlocks) {
        std::cout << match.start << "--" << match.end << ". Line: " << match.line << "    " << match.matchText << std::endl << std::endl;
    }
    return 0;
}
