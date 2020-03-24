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

int main(){
    try{
        ifstream_jin<music_jin> fff_out("LetItGo.wav", "binary", "music");
        music_jin music1("wav", "LetItGo");
        fff_out.read(music1);
        music1.showHeader();

        fff_out.close();


    } catch (std::exception &ex){
        ex.what();
    }


    return 1;
}


