#include "export.h"

void ExportOperations::ExportImage(ImageData& image, InputData& input, OutputData& output, const SandpileModel& sandpile, ArgsParserValues& args, int i){
    image.InitImage(sandpile.GetSize().width * sandpile.GetSize().height);
    image.InitColors(sandpile);

    output.SetOutput((args.outputString+std::to_string(i)+".bmp"));
    output.Export(output.GetOutputStream(), sandpile, image);
}

void ExportOperations::ExportImage(ImageData& image, InputData& input, OutputData& output, const SandpileModel& sandpile, ArgsParserValues& args){
    image.InitImage(sandpile.GetSize().width * sandpile.GetSize().height);
    image.InitColors(sandpile);

    output.SetOutput((args.outputString+".bmp"));
    output.Export(output.GetOutputStream(), sandpile, image);
}