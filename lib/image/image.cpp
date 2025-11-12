#include "image.h"


void ImageData::InitImage(int64_t size){
    _pixelColorsArray = new ColorData::Color[size]{};
}

ColorData::Color ImageData::GetColor(int64_t position){
    return _pixelColorsArray[position];
}

void ImageData::SetColor(uint64_t sandpileValue, size_t position){
    if(sandpileValue == 0){
        _pixelColorsArray[position].Red = 255;
        _pixelColorsArray[position].Green = 255;
        _pixelColorsArray[position].Blue = 255;
    } else if(sandpileValue == 1){
        _pixelColorsArray[position].Red = 0;
        _pixelColorsArray[position].Green = 255;
        _pixelColorsArray[position].Blue = 0;
    } else if(sandpileValue == 2){
        _pixelColorsArray[position].Red = 255;
        _pixelColorsArray[position].Green = 255;
        _pixelColorsArray[position].Blue = 0;
    } else if (sandpileValue == 3){
        _pixelColorsArray[position].Red = 255;
        _pixelColorsArray[position].Green = 0;
        _pixelColorsArray[position].Blue = 255;
    } else {
        _pixelColorsArray[position].Red = 0;
        _pixelColorsArray[position].Green = 0;
        _pixelColorsArray[position].Blue = 0;
    }
}

void ImageData::InitColors(const SandpileModel& sandpile){
    for(int32_t i = 0; i < sandpile.GetSize().width; ++i){
        for(int32_t j = 0; j < sandpile.GetSize().height; ++j){
            SetColor(sandpile.GetSandCount(j+i*sandpile.GetSize().height), j+i*sandpile.GetSize().height);
        }
    }
}