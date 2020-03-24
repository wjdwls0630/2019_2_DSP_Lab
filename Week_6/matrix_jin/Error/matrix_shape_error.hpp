//
// Created by ParkJungJin on 2019-09-27.
//

#ifndef _MATRIXSHAPEERROR_HPP
#define _MATRIXSHAPEERROR_HPP

class MatrixShapeError : public std::exception{
private:
    std::string message;
public:
    MatrixShapeError(int& t_length, int &t_row, int &t_col)
    :message("MatrixShapeError : the matrix can't reshape "+std::to_string(t_length)+" elements to ("+std::to_string(t_row)+", "+std::to_string(t_col)+")") {}
    const char* what() const throw(){
        return message.c_str();
    }
};

#endif //_MATRIXSHAPEERROR_HPP
