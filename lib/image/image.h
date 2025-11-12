#pragma once
#include <cstdint>
#include <iostream>
#include "../sandpile/sandpile.cpp"

class ColorData{
    public:
    struct Color{
        float Red;
        float Green;
        float Blue;

        Color(): Red(0), Green(0), Blue(0){};
    };
};

class ImageData{
    public:
    ImageData() : _pixelColorsArray(nullptr) {}
    ~ImageData() {
        delete[] _pixelColorsArray;
    }

    void InitImage(int64_t size);
    void SetColor(uint64_t sandpileValue, size_t position);
    void InitColors(const SandpileModel& sandpile);
    ColorData::Color GetColor(int64_t position);

    private:
    ColorData::Color* _pixelColorsArray;
};