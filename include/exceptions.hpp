/*!
    @file Custom exceptions for the bship engine
*/

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <iostream>
#include <exception>

namespace bship{
    class bship_exception;
    class index_exception;
}


/*!
    @class bship_exception

    @brief Custom exceptions for bship engine

    The base class to all exceptions related to battleship engine
*/
class bship::bship_exception : public std::exception{

    virtual const char *what() const throw(){
    	return "Battleship exception";
    }

};



/*!
    @class index_exception

    @brief Grid index exceptions

    This exception is thrown in case an invalid operation
    is carried out with indices of bs_grid
*/
class bship::index_exception : public bship_exception{

    const char *what(){
    	return "";
    }

};



#endif