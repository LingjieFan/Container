#include "UnitTest_Container.h"

int main()
{
    UnitTest_Container* unit_test;
    
    unit_test = UnitTest_Container_New();
    UnitTest_Container_TestAll(unit_test);
    UnitTest_Container_Del(unit_test);
    
    return 0;
}