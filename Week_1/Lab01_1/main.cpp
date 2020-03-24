//
// Created by ParkJungJin on 2019-09-21.
//

#include <iostream>
#include <fstream>
#include <cmath>

int main(){
    std::ofstream outFile;
    outFile.open("data.txt", std::ios::out);
    float t, dt, f0;
    t = 0 ;
    dt = 1./44000.; // fs = 44000Hz sampling freq.
    f0 = 440 ; //440Hz signal

    for (int i = 0; i < 400; i++, t+=dt) {
        outFile<< t <<" "<<sin(2*M_PI*f0*t)<<'\n';
    }

    outFile.close();
    return 0;
}