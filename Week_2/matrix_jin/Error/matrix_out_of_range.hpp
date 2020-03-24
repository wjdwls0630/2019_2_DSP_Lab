//
// Created by ParkJungJin on 2019-09-27.
//

#ifndef _MATRIXOUTOFRANGE_HPP
#define _MATRIXOUTOFRANGE_HPP

class MatrixOutOfRange : public std::exception{
private:
    std::string message;
public:
    MatrixOutOfRange(const int &t_length)
            :message("Matrix_Out_of_Range : the index is out of range, matrix only has "+std::to_string(t_length)+" elements"){}
    const char* what() const throw(){
        return message.c_str();
    }
};

#endif //_MATRIXOUTOFRANGE_HPP
