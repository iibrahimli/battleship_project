#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include "test_bs_grid.hpp"
#include "test_battleship.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(test_bs_grid);
CPPUNIT_TEST_SUITE_REGISTRATION(test_battleship);


int main(){
    CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
    CppUnit::TextTestRunner runner;
    runner.addTest(suite);
    return runner.run() ? 0 : 1;
}
