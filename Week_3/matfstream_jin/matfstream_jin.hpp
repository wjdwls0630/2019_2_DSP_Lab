//
// Created by ParkJungJin on 2019-10-02.
//

#ifndef _MATFSTREAM_JIN_HPP
#define _MATFSTREAM_JIN_HPP

#include <fstream>
#include "../matrix_jin/matrix_jin.hpp"
#include "Error/file_not_found.hpp"

template <typename T>
class MatFstream_Jin : public std::fstream {

private:
    std::string m_fname;

public:
    MatFstream_Jin(const std::string &t_filename):m_fname(t_filename){}

    virtual ~MatFstream_Jin(){}

    const std::string &getFname() const { return this->m_fname; }

    void setFname(const std::string &t_Fname) { this->m_fname = t_Fname; }

    virtual int open(const std::string &t_Filename="", const std::string &t_mode="none"){}

    virtual int close(){}
};


#endif //_MATFSTREAM_JIN_HPP
