#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "AbstractHwSpeedTest.h"
#include <iostream>

using namespace Functional;

AbstractHwSpeedTest::AbstractHwSpeedTest(const bool& isNoiseTets, const double& expectValue, const uint16_t& m_loopCount) : m_isNoiseTest(isNoiseTets), m_expect(expectValue), m_loopCount(m_loopCount)
{
}

void AbstractHwSpeedTest::PopulateHwParams(const std::vector<uint32_t>& channelList)
{
    m_channelList = channelList;
}

uint16_t AbstractHwSpeedTest::GetLoopCount()
{
    return m_loopCount;
}

double AbstractHwSpeedTest::GetMean(const unsigned int& channel)
{
    double speed = 0.0;
    switch(channel)
    {
    case 1: speed = 100.0; break;
    case 2: speed = 101.0; break;
    case 3: speed = 200.0; break;
    case 4: speed = 300.0; break;
    case 5: speed = 400.0; break;
    case 6: speed = 500.0; break;
    default:
        throw std::invalid_argument("Invalid channel.");
    }
    return speed;
}

double AbstractHwSpeedTest::GetStdDev(const unsigned int& channel)
{
    double speed = 0.0;
    switch(channel)
    {
    case 1: speed = 0.0; break;
    case 2: speed = 0.072; break;
    case 3: speed = 0.0002; break;
    case 4: speed = 0.012; break;
    case 5: speed = 0.012; break;
    case 6: speed = 0.034; break;
    default:
        throw std::invalid_argument("Invalid channel.");
    }
    return speed;
}

void AbstractHwSpeedTest::CheckHwSpeed()
{
    m_multimeterChannelToHwSpeedStoreMap.clear();

    for(const auto meterChannel : m_channelList)
    {
        for(auto loop = 0u; loop < GetLoopCount(); ++loop)
        {
            if(loop % 100 == 0 && m_isNoiseTest)
            {
                std::cout << "Loop: " << loop << std::endl;
            }
            m_fanSpeedReading = ReadHwSpeed(meterChannel);
            m_multimeterChannelToHwSpeedStoreMap[meterChannel].push_back(m_fanSpeedReading);

            m_actualHwSpeed.push_back(m_fanSpeedReading);
            m_expectedlHwSpeed.push_back(m_expect);
        }
    }
    ProcessFanSpeedMeasurement();
}

void AbstractHwSpeedTest::ProcessFanSpeedMeasurement()
{
    if(m_isNoiseTest)
    {
        ProcessFanSpeedNoiseData();
    }
    else
    {
        ProcessFanSpeedData();
    }
}

std::vector<std::string> AbstractHwSpeedTest::GetErrorMsg()
{
    return m_errorMsgVec;
}

bool AbstractHwSpeedTest::IsMeasurementValid(double measurement, double lowerLimit, double upperLimit)
{
    return !(measurement < lowerLimit || measurement > upperLimit);
}

void AbstractHwSpeedTest::ProcessFanSpeedNoiseData()
{
    for(auto ch : m_channelList)
    {
        //const auto expect = m_expect;
        auto readList = m_multimeterChannelToHwSpeedStoreMap[ch];
        //if(readList.size() != GetLoopCount)
        //{
        //    m_errorMsgVec.push_back("Data points for fan " + std::to_string(ch) + " mismatched with the loop count. Actual: " + std::to_string(readList.size()) + ", Expected: " + std::to_string(expect));
        //    continue;
        //}

        #pragma region Mean
        {
            //const auto meanExpect = m_expect;
            const auto meanLcl = m_expect - 10;
            const auto meanUcl = m_expect + 10;

            const auto mean = readList.at(0);
            const auto result = IsMeasurementValid(mean, meanLcl, meanUcl);
            if(!result)
            {
                m_errorMsgVec.push_back("HW speed MOOR for " + std::to_string(ch) + ", Actual: " + std::to_string(mean) + ", Expected mean: " + std::to_string(m_expect));
            }
        }
        #pragma endregion

        #pragma region StdDev
        {
            //constexpr auto stdDevExpect = 0.0;
            const auto stdDevLcl = m_expect - 10;
            const auto stdDevUcl = m_expect + 10;
            const auto stdDevExpect = 0.1;

            const auto stdDev = readList.at(0);
            const auto result = IsMeasurementValid(stdDev, stdDevLcl, stdDevUcl);
            if(!result)
            {
                m_errorMsgVec.push_back("HW speed MOOR for " + std::to_string(ch) + ", Actual: " + std::to_string(stdDev) + ", Expected std deviation: " + std::to_string(stdDevExpect));
            }
        }
        #pragma endregion
    }
}

void AbstractHwSpeedTest::ProcessFanSpeedData()
{
    for(auto ch : m_channelList)
    {
        auto readList = m_multimeterChannelToHwSpeedStoreMap[ch];

        const auto actualHwSpeed = readList.at(0);

        const auto lcl = m_expect - 10;
        const auto ucl = m_expect + 10;

        const auto result = IsMeasurementValid(actualHwSpeed, lcl, ucl);
        if(!result)
        {
            m_errorMsgVec.push_back("HW speed MOOR for " + std::to_string(ch) + ", Actual: " + std::to_string(actualHwSpeed) + ", Expected: " + std::to_string(m_expect));
        }
    }


    //{
    //class AbstractHwSpeedTest
    //{
    //public:
    //    SAMPLETESTMETHOD_API AbstractHwSpeedTest(const bool& isNoiseTets, const double& expectValue, const uint16_t& m_loopCount);
    //    SAMPLETESTMETHOD_API void CheckHwSpeed();
    //    SAMPLETESTMETHOD_API void PopulateHwParams(const std::vector<uint32_t>& channelList);
    //    SAMPLETESTMETHOD_API uint16_t GetLoopCount();
    //    SAMPLETESTMETHOD_API std::vector<std::string> GetErrorMsg();
    //    SAMPLETESTMETHOD_API bool IsMeasurementValid(double measurement, double lowerLimit, double upperLimit);
    //    SAMPLETESTMETHOD_API double GetMean(const unsigned int& channel);
    //    SAMPLETESTMETHOD_API double GetStdDev(const unsigned int& channel);
    //
    //protected:
    //    virtual double ReadHwSpeed(const unsigned int& channel) = 0;
    //    virtual std::vector<double> PolyFit(const std::vector<double>& expectedFanSpeed, const std::vector<double>& actualFanSpeed,
    //                                        const int degree);//API2
    //    virtual void CreateReport() = 0;
    //    virtual  void PlotGraph(const std::vector<double>& expectedHwSpeed, const std::vector<double>& actualHwSpeed) = 0;
    //    virtual void Draw(const std::vector<double>& hwSpeed) = 0;
    //
    //private:
    //    double m_expect;
    //    double m_fanSpeedReading;
    //    bool m_isNoiseTest;
    //    uint16_t m_loopCount;
    //    std::vector<uint32_t> m_channelList;
    //    std::vector<double> m_actualHwSpeed{};
    //    std::vector<double> m_expectedlHwSpeed{};
    //    std::vector<std::string> m_errorMsgVec;
    //    std::map<int, std::vector<double>> m_multimeterChannelToHwSpeedStoreMap;
    //
    //    void ProcessFanSpeedMeasurement();
    //    void ProcessFanSpeedNoiseData();
    //    void ProcessFanSpeedData();
    //};
}