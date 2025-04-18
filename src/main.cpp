#include <iostream>

#include "core/hex_stream.h"
#include "protocol/v1/messages.h"
#include "parser/parser.h"
#include "core/information_buffer.h"
#include "core/exception/mbim_exception.h"
#include "core/exception/mbim_errors.h"
#include "core/exception/mbim_warnings.h"


extern void register_all_buffers();

int main() {
    BufferTooShortException ex("expected 2, got 4");
    throw ex;
    std::cout << ex << "\n";

    DeprecatedFieldWarning ex2("asdasd");
    std::cout << ex2 << "\n";
    return 0;
    // std::string fileContents = readFile("mbim_log.txt");    
    // std::vector<MatchInfo> parsedLines = parseMbimLines(fileContents);
    // std::vector<MatchInfo> parsedBlocks = parseMbimBlocks(parsedLines);
    // std::string exampleMbim = parsedBlocks[0].matchText;

    // register_all_buffers();

    // std::string mbim_open = "02000080000000000100000000000000";
    //                        0100000034000000150000000100000000000000a289cc33bcbb8b4fb6b0133ec2aae6df0100000000000000080000000100000001000000020000000200000004000000
    // 40000000
    // 18000000
    // 58000000
    // 16000000
    // 6e000000
    // 1e000000
    // 8c000000
    // 1e000000

    // 3C006400610074006100200063006C006100730073003E00
    // 3C006400650076006900630065002000690064003E00
    // 3C006600690072006D007700610072006500200069006E0066006F003E00
    // 3C0068006100720064007700610072006500200069006E0066006F003E00

    // 400000001800000058000000160000006e0000001e0000008c0000001e0000003C006400610074006100200063006C006100730073003E003C006400650076006900630065002000690064003E003C006600690072006D007700610072006500200069006E0066006F003E003C0068006100720064007700610072006500200069006E0066006F003E00

        // BASE: 0100000034000000150000000100000000000000a289cc33bcbb8b4fb6b0133ec2aae6df0100000000000000080000000100000001000000020000000200000004000000050000000600000007000000

    // std::string mbim_close = "0100000034000000150000000100000000000000a289cc33bcbb8b4fb6b0133ec2aae6df0100000000000000080000000100000001000000020000000200000004000000050000000600000007000000400000001800000058000000160000006e0000001e0000008c0000001e0000003C006400610074006100200063006C006100730073003E003C006400650076006900630065002000690064003E003C006600690072006D007700610072006500200069006E0066006F003E003C0068006100720064007700610072006500200069006E0066006F003E00";
    // hexStream ex(mbim_close);
    // MBIM_COMMAND_MSG mbim_close_msg(ex);

    // std::cout << exampleMbim << std::endl;

    // std::cout << mbim_close_msg.to_string() << std::endl;

    // std::cout << exampleMbim << std::endl;
    //std::cout << header.to_string() << std::endl;
    // std::cout << header.TRANSACTION_ID << std::endl;
    // std::cout << exampleMbim << std::endl;

    // for (MatchInfo match: parsedBlocks) {
    //     std::cout << match.start << "--" << match.end << ". Line: " << match.line << "    " << match.matchText << std::endl << std::endl;
    // }
}
