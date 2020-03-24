//
// Created by ParkJungJin on 2019-11-05.
//

#ifndef _MATNODE_HPP
#define _MATNODE_HPP

template <typename T>
class matnode{

private:
    T* m_data; // container
    int m_length; // num of elements
public:

    /**
*	default constructor.
*/
    matnode(int t_length=0, T* t_data = nullptr) : m_length(t_length) {
        if (this->m_length>0){
            this->m_data = new T[this->m_length];
        }

        if(t_data!= nullptr){
            for (int i = 0; i < this->m_length; ++i) {
                this->m_data[i] = t_data[i];
            }
        }
    }

    /**
    *	copy constructor.(by deep copy)
    */
    matnode(const matnode<T>& mt) :  m_length(mt.m_length){
        if (!mt.isEmpty()){
            this->m_data = new T [mt.m_length];
            for (int i = 0; i < mt.m_length ; i++) {
                this->m_data[i] = mt.m_data[i]; //deep copy
            }
        }
    }

    virtual ~matnode() {
        if (!this->isEmpty()) {
            this->makeEmpty();
        }
    }

    T *getData() const {
        return this->m_data;
    }

    void setData(T *t_data) {
        this->m_data = t_data;
    }

    int getLength() const {
        return this->m_length;
    }

    void setLength(int t_length) {
        this->m_length = t_length;
    }

    //function

    /**
    *	@brief	Check matrix is empty.
    *	@pre	none.
    *	@post	none.
    *	@return	return matrix if tree is empty, otherwise return false.
    */
    bool isEmpty() const { return this->m_length == 0;}

    /**
    *	@brief	Initialize matrix to empty state.
    *	@pre	None
    *	@post	matrix is empty.
    */
    void makeEmpty(){
        if(this->m_length!=0){
            delete [] this->m_data;
            this->m_data = nullptr; //init data
        }
        this->m_length=0;
    }

    T* copy_data();

    int append(T* t_list, const int t_length);

    void showData();

    //operator overloading

    T& operator [](const int &index);

    matnode<T>& operator =(const matnode<T> &mt);

    friend std::ostream & operator<<(std::ostream & os, const matnode<T> & mt){
        for (int i = 0; i < mt.m_length; i++) {
            os << mt.m_data[i] << "\t";
        }
        return os;
    }

    bool operator == (const matnode<T> & mt) const;

    bool operator!=(const matnode<T> & mt) const;

};

template<typename T>
T* matnode<T>::copy_data() {
    T* copy_list = new T [this->m_length];
    for (int i = 0; i < this->m_length; ++i) {
        copy_list[i] = this->m_data[i];
    }
    return copy_list;
}
template<typename T>
int matnode<T>::append(T *t_list, const int t_length) {
    if (this->isEmpty()) {

        //set property
        this->m_length = t_length;

        this->m_data = new T [t_length];

        for (int i = 0; i < this->m_length; ++i) {
            this->m_data[i] = t_list[i];
        }

        return 1;

    }


    // copy original
    T* temp = this->copy_data();

    //deallocate
    delete [] this->m_data;
    //re-make matrix
    this->m_data = new T [this->m_length+t_length];

    //set original
    for (int i = 0; i < this->m_length; i++) {
        this->m_data[i] = temp[i];
    }

    //new row
    for (int j = 0; j < t_length; ++j) {
        this->m_data[this->m_length+j] = t_list[j];
    }

    delete [] temp;

    //set new property
    this->m_length += t_length;

    return 1;
}

template <typename T>
void matnode<T>::showData(){
    std::cout<<*this<<'\n';
}

template <typename T>
T& matnode<T>::operator [](const int &index){
    if (index >= this->m_length ) {
        throw MatrixOutOfRange(this->m_length);
    }
    return *(this->m_data+index);
}

template <typename T>
matnode<T>& matnode<T>::operator =(const matnode<T> &mt) {
    if (this!=&mt) {
        if (!mt.isEmpty()){
            if (!this->isEmpty()) {
                delete [] this->m_data;
            }
            this->m_data = new T [mt.m_length];
            //copy matrix
            for (int i = 0; i < mt.m_length ; i++) {
                this->m_data[i] = mt.m_data[i]; //deep copy
            }
        }
        this->m_length = mt.m_length;
    }
    return *this;
}

template <typename T>
bool matnode<T>::operator == (const matnode<T> & mt) const {
    //check all private member first
    if (this->m_length != mt.m_length) {
        return false;
    }

    //and next check all elements in list
    for (int i = 0; i < this->m_length ; ++i) {
        if (this->m_data[i] != mt.m_data[i]) {
            return false;
        }
    }

    //all finish
    return true;
}

template <typename T>
bool matnode<T>::operator!=(const matnode<T> & mt) const {
    return !(*this==mt);
}

#endif //_MATNODE_HPP
