//
// Created by ParkJungJin on 2019-10-02.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "../fstream_jin/ifstream_jin.hpp"
#include "../fstream_jin/ofstream_jin.hpp"
#include "../music_jin/music_jin.hpp"

#define WORD unsigned short
#define DWORD unsigned int

inline short A4(const double &t) {return short(20000.0*sin(2 * M_PI * 440 * t)); }
inline short A4_Sharp(const double &t) {return short(20000.0*sin(2 * M_PI * 440 *pow(2, (1.0/12.0)) * t)); }
inline short B4(const double &t) {return short(20000.0*sin(2 * M_PI * 440 * pow(2, (2.0/12.0)) * t)); }
inline short C5(const double &t) {return short(20000.0*sin(2 * M_PI * 440 * pow(2, (3.0/12.0)) * t)); }
inline short C5_Sharp(const double &t) {return short(20000.0*sin(2 * M_PI * 440 *pow(2, (4.0/12.0)) * t)); }
inline short D5(const double &t) {return short(20000.0*sin(2 * M_PI * 440 * pow(2, (5.0/12.0)) * t)); }
inline short D5_Sharp(const double &t) {return short(20000.0*sin(2 * M_PI * 440 *pow(2, (6.0/12.0)) * t)); }
inline short E5(const double &t) { return short(20000.0*sin(2 * M_PI * 440 * pow(2, (7.0/12.0)) * t)); }
inline short F5(const double &t) { return short(20000.0*sin(2 * M_PI * 440 * pow(2, (8.0/12.0)) * t)); }
inline short F5_Sharp(const double &t) { return short(20000.0*sin(2 * M_PI * 440 * pow(2, (9.0/12.0)) * t)); }
inline short G5(const double &t) { return short(20000.0*sin(2 * M_PI * 440 * pow(2, (10.0/12.0)) * t)); }
inline short G5_Sharp(const double &t) { return short(20000.0*sin(2 * M_PI * 440 * pow(2, (11.0/12.0)) * t)); }
inline short A5(const double &t) { return short(20000.0*sin(2 * M_PI * 440 * 2 * t)); }
inline short None(const double &t) { return short(20000.0*sin(2 * M_PI * 0.0 * t)); }
int main(){
    try{
        ifstream_jin<music_jin> fff_out("LetItGo.wav", "binary", "music");
        music_jin music1("wav", "LetItGo");
        fff_out.read(music1);
        music1.showHeader();

        fff_out.close();
        //start time 3
        int start_time = 3;

        music1.setCurIdx(music1.getFs()*start_time);
        music1.changeMelody(0.9, (G5));
        music1.changeMelody(0.1, (None));
        music1.changeMelody(0.4, (E5));
        music1.changeMelody(0.1, (None));
        music1.changeMelody(0.4, (E5));
        music1.changeMelody(0.1, (None));
        music1.changeMelody(0.9, (G5));
        music1.changeMelody(0.1, (None));
        music1.changeMelody(0.4, (E5));
        music1.changeMelody(0.1, (None));
        music1.changeMelody(0.4, (C5));
        music1.changeMelody(0.9, (None));
        music1.mergeData();

        ofstream_jin<music_jin> fff_in("ReLetItGo.wav", "binary", "music");
        fff_in.write(music1);

    } catch (std::exception &ex){
        ex.what();
    }


    return 1;
}


