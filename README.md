# TestCraft
This project will design a model which can generate unit tests with AI based on C++ files from user inputs.

# HwSpeedTest
Starting with a sample unit test dataset for HwSpeedTest. Folder structure as below:

hwSpeed (a shared library)
  |->include
        |->AbstractHwSpeedTest.h
        |->HwSpeedReport.h
        |->SampleTestMethod_Export.h

  |->src
        |->AbstractHwSpeedTest.cpp
        |->HwSpeedReport.cpp
        
apps (the executable)
  |->main.cpp

tests (unit tests)
  |->SampleTestMethodUnitTestBase.h
  |->HwSpeedTestMock.h
  |->HwSpeedReportTests.cpp
