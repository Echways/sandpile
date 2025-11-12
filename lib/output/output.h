#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "../image/image.cpp"

class OutputData{
    public:
    void SetOutput(const std::string& filePath);
    void Export(std::ofstream& outputStream, const SandpileModel& sandpile, ImageData& image);
    std::ofstream& GetOutputStream();
    

    private:
    std::ofstream _outputStream;
    std::string _outputString;
};