# TestCraft
This project will design a model which can generate unit tests with AI based on C++ files from user inputs.

# HwSpeedTest
Starting with a sample unit test dataset for HwSpeedTest. Folder structure as below:

hwSpeed (a shared library)  
  |->include  
        &emsp;|->AbstractHwSpeedTest.h  
        &emsp;|->HwSpeedReport.h  
        &emsp;|->SampleTestMethod_Export.h  
  
  |->src  
        &emsp;|->AbstractHwSpeedTest.cpp  
        &emsp;|->HwSpeedReport.cpp  
          
  |->apps (the executable)  
        &emsp;|->main.cpp  
  
  |->tests (unit tests)  
        &emsp;|->SampleTestMethodUnitTestBase.h  
        &emsp;|->HwSpeedTestMock.h  
        &emsp;|->HwSpeedReportTests.cpp  



