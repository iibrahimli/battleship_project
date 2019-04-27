#ifndef TEST_BS_GRID_HPP
#define TEST_BS_GRID_HPP

#include <string>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include "bs_grid.h"
#include "exceptions.hpp"


class test_bs_grid : public CppUnit::TestCase{

public:

    test_bs_grid(){}


    // test constructor
    void test_constructor(){

        // invalid size
        CPPUNIT_ASSERT_THROW(bship::bs_grid g(0, 10), bship::index_exception);

        // valid size
        CPPUNIT_ASSERT_NO_THROW(bship::bs_grid g(10, 10));

        bship::bs_grid grid(10, 10);

        // width and height tests
        CPPUNIT_ASSERT_EQUAL(10ul, grid.get_width());
        CPPUNIT_ASSERT_EQUAL(10ul, grid.get_height());
        
        // cells are initialized with ship id -1
        CPPUNIT_ASSERT_EQUAL(-1, grid.cell_at(0, 0).ship_id);
        
        // an empty grid is not ready
        CPPUNIT_ASSERT_EQUAL(false, grid.is_ready());

    }


    // test cell adressing
    void test_cell_at(){

        bship::bs_grid grid(10, 10);

        // out-of-bounds indices
        CPPUNIT_ASSERT_THROW(grid.cell_at(10, 11), bship::index_exception);
        CPPUNIT_ASSERT_THROW(grid.cell_at(-1, 0), bship::index_exception);

        // cells are initialized with empty state
        CPPUNIT_ASSERT_EQUAL(bship::CS_EMPTY, grid.cell_at(5, 3).state);
        
        // indexing and setting a value
        grid.cell_at(1, 0).state = bship::CS_MISSED;
        CPPUNIT_ASSERT_EQUAL(bship::CS_MISSED, grid.cell_at(1, 0).state);

    }


    // test ship placement
    void test_place_ship(){

        bship::bs_grid grid(10, 10);

        // correct placement
        grid.place_ship(bship::ST_FIVE, 4, 5, bship::SO_VERT);
        CPPUNIT_ASSERT_EQUAL(bship::CS_FULL, grid.cell_at(7, 5).state);
        CPPUNIT_ASSERT_EQUAL(1, grid.get_num_alive_ships());

        // return value of correct placement
        CPPUNIT_ASSERT_EQUAL(true, grid.place_ship(bship::ST_TWO, 0, 6, bship::SO_HOR));

        // no exceptions during correct placement
        CPPUNIT_ASSERT_NO_THROW(grid.place_ship(bship::ST_FOUR, 9, 0, bship::SO_HOR));
        CPPUNIT_ASSERT_EQUAL(3, grid.get_num_alive_ships());

        // return value of overlapping placement
        CPPUNIT_ASSERT_EQUAL(false, grid.place_ship(bship::ST_THREE, 9, 2, bship::SO_HOR));

        // return value of out-of-bounds placement
        CPPUNIT_ASSERT_EQUAL(false, grid.place_ship(bship::ST_THREE, 10, 2, bship::SO_HOR));
        CPPUNIT_ASSERT_EQUAL(3, grid.get_num_alive_ships());

        // placing a ship second time
        CPPUNIT_ASSERT_THROW(grid.place_ship(bship::ST_FIVE, 4, 9, bship::SO_VERT), bship::illegal_move_exception);
        CPPUNIT_ASSERT_EQUAL(3, grid.get_num_alive_ships());

    }


    // test targeting and hits
    void test_shoot_at(){

        bship::bs_grid grid(10, 8);
        std::pair<bship::shot_result, int> sr;

        // shooting an empty cell
        sr = grid.shoot_at(0, 0);
        CPPUNIT_ASSERT_EQUAL(bship::SR_MISS, sr.first);
        CPPUNIT_ASSERT_EQUAL(-1, sr.second);

        grid.place_ship(bship::ST_THREE, 1, 1, bship::SO_VERT);
        CPPUNIT_ASSERT_EQUAL(1, grid.get_num_alive_ships());

        // injuring a ship
        sr = grid.shoot_at(2, 1);
        CPPUNIT_ASSERT_EQUAL(bship::SR_HIT, sr.first);
        CPPUNIT_ASSERT_EQUAL(0, sr.second);
        CPPUNIT_ASSERT_EQUAL(1, grid.get_num_alive_ships());

        // sinking a ship
        sr = grid.shoot_at(3, 1);
        sr = grid.shoot_at(1, 1);
        CPPUNIT_ASSERT_EQUAL(bship::SR_SINK, sr.first);
        CPPUNIT_ASSERT_EQUAL(0, sr.second);
        CPPUNIT_ASSERT_EQUAL(0, grid.get_num_alive_ships());

        // checking return ship id value of ships placed after a hit
        grid.place_ship(bship::ST_TWO, 7, 5, bship::SO_VERT);
        sr = grid.shoot_at(7, 5);
        sr = grid.shoot_at(8, 5);
        CPPUNIT_ASSERT_EQUAL(bship::SR_SINK, sr.first);
        CPPUNIT_ASSERT_EQUAL(1, sr.second);
        CPPUNIT_ASSERT_EQUAL(0, grid.get_num_alive_ships());
        CPPUNIT_ASSERT_EQUAL(0, (int) grid.get_n_ships()[bship::ST_TWO]);

        // shooting a previously shot cell
        CPPUNIT_ASSERT_THROW(grid.shoot_at(1, 1), bship::illegal_move_exception);

        // making sure no exceptions are thrown
        CPPUNIT_ASSERT_NO_THROW(grid.shoot_at(5, 1));

        // shooting invalid index
        CPPUNIT_ASSERT_THROW(grid.shoot_at(-1, 1), bship::index_exception);
        CPPUNIT_ASSERT_THROW(grid.shoot_at(1, 8), bship::index_exception);

    }


    CPPUNIT_TEST_SUITE(test_bs_grid);
    CPPUNIT_TEST(test_constructor);
    CPPUNIT_TEST(test_cell_at);
    CPPUNIT_TEST(test_place_ship);
    CPPUNIT_TEST(test_shoot_at);
    CPPUNIT_TEST_SUITE_END();

};


#endif