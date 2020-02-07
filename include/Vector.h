#ifndef VECTOR_H
#define VECTOR_H
#include <cmath>
#include <string>
#include <iostream>

//Double Equals for floating point comparisons
static bool double_equals(double a, double b, double epsilon = 0.001)
{
    return std::abs(a - b) < epsilon;
}

class Vector {
	public:
		double X, Y, Z;
	public:
		static double Angle(const Vector &a, const Vector &b) {
			return std::acos(DotProduct(a,b)/(a.Magnitude()*b.Magnitude()));	
		}
		static bool IsParallel(const Vector &a, const Vector &b){
			return a.UnitVector() == b.UnitVector();
		}
		static double Distance(Vector &a, Vector &b) {
			Vector ret = b-a;
			return std::sqrt(ret.X*ret.X+
					ret.Y*ret.Y+
					ret.Z*ret.Z);
		}
		static double DotProduct(const Vector &a, const Vector &b) {
	return (a.X*b.X +
            a.Y*b.Y +
            a.Z*b.Z);
		}

		Vector operator+(const Vector& rhs){
			Vector ret;
			ret.X = this->X + rhs.X;
			ret.Y = this->Y + rhs.Y;
			ret.Z = this->Z + rhs.Z;
			return ret;
		}
		Vector operator-(const Vector& rhs){
			Vector ret;
			ret.X = this->X - rhs.X;
			ret.Y = this->Y - rhs.Y;
			ret.Z = this->Z - rhs.Z;
			return ret;
		}
		bool operator==(const Vector& rhs) const {
		return (double_equals(this->X, rhs.X) && 
		double_equals(this->Y,rhs.Y) && 
		double_equals(this->Z,rhs.Z)); 
		}

		
		const std::string AsString() {
			return std::string("(" + std::to_string(this->X) + ", "+  std::to_string(this->Y) +"," + std::to_string(this->Z) + ")" );
		}
		//AKA Distance From Origin
		double Magnitude() const;
		Vector UnitVector() const;
        Vector(float x, float y,float z): X(x), Y(y), Z(z) {}
		Vector();
		~Vector();
		//Deep copy
		Vector(const Vector& other);
};


struct Coordinate {
    double X;
    double Y;
    double Z;
    
    operator Vector() const {
            Vector v;
            v.X = this->X;
            v.Y = this->Y;
            v.Z = this->Z;
            return v;
    }
    
    Coordinate(double lX, double lY, double lZ):X(lX), Y(lY), Z(lZ) {} 
    Coordinate(){X=0;Y=0;Z=0;}
};

#endif
