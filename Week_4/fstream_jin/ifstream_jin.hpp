//
// Created by ParkJungJin on 2019-10-02.
//

#ifndef _ifstream_jin_HPP
#define _ifstream_jin_HPP

#include "fstream_jin.hpp"

template <typename T>
class ifstream_jin : public fstream_jin {
private:
    std::ifstream m_inFile;
public:
    ifstream_jin(const std::string &t_Fname="", const std::string &t_Mode="none", const std::string &t_Type="none")
    : fstream_jin(t_Fname, t_Mode, t_Type){
        if (this->getFname()!=""){
            if(this->getMode()=="binary"){
                this->open(this->getFname(), this->getMode(), this->getType());
            } else{
                this->open(this->getFname());
            }
        }
    }

    virtual ~ifstream_jin(){
        if(this->m_inFile.is_open()){
            this->m_inFile.close();
        }
    }



    //function
    int open(const std::string &t_Filename="", const std::string &t_Mode="none", const FileType &t_Type = FileType::NORAML) override;

    int read(const matrix_jin<T> &t_matrix);

    int read(const matrix_jin_3d<T> &t_matrix);

    int read(music_jin & t_music);

    int close() override {
        if (this->m_inFile.is_open()){
            this->m_inFile.close();
            return 1;
        }
        return 0;
    }
};

template <typename T>
int ifstream_jin<T>::open(const std::string &t_Fname, const std::string &t_Mode, const FileType &t_Type){
    //set file info
    this->setFname(t_Fname);
    this->setMode(t_Mode);
    this->setType(t_Type);

    if (this->getFname()!=""){
        if (this->getMode()=="none"){
            this->m_inFile.open(this->getFname());
            if(!this->m_inFile){
                throw FileNotFound(this->getFname());
            }
        } else if(this->getMode()=="binary"){
            this->m_inFile.open(this->getFname(), std::ios::binary);
            if(!this->m_inFile){
                throw FileNotFound(this->getFname());
            }
        }
        return 1;
    }
    return 0;
}

template<typename T>
int ifstream_jin<T>::read(const matrix_jin<T> &t_matrix) {
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

template<typename T>
int ifstream_jin<T>::read(const matrix_jin_3d<T> &t_matrix){
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

template<typename T>
int ifstream_jin<T>::read(music_jin &t_music) {
    if (this->getMode()=="none"){
        return 0;
    } else if(this->getMode()=="binary"){
        this->m_inFile.read((char *)t_music.getHeader(), t_music.getHeaderSize());
        t_music.synchronize();
        this->m_inFile.read((char *)t_music.getData(), t_music.getMusicSize());
        t_music.splitData();
    }
    return 0;
}


#endif //_ifstream_jin_HPP
