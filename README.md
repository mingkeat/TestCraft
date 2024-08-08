# TestCraft
Currently this repository contains a sample C++ project: HwSpeedReport, which is used to perform experiments with user prompt (e.g. GitHub Copilot) to generate the unit test with the best coverage scores.

Our baseline prompt as below:<br />
**_You're a hardware validation test engineer._**
**_Given these files:_**
**_{tag/ reference the opened .h/.cpp files in Visual Studio}_**
**_Write the unit test code for the given unit test functions:_**
**_{function_names} Important: Make sure to cover all test functions given. Note: Provide comments in the code if you need any additional help. Provide the name of the test case in the comment. Remember to use_** **_TEST_F instead of TEST._**

**_Analyse the relationship of the input file and check if there is any inheritance relationship between them, if yes, please generate the unit test by treating the entire inheritance as 1 entity, instead of_** **_creating the unit test for each function as an individual class._**

**_If mock class is available, inherit the mock class when creating the unit tests from the input files. Use the mock function declared under the mock class when generating the unit test._**

**_Use the mock function provided in the input, and avoid generating new mock class and mock function. Please generate unit tests for all accessible tests._**

**_If there is any mock function being declared, please help to generate additional unit test for each of them to test the actual code implementation._**

**_Generate the unit test such that every condition in the function are being tested._**

**_For function (including the constructor) with argument of Boolean data type, please ensure that the unit test testing both possible inputs, i.e. ‘true’ and ‘false’._**

**_Never use the EXPECT_CALL with the function which is not being mocked._**

Developer can use Bullseye to evaluate the unit test coverage score for the generated unit tests.


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



