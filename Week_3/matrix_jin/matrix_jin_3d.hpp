//
// Created by ParkJungJin on 2019-10-26.
//

#ifndef _MATRIX_JIN_3D_HPP
#define _MATRIX_JIN_3D_HPP

#include "matrix_jin.hpp"

template <typename T>
class matrix_jin_3d {

private:
    int m_row, m_col, m_height; // matrix is composed 2d, row and col
    int m_length; // number of elements in matrix
    T *m_matrix; // container to store element
    std::string m_name; // matrix name

public:
    /**
    *	default constructor.
    */

    matrix_jin_3d(int mRow = 0, int mCol = 0, int mHeight = 0, const std::string &mName = "untitled",
                  T *mMatrix = nullptr)
            : m_row(mRow), m_col(mCol), m_height(mHeight), m_length(mRow * mCol * mHeight), m_name(mName),
              m_matrix(nullptr) {

        //first choose row and col
        if (this->m_length != 0) {
            this->m_matrix = new T[this->m_row * this->m_col * this->m_height];
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
    matrix_jin_3d(const matrix_jin_3d<T> &mt) : m_row(mt.m_row), m_col(mt.m_col), m_height(mt.m_height),
                                                m_length(mt.m_length), m_name(mt.m_name) {
        if (!mt.isEmpty()) {
            this->m_matrix = new T[mt.m_row * mt.m_col * mt.m_height];
            for (int i = 0; i < mt.m_length; i++) {
                this->m_matrix[i] = mt.m_matrix[i]; //deep copy
            }
        }
    }

    /**
    *	destructor
    */
    virtual ~matrix_jin_3d() {
        if (!this->isEmpty()) {
            this->makeEmpty();
        }
    }

    //get and set

    int getRow() const { return this->m_row; }

    void setRow(int mRow) { this->m_row = mRow; }

    int getCol() const { return this->m_col; }

    void setCol(int mCol) { this->m_col = mCol; }

    int getHeight() const { return this->m_height; }

    void setHeight(int mHeight) { this->m_height = mHeight; }

    int getLength() const { return this->m_length; }

    void setLength(int t_Length) {
        if (this->m_length == 0) {
            this->m_matrix = new T[t_Length];
        }
        this->m_length = t_Length;
    }

    const std::string &getName() const { return this->m_name; }

    void setName(const std::string &mName) { this->m_name = mName; }

    T *getMatrix() const { return this->m_matrix; }



    //function

    /**
    *	@brief	Check matrix is empty.
    *	@pre	none.
    *	@post	none.
    *	@return	return matrix if tree is empty, otherwise return false.
    */
    bool isEmpty() const { return this->m_length == 0; }

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
    void makeEmpty() {
        if (this->m_length != 0) {
            delete[] this->m_matrix;
            this->m_matrix = nullptr; //init matrix
        }
        this->m_length = 0;
        this->m_row = 0;
        this->m_col = 0;
        this->m_height = 0;
    }

    T *copy_matrix();

    //operator overloading

    T& operator [](const int &index);

    matrix_jin<T>& operator =(const matrix_jin_3d<T> &mt);

    friend std::ostream & operator<<(std::ostream & os, const matrix_jin_3d<T> & mt){
        for (int i = 0; i < mt.m_row; i++) {
            for (int j = 0; j < mt.m_col; j++) {
                for (int k = 0; k <mt.m_height ; ++k) {
                    os <<"["<<mt.m_matrix[i*mt.m_col + j*mt.m_height + k] << "\t";
                }
            }
            os << "\n";
        }
        return os;
    }
};

template<typename T>
T* matrix_jin_3d<T>::copy_matrix() {
    T* copy_list = new T [this->m_length];
    for (int i = 0; i < this->m_length; ++i) {
        copy_list[i] = this->m_matrix[i];
    }
    return copy_list;
}

template <typename T>
T& matrix_jin_3d<T>::operator [](const int &index){
    if (index >= this->m_length ) {
        throw MatrixOutOfRange(this->m_length);
    }
    return *(this->m_matrix+index);
}

template <typename T>
matrix_jin<T>& matrix_jin_3d<T>::operator =(const matrix_jin_3d<T> &mt) {
    if (this!=&mt) {
        if (!mt.isEmpty()){
            if (!this->isEmpty()) {
                delete [] this->m_matrix;

            }
            this->m_matrix = new T [mt.m_row * mt.m_col * mt.m_height];
            //copy matrix
            for (int i = 0; i < mt.m_length ; i++) {
                this->m_matrix[i] = mt.m_matrix[i]; //deep copy
            }
        }
        this->m_row = mt.m_row;
        this->m_col = mt.m_col;
        this->m_height = mt.m_height;
        this->m_length = mt.m_length;
        this->m_name = mt.m_name;
    }
    return *this;
}
#endif //_MATRIX_JIN_3D_HPP
