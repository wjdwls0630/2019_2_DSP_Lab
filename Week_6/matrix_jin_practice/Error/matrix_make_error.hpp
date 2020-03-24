//
// Created by ParkJungJin on 2019-11-06.
//

#ifndef _MATRIX_MAKE_ERROR_HPP
#define _MATRIX_MAKE_ERROR_HPP

class MatrixMakeError : public std::exception {
private:
    std::string message;
public:
    MatrixShapeError(int &t_length, int &t_make_length) {
        if (t_length > t_make_length) {
            message = "MatrixMakeError : the matrix is too big to make" + std::to_string(t_make_length)
                      + " elements container(matrix length : " + std::to_string(t_length) + ")";
        } else {
            message = "MatrixMakeError : the matrix is too small to make" + std::to_string(t_make_length)
                      + " elements container(matrix length : " + std::to_string(t_length) + ")";
        }
    }

    const char *what() const throw() {
        return message.c_str();
    }
}

#endif //_MATRIX_MAKE_ERROR_HPP
