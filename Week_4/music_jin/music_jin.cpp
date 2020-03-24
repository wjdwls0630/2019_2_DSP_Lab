//
// Created by ParkJungJin on 2019-10-09.
//

#include "music_jin.hpp"

music_jin::~music_jin() {
    if(this->m_header!=nullptr){
        delete [] this->m_header;
    }

    if(this->m_data!=nullptr){
        delete [] this->m_data;
    }

    if(this->m_left_data!=nullptr){
        delete [] this->m_left_data;
    }

    if(this->m_right_data!=nullptr){
        delete [] this->m_right_data;
    }
}



void music_jin::showHeader() {
    if (this->m_header== nullptr){
        std::cerr<<"can't read"<<'\n';
        exit(444);
    }
    std::cout<<"RIFF      "<<this->m_header[0]<<this->m_header[1]<<this->m_header[2]<<this->m_header[3]<<'\n';
    std::cout<<"filesize  "<<*(DWORD*)(this->m_header+4)<<'\n';
    std::cout<<"WAVE      "<<this->m_header[8]<<this->m_header[9]<<this->m_header[10]<<this->m_header[11]<<'\n';
    std::cout<<"cksize    "<<*(DWORD*)(this->m_header+16)<<'\n';
    std::cout<<"channels  "<<*(WORD*)(this->m_header+22)<<'\n';
    std::cout<<"fs        "<<*(DWORD*)(this->m_header+24)<<'\n';
    std::cout<<"bytes/s   "<<*(DWORD*)(this->m_header+28)<<'\n';
    std::cout<<"bits/sam  "<<*(WORD*)(this->m_header+34)<<'\n';
    std::cout<<"data      "<<this->m_header[36]<<this->m_header[37]<<this->m_header[38]<<this->m_header[39]<<'\n';
    std::cout<<"cksize    "<<*(DWORD*)(this->m_header+40)<<'\n';
}

int music_jin::splitData() {
    for (int i = 0, ii = 0; i < this->m_mono_size ; i++, ii+=2) {
        this->m_left_data[i] = this->m_data[ii];
        this->m_right_data[i] = this->m_data[ii + 1];
    }
    return 1;
}

int music_jin::mergeData() {
    for (int i = 0, ii = 0; i < this->m_mono_size; i++, ii += 2){
        this->m_data[ii] = this->m_left_data[i];
        this->m_data[ii + 1] =  this->m_right_data[i];
    }
    return 1;
}


int music_jin::synchronize() {
    //modify
    this->m_music_size = (int)((*(DWORD*)(this->m_header+4)))+8 - this->m_header_size;
    this->m_fs = (double)(*(DWORD*)(this->m_header+24));
    this->m_mono_size = this->m_music_size/2;
    this->m_data = new short[this->m_music_size];
    this->m_left_data = new short [this->m_mono_size];
    this->m_right_data = new short [this->m_mono_size];
    return 1;
}

int music_jin::changeMelody(const double &t_Time, short(*t_Melody)(const double &)) {
    for (double t = 0; t < t_Time ; t+=(1.0/this->m_fs)) {
        this->m_left_data[this->m_cur_idx] = this->m_right_data[this->m_cur_idx] = t_Melody(t);
        this->m_cur_idx++;
    }
}

