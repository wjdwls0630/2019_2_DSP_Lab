//
// Created by ParkJungJin on 2019-10-01.
//

#ifndef _MATRIXAPPENDERROR_HPP
#define _MATRIXAPPENDERROR_HPP

class MatrixAppendError : public std::exception{
private:
    std::string message;
    int m_row_or_col; // 0 : row append 1: col append
public:
    MatrixAppendError(int t_row_or_col, const int& t_length, const int &t_row, const int &t_col){
        if (t_row_or_col == 0) {
            //row append
            message = "MatrixAppendError : "+ std::to_string(t_length)+" elements can't append "+std::to_string(t_row)+" rows by "+std::to_string(t_col)+" cols";
        } else {
            message = "MatrixAppendError : "+ std::to_string(t_length)+" elements can't append "+std::to_string(t_col)+" cols by "+std::to_string(t_row)+" rows";
        }
    }

    const char* what() const throw(){
        return message.c_str();
    }
};

#endif //_MATRIXAPPENDERROR_HPP
