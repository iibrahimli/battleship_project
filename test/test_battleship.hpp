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


    // test move
    void test_move(){
    }


    // test finished game detection
    void test_game_finished(){

    }


    // test connecting game and players
    void test_connect(){

    }


    // test winner
    void test_winner(){

    }


    CPPUNIT_TEST_SUITE(test_battleship);
    CPPUNIT_TEST(test_constructor);
    CPPUNIT_TEST(test_move);
    CPPUNIT_TEST(test_game_finished);
    CPPUNIT_TEST(test_connect);
    CPPUNIT_TEST(test_winner);
    CPPUNIT_TEST_SUITE_END();

};


#endif