#include "Vector.h"
#include <iostream>

double Vector::Magnitude() const {
	return std::sqrt(this->X*this->X+this->Y*this->Y+this->Z*this->Z);
}

Vector::Vector(const Vector& other){ 
			this->X = other.X;
            this->Y = other.Y;
            this->Z = other.Z;	
};
        
Vector Vector::UnitVector() const {
	Vector a;
	double mag = Magnitude();
	a.X = this->X/mag;
	a.Y = this->Y/mag;
	a.Z = this->Z/mag;
	return a;
}

Vector::Vector(): X(0), Y(0), Z(0) {}

Vector::~Vector() {}
