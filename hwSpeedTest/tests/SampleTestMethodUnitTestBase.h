#pragma once
#include "HwSpeedReport.h"
#include "HwSpeedTestMock.h"
#include <gtest/gtest.h>

#define EXPECT_EXCEPTION(statement, exceptionMessageStr ) \
    EXPECT_THROW({ \
        try { \
            statement; \
        } catch(std::invalid_argument const& ex) { \
            EXPECT_EQ(std::string(ex.what()), exceptionMessageStr); \
            throw; \
        } \
    }, std::invalid_argument)

namespace SampleTestMethodUnitTests
{
class SampleTestMethodUnitTestBase : public ::testing::Test
{
public:
    void TearDown() override
    {
        m_test.reset();

    }
protected:

    void SetTestObject(const std::shared_ptr<Functional::HwSpeedReport>& diagTestPtr)
    {
        m_test = diagTestPtr;
    }

    [[nodiscard]] std::shared_ptr<Functional::HwSpeedReport> GetTestObject() const
    {
        return m_test;
    }

    void SetMockTestObject(const std::shared_ptr<Functional::HwSpeedReportMock>& diagTestPtr)
    {
        m_mockReport = diagTestPtr;
    }


    [[nodiscard]] std::shared_ptr<Functional::HwSpeedReportMock> GetMockTestReportObject() const
    {
        return m_mockReport;
    }

private:
    std::shared_ptr<Functional::HwSpeedReport>  m_test;
    std::shared_ptr<Functional::HwSpeedReportMock>  m_mockReport;
};
}
