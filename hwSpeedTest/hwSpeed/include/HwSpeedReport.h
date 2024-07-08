#pragma once
#include <vector>
#include "AbstractHwSpeedTest.h"
#include "SampleTestMethod_Export.h"

#define CommonTestMethod_EXPORTS

namespace Functional
{
class HwSpeedReport : public AbstractHwSpeedTest
{
public:
    SAMPLETESTMETHOD_API HwSpeedReport(const bool& isNoiseTets, const double& expectValue, const uint16_t& m_loopCount);
    SAMPLETESTMETHOD_API virtual std::vector<double> PolyFit(const std::vector<double>& expectedFanSpeed, const std::vector<double>& actualFanSpeed,
            const int degree) override;//API2
    SAMPLETESTMETHOD_API void CreateReport() override;
    SAMPLETESTMETHOD_API void PlotGraph(const std::vector<double>& expectedHwSpeed, const std::vector<double>& actualHwSpeed) override;
    SAMPLETESTMETHOD_API void Draw(const std::vector<double>& hwSpeed) override;


protected:
    SAMPLETESTMETHOD_API double ReadHwSpeed(const unsigned int& channel) override;
};
}