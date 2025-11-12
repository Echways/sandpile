#include "input.h"
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <utility>
#include <cerrno>

void InputData::SetInput(const std::string& filePath){
    std::ifstream input;
    input.open(filePath);

    if(!input.is_open()){
        std::cerr << "Wrong input! Please restart the app with a correct input file." << std::endl;
        exit(0);
    }
    
    _inputStream = std::ifstream(filePath);
}

std::ifstream& InputData::GetInputStream(){
    return _inputStream;
}