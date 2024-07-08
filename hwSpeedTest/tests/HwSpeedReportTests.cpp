#include <iomanip>
#include <gtest/gtest.h>
#include "SampleTestMethodUnitTestBase.h"
#include "HwSpeedReport.h"
#include "HwSpeedTestMock.h"

using ::testing::_;
using ::testing::Return;

namespace HwSpeedReportTests
{
using namespace Functional;

class HwSpeedReportTests : public SampleTestMethodUnitTests::SampleTestMethodUnitTestBase
{
public:
    void SetUp() override
    {
        SetMockTestObject(std::make_shared<HwSpeedReportMock>(false, 100.0, static_cast<uint16_t>(1)));//using mock function
    }
};

TEST_F(HwSpeedReportTests, ExpectPassPopulateTestParam)
{
    std::vector<uint32_t> chList = { 1, 2, 3, 4, 5, 6 };
    EXPECT_NO_THROW(GetMockTestReportObject()->PopulateHwParams(chList));
}
TEST_F(HwSpeedReportTests, ExpectPass_CheckHwSpeed)
{
    std::vector<uint32_t> chList = { 1, 2, 3, 4, 5, 6 };
    EXPECT_NO_THROW(GetMockTestReportObject()->PopulateHwParams(chList));
    EXPECT_CALL(*GetMockTestReportObject(), ReadHwSpeed(_)).WillRepeatedly(Return(static_cast<float>(100.0)));
    EXPECT_NO_THROW(GetMockTestReportObject()->CheckHwSpeed());
    EXPECT_EQ(GetMockTestReportObject()->GetErrorMsg().size(), 0);//expect no errors
}
TEST_F(HwSpeedReportTests, ExpectFail_CreateReportForHwSpeedTest)
{
    std::vector<uint32_t> chList = { 1, 2, 3, 4, 5, 6 };
    std::vector<double> y;
    y.push_back(1);

    EXPECT_NO_THROW(GetMockTestReportObject()->PopulateHwParams(chList));

    EXPECT_CALL(*GetMockTestReportObject(), PolyFit(_, _, _)).WillOnce(Return(y));
    EXPECT_CALL(*GetMockTestReportObject(), ReadHwSpeed(_)).WillRepeatedly(Return(static_cast<float>(5000.0)));

    EXPECT_NO_THROW(GetMockTestReportObject()->CreateReport());
    EXPECT_EQ(GetMockTestReportObject()->GetErrorMsg().size(), 6);
    EXPECT_EQ(GetMockTestReportObject()->GetErrorMsg().at(0), "HW speed MOOR for 1, Actual: 5000.000000, Expected: 100.000000");
}

TEST_F(HwSpeedReportTests, ExpectFail_CreateReportForHwSpeedNoiseTest)
{
    std::vector<uint32_t> chList = { 1, 2, 3, 4, 5, 6 };
    std::vector<double> y;
    y.push_back(1);

    SetMockTestObject(std::make_shared<HwSpeedReportMock>(true, 100.0, static_cast<uint16_t>(1)));//set it to become noise test, so it can exercise HwSpeedReport::ProcessFanSpeedNoiseData()

    EXPECT_NO_THROW(GetMockTestReportObject()->PopulateHwParams(chList));

    EXPECT_CALL(*GetMockTestReportObject(), PolyFit(_, _, _)).WillOnce(Return(y));
    EXPECT_CALL(*GetMockTestReportObject(), ReadHwSpeed(_)).WillRepeatedly(Return(static_cast<float>(5000.0)));

    EXPECT_NO_THROW(GetMockTestReportObject()->CreateReport());
    EXPECT_EQ(GetMockTestReportObject()->GetErrorMsg().size(), 12);
    EXPECT_EQ(GetMockTestReportObject()->GetErrorMsg().at(0), "HW speed MOOR for 1, Actual: 5000.000000, Expected mean: 100.000000");
    EXPECT_EQ(GetMockTestReportObject()->GetErrorMsg().at(11), "HW speed MOOR for 6, Actual: 5000.000000, Expected std deviation: 0.100000");
}
TEST_F(HwSpeedReportTests, ExpectTrue_IsMeasurementValid)
{
    EXPECT_EQ(GetMockTestReportObject()->IsMeasurementValid(20, 19, 21), true);
}
TEST_F(HwSpeedReportTests, ExpectFalse_IsMeasurementValid)
{
    EXPECT_EQ(GetMockTestReportObject()->IsMeasurementValid(20, 21, 19), false);
}

TEST_F(HwSpeedReportTests, ExpectPass_GetMean)
{
    EXPECT_NO_THROW(GetMockTestReportObject()->GetMean(1));
    EXPECT_EQ(100.0, GetMockTestReportObject()->GetMean(1));
    EXPECT_EQ(101.0, GetMockTestReportObject()->GetMean(2));
    EXPECT_EQ(200.0, GetMockTestReportObject()->GetMean(3));
    EXPECT_EQ(300.0, GetMockTestReportObject()->GetMean(4));
    EXPECT_EQ(400.0, GetMockTestReportObject()->GetMean(5));
}
// Test case for GetStdDev
TEST_F(HwSpeedReportTests, ExpectPass_GetStdDev)
{
    EXPECT_NO_THROW(GetMockTestReportObject()->GetStdDev(2));
    EXPECT_EQ(0.0, GetMockTestReportObject()->GetStdDev(1));
    EXPECT_EQ(0.072, GetMockTestReportObject()->GetStdDev(2));
    EXPECT_EQ(0.0002, GetMockTestReportObject()->GetStdDev(3));
    EXPECT_EQ(0.012, GetMockTestReportObject()->GetStdDev(4));
    EXPECT_EQ(0.012, GetMockTestReportObject()->GetStdDev(5));
}
TEST_F(HwSpeedReportTests, ExpectFail_GetMean)
{
    EXPECT_EXCEPTION(GetMockTestReportObject()->GetMean(7), "Invalid channel.");
}
TEST_F(HwSpeedReportTests, ExpectFail_GetStdDev)
{
    EXPECT_EXCEPTION(GetMockTestReportObject()->GetStdDev(7), "Invalid channel.");
}
}



