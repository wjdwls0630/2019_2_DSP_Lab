//
// Created by ParkJungJin on 2019-10-02.
//

#ifndef _MATOFSTREAM_JIN_HPP
#define _MATOFSTREAM_JIN_HPP

#include <fstream>
#include "Error/file_not_found.hpp"

template <typename T>
class MatOfstream_Jin {
private:
    std::string m_fname;
    std::string m_mode;
    std::ofstream m_outFile;
public:
    MatOfstream_Jin(const std::string &t_Filename="", const std::string &t_mode="none")
    : m_fname(t_Filename), m_mode(t_mode){
        if (this->m_fname!=""){
            this->open(this->m_fname, this->m_mode);
        }
    }

    virtual ~MatOfstream_Jin(){
        if(this->m_outFile.is_open()){
            this->m_outFile.close();
        }
    }

    const std::string &getFname() const { return this->m_fname; }

    void setFname(const std::string &t_Fname) { this->m_fname = t_Fname; }

    const std::string &getMode() const{ return this->m_mode; }

    void setMode(const std::string &mMode);

    //function
    int open(const std::string &t_Filename="", const std::string &t_mode="none");
    int write(const matrix_jin<T> &t_matrix);
    int write(const matrix_jin_3d<T> &t_matrix);
    int close() {
        if (this->m_outFile.is_open()){
            this->m_outFile.close();
            return 1;
        }
        return 0;
    }
};

template <typename T>
int MatOfstream_Jin<T>::open(const std::string &t_Filename, const std::string &t_mode) {
    if (this->getFname()!=""){
        if (this->m_mode=="none"){
            this->m_outFile.open(this->m_fname);
            if(!this->m_outFile){
                throw FileNotFound(t_Filename);
            }
        } else if(this->m_mode=="binary"){
            this->m_outFile.open(this->m_fname, std::ios::binary | std::ios::out);
            if(!this->m_outFile){
                throw FileNotFound(t_Filename);
            }
        }
        return 1;
    }
    return 0;
}

template<typename T>
int MatOfstream_Jin<T>::write(const matrix_jin<T> &t_matrix) {
    if (this->m_mode == "none"){
        for (int i = 0; i < t_matrix.getRow(); i++) {
            for (int j = 0; j < t_matrix.getCol(); j++) {
                this->m_outFile << t_matrix.getMatrix()[i*t_matrix.getCol() + j] << "\t";
            }
            this->m_outFile << "\n";
        }
        return 1;
    } else if(this->m_mode == "binary"){
        this->m_outFile.write((char *)t_matrix.getMatrix(), t_matrix.getLength()* sizeof(T));
        return 1;
    }
    return 0;
}

template<typename T>
int MatOfstream_Jin<T>::write(const matrix_jin_3d<T> &t_matrix) {
    if (this->m_mode == "none"){
        for (int i = 0; i < t_matrix.getRow(); i++) {
            for (int j = 0; j < t_matrix.getCol(); j++) {
                for (int k = 0; k <t_matrix.getHeight() ; ++k) {
                    this->m_outFile <<"["<<t_matrix.getMatrix()[i*t_matrix.getCol() + j*t_matrix.getHeight() + k] << ", ";
                }
                this->m_outFile<<"]"<<'\t';
            }
            this->m_outFile << "\n";
        }
        return 1;
    } else if(this->m_mode == "binary"){
        this->m_outFile.write((const char *)t_matrix.getMatrix(), t_matrix.getLength()* sizeof(T));
        return 1;
    }
    return 0;
}


#endif //_MATOFSTREAM_JIN_HPP
