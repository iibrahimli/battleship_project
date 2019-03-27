#ifndef TEST_BS_GRID_HPP
#define TEST_BS_GRID_HPP

#include <string>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include "bs_grid.hpp"
#include "exceptions.hpp"


class test_bs_grid : public CppUnit::TestCase{

public:

    test_bs_grid() {}


    // test constructor
    void test_constructor(){
        
    }


    // test cell adressing
    void test_cell_at(){
        
    }


    // test ship placement
    void test_place_ship(){

    }


    // test targeting and hits
    void test_hit(){

    }


    // test stats (# of ships, # of shots etc)
    void test_stats(){

    }


    CPPUNIT_TEST_SUITE(test_bs_grid);
    CPPUNIT_TEST(test_constructor);
    CPPUNIT_TEST(test_cell_at);
    CPPUNIT_TEST(test_place_ship);
    CPPUNIT_TEST(test_hit);
    CPPUNIT_TEST(test_stats);
    CPPUNIT_TEST_SUITE_END();

};


#endif