//
// Created by ParkJungJin on 2019-09-27.
//

#ifndef _MATRIXCALCULATEERROR_HPP
#define _MATRIXCALCULATEERROR_HPP

class MatrixCalculateError : public std::exception{
private:
    std::string message;
public:
    MatrixCalculateError(const int &a_row, const  int &a_col, const  int &b_row, const  int &b_col)
            :message("MatrixCalculateError : the matrix can't calculate ("+std::to_string(a_row)+", "+std::to_string(a_col)+") by ("+std::to_string(b_row)+", "+std::to_string(b_col)+")") {}
    const char* what() const throw(){
        return message.c_str();
    }
};

#endif //_MATRIXCALCULATEERROR_HPP
