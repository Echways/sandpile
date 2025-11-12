#include "lib/export/export.cpp"

int main(int argc, char* argv[]){
    ArgsParserValues argValues;

    SandpileModel sandpile;
    ImageData image;

    ArgsParser args;
    ExportOperations exp;

    InputData input;
    OutputData output;

    argValues = args.ProcessArgs(argc, argv);

    input.SetInput(argValues.inputString);

    sandpile.Init(input);

    if(argValues.maxIter>0){
        for(int i=0; i<argValues.maxIter; i++){
            sandpile.Proceed(sandpile);
            if(argValues.Freq>0 && (i+1)%argValues.Freq==0){
                exp.ExportImage(image, input, output, sandpile, argValues, i);
            }
        }
    }else{
        int i=0;
        while(sandpile.HasFours()){
            sandpile.Proceed(sandpile);
            if(argValues.Freq>0 && (i+1)%argValues.Freq==0){
                exp.ExportImage(image, input, output, sandpile, argValues, i);
            }
            ++i;
        }
    }

   exp.ExportImage(image, input, output, sandpile, argValues);
}