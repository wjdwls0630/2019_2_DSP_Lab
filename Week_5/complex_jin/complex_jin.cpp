//
// Created by ParkJungJin on 2019-10-27.
//

#include "complex_jin.hpp"

complex_jin::complex_jin() : m_re(0), m_im(0) {}

complex_jin::complex_jin(double mRe, double mIm) : m_re(mRe), m_im(mIm) {}

complex_jin::complex_jin(double theta) : m_re(cos(theta)), m_im(sin(theta)) {}

complex_jin::~complex_jin() {}

double complex_jin::getRe() const { return this->m_re; }

void complex_jin::setRe(double mRe) { this->m_re = mRe; }

double complex_jin::getIm() const { return this->m_im; }

void complex_jin::setIm(double mIm) { this->m_im = mIm; }

double complex_jin::getMag() const { return sqrt(pow(this->m_re, 2)+pow(this->m_im, 2)); }

void complex_jin::setMag(double mMag) {
    this->makeUnit();
    *this *= mMag;
}

double complex_jin::getPhase() const {
    if (this->m_re==0){ //can calculate tangent
        if(this->m_im>=0.0){
            return M_PI/2;
        } else{
            return -(M_PI/2);
        }
    }
    return atan2(this->m_im, this->m_re);
}

void complex_jin::setPhase(double mPhase) {
    double temp_mag = this->getMag();
    this->m_re = temp_mag*cos(mPhase);
    this->m_im = temp_mag*sin(mPhase);
}

int complex_jin::makeUnit() {
    double temp_phase = this->getPhase();
    this->m_re = cos(temp_phase);
    this->m_im = sin(temp_phase);
    return 1;
}

void complex_jin::showInfo() {
    std::cout<<"Re : "<<this->m_re<<'\t'<<"Im : "<<this->m_im<<'\n';
    std::cout<<"Mag : "<<this->getMag()<<'\t'<<"Phase : "<<this->getPhase()<<'\n';
}

int complex_jin::conjugate() {
    this->m_im *= -1;
    return 1;
}


bool complex_jin::operator==(const complex_jin &comp) const {
    return (m_re == comp.m_re && m_im == comp.m_im);
}

bool complex_jin::operator!=(const complex_jin &comp) const {
    return !(comp == *this);
}

complex_jin &complex_jin::operator+=(const complex_jin &comp) {
    this->m_re += comp.m_re;
    this->m_im += comp.m_im;
    return *this;
}

complex_jin &complex_jin::operator-=(const complex_jin &comp) {
    this->m_re -= comp.m_re;
    this->m_im -= comp.m_im;
    return *this;
}

complex_jin &complex_jin::operator*=(const complex_jin &comp) {
    double temp_mag = this->getMag()*comp.getMag();
    double temp_phase = this->getPhase()+comp.getPhase();

    this->setMag(temp_mag);
    this->setPhase(temp_phase);
    return *this;
}

complex_jin &complex_jin::operator*=(const double &scalar) {
    this->m_re *= scalar;
    this->m_im *= scalar;
    return *this;
}

complex_jin &complex_jin::operator/=(const complex_jin &comp) {
    double temp_mag = this->getMag()/comp.getMag();
    double temp_phase = this->getPhase()-comp.getPhase();

    this->setMag(temp_mag);
    this->setPhase(temp_phase);
    return *this;
}

complex_jin &complex_jin::operator/=(const double &scalar) {
    this->m_re /= scalar;
    this->m_im /= scalar;
    return *this;
}

const complex_jin complex_jin::operator+(const complex_jin &comp) const {
    return complex_jin(*this)+=comp;
}

const complex_jin complex_jin::operator-(const complex_jin &comp) const {
    return complex_jin(*this)-=comp;
}

const complex_jin complex_jin::operator*(const complex_jin &comp) const {
    return complex_jin(*this)*=comp;
}

const complex_jin complex_jin::operator*(const double &scalar) const {
    return complex_jin(*this)*=scalar;
}

const complex_jin complex_jin::operator/(const complex_jin &comp) const {
    return complex_jin(*this)/=comp;
}

const complex_jin complex_jin::operator/(const double &scalar) const {
    return complex_jin(*this)/=scalar;
}




