#include "parser.h"

std::string ArgsParser::GetArgFromString(std::string argfull){
    argfull.erase(0, argfull.find('=') + 1);
    return argfull;
}

ArgsParserValues ArgsParser::ProcessArgs(int& argc, char* argv[]){
    ArgsParserValues returnValues;
    
    for(int i=1;i<argc; i++){
        std::string currarg = argv[i];

        if (argc > 1) {
            switch (currarg[1]) {
                case 'o':{
                    ++i;
                    returnValues.outputString = argv[i];
                    returnValues.outputString.erase(returnValues.outputString.size()-4);
                    break;}
                case 'i':{
                    ++i;
                    returnValues.inputString = argv[i];
                    break;}
                case 'm':{
                    ++i;
                    returnValues.maxIter = std::stoi(argv[i]);
                    break;}
                case 'f':{
                    ++i;
                    returnValues.Freq = std::stoi(argv[i]);
                    break;}
                default:{

                }
            }

            switch (currarg[2]) {
                case 'o':{
                    returnValues.outputString = GetArgFromString(currarg);
                    returnValues.outputString.erase(returnValues.outputString.size()-4);
                    break;}
                case 'i':{
                    returnValues.inputString = GetArgFromString(currarg);
                    break;}
                case 'm':{
                    returnValues.maxIter = std::stoi(GetArgFromString(currarg));
                    break;}
                case 'f':{
                    returnValues.Freq = std::stoi(GetArgFromString(currarg));
                    break;}
                default:{

                }
            }
        }
        else {
            std::cerr << "No options provided" << std::endl;
        }
    }
    return returnValues;
}
