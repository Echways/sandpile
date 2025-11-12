#include "../parser/parser.cpp"


class ExportOperations{
    public:
    void ExportImage(ImageData& image, InputData& input, OutputData& output, const SandpileModel& sandpile, ArgsParserValues& args, int i);
    void ExportImage(ImageData& image, InputData& input, OutputData& output, const SandpileModel& sandpile, ArgsParserValues& args);
};