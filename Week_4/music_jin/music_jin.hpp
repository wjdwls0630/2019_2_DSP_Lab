//
// Created by ParkJungJin on 2019-10-09.
//

#ifndef _MUSIC_JIN_HPP
#define _MUSIC_JIN_HPP

#define WORD unsigned short
#define DWORD unsigned int

#include <iostream>
#include <string>

enum MusicType {WAV};

class music_jin {
private:
    MusicType m_type;
    std::string m_name;
    int m_header_size;
    int m_music_size;
    int m_mono_size;
    double m_fs;
    int m_cur_idx;
    char* m_header;
    short* m_data;
    short* m_left_data;
    short* m_right_data;



public:
    music_jin(const std::string t_Type = "", const std::string t_Name = "")
    :m_name(t_Name), m_header_size(0), m_music_size(0), m_mono_size(0), m_fs(0.0), m_cur_idx(0),
    m_header(nullptr), m_data(nullptr), m_left_data(nullptr), m_right_data(nullptr){
        if (t_Type=="wav"){
            this->m_type = MusicType ::WAV;
            this->m_header_size = 44;
            this->m_header = new char[this->m_header_size];
        }
    }

    virtual ~music_jin();

    MusicType getType() const { return this->m_type; }

    int getMusicSize() const { return this->m_music_size; }

    int getHeaderSize() const { return this->m_header_size; }

    char * getHeader() const { return this->m_header; }

    void showHeader() ;

    short* getData() const { return this->m_data; }

    double getFs() const { return this->m_fs; }

    int getCurIdx() const { return this->m_cur_idx; }

    void setCurIdx(const int &t_Index) { this->m_cur_idx = t_Index; }

    int splitData();

    int mergeData();

    int synchronize();

    int changeMelody(const double& t_Time, short(*t_Melody)(const double &));

};





#endif //_MUSIC_JIN_HPP
