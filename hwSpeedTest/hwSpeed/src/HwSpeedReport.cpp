#include "HwSpeedReport.h"

#include <algorithm>
#include <functional>
#include <sstream>
#include <iomanip>

using namespace Functional;

HwSpeedReport::HwSpeedReport(const bool& isNoiseTets, const double& expectValue, const uint16_t& m_loopCount): AbstractHwSpeedTest(isNoiseTets, expectValue, m_loopCount)
{
}

void HwSpeedReport::CreateReport()
{
    CheckHwSpeed();
    PlotGraph(m_expectedlHwSpeed, m_actualHwSpeed);
}

double HwSpeedReport::ReadHwSpeed(const unsigned int& channel)
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

void HwSpeedReport::PlotGraph(const std::vector<double>& expectedHwSpeed, const std::vector<double>& actualHwSpeed)
{
    if(expectedHwSpeed.size() != actualHwSpeed.size())
    {
        throw std::invalid_argument("expectedHwSpeed and actualHwSpeed vector sizes do not match: " + std::to_string(expectedHwSpeed.size()) + ", " +
                                    std::to_string(actualHwSpeed.size()));
    }

    auto graph = PolyFit(expectedHwSpeed, actualHwSpeed, 1);

    Draw(graph);
}

void HwSpeedReport::Draw(const std::vector<double>& hwSpeed)
{

    std::cout << "Draw graph for " << hwSpeed.size() << std::endl;
}

std::vector<double> HwSpeedReport::PolyFit(const std::vector<double>& expectedHwSpeed, const std::vector<double>& actualHwSpeed,
        const int degree)
{
    auto a = expectedHwSpeed;
    auto b = actualHwSpeed;

    std::transform(a.begin(), a.end(), b.begin(), a.begin(), std::minus<double>());

    std::transform(a.begin(), a.end(), a.begin(), std::bind(std::multiplies<double>(), std::placeholders::_1, degree));

    return a;
}
