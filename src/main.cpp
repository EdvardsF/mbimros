#include <iostream>

#include "hex_stream.h"
#include "mbim_decoder.h"
#include "parser.h"


int main() {
    std::string fileContents = readFile("mbim_log.txt");    
    std::vector<MatchInfo> parsedLines = parseMbimLines(fileContents);
    std::vector<MatchInfo> parsedBlocks = parseMbimBlocks(parsedLines);

    std::string exampleMbim = parsedBlocks[2].matchText;
    std::string ex = "010000000000000000000000000300000000";
    hexStream hexStream(ex);
    MBIM_OPEN_MSG open_msg(hexStream);

    std::cout << ex << std::endl;

    std::cout << open_msg.to_string() << std::endl;

    // std::cout << exampleMbim << std::endl;
    //std::cout << header.to_string() << std::endl;
    // std::cout << header.TRANSACTION_ID << std::endl;
    // std::cout << exampleMbim << std::endl;

    // for (MatchInfo match: parsedBlocks) {
    //     std::cout << match.start << "--" << match.end << ". Line: " << match.line << "    " << match.matchText << std::endl << std::endl;
    // }
    return 0;
}
