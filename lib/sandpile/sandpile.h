#include "../input/input.cpp"

struct AddWidth{};
struct AddHeight{};


struct SandpileStruct{
    int32_t width;
    int32_t height;
};

struct GrainsInPosition{
    int32_t cordX;
    int32_t cordY;
    uint64_t grainCount;
};

class SandpileModel{
    public:
    SandpileModel() : _sandpileUnit(nullptr) {}

    bool HasFours();

    SandpileStruct GetSize() const;
    uint64_t GetSandCount(int64_t position) const;


    void Proceed(SandpileModel& sandpiles);
    void Init(InputData& input);

    ~SandpileModel();
    void ClearMemory();

    private:
    void Setup(int64_t size);
    void SizeFromInput(InputData& input);
    void FillPile(InputData& input);
    GrainsInPosition GetGrainsPerPosition(InputData& input);

    SandpileStruct _sandpileSize;
    uint64_t* _sandpileUnit;
};