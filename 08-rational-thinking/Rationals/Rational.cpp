#include "Rational.h"
#include "Integer.h"

namespace cosc326
{
	/**
	 * @brief Default constructor for the Rational class.
	 * Initializes the Rational object with a numerator of 0 and a denominator of 1.
	 */
	Rational::Rational() : numerator(Integer("0")), denominator(Integer("1")) {}

	/**
	 * @brief Copy constructor for the Rational class.
	 * Initializes the Rational object with the same numerator and denominator as the provided Rational object.
	 *
	 * @param r The Rational object to be copied.
	 */
	Rational::Rational(const Rational& r) : numerator(r.numerator), denominator(r.denominator) {}

	/**
	 * @brief Constructor for the Rational class.
	 * Initializes the Rational object with a numerator provided as an Integer object and a denominator of 1.
	 *
	 * @param a The numerator as an Integer object.
	 */
	Rational::Rational(const Integer& a) : numerator(a), denominator(Integer("1")) {
		simplfyFraction();
	}

	/**
	 * @brief Constructor for the Rational class.
	 * Initializes the Rational object with the provided numerator and denominator.
	 * Simplifies the fraction
	 *
	 * @param a The numerator as an Integer object.
	 * @param b The denominator as an Integer object.
	 */
	Rational::Rational(const Integer& a, const Integer& b) : numerator(a), denominator(b) {
		simplfyFraction();
	}

	/**
	 * @brief Constructs a Rational object from a mixed fraction represented by three Integer objects.
	 * Ignores the sign sign of b and c
	 *
	 * @param a The whole number part of the mixed fraction.
	 * @param b The numerator part of the mixed fraction.
	 * @param c The denominator part of the mixed fraction.
	 */
	Rational::Rational(const Integer& a, const Integer& b, const Integer& c)
	{
		// Convert mixed fractions to improper fractions
		// Ignore the sign of b and c
 		Integer numeratorInteger = (+a * +c) + b;
		Integer sign = a >= Integer("0") ? Integer("1") : Integer("-1");
		*this = Rational(numeratorInteger * sign, +c);
	}

	/**
	 * @brief Constructs a Rational object from a string representation of a rational number.
	 *
	 * @param str The string representing the rational number.
	 */
	Rational::Rational(const std::string& str)
	{
		int dotPos = str.find('.');
		int slashPos = str.find('/');

		// If there is no dot or slash it must be a whole number
		if (dotPos == -1 && slashPos == -1)
		{
			*this = Rational(Integer(str));
			return;
		}

		// If there is no dot we have a fraction
		if (dotPos == -1) 
		{
			std::string b = str.substr(0, slashPos);
			std::string c = str.substr(slashPos + 1);
			*this = Rational(Integer(b), Integer(c));
			return;
		}

		// Otherwise we have a mixed fraction
		std::string a, b, c;
		a = str.substr(0, dotPos);
		b = str.substr(dotPos + 1, slashPos - dotPos - 1);
		c = str.substr(slashPos + 1);
		*this = Rational(Integer(a), Integer(b), Integer(c));
	}

	/**
	 * @brief Rational class destructor.
	 */
	Rational::~Rational() {}

	/**
	 * @brief Simplifies the fraction represented by the Rational object.
	 *
	 * This function simplifies the fraction by dividing both the numerator and denominator
	 * by their greatest common divisor (gcd). It also handles the sign of the fraction.
	 */
	void Rational::simplfyFraction()
	{
		// if one is negative but not both make the sign zero (bool != bool is functionally XOR)
		Integer sign("1");
		if ((this->numerator >= Integer("0")) != (this->denominator >= Integer("0"))) {
			sign = Integer("-1");
		}
		Integer common_divisor = gcd(this->numerator, this->denominator);
		this->numerator = +this->numerator / common_divisor * sign;
		this->denominator = +this->denominator / common_divisor;
	}

	/**
	 * @brief Assignment operator overload. Assigns the value of a Rational object to another.
	 *
	 * @param r The Rational object to assign from.
	 * @return Reference to the assigned Rational object.
	 */
	Rational& Rational::operator=(const Rational& r)
	{
		this->numerator = r.numerator;
		this->denominator = r.denominator;
		return *this;
	}

	/**
	 * @brief Negation operator overload. Returns the negation of a Rational object.
	 *
	 * @return A new Rational object with the negated value.
	 */
	Rational Rational::operator-() const
	{
		if (this->numerator == Integer("0")) {
			return *this;
		}
		Rational neg = Rational(*this);
		neg.numerator *= Integer("-1");
		return neg;
	}

	/**
	 * @brief Unary plus operator overload. Returns the positive value of a Rational object.
	 *
	 * @return A new Rational object with the positive value.
	 */
	Rational Rational::operator+() const
	{
		Rational pos = Rational(*this);
		pos.numerator = +pos.numerator;
		return pos;
	}

	/**
	 * @brief Overload of the compound addition assignment operator (+=) for Rational numbers.
	 *
	 * @param r The Rational number to be added.
	 * @return Reference to the modified Rational object after addition.
	 */	
	Rational& Rational::operator+=(const Rational& r)
	{
		this->numerator = this->numerator * r.denominator + r.numerator * this->denominator;
		this->denominator = this->denominator * r.denominator;
		simplfyFraction();
		return *this;
	}

	/**
	 * @brief Overload of the compound subtraction assignment operator (-=) for Rational numbers.
	 *
	 * @param r The Rational number to be subtracted.
	 * @return Reference to the modified Rational object after subtraction.
	 */	
	Rational& Rational::operator-=(const Rational& r)
	{
		Rational negativeR = -r;
		*this += negativeR;
		return *this;
	}

	/**
	 * @brief Overload of the compound multiplication assignment operator (*=) for Rational numbers.
	 *
	 * @param r The Rational number to be multiplied.
	 * @return Reference to the modified Rational object after multiplication.
	 */
	Rational& Rational::operator*=(const Rational& r)
	{
		// Multiply the numerators and denominators
		this->numerator = this->numerator * r.numerator;
		this->denominator = this->denominator * r.denominator;
		simplfyFraction();
		return *this;
	}

	/**
	 * @brief Overload of the compound division assignment operator (/=) for Rational numbers.
	 *
	 * @param r The Rational number to be divided by.
	 * @return Reference to the modified Rational object after division.
	 */
	Rational& Rational::operator/=(const Rational& r)
	{
		// Create inverted fraction
		Rational rInverse(r.denominator, r.numerator);

		// Perform division by multiplication
		*this *= rInverse; // *= operator always returns simple frations
		return *this;
	}

	/**
	 * @brief Overloaded addition operator for Rational numbers.
	 *
	 * @param lhs The left-hand side Rational operand.
	 * @param rhs The right-hand side Rational operand.
	 * @return The sum of lhs and rhs as a new Rational object.
	 */
	Rational operator+(const Rational& lhs, const Rational& rhs)
	{
		Rational result(lhs);
		result += rhs;
		return result;
	}

	/**
	 * @brief Overloaded subtraction operator for Rational numbers.
	 *
	 * @param lhs The left-hand side Rational operand.
	 * @param rhs The right-hand side Rational operand.
	 * @return The difference between lhs and rhs as a new Rational object.
	 */
	Rational operator-(const Rational& lhs, const Rational& rhs)
	{
		Rational result(lhs);
		result -= rhs;
		return result;
	}

	/**
	 * @brief Overloaded multiplication operator for Rational numbers.
	 *
	 * @param lhs The left-hand side Rational operand.
	 * @param rhs The right-hand side Rational operand.
	 * @return The product of lhs and rhs as a new Rational object.
	 */
	Rational operator*(const Rational& lhs, const Rational& rhs)
	{
		Rational result(lhs);
		result *= rhs;
		return result;
	}

	/**
	 * @brief Overloaded division operator for Rational numbers.
	 *
	 * @param lhs The left-hand side Rational operand (dividend).
	 * @param rhs The right-hand side Rational operand (divisor).
	 * @return The result of dividing lhs by rhs as a new Rational object.
	 */
	Rational operator/(const Rational& lhs, const Rational& rhs)
	{
		Rational result(lhs);
		result /= rhs;
		return result;
	}

	/**
	 * @brief Overloaded stream insertion operator to output a Rational object.
	 *
	 * This function inserts the rational number represented by the Rational object
	 * into the output stream in a human-readable format. If the rational number is
	 * a whole number or an integer fraction, it will be output accordingly. If the
	 * rational number is a mixed fraction, it will be output in the form of a mixed
	 * number.
	 *
	 * @param os The output stream to insert the rational number into.
	 * @param i The Rational object to be inserted into the output stream.
	 * @return A reference to the output stream after inserting the rational number.
	 */	
	std::ostream& operator<<(std::ostream& os, const Rational& i)
	{
		Rational copy(i);
		copy.simplfyFraction();

		if (copy.numerator == Integer("0") || copy.denominator == Integer("1")) {
			os << copy.numerator;
		} else if (+copy.numerator < +copy.denominator) {
			os << copy.numerator << "/" << copy.denominator;
		} else {
			Integer whole = copy.numerator / copy.denominator;
			Integer simpleNumerator = copy.numerator % copy.denominator;
			os << whole << "." << simpleNumerator << "/" << copy.denominator;
		}
		return os;
	}

	/**
	 * @brief Overloaded stream extraction operator to input a Rational object.
	 *
	 * This function extracts a rational number from the input stream and assigns it
	 * to the Rational object. The input stream is expected to contain a valid string
	 * representation of a rational number. The function assumes that the Rational
	 * constructor is capable of parsing the input string and constructing a valid Rational object.
	 *
	 * @param is The input stream to extract the rational number from.
	 * @param i The Rational object to store the extracted rational number.
	 * @return A reference to the input stream after extracting the rational number.
	 */
	std::istream& operator>>(std::istream& is, Rational& i)
	{
		std::string input;
		is >> input;
		i = Rational(input);
		return is;
	}

	/**
	 * @brief Checks if the left-hand side Rational is less than the right-hand side Rational.
	 *
	 * @param lhs The left-hand side Rational.
	 * @param rhs The right-hand side Rational.
	 * @return True if lhs is less than rhs, False otherwise.
	 */
	bool operator<(const Rational& lhs, const Rational& rhs)
	{
		// Equivalent to converting to use the same denominator and comparing numerators
		return lhs.numerator * rhs.denominator < rhs.numerator * lhs.denominator;
	}

	/**
	 * @brief Checks if the left-hand side Rational is equal to the right-hand side Rational.
	 *
	 * @param lhs The left-hand side Rational.
	 * @param rhs The right-hand side Rational.
	 * @return True if lhs is equal to rhs, False otherwise.
	 */
	bool operator==(const Rational& lhs, const Rational& rhs)
	{
		if (lhs.numerator == rhs.numerator &&
			lhs.denominator == rhs.denominator)
		{
			return true;
		}
		return false;
	}

	/**
	 * @brief Checks if the left-hand side Rational is greater than the right-hand side Rational.
	 *
	 * @param lhs The left-hand side Rational.
	 * @param rhs The right-hand side Rational.
	 * @return True if lhs is greater than rhs, False otherwise.
	 */
	bool operator>(const Rational& lhs, const Rational& rhs)
	{
		if (lhs == rhs)
		{
			return false;
		}
		return !(lhs < rhs);
	}

	/**
	 * @brief Checks if the left-hand side Rational is less than or equal to the right-hand side Rational.
	 *
	 * @param lhs The left-hand side Rational.
	 * @param rhs The right-hand side Rational.
	 * @return True if lhs is less than or equal to rhs, False otherwise.
	 */
	bool operator<=(const Rational& lhs, const Rational& rhs)
	{
		if (lhs == rhs)
		{
			return true;
		}
		return lhs < rhs;
	}

	/**
	 * @brief Checks if the left-hand side Rational is greater than or equal to the right-hand side Rational.
	 *
	 * @param lhs The left-hand side Rational.
	 * @param rhs The right-hand side Rational.
	 * @return True if lhs is greater than or equal to rhs, False otherwise.
	 */
	bool operator>=(const Rational& lhs, const Rational& rhs)
	{
		if (lhs == rhs)
		{
			return true;
		}
		return lhs > rhs;
	}

	/**
	 * @brief Checks if the left-hand side Rational is not equal to the right-hand side Rational.
	 *
	 * @param lhs The left-hand side Rational.
	 * @param rhs The right-hand side Rational.
	 * @return True if lhs is not equal to rhs, False otherwise.
	 */
	bool operator!=(const Rational& lhs, const Rational& rhs)
	{
		return !(rhs == lhs);
	}
}
