#include <iostream>

#include "core/hex_stream.h"
#include "protocol/messages.h"
#include "parser/parser.h"


int main() {
    std::string fileContents = readFile("mbim_log.txt");    
    std::vector<MatchInfo> parsedLines = parseMbimLines(fileContents);
    std::vector<MatchInfo> parsedBlocks = parseMbimBlocks(parsedLines);
    std::string exampleMbim = parsedBlocks[2].matchText;

    std::string mbim_open = "01000000340000001500000003000000";
    std::string mbim_close = "0100000034000000150000000100000000000000a289cc33bcbb8b4fb6b0133ec2aae6df01000000000000000400000011111111";
    hexStream ex(mbim_open);
    MBIM_HOST_ERROR_MSG mbim_close_msg(ex);

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
