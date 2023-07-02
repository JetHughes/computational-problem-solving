
// Most compilers understand the once pragma, but just in case...
#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

namespace cosc326
{

	class Integer
	{

	public:
		Integer();                     // Integer i;	
		Integer(const Integer& i);     // Integer j(i);		
		Integer(const std::string& s); // Integer k("123");		
		Integer(const std::vector<int> value, int sign);

		~Integer();	

		// Assignment operator
		Integer& operator=(const Integer& i); // j = i;		

		// Unary operators
		Integer operator-() const; // -j;	
		Integer operator+() const; // +j;	

		// Arithmetic assignment operators
		Integer& operator+=(const Integer& i); // j += i;	
		Integer& operator-=(const Integer& i); // j -= i;	
		Integer& operator*=(const Integer& i); // j *= i;	
		Integer& operator/=(const Integer& i); // j /= i;	
		Integer& operator%=(const Integer& i); // j %= i;	

		// lhs < rhs -- a 'friend' means operator isn't a member, but can access the private parts of the class.
		// You may need to make some other functions friends, but do so sparingly.
		friend bool operator<(const Integer& lhs, const Integer& rhs);	// 
		friend bool operator==(const Integer& lhs, const Integer& rhs); // lhs == rhs	
		friend std::ostream& operator<<(std::ostream& os, const Integer& i);//	
		friend std::istream& operator>>(std::istream& is, Integer& i);       // std::cin >> i;
	private:
		// Can add internal storage or methods here

		// vector of ints that make up the number.
		std::vector<int> number;
		int sign;
		std::vector<int> removeLeadingZeroes(std::vector<int> value);
		std::vector<int> doLongAddition(std::vector<int> top, std::vector<int> bottom);
		std::vector<int> doLongSubtraction(std::vector<int> top, std::vector<int> bottom);
		std::vector<int> doLongMultiplication(std::vector<int> top, std::vector<int> bottom);
		std::vector<int> doLongDivision(std::vector<int> divisor, std::vector<int> dividend);
	};

	// Binary operators
	Integer operator+(const Integer& lhs, const Integer& rhs); // lhs + rhs;	
	Integer operator-(const Integer& lhs, const Integer& rhs); // lhs - rhs;	
	Integer operator*(const Integer& lhs, const Integer& rhs); // lhs * rhs;	
	Integer operator/(const Integer& lhs, const Integer& rhs); // lhs / rhs;	
	Integer operator%(const Integer& lhs, const Integer& rhs); // lhs % rhs;	

	bool operator>(const Integer& lhs, const Integer& rhs);  // lhs > rhs	 
	bool operator<=(const Integer& lhs, const Integer& rhs); // lhs <= rhs	
	bool operator>=(const Integer& lhs, const Integer& rhs); // lhs >= rhs	
	bool operator!=(const Integer& lhs, const Integer& rhs); // lhs != rhs	

	Integer gcd(const Integer& a, const Integer& b); // i = gcd(a, b);	
}

#endif
