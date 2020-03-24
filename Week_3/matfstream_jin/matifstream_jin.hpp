//
// Created by ParkJungJin on 2019-10-02.
//

#ifndef _MATIFSTREAM_JIN_HPP
#define _MATIFSTREAM_JIN_HPP

#include "Error/file_not_found.hpp"

template <typename T>
class MatIfstream_Jin {
private:
    std::string m_fname;
    std::string m_mode;
    std::ifstream m_inFile;
public:
    MatIfstream_Jin(const std::string &t_Filename="", const std::string &t_mode="none")
            : m_fname(t_Filename), m_mode(t_mode){
        if (this->m_fname!=""){
            this->open(this->m_fname, this->m_mode);
        }
    }

    virtual ~MatIfstream_Jin(){
        if(this->m_inFile.is_open()){
            this->m_inFile.close();
        }
    }

    const std::string &getFname() const { return this->m_fname; }

    void setFname(const std::string &t_Fname) { this->m_fname = t_Fname; }

    const std::string &getMode() const{ return this->m_mode; }

    void setMode(const std::string &mMode);

    //function
    int open(const std::string &t_Filename="", const std::string &t_mode="none");
    int read(const Matrix_Jin<T> &t_matrix);
    int close() {
        if (this->m_inFile.is_open()){
            this->m_inFile.close();
            return 1;
        }
        return 0;
    }
};

template <typename T>
int MatIfstream_Jin<T>::open(const std::string &t_Filename, const std::string &t_mode) {
    if (this->getFname()!=""){
        if (this->m_mode=="none"){
            this->m_inFile.open(this->m_fname);
            if(!this->m_inFile){
                throw FileNotFound(t_Filename);
            }
        } else if(this->m_mode=="binary"){
            this->m_inFile.open(this->m_fname, std::ios::binary | std::ios::out);
            if(!this->m_inFile){
                throw FileNotFound(t_Filename);
            }
        }
        return 1;
    }
    return 0;
}

template<typename T>
int MatIfstream_Jin<T>::read(const Matrix_Jin<T> &t_matrix) {
    if (this->m_mode == "none"){
        for (int i = 0; i < t_matrix.getLength(); i++) {
            this->m_inFile >> t_matrix.getMatrix()[i];
        }
        return 1;
    } else if(this->m_mode == "binary"){
        this->m_inFile.read((char *)t_matrix.getMatrix(), t_matrix.getLength()* sizeof(T));
        return 1;
    }
    return 0;
}


#endif //_MATIFSTREAM_JIN_HPP
