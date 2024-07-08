#pragma once
#include <map>
#include <mutex>
#include <string>
#include <vector>
#include <iostream>
#include "SampleTestMethod_Export.h"

namespace Functional
{
class AbstractHwSpeedTest
{
public:
    SAMPLETESTMETHOD_API AbstractHwSpeedTest(const bool& isNoiseTets, const double& expectValue, const uint16_t& m_loopCount);
    SAMPLETESTMETHOD_API void CheckHwSpeed();
    SAMPLETESTMETHOD_API void PopulateHwParams(const std::vector<uint32_t>& channelList);
    SAMPLETESTMETHOD_API uint16_t GetLoopCount();
    SAMPLETESTMETHOD_API std::vector<std::string> GetErrorMsg();
    SAMPLETESTMETHOD_API bool IsMeasurementValid(double measurement, double lowerLimit, double upperLimit);
    SAMPLETESTMETHOD_API double GetMean(const unsigned int& channel);
    SAMPLETESTMETHOD_API double GetStdDev(const unsigned int& channel);

protected:
    std::vector<double> m_actualHwSpeed{};
    std::vector<double> m_expectedlHwSpeed{};
    std::vector<std::string> m_errorMsgVec{};
    virtual double ReadHwSpeed(const unsigned int& channel) = 0;
    virtual std::vector<double> PolyFit(const std::vector<double>& expectedFanSpeed, const std::vector<double>& actualFanSpeed,
                                        const int degree) = 0; //API2
    virtual void CreateReport() = 0;
    virtual  void PlotGraph(const std::vector<double>& expectedHwSpeed, const std::vector<double>& actualHwSpeed) = 0;
    virtual void Draw(const std::vector<double>& hwSpeed) = 0;

private:
    double m_expect;
    double m_fanSpeedReading;
    bool m_isNoiseTest;
    uint16_t m_loopCount;
    std::vector<uint32_t> m_channelList;

    std::map<int, std::vector<double>> m_multimeterChannelToHwSpeedStoreMap;

    void ProcessFanSpeedMeasurement();
    void ProcessFanSpeedNoiseData();
    void ProcessFanSpeedData();
};
}