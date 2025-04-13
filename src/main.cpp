#include <iostream>

#include "hex_stream.h"
#include "mbim_decoder.h"
#include "parser.h"


int main() {
    std::string fileContents = readFile("mbim_log.txt");    
    std::vector<MatchInfo> parsedLines = parseMbimLines(fileContents);
    std::vector<MatchInfo> parsedBlocks = parseMbimBlocks(parsedLines);
    std::string exampleMbim = parsedBlocks[2].matchText;

    std::string mbim_open = "010000000000000000000000000300000000";
    std::string mbim_close = "020000000000000000000000";
    hexStream ex(mbim_close);
    MBIM_CLOSE_MSG mbim_close_msg(ex);

    std::cout << mbim_close << std::endl;

    std::cout << mbim_close_msg.to_string() << std::endl;

    // std::cout << exampleMbim << std::endl;
    //std::cout << header.to_string() << std::endl;
    // std::cout << header.TRANSACTION_ID << std::endl;
    // std::cout << exampleMbim << std::endl;

    // for (MatchInfo match: parsedBlocks) {
    //     std::cout << match.start << "--" << match.end << ". Line: " << match.line << "    " << match.matchText << std::endl << std::endl;
    // }
    return 0;
}
