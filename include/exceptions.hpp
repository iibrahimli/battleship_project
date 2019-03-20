/*!
    Custom exceptions for the bship engine
*/

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <iostream>
#include <exception>
#include <string>


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
public:

    /*!
        @brief Base class what()

        Returns a generic error message ("Battleship exception"), 
        is overrided in its children bship exceptions

        @return Message of the exception
    */
    virtual const char *what() const noexcept {
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
    int          _row_idx;   //< row index
    int          _col_idx;   //< column index
    std::string  _msg;       //< message of the exception

public:

    /*!
        @brief Index exception constructor

        Constructs an index_exception given indices and a message

        @param row Row index
        @param col Column index
        @param msg Custom message (default: "Error at index")
    */
    index_exception(int row, int col, const char* msg = "Error at index")
    :   _row_idx(row), _col_idx(col)
    {
        _msg = std::string(msg) + " (" + std::to_string(_row_idx) + ", " + std::to_string(_col_idx) + ")";
    }


    /*!
        @brief Overridden what()

        @return User-supplied message or default "Error at index (i, j)"
    */
    const char *what(){
    	return _msg.c_str();
    }

};



#endif