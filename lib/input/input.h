#pragma once
#include <cstdint>
#include <iostream>
#include <fstream>

class InputData{
    public:
    void SetInput(const std::string& filePath);
    std::ifstream& GetInputStream();
    
    private:
    std::ifstream _inputStream;
};