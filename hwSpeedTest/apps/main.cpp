#include <iostream>
#include "HwSpeedReport.h"

using namespace Functional;

int main(int, char**)
{
    HwSpeedReport report(true, 100, 2);
    report.PopulateHwParams({1, 2, 3, 4, 5, 6});
    report.CreateReport();
    return 0;
}