//
// Created by ParkJungJin on 2019-11-06.
//

#ifndef _MATRIX_HEIGHT_ERROR_HPP
#define _MATRIX_HEIGHT_ERROR_HPP

class MatrixHeightError : public std::exception{
private:
    std::string message;
    int m_row_or_col; // 0 : row append 1: col append
public:
    MatrixHeightError(const int& t_height)
    :message("MatrixHeightError : "+ std::to_string(t_height)+" is out of height"){}

    const char* what() const throw(){
        return message.c_str();
    }
};

#endif //_MATRIX_HEIGHT_ERROR_HPP
