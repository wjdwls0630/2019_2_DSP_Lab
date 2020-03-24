//
// Created by ParkJungJin on 2019-09-30.
//

#ifndef __MATRIX_JIN_HPP
#define __MATRIX_JIN_HPP

#include <iostream>
#include <cmath>
#include "matnode.hpp"
#include "Error/matrix_make_error.hpp"
#include "Error/matrix_shape_error.hpp"
#include "Error/matrix_calculate_error.hpp"
#include "Error/matrix_out_of_range.hpp"
#include "Error/matrix_empty.hpp"
#include "Error/matrix_append_error.hpp"
#include "Error/matrix_height_error.hpp"

template <typename T>
class matrix_jin {

private:
    int m_row, m_col, m_height; // matrix property
    int m_length; // number of elements in 2d-dimension
    int m_total_length; // total number of elements in matrix
    matnode<T> *m_matrix; // container to store element
    std::string m_name; // matrix name

public:
    /**
    *	default constructor.
    */

    matrix_jin(int t_row = 0, int t_col = 0, int t_height = 0, const std::string &t_name = "untitled", T *t_matrix = nullptr, int t_mat_length = 0)
    : m_row(t_row), m_col(t_col), m_height(t_height), m_length(t_row*t_col), m_total_length(t_row*t_col*t_height), m_name(t_name), m_matrix(nullptr) {
        //check length first
        if (this->m_total_length!=t_mat_length){
            throw MatrixMakeError(this->m_total_length, t_mat_length);
        }

        //next, choose row and col
        if (this->m_length != 0 ) {
            this->m_matrix = new matnode<T> [this->m_length];

            //initiallize matnode
            T* temp;
            for (int i = 0; i < this->m_length; i++) {
                temp = new T[this->m_height];
                this->m_matrix[i].setData(temp);
                this->m_matrix[i].setLength(this->m_height);
            }

        }

        //finally, if initiallize together, check length first
        if (t_matrix != nullptr) {
            for (int i = 0; i < this->m_length; i++) {
                for (int j = 0; j < this->m_height; j++) {
                    this->m_matrix[i][j] = t_matrix[i*this->m_height+j];
                }
            }
        }


    }

    /**
    *	copy constructor.(by deep copy)
    */
    matrix_jin(const matrix_jin<T>& mt) : m_row(mt.m_row), m_col(mt.m_col), m_length(mt.m_length), m_name(mt.m_name){
        if (!mt.isEmpty()){
            this->m_matrix = new matnode<T> [mt.m_row * mt.m_col];
            for (int i = 0; i < mt.m_length ; i++) {
                for (int j = 0; j < mt.m_height; j++) {
                    this->m_matrix[i][j] = mt.m_length[i][j]; //deep copy
                }
            }
        }
    }

    /**
    *	destructor
    */
    virtual ~matrix_jin() {
        if (!this->isEmpty()) {
            this->makeEmpty();
        }
    }

    //get and set

    int getRow() const { return this->m_row; }

    void setRow(int t_row) { this->m_row = t_row; }

    int getCol() const { return this->m_col; }

    void setCol(int t_col) { this->m_col = t_col; }

    int getLength() const { return this->m_length; }

    void setLength(int t_Length) {
        if (this->m_length == 0) {
            this->m_matrix = new matnode<T>[t_Length];
        }
        this->m_length = t_Length;
    }

    const std::string &getName() const { return this->m_name; }

    void setName(const std::string &t_name) { this->m_name = t_name; }

    T *getMatrix() const { return this->m_matrix; }



    //function

    /**
    *	@brief	Check matrix is empty.
    *	@pre	none.
    *	@post	none.
    *	@return	return matrix if tree is empty, otherwise return false.
    */
    bool isEmpty() const { return this->m_total_length == 0;}

    /**
     *	@brief	Check tree is full.
     *	@details return true when rise bad_memory allocation , it means there is no memory to allocate node
     *	@pre	none.
     *	@post	none.
     *	@return	return true if tree is full, otherwise return false.
     */
    bool isFull() const {}

    /**
    *	@brief	Initialize matrix to empty state.
    *	@pre	None
    *	@post	matrix is empty.
    */
    void makeEmpty(){
        if(this->m_total_length!=0){
            for (int i = 0; i < this->m_length; i++) {
                delete this->m_matrix[i];
            }
            delete [] this->m_matrix;
            this->m_matrix = nullptr; //init matrix
        }
        this->m_total_length=0;
        this->m_length=0;
        this->m_row=0;
        this->m_col=0;
        this->m_height=0;
    }
    matnode<T>* copy_matrix();

    int appendRow(T* t_list, const int t_length, const int t_row = 1, const int t_height=1);

    int appendCol(T *t_list, const int t_length, const int t_col = 1, const int t_height=1);

    int reshape(const int t_row, const int t_col, const int t_height=1);

    int swapRow(const int &t_row_1, const int &t_row_2, const int t_height=1);

    int swapCol(const int &t_col_1, const int &t_col_2, const int t_height=1);

    void showMatrix(const int t_height=1);

    int transpose(const int t_height=1);

    //how can it calculate if type is integer? (need to modify
    int normalize(const int t_height=1);

    //operator overloading

    T& operator [](const int &index);

    matrix_jin<T>& operator =(const matrix_jin<T> &mt);

    friend std::ostream & operator<<(std::ostream & os, const matrix_jin<T> & mt){
        for (int i = 0; i < mt.m_row; i++) {
            for (int j = 0; j < mt.m_col; j++) {
                os << mt.m_matrix[i*mt.m_col + j] << "\t";
            }
            os << "\n";
        }
        return os;
    }

    matrix_jin<T>& operator+=(const matrix_jin<T> & mt), const int t_height=1;

    matrix_jin<T>& operator-=(const matrix_jin<T> & mt, const int t_height=1);

    matrix_jin<T>& operator*=(const matrix_jin<T> & mt, const int t_height=1);

    matrix_jin<T>& operator*=(const T & scalar, const int t_height=1);

    const matrix_jin<T> operator+(const matrix_jin<T> & mt, const int t_height=1) const;

    const matrix_jin<T> operator-(const matrix_jin<T> & mt, const int t_height=1) const;

    const matrix_jin<T> operator*(const matrix_jin<T> & mt, const int t_height=1) const;

    const matrix_jin<T> operator*(const T & scalar, const int t_height=1) const;

    bool operator == (const matrix_jin<T> & mt) const;

    bool operator!=(const matrix_jin<T> & mt) const;
};

template<typename T>
matnode<T>* matrix_jin<T>::copy_matrix() {
    matnode<T>* copy_list = new matnode<T> [this->m_length];
    for (int i = 0; i < this->m_length; ++i) {
        copy_list[i] = this->m_matrix[i];
    }
    return copy_list;
}



template<typename T>
int matrix_jin<T>::appendRow(T *t_list, const int t_length, const int t_row, const int t_height) {
    if (this->isEmpty()) {
        //set property
        this->m_row = t_row ;
        this->m_col = t_length/t_row;
        this->m_height=1;
        this->m_length = t_length;
        this->m_total_length = this->m_row*this->m_col*this->m_height;


        this->m_matrix = new matnode<T> [this->m_row * this->m_col];
        //initiallize matnode
        T* temp;
        for (int i = 0; i < this->m_length; i++) {
            temp = new T[this->m_height];
            this->m_matrix[i].setData(temp);
            this->m_matrix[i].setLength(this->m_height);
        }

        for (int i = 0; i < this->m_length; i++) {
            for (int j = 0; j < this->m_height; j++) {
                //m_height is 1, it dont need to use loop, but for coding consistent
                this->m_matrix[i][j] = t_list[i*this->m_height+j];
            }

        }

        return 1;

    } else if((t_length/t_row)!=this->m_col){
        throw MatrixAppendError(0, t_length, t_row, this->m_col);
    }

    //check height to do function
    if(this->m_height< t_height){
        throw MatrixHeightError(t_height);
    }


    // copy original
    matnode<T>* temp = this->copy_matrix();

    //deallocate
    this->makeEmpty();
    //re-make matrix
    this->m_matrix = new T [(this->m_row+t_row)*this->m_col];

    //set original
    for (int i = 0; i < this->m_length; i++) {
        this->m_matrix[i] = temp[i];
    }

    //new row
    for (int j = 0; j < t_length; ++j) {
        this->m_matrix[this->m_length+j] = t_list[j];
    }

    delete [] temp;

    //set new property
    this->m_row += t_row;
    this->m_length = this->m_row*this->m_col;

    return 1;
}

template<typename T>
int matrix_jin<T>::appendCol(T *t_list, const int t_length, const int t_col) {
    if (this->isEmpty()) {

        //set property
        this->m_row = t_length/t_col ;
        this->m_col = t_col;
        this->m_length = t_length;

        this->m_matrix = new T [this->m_row * this->m_col];

        for (int i = 0; i < this->m_length; ++i) {
            this->m_matrix[i] = t_list[i];
        }

        return 1;

    } else if((t_length/t_col)!=this->m_row){
        throw MatrixAppendError(1, t_length, this->m_row, t_col);
    }

    // copy original
    T* temp = this->copy_matrix();

    //deallocate
    this->makeEmpty();

    //re-make matrix
    this->m_matrix = new matnode<T> [this->m_row*(this->m_col+t_col)];

    //set original
    for (int i = 0; i < this->m_row; ++i) {
        for (int j = 0; j < this->m_col; ++j) {
            this->m_matrix[i*(this->m_row+1)+j] = temp[i*this->m_row+j];
        }
    }

    //new col
    for (int k = 0; k < t_length; ++k) {
        this->m_matrix[k*(this->m_row+1)+this->m_col] = t_list[k];
    }

    delete [] temp;

    //set new property
    this->m_col += t_col;
    this->m_length = this->m_row*this->m_col;

    return 1;
}


template <typename T>
int matrix_jin<T>::reshape(int t_row, int t_col){
    if (this->m_length != t_row*t_col){
        throw MatrixShapeError(this->m_length, t_row, t_col);
    }
    this->m_row = t_row;
    this->m_col = t_col;
    return 1;
}

template<typename T>
int matrix_jin<T>::swapRow(const int &t_row_1, const int &t_row_2) {
    if (t_row_1 < 0 && t_row_2 < 0 && t_row_1 >= this->m_length && t_row_2 >= this->m_length ){
        throw MatrixOutOfRange(this->m_length);
    }

    T * temp;
    temp = new T[this->m_col];

    for (int i = 0; i < this->m_col; i++){
        temp[i] = this->m_matrix[t_row_1 * this->m_col + i];
    }

    for (int i = 0; i < this->m_col; i++){
        this->m_matrix[t_row_1 * this->m_col + i]= this->m_matrix[t_row_2 * this->m_col + i];
    }
    for (int i = 0; i < this->m_col; i++){
        this->m_matrix[t_row_2 * this->m_col + i] = temp[i];
    }

    delete [] temp;

    return 1;
}

template<typename T>
int matrix_jin<T>::swapCol(const int &t_col_1, const int &t_col_2) {
    T * temp;
    temp = new T[this->m_row];

    for (int i = 0; i < this->m_row; ++i) {
        temp[i] = this->m_matrix[i * this->m_row + t_col_1];
    }

    for (int i = 0; i < this->m_row; ++i) {
        this->m_matrix[i * this->m_row + t_col_1] = this->m_matrix[i * this->m_row + t_col_2];
    }

    for (int i = 0; i < this->m_row; ++i) {
        this->m_matrix[i * this->m_row + t_col_2] = temp[i];
    }

    delete [] temp;

    return 1;
}


template <typename T>
void matrix_jin<T>::showMatrix(){
    std::cout<<this->m_name<<'\n';
    std::cout<<*this<<'\n';
}

template<typename T>
int matrix_jin<T>::transpose() {
    if (!this->isEmpty()) {
        T* temp = new T[this->m_length];

        for (int i = 0; i < this->m_col; ++i) {
            for (int j = 0; j < this->m_row; ++j) {
                temp[i*this->m_row+j] = this->m_matrix[j*this->m_col+i];
            }
        }

        // delete old data
        delete [] this->m_matrix;

        //and reshape, make new matrix
        this->reshape(this->m_col, this->m_row);
        this->m_matrix = new T [this->m_length];
        for (int i = 0; i < this->m_length ; ++i) {
            this->m_matrix[i] = temp[i];
        }

        //delete dynamic array temp
        delete [] temp;


    }
    return 1;
}

template<typename T>
int matrix_jin<T>::normalize() {
    if (!this->isEmpty()) {
        T sum;
        for (int i = 0; i < this->m_row; ++i) {
            //calculate sum of square cols;
            sum = 0;
            for (int j = 0; j < this->m_col; ++j) {
                sum+=pow(this->m_matrix[i*this->m_col+j], 2);
            }

            //square root sum
            sum = sqrt(sum);

            //apply in matrix
            for (int k = 0; k < this->m_col; ++k) {
                this->m_matrix[i*this->m_col+k] *= (1/sum);
            }
        }

        return 1;
    }

    throw MatrixEmpty();
}

template <typename T>
T& matrix_jin<T>::operator [](const int &index){
    if (index >= this->m_length ) {
        throw MatrixOutOfRange(this->m_length);
    }
    return *(this->m_matrix+index);
}

template <typename T>
matrix_jin<T>& matrix_jin<T>::operator =(const matrix_jin<T> &mt) {
    if (this!=&mt) {
        if (!mt.isEmpty()){
            if (!this->isEmpty()) {
                delete [] this->m_matrix;

            }
            this->m_matrix = new T [mt.m_row * mt.m_col];
            //copy matrix
            for (int i = 0; i < mt.m_length ; i++) {
                this->m_matrix[i] = mt.m_matrix[i]; //deep copy
            }
        }
        this->m_row = mt.m_row;
        this->m_col = mt.m_col;
        this->m_length = mt.m_length;
        this->m_name = mt.m_name;
    }
    return *this;
}

template <typename T>
matrix_jin<T>& matrix_jin<T>::operator+=(const matrix_jin<T> & mt) {
    for(int i=0;i<this->m_length; i++){
        this->m_matrix[i] = this->m_matrix[i]+mt.m_matrix[i];
    }
    return *this;
}

template <typename T>
matrix_jin<T>& matrix_jin<T>::operator-=(const matrix_jin<T> & mt) {
    for(int i=0;i<this->m_length; i++){
        this->m_matrix[i] = this->m_matrix[i]-mt[i];
    }
    return *this;
}

template <typename T>
matrix_jin<T>& matrix_jin<T>::operator*=(const matrix_jin<T> & mt) {
    if (this->m_col != mt.m_row){
        throw MatrixCalculateError(this->m_row, this->m_col, mt.m_row, mt.m_col);
    }

    matrix_jin<T> temp(this->m_row, mt.m_col);
    temp.setName(this->m_name);

    for (int n = 0; n < this->m_row; n++)
        for (int m = 0; m < mt.m_col; m++) {
            T sum = 0;
            for (int k = 0; k < this->m_col; k++) {
                sum += this->m_matrix[n*this->m_col + k] * mt.m_matrix[k*mt.m_col + m];
            }
            temp[n*mt.m_col + m] = sum;
        }

    //reset matrix
    this->makeEmpty();

    //copy
    *this = temp;
    return *this;

}

template<typename T>
matrix_jin<T> &matrix_jin<T>::operator*=(const T &scalar) {
    for(int i=0;i<this->m_length; i++){
        this->m_matrix[i] = this->m_matrix[i]*scalar;
    }
    return *this;
}

template <typename T>
const matrix_jin<T> matrix_jin<T>::operator+(const matrix_jin<T> & mt) const {
    return matrix_jin<T>(*this)+=mt;
}

template <typename T>
const matrix_jin<T> matrix_jin<T>::operator-(const matrix_jin<T> & mt) const {
    return matrix_jin<T>(*this)-=mt;
}

template <typename T>
const matrix_jin<T> matrix_jin<T>::operator*(const matrix_jin<T> & mt) const {
    return matrix_jin<T>(*this)*=mt;
}

template<typename T>
const matrix_jin<T> matrix_jin<T>::operator*(const T &scalar) const {
    return matrix_jin<T>(*this)*=scalar;
}



template <typename T>
bool matrix_jin<T>::operator == (const matrix_jin<T> & mt) const {
    //check all private member first
    if ((this->m_length != mt.m_length)||(this->m_name != mt.m_name)||(this->m_row != mt.m_row)||(this->m_col != mt.m_col)) {
        return false;
    }

    //and next check all elements in list
    for (int i = 0; i < this->m_length ; ++i) {
        if (this->m_matrix[i] != mt.m_matrix[i]) {
            return false;
        }
    }

    //all finish
    return true;
}

template <typename T>
bool matrix_jin<T>::operator!=(const matrix_jin<T> & mt) const {
    return !(*this==mt);
}



#endif //__MATRIX_JIN_HPP
