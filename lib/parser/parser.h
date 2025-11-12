#include "../output/output.cpp"
#include <string>

struct ArgsParserValues{
    std::string inputString;
    std::string outputString;
    int Freq = 0;
    int maxIter = 0;
};


class ArgsParser{
    public:
    ArgsParserValues ProcessArgs(int& argc, char* argv[]);
    std::string GetArgFromString(std::string argfull);
};