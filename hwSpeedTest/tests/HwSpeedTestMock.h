#pragma once
#include "HwSpeedReport.h"
#include <gmock/gmock.h>

namespace Functional
{
class HwSpeedReportMock : public HwSpeedReport
{
public:
    using HwSpeedReport::HwSpeedReport;

    MOCK_METHOD(double, ReadHwSpeed, (const unsigned int& channel), (override));
    MOCK_METHOD(std::vector<double>, PolyFit, (const std::vector<double>& expectedFanSpeed, const std::vector<double>& actualFanSpeed,
                const int degree), (override));
};
}