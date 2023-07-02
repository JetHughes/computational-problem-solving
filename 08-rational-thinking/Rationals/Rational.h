#pragma once

// Most compilers understand the once pragma, but just in case...
#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED

#include <iostream>
#include <string>
#include "Integer.h"

namespace cosc326 {

	class Rational {
    
	public:

		Rational();
        Rational(const std::string& str);
        Rational(const Rational& r);
        Rational(const Integer& a); // a
        Rational(const Integer& a, const Integer& b); // a/b
        Rational(const Integer& a, const Integer& b, const Integer& c); // a + b/c
        
		~Rational();

        Rational& operator=( const Rational& r); // q = r;
        
		// Unary operators
		Rational operator-() const; // -r;
		Rational operator+() const; // +r;
	   
        // Arithmetic assignment operators
		Rational& operator+=(const Rational& r); // q += r;
		Rational& operator-=(const Rational& r); // q -= r;
		Rational& operator*=(const Rational& r); // q *= r;
		Rational& operator/=(const Rational& r); // q /= r;
												 
		// lhs < rhs -- a 'friend' means < isn't a member, but can access the private parts of the class.
		// You may need to make some other functions friends, but do so sparingly.
		friend bool operator<(const Rational& lhs, const Rational& rhs);
		friend bool operator==(const Rational& lhs, const Rational& rhs); // lhs == rhs
		friend std::ostream& operator<<(std::ostream& os, const Rational& i);  // std::cout << i << std::endl;
		friend std::istream& operator>>(std::istream& is, Rational& i);        // std::cin >> i;

	private:
		Integer numerator;
		Integer denominator;
		void simplfyFraction();
	};

	// Binary operators
	Rational operator+(const Rational& lhs, const Rational& rhs); // lhs + rhs;
	Rational operator-(const Rational& lhs, const Rational& rhs); // lhs - rhs;
	Rational operator*(const Rational& lhs, const Rational& rhs); // lhs * rhs;
	Rational operator/(const Rational& lhs, const Rational& rhs); // lhs / rhs;
	
	bool operator> (const Rational& lhs, const Rational& rhs); // lhs > rhs
	bool operator<=(const Rational& lhs, const Rational& rhs); // lhs <= rhs
	bool operator>=(const Rational& lhs, const Rational& rhs); // lhs >= rhs
	bool operator!=(const Rational& lhs, const Rational& rhs); // lhs != rhs

}

#endif
