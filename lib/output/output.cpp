#include "output.h"
#include <fstream>
#include <ios>

void OutputData::SetOutput(const std::string& filePath){
    _outputStream = std::ofstream(filePath, std::ios::out | std::ios::binary);
}

std::ofstream& OutputData::GetOutputStream(){
    return _outputStream;
}

void OutputData::Export(std::ofstream& outputStream, const SandpileModel& sandpile, ImageData& image){
    const int paddingAmount = (4 - (sandpile.GetSize().width * 3) % 4) % 4;
    const int fileHeaderSize = 14;
    const int infoHeaderSize = 40;
    const int fileSize = fileHeaderSize + infoHeaderSize + (sandpile.GetSize().width * 3 + paddingAmount) * sandpile.GetSize().height;

    unsigned char fileHeader[fileHeaderSize] = {
        'B', 'M',
        0, 0, 0, 0,
        0, 0, 0, 0,
        fileHeaderSize + infoHeaderSize, 0, 0, 0
    };

    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;

    unsigned char infoHeader[infoHeaderSize] = {
        infoHeaderSize, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,      
        1, 0, 
        24, 0,   
        0, 0, 0, 0,   
        0, 0, 0, 0,               
        0, 0, 0, 0,             
        0, 0, 0, 0,    
        0, 0, 0, 0,
        0, 0, 0, 0 
    };

    infoHeader[4] = sandpile.GetSize().width;
    infoHeader[5] = sandpile.GetSize().width >> 8;
    infoHeader[6] = sandpile.GetSize().width >> 16;
    infoHeader[7] = sandpile.GetSize().width >> 24;

    infoHeader[8] = sandpile.GetSize().height;
    infoHeader[9] = sandpile.GetSize().height >> 8;
    infoHeader[10] = sandpile.GetSize().height >> 16;
    infoHeader[11] = sandpile.GetSize().height >> 24;

    outputStream.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    outputStream.write(reinterpret_cast<char*>(infoHeader), infoHeaderSize);

    unsigned char bmpPad[3] = {0, 0, 0};
    for (size_t i = 0; i < sandpile.GetSize().height; i++) {
        for (size_t j = 0; j < sandpile.GetSize().width; j++) {
            const ColorData::Color& color = image.GetColor(j + i * sandpile.GetSize().width);
            unsigned char pixel[] = {static_cast<unsigned char>(color.Blue), static_cast<unsigned char>(color.Green), static_cast<unsigned char>(color.Red)};
            outputStream.write(reinterpret_cast<char*>(pixel), 3);
        }
        outputStream.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
    }

    outputStream.close();
}
