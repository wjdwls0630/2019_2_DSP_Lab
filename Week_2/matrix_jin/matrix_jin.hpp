//
// Created by ParkJungJin on 2019-09-30.
//

#ifndef __MATRIX_JIN_HPP
#define __MATRIX_JIN_HPP

#include <iostream>
#include <cmath>
#include "Error/matrix_shape_error.hpp"
#include "Error/matrix_calculate_error.hpp"
#include "Error/matrix_out_of_range.hpp"
#include "Error/matrix_empty.hpp"
#include "Error/matrix_append_error.hpp"

template <typename T>
class Matrix_Jin {
private:
    int m_row, m_col; // matrix is composed 2d, row and col
    int m_length; // number of elements in matrix
    T *m_matrix; // container to store element
    std::string m_name; // matrix name

public:
    /**
    *	default constructor.
    */

    Matrix_Jin(const int &mRow = 0, const int &mCol = 0, const std::string &mName = "untitled", T *mMatrix = nullptr)
    : m_row(mRow), m_col(mCol), m_length(mRow*mCol), m_name(mName) {

        //first choose row and col
        if (this->m_length != 0 ) {
            m_matrix = new T [this->m_row * this->m_col];
        }

        if (mMatrix != nullptr) {
            for (int i = 0; i < this->m_length; ++i) {
                this->m_matrix[i] = mMatrix[i];
            }
        }
    }

    /**
    *	copy constructor.(by deep copy)
    */
    Matrix_Jin(const Matrix_Jin<T>& mt) : m_row(mt.m_row), m_col(mt.m_col), m_length(mt.m_length), m_name(mt.m_name){
        if (!mt.isEmpty()){
            this->m_matrix = new T [mt.m_row * mt.m_col];
            for (int i = 0; i < mt.m_length ; i++) {
                this->m_matrix[i] = mt.m_matrix[i]; //deep copy
            }
        }
    }

    /**
    *	destructor
    */
    virtual ~Matrix_Jin() {
        if (!this->isEmpty()) {
            this->makeEmpty();
        }
    }

    //get and set

    int getRow() const { return this->m_row; }

    void setRow(int mRow) { this->m_row = mRow; }

    int getCol() const { return this->m_col; }

    void setCol(int mCol) { this->m_col = mCol; }

    int getLength() const { return this->m_length; }

    void setLength(int t_Length) {
        if (this->m_length == 0) {
            this->m_matrix = new T[t_Length];
        }
        this->m_length = t_Length;
    }

    T *getMatrix() const { return this->m_matrix; }
/*
    void setMatrix(T *mMatrix) {
        if (!this->isEmpty()) {
            delete [] this->m_matrix;
        }
        for (int i = 0; i < ; ++i) {

        }
        this->m_matrix = mMatrix;
    }
*/
    const std::string &getName() const { return this->m_name; }

    void setName(const std::string &mName) { this->m_name = mName; }

    //function

    /**
    *	@brief	Check matrix is empty.
    *	@pre	none.
    *	@post	none.
    *	@return	return matrix if tree is empty, otherwise return false.
    */
    bool isEmpty() const { return this->m_length == 0;}

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
        if(this->m_length!=0){
            delete [] this->m_matrix;
            this->m_matrix = nullptr; //init matrix
        }
        this->m_length=0;
        this->m_row=0;
        this->m_col=0;
    }
    T* copy_matrix();

    int appendRow(T* t_list, const int t_length, const int t_row = 1 );

    int appendCol(T *t_list, const int t_length, const int t_col = 1);

    int reshape(const int t_row, const int t_col);

    int swapRow(const int &t_row_1, const int &t_row_2);

    int swapCol(const int &t_col_1, const int &t_col_2);

    void showMatrix();

    int transpose();

    //how can it calculate if type is integer? (need to modify
    int normalize();



    //operator overloading

    T& operator [](const int &index);

    Matrix_Jin<T>& operator =(const Matrix_Jin<T> &mt);

    friend std::ostream & operator<<(std::ostream & os, const Matrix_Jin<T> & mt){
        for (int i = 0; i < mt.m_row; i++) {
            for (int j = 0; j < mt.m_col; j++) {
                os << mt.m_matrix[i*mt.m_col + j] << "\t";
            }
            os << "\n";
        }
        return os;
    }

    Matrix_Jin<T>& operator+=(const Matrix_Jin<T> & mt);

    Matrix_Jin<T>& operator-=(const Matrix_Jin<T> & mt);

    Matrix_Jin<T>& operator*=(const Matrix_Jin<T> & mt);

    Matrix_Jin<T>& operator*=(const T & scalar);

    const Matrix_Jin<T> operator+(const Matrix_Jin<T> & mt) const;

    const Matrix_Jin<T> operator-(const Matrix_Jin<T> & mt) const;

    const Matrix_Jin<T> operator*(const Matrix_Jin<T> & mt) const;

    const Matrix_Jin<T> operator*(const T & scalar) const;

    bool operator == (const Matrix_Jin<T> & mt) const;

    bool operator!=(const Matrix_Jin<T> & mt) const;
};

template<typename T>
T* Matrix_Jin<T>::copy_matrix() {
    T* copy_list = new T [this->m_length];
    for (int i = 0; i < this->m_length; ++i) {
        copy_list[i] = this->m_matrix[i];
    }
    return copy_list;
}



template<typename T>
int Matrix_Jin<T>::appendRow(T *t_list, const int t_length, const int t_row) {
    if (this->isEmpty()) {

        //set property
        this->m_row = t_row ;
        this->m_col = t_length/t_row;
        this->m_length = t_length;

        for (int i = 0; i < this->m_length; ++i) {
            this->m_matrix[i] = t_list[i];
        }

        return 1;

    } else if((t_length/t_row)!=this->m_col){
        throw MatrixAppendError(0, t_length, t_row, this->m_col);
    }


    // copy original
    T* temp = this->copy_matrix();

    //deallocate
    delete [] this->m_matrix;
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
int Matrix_Jin<T>::appendCol(T *t_list, const int t_length, const int t_col) {
    if (this->isEmpty()) {

        //set property
        this->m_row = t_length/t_col ;
        this->m_col = t_col;
        this->m_length = t_length;

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
    delete [] this->m_matrix;

    //re-make matrix
    this->m_matrix = new T [this->m_row*(this->m_col+t_col)];

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
int Matrix_Jin<T>::reshape(int t_row, int t_col){
    if (this->m_length != t_row*t_col){
        throw MatrixShapeError(this->m_length, t_row, t_col);
    }
    this->m_row = t_row;
    this->m_col = t_col;
    return 1;
}

template<typename T>
int Matrix_Jin<T>::swapRow(const int &t_row_1, const int &t_row_2) {
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
int Matrix_Jin<T>::swapCol(const int &t_col_1, const int &t_col_2) {
    T * temp;
    temp = new T[this->m_row];

    for (int i = 0; i < this->m_row; ++i) {
        temp[i] = this->m_matrix[i * (this->m_row+1) + t_col_1];
    }

    for (int i = 0; i < this->m_row; ++i) {
        this->m_matrix[i * (this->m_row+1) + t_col_1] = this->m_matrix[i * (this->m_row+1) + t_col_2];
    }

    for (int i = 0; i < this->m_row; ++i) {
        this->m_matrix[i * (this->m_row+1) + t_col_2] = temp[i];
    }

    delete [] temp;

    return 1;
}

template <typename T>
void Matrix_Jin<T>::showMatrix(){
    std::cout<<this->m_name<<'\n';
    std::cout<<*this<<'\n';
}

template<typename T>
int Matrix_Jin<T>::transpose() {
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
int Matrix_Jin<T>::normalize() {
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
T& Matrix_Jin<T>::operator [](const int &index){
    if (index >= this->m_length ) {
        throw MatrixOutOfRange(this->m_length);
    }
    return *(this->m_matrix+index);
}

template <typename T>
Matrix_Jin<T>& Matrix_Jin<T>::operator =(const Matrix_Jin<T> &mt) {
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
Matrix_Jin<T>& Matrix_Jin<T>::operator+=(const Matrix_Jin<T> & mt) {
    for(int i=0;i<this->m_length; i++){
        this->m_matrix[i] = this->m_matrix[i]+mt.m_matrix[i];
    }
    return *this;
}

template <typename T>
Matrix_Jin<T>& Matrix_Jin<T>::operator-=(const Matrix_Jin<T> & mt) {
    for(int i=0;i<this->m_length; i++){
        this->m_matrix[i] = this->m_matrix[i]-mt[i];
    }
    return *this;
}

template <typename T>
Matrix_Jin<T>& Matrix_Jin<T>::operator*=(const Matrix_Jin<T> & mt) {
    if (this->m_col != mt.m_row){
        throw MatrixCalculateError(this->m_row, this->m_col, mt.m_row, mt.m_col);
    }

    Matrix_Jin<T> temp(this->m_row, mt.m_col);
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
Matrix_Jin<T> &Matrix_Jin<T>::operator*=(const T &scalar) {
    for(int i=0;i<this->m_length; i++){
        this->m_matrix[i] = this->m_matrix[i]*scalar;
    }
    return *this;
}

template <typename T>
const Matrix_Jin<T> Matrix_Jin<T>::operator+(const Matrix_Jin<T> & mt) const {
    return Matrix_Jin<T>(*this)+=mt;
}

template <typename T>
const Matrix_Jin<T> Matrix_Jin<T>::operator-(const Matrix_Jin<T> & mt) const {
    return Matrix_Jin<T>(*this)-=mt;
}

template <typename T>
const Matrix_Jin<T> Matrix_Jin<T>::operator*(const Matrix_Jin<T> & mt) const {
    return Matrix_Jin<T>(*this)*=mt;
}

template<typename T>
const Matrix_Jin<T> Matrix_Jin<T>::operator*(const T &scalar) const {
    return Matrix_Jin<T>(*this)*=scalar;
}



template <typename T>
bool Matrix_Jin<T>::operator == (const Matrix_Jin<T> & mt) const {
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
bool Matrix_Jin<T>::operator!=(const Matrix_Jin<T> & mt) const {
    return !(*this==mt);
}




#endif //_MATRIX_JIN_HPP
