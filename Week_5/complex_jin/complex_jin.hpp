//
// Created by ParkJungJin on 2019-10-27.
//

#ifndef _COMPLEX_JIN_HPP
#define _COMPLEX_JIN_HPP

#include <iostream>
#include <cmath>

//phase is radian scale

class complex_jin {
private:
    double m_re, m_im;
public:
    //constructor - default
    complex_jin();

    complex_jin(double mRe, double mIm);

    //constructor - polar
    complex_jin(double theta);

    //destructor
    virtual ~complex_jin();

    //function

    //getter and setter

    double getRe() const;

    void setRe(double mRe);

    double getIm() const;

    void setIm(double mIm);

    double getMag() const;

    void setMag(double mMag);

    double getPhase() const;

    void setPhase(double mPhase);

    //to make unit
    int makeUnit();

    void showInfo();

    int conjugate();

    //operator overloading

    bool operator==(const complex_jin &comp) const;

    bool operator!=(const complex_jin &comp) const;

    complex_jin& operator+=(const complex_jin & comp);

    complex_jin& operator-=(const complex_jin & comp);

    complex_jin& operator*=(const complex_jin & comp);

    complex_jin& operator*=(const double & scalar);

    complex_jin& operator/=(const complex_jin &comp);

    complex_jin& operator/=(const double &scalar);

    const complex_jin operator+(const complex_jin & comp) const;

    const complex_jin operator-(const complex_jin & comp) const;

    const complex_jin operator*(const complex_jin & comp) const;

    const complex_jin operator*(const double & scalar) const;

    const complex_jin operator/(const complex_jin & comp) const;

    const complex_jin operator/(const double & scalar) const;


    friend std::ostream & operator<<(std::ostream & os, const complex_jin &comp){
        if(comp.m_im>=0){
            os<<comp.m_re<<"+"<<comp.m_im<<"j";
        } else{
            os<<comp.m_re<<comp.m_im<<"j";
        }
        return os;
    }




};


#endif //_COMPLEX_JIN_HPP
