//
// Created by ParkJungJin on 2019-10-02.
//

#include <iostream>
#include <cmath>
#include "../matrix_jin/matrix_jin.hpp"
#include "../matrix_jin/Error/matrix_out_of_range.hpp"


float elementA(int t_row, int t_col);
float elementB(int, int);

#define ROW 8
#define COL 8

int main(){
    Matrix_Jin<double> A(ROW, COL), B(ROW, COL);
    A.setName("A");
    B.setName("B");

    for (int i = 0; i < A.getRow(); ++i) {
        for (int j = 0; j < A.getCol(); ++j) {
            A[i*A.getCol()+j] = elementA(i, j);
        }
    }

    for (int i = 0; i < B.getRow(); ++i) {
        for (int j = 0; j < B.getCol(); ++j) {
            B[i*B.getCol()+j] = elementB(i, j);
        }
    }

    double* RowNew;
    RowNew = new double[COL];
    for (int i = 0; i < COL; i++){
        RowNew[i] = A[A.getCol() * 2 + i];
    }

    A.appendRow(RowNew, COL, 1);



    double* ColNew;
    ColNew = new double[ROW];
    for (int i = 0; i < ROW; i++){
        ColNew[i] = B[B.getRow() * i + 3];
    }

    B.appendCol(ColNew, ROW, 1);

    Matrix_Jin<double> C = A*B;
    C.setName("C");

    A.showMatrix();
    B.showMatrix();
    C.showMatrix();

    A.showMatrix();
    A.swapCol(3, 4);
    A.showMatrix();
    A.swapRow(2, 5);
    A.showMatrix();

    return 1;
}

float elementA(int t_row, int t_col){
    if (t_row == 0){
        return cos(M_PI*(2*t_col+1)*t_row/16)/(2.*sqrt(2));
    } else if(t_row >= 1 && t_row <= ROW-1){
        return cos(M_PI*(2*t_col+1)*t_row/16)/2.;
    }

    throw MatrixOutOfRange(t_row*t_col);
}

float elementB(int t_row, int t_col){
    if (t_col == 0){
        return cos(M_PI*(2*t_row+1)*t_col/16)/(2.*sqrt(2));
    } else if(t_col >= 1 && t_col <= ROW-1){
        return cos(M_PI*(2*t_row+1)*t_col/16)/2.;
    }

    throw MatrixOutOfRange(t_row*t_col);
}
