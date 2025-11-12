#include "sandpile.h"

void SandpileModel::Setup(int64_t size){
    if (_sandpileUnit != nullptr) {
        delete[] _sandpileUnit;
    }
    _sandpileUnit = new uint64_t[size]{0};
}

SandpileModel::~SandpileModel() {}

void SandpileModel::SizeFromInput(InputData& input){
    input.GetInputStream().seekg(0, std::ios::beg);

    int32_t maxX=1;
    int32_t maxY=1;

    std::string tempX;
    std::string tempY;
    std::string grainCount;
    std::string tempFull;
    std::stringstream tempMinor;

    while(!input.GetInputStream().eof()){
        std::getline(input.GetInputStream(), tempFull, '\t');
        tempMinor << tempFull;

        std::getline(tempMinor, tempX, ',');
        std::getline(tempMinor, tempY, ',');
        std::getline(tempMinor, grainCount, ')');

        tempX = tempX.substr(1);
        tempMinor.str("");

        maxX = std::max(maxX, abs(std::stoi(tempX)));
        maxY = std::max(maxY, abs(std::stoi(tempY)));
    }

    _sandpileSize.width = maxX*2+1;
    _sandpileSize.height = maxY*2+1;
}

GrainsInPosition SandpileModel::GetGrainsPerPosition(InputData& input){
    GrainsInPosition result;

    std::string stringX;
    std::string stringY;
    std::string stringGrainCount;
    std::string tempFull;
    std::stringstream tempMinor;

    std::getline(input.GetInputStream(), tempFull, '\t');
    tempMinor << tempFull;

    std::getline(tempMinor, stringX, ',');
    std::getline(tempMinor, stringY, ',');
    std::getline(tempMinor, stringGrainCount, ')');

    stringX = stringX.substr(1);
    tempMinor.str("");

    result.cordX = std::stoi(stringX);
    result.cordY = std::stoi(stringY);
    result.grainCount = std::stoi(stringGrainCount);

    return result;
}

void SandpileModel::FillPile(InputData& input){
    input.GetInputStream().seekg(0, std::ios::beg);

    GrainsInPosition grainsPerPosition;

    _sandpileUnit += (_sandpileSize.width*_sandpileSize.height)/2;

    while(!input.GetInputStream().eof()){
        grainsPerPosition = GetGrainsPerPosition(input);

        _sandpileUnit[grainsPerPosition.cordX+grainsPerPosition.cordY*_sandpileSize.height] = grainsPerPosition.grainCount;
    }
    _sandpileUnit -= (_sandpileSize.width*_sandpileSize.height)/2;
}


void SandpileModel::Proceed(SandpileModel& sandpileOld){
    bool needsExpansionWidth = 0;
    bool needsExpansionHeight = 0;

    for (int32_t i = 0; i < sandpileOld._sandpileSize.height; ++i) {
        for (int32_t j = 0; j < sandpileOld._sandpileSize.width; ++j) {
            if (sandpileOld._sandpileUnit[j + i * sandpileOld._sandpileSize.width] >= 4) {
                if (j == 0 || j == sandpileOld._sandpileSize.width - 1) {
                    needsExpansionWidth = 1;
                }
                if (i == 0 || i == sandpileOld._sandpileSize.height - 1){
                    needsExpansionHeight = 1;
                }
            }
        }
        if (needsExpansionWidth && needsExpansionHeight){
            break;
        }
    }

    if(needsExpansionWidth){
        SandpileModel expandedSandpile;

        expandedSandpile._sandpileSize.width = sandpileOld._sandpileSize.width+2;
        expandedSandpile._sandpileSize.height = sandpileOld._sandpileSize.height;
     
        expandedSandpile.Setup(expandedSandpile._sandpileSize.width * expandedSandpile._sandpileSize.height);

        for (int32_t i = 0; i < sandpileOld._sandpileSize.height; ++i) {
            for (int32_t j = 0; j < sandpileOld._sandpileSize.width; ++j) {
                expandedSandpile._sandpileUnit[(j+1)+i*expandedSandpile._sandpileSize.width] = sandpileOld._sandpileUnit[j+i*sandpileOld._sandpileSize.width];
            }
        }

        ClearMemory();
        sandpileOld = expandedSandpile;
    }
    if(needsExpansionHeight){
        SandpileModel expandedSandpile;

        expandedSandpile._sandpileSize.width = sandpileOld._sandpileSize.width;
        expandedSandpile._sandpileSize.height = sandpileOld._sandpileSize.height+2;

        expandedSandpile.Setup(expandedSandpile._sandpileSize.width * expandedSandpile._sandpileSize.height);

        for (int32_t i = 0; i < sandpileOld._sandpileSize.height; ++i) {
            for (int32_t j = 0; j < sandpileOld._sandpileSize.width; ++j) {
                expandedSandpile._sandpileUnit[j+(i+1)*expandedSandpile._sandpileSize.width] = sandpileOld._sandpileUnit[j+i*sandpileOld._sandpileSize.width];
            }
        }
        
        ClearMemory();
        sandpileOld = expandedSandpile;
    }

    SandpileModel sandpileNew;
    sandpileNew._sandpileSize = sandpileOld._sandpileSize;

    sandpileNew.Setup(sandpileNew._sandpileSize.width*sandpileNew._sandpileSize.height);

    for(int32_t i = 0; i < sandpileNew._sandpileSize.width; ++i){
        for(int32_t j = 0; j < sandpileNew._sandpileSize.height; ++j){
            uint64_t num = sandpileOld._sandpileUnit[j+i*sandpileOld._sandpileSize.width];
            if(num<4){
                sandpileNew._sandpileUnit[j+i*sandpileOld._sandpileSize.width] = num;
            }
        }
    }

    for(int32_t i = 0; i < sandpileNew._sandpileSize.width; ++i){
        for(int32_t j = 0; j < sandpileNew._sandpileSize.height; ++j){
            uint64_t num = sandpileOld._sandpileUnit[j+i*sandpileOld._sandpileSize.width];
            if(num>=4){
                sandpileNew._sandpileUnit[j+i*sandpileOld._sandpileSize.width] += num-4;
                sandpileNew._sandpileUnit[j+1+i*sandpileOld._sandpileSize.width]++;
                sandpileNew._sandpileUnit[j-1+i*sandpileOld._sandpileSize.width]++;
                sandpileNew._sandpileUnit[j+(i+1)*sandpileOld._sandpileSize.width]++;
                sandpileNew._sandpileUnit[j+(i-1)*sandpileOld._sandpileSize.width]++;
            }

        }
    
    }

    ClearMemory();
    sandpileOld = sandpileNew;
}


bool SandpileModel::HasFours(){
    for(int32_t i = 0; i < _sandpileSize.width; ++i){
        for(int32_t j = 0; j < _sandpileSize.height; ++j){
            uint64_t num = _sandpileUnit[j+i*_sandpileSize.width];
            if(num>=4){
                return 1;
            }

        }
    }
    return 0;
}

void SandpileModel::ClearMemory() {
    if (_sandpileUnit != nullptr) {
        delete[] _sandpileUnit;
        _sandpileUnit = nullptr;
    }
}

void SandpileModel::Init(InputData &input){
    SizeFromInput(input);
    Setup(_sandpileSize.width * _sandpileSize.height);
    FillPile(input);
}

SandpileStruct SandpileModel::GetSize() const{
    return _sandpileSize;
}

uint64_t SandpileModel::GetSandCount(int64_t position) const{
    return _sandpileUnit[position];
}
