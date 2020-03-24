//
// Created by ParkJungJin on 2019-10-01.
//

#ifndef _MATRIXEMPTY_HPP
#define _MATRIXEMPTY_HPP

class MatrixEmpty : public std::exception{
private:
    std::string message;
public:
    MatrixEmpty()
            :message("Matrix_Empty : the matrix is empty" ){}
    const char* what() const throw(){
        return message.c_str();
    }
};

#endif //_MATRIXEMPTY_HPP
