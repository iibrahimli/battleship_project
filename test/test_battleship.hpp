#ifndef TEST_BATTLESHIP_HPP
#define TEST_BATTLESHIP_HPP

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include "battleship.hpp"
#include "exceptions.hpp"


class test_battleship : public CppUnit::TestCase{

public:

    test_battleship() {}


    // test constructor
    void test_constructor(){
        
    }


    // test constructor
    void test_move(){
    }


    CPPUNIT_TEST_SUITE(test_battleship);
    CPPUNIT_TEST(test_constructor);
    CPPUNIT_TEST(test_move);
    CPPUNIT_TEST_SUITE_END();

};


#endif