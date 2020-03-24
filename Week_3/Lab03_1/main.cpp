//
// Created by ParkJungJin on 2019-10-02.
//

#include <iostream>
#include <cmath>
#include "../matrix_jin/matrix_jin.hpp"
#include "../matrix_jin/matrix_jin_3d.hpp"
#include "../matfstream_jin/matofstream_jin.hpp"
#include "../matrix_jin/Error/matrix_out_of_range.hpp"

#define W 400 //col
#define L 300 //row

int main(){
    matrix_jin<unsigned char> R(L, W, "R"), G(L, W, "G"), B(L, W, "B");
    matrix_jin_3d<unsigned char>RGB(L, W, 3);

    //all yellow
    for (int i = 0; i < W*L; ++i) {
        R[i] = 255;
        G[i] = 255;
        B[i] = 0;
    }


    //red square
    int individual_idx = 0;
    for (int i = 80; i < 100 ; ++i) {
        //row 80~99
        for (int j = 0; j < 40; ++j) {
            //col 100 ~ 139
            individual_idx = 400 * i + j + 100;
            R[individual_idx] = 255;
            G[individual_idx] = B[individual_idx] = 0;
        }
    }

    int idx, compositive_idx;
    for (idx = compositive_idx = 0; idx < W*L; idx++, compositive_idx+=3) {
        RGB[compositive_idx] = R[idx];
        RGB[compositive_idx+1] = G[idx];
        RGB[compositive_idx+2] = B[idx];
    }


    MatOfstream_Jin<unsigned char>out("frame.rgb", "binary");
    out.write(RGB);
    std::cout<< sizeof(unsigned char)<<'\n';


    return 1;
}

