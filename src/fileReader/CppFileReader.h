#include <string>
#include <vector>

class CppFileReader
{
public:
    static std::string ReadInputOfDay(int day);
    static std::vector<std::string> InputAsLines(const std::string& inputContents);
    static std::vector<std::string> InputAsLines(int day);
    static std::vector<std::string> SplitStringAtChar(const std::string& string, char splitAt);
};