#include "Integer.h"

namespace cosc326 {

	/**
	 * @brief Default constructor for the Integer class.
	 *        Initializes an Integer object with a value of 0.
	 */
	Integer::Integer() : sign(1), number({0}) {}

	/**
	 * @brief Copy constructor for the Integer class.
	 * @param i The Integer object to be copied.
	 */
	Integer::Integer(const Integer& i) : sign(i.sign), number(i.number) {}

	/**
	 * @brief Constructor for the Integer class.
	 * @param value A vector of integers representing the Integer value.
	 * @param sign The sign of the Integer value.
	 */
	Integer::Integer(const std::vector<int> value, int sign) : sign(sign), number(value) {}

	/**
	 * @brief String constructor for the Integer class.
	 * @param s The string representation of the Integer value.
	 * @details This constructor parses the input string and initializes an Integer object accordingly.
	 */
	Integer::Integer(const std::string& s) {
		// First check if the number is negative
		this->sign = s[0] == '-' ? -1 : 1;

		// Then read the digits
		for (const auto& digit : s) {
			if (digit != '-' && digit != '+') { // Need to avoid + or i signs
				int val = digit - '0'; // subtract ascii 0 to convert ascii number to integer value
				number.push_back(val);
			}
		}
	}

	/**
	 * @brief Destructor for the Integer class.
	 * @details Since the Integer class uses std::vector, there is no additional cleanup required.
	 */
	Integer::~Integer() {}

	/**
	 * @brief Shallow copy assignment operator for the Integer class.
	 * @param i The Integer object to be assigned.
	 * @return A reference to the assigned Integer object.
	 */
	Integer& Integer::operator=(const Integer& i) {
		number = i.number;
		sign = i.sign;
		return *this;
	}

	/**
	 * @brief Unary minus operator for the Integer class.
	 * @return A new Integer object with the negation of the original value.
	 */
	Integer Integer::operator-() const {
		Integer neg = Integer(*this);
		neg.sign *= -1;
		return neg;
	}

	/**
	 * @brief Unary plus operator for the Integer class.
	 * @return A new Integer object with the positive value.
	 */
	Integer Integer::operator+() const {
		Integer pos = Integer(*this);
		pos.sign = 1;
		return pos;
	}

	/**
	 * Perform long addition on two vectors of integers.
	 *
	 * @param top The top vector representing the larger number.
	 * @param bottom The bottom vector representing the smaller number.
	 * @return The result of the long addition as a vector of integers.
	 */
	std::vector<int> Integer::doLongAddition(std::vector<int> top, std::vector<int> bottom) {
		std::vector<int> result;

		// Start at the last digit of the number
		std::reverse(top.begin(), top.end());
		std::reverse(bottom.begin(), bottom.end());

		int carry = 0;
		int sum = 0;
		for (int j = 0; j < top.size(); j++) {
			// if there is no corresponding number in bottom. return top + 0 + carry
			if (j >= bottom.size()) {
				sum = top[j] + carry;
			}
			else {
				// add the first two numbers and the carry. 
				sum = top[j] + bottom[j] + carry;
			}
			// now we used the carry so reset it to zero
			carry = 0;
			// if the sum is greater than 9
			if (sum > 9) {
				// divide by 10 to get the carry (tens)
				carry = sum / 10;
				// take modulo 10 to get the digit (ones)
				sum = sum % 10;
			}
			// save the sum in result
			result.push_back(sum);
		}
		// Add leftover carry
		if (carry != 0) {
			result.push_back(carry);
		}
		std::reverse(result.begin(), result.end());
		return result;
	}

	/**
	 * Perform long subtraction of two vectors of integers.
	 *
	 * @param top The vector representing the top number (minuend).
	 * @param bottom The vector representing the bottom number (subtrahend).
	 * @return The result of the long subtraction as a vector of integers.
	 */
	std::vector<int> Integer::doLongSubtraction(std::vector<int> top, std::vector<int> bottom) {
		std::vector<int> result;

		// Start at the last digit of the number
		std::reverse(top.begin(), top.end());
		std::reverse(bottom.begin(), bottom.end());
		int sum = 0;
		for (int j = 0; j < top.size(); j++) {
			// if there is no corresponding number save the number to result
			if (j >= bottom.size()) {
				sum = top[j];
			}
			else {
				// subtract the second from the fist 
				sum = top[j] - bottom[j];
				// if the first number is smaller than the second
				if (top[j] < bottom[j]) {
					// subtract one from the column above
					// if the column above is zero subtract one anyway
					top[j + 1] -= 1;
					// add 10 to the sum
					sum += 10;
				}
			}
			// save the sum in result
			result.push_back(sum);
		}
		std::reverse(result.begin(), result.end());
		result = removeLeadingZeroes(result);
		return result;
	}

	/**
	 * @brief Removes leading zeroes from the given vector of integers.
	 *
	 * This function removes any leading zeroes from the vector by continuously erasing
	 * the first element until either there is only one element left or the first element
	 * is non-zero.
	 *
	 * @param value The vector of integers to remove leading zeroes from.
	 * @return The vector with leading zeroes removed.
	 */
	std::vector<int> Integer::removeLeadingZeroes(std::vector<int> value) {
		while (value.size() > 1 && value.front() == 0) {
			value.erase(value.begin());
		}
		return value;
	}

	/**
	 * Performs long multiplication of two vectors representing integers.
	 *
	 * @param top The vector representing the top number in the multiplication.
	 * @param bottom The vector representing the bottom number in the multiplication.
	 * @return The result of the multiplication as a vector.
	 */
	std::vector<int> Integer::doLongMultiplication(const std::vector<int> top, const std::vector<int> bottom) {
		int m = top.size();
		int n = bottom.size();

		std::vector<int> result(m + n, 0);

		for (int i = m - 1; i >= 0; --i) {
			for (int j = n - 1; j >= 0; --j) {
				int product = top[i] * bottom[j]; // Multiply the digits at the current positions
				int sum = product + result[i + j + 1]; // Add the product to the corresponding result digit
				result[i + j] += sum / 10; // Carry over the tens place to the next digit	
				result[i + j + 1] = sum % 10; // Store the ones place in the result
			}
		}

		// Remove leading zeros from the result
		while (result.size() > 1 && result[0] == 0) {
			result.erase(result.begin());
		}

		return result;
	}

	/**
	 * Performs long division on the given dividend and divisor.
	 *
	 * @param divisor The divisor vector.
	 * @param dividend The dividend vector.
	 * @return The result of the long division as a vector of integers.
	 * @throws std::invalid_argument if attempting to divide by zero.
	 */
	std::vector<int> Integer::doLongDivision(std::vector<int> divisor, std::vector<int> dividend) {
		std::vector<int> result;

		// divide by zero
		if (divisor.size() == 1 && divisor[0] == 0) {
			throw std::invalid_argument("Divide by zero");
		}

		// divide by one
		if (divisor.size() == 1 && divisor[0] == 1) {
			return dividend;
		}

		// divisor larger than dividend -> return 0
		if (Integer(dividend, 1) < Integer(divisor, 1)) {
			result.push_back(0);
			return result;
		}

		// Initialize the remainder vector with the elements from the beginning 
		// of the dividend up to the size of the divisor.
		std::vector<int> remainder(dividend.begin(), dividend.begin() + divisor.size());

		int idx = divisor.size();
		Integer remainderInteger(remainder, 1);
		Integer divisorInteger(divisor, 1);
		while (idx <= dividend.size()) {
			// Count how many times the divisor fits into the remainder
			// This is our quotient
			int q = 0;
			while (remainderInteger >= divisorInteger) {
				remainderInteger -= divisorInteger;
				q++;
			}
			result.push_back(q);

			// If there are more digits in the dividend, append the next 
			// digit to the remainder and make sure to remove leading zeroes
			if (idx < dividend.size()) {
				remainderInteger.number.push_back(dividend[idx]);
				remainderInteger.number = removeLeadingZeroes(remainderInteger.number);
			}
			idx++;
		}
		return removeLeadingZeroes(result);
	}

	/**
	 * @brief Adds another Integer to the current Integer and assigns the result to the current Integer.
	 * @param i The Integer to be added.
	 * @return Reference to the current Integer after the addition.
	 */
	Integer& Integer::operator+=(const Integer& i) {
		// find the highest absolute number for the "top"
		const Integer& larger = (+i > +*this) ? i : *this;
		const Integer& smaller = (+i > +*this) ? *this : i;

		if (i.sign == -1 && sign == -1) {
			// Both negative, do addition with absolute values and reverse the sign
			this->number = doLongAddition(larger.number, smaller.number);
			this->sign = -1;
		} 
		else if (i.sign == -1) {
			// i is negative: subract absolute values and adjust sign
			this->sign = +i > +*this ? -1 : 1;
			this->number = doLongSubtraction(larger.number, smaller.number);
		} 
		else if (sign == -1) {
			// this is negative: subract absolute values and adjust sign
			this->sign = +i >= +*this ? 1 : -1;
			this->number = doLongSubtraction(larger.number, smaller.number);
		} 
		else {
			// Both positive. Do normal addition
			this->number = doLongAddition(larger.number, smaller.number);
		}
		return *this;
	}

	/**
	 * @brief Subtract an Integer from the current Integer object.
	 *
	 * @param i The Integer to subtract.
	 * @return Reference to the updated Integer object after subtraction.
	 */
	Integer& Integer::operator-=(const Integer& i) {
		Integer neg = Integer(i);
		neg.sign *= -1;
		*this += neg;
		return *this;
	}

	/**
	 * @brief Multiply the current Integer object by another Integer.
	 *
	 * @param i The Integer to multiply with.
	 * @return Reference to the updated Integer object after multiplication.
	 */
	Integer& Integer::operator*=(const Integer& i) {
		this->number = doLongMultiplication(i.number, number);
		this->sign *= i.sign;
		return *this;
	}

	/**
	 * @brief Divide the current Integer object by another Integer.
	 *
	 * @param i The Integer to divide by.
	 * @return Reference to the updated Integer object after division.
	 * @throws std::runtime_error if attempting to divide by zero.
	 */
	Integer& Integer::operator/=(const Integer& i) {
		this->number = doLongDivision(i.number, number);
		this->sign /= i.sign;
		if (this->number[0] == 0) { // Avoid -0
			sign = 1;
		}
		return *this;
	}

	/**
	 * @brief Compute the remainder of division of the current Integer object by another Integer.
	 *
	 * @param i The Integer divisor.
	 * @return Reference to the updated Integer object representing the remainder.
	 * @throws std::runtime_error if attempting to divide by zero.
	 */
	Integer& Integer::operator%=(const Integer& i) {
		if (i == Integer("0")) {
			throw std::runtime_error("Divide by zero");
		}
		*this -= (*this / i) * i;
		this->sign = 1;
		return *this;
	}

	/**
	 * @brief Addition operator for Integer objects.
	 * @param lhs The left-hand side Integer object.
	 * @param rhs The right-hand side Integer object.
	 * @return The result of the addition operation.
	 */
	Integer operator+(const Integer& lhs, const Integer& rhs) {
		Integer result = lhs;
		result += rhs;
		return result;
	}

	/**
	 * @brief Subtraction operator for Integer objects.
	 * @param lhs The left-hand side Integer object.
	 * @param rhs The right-hand side Integer object.
	 * @return The result of the subtraction operation.
	 */
	Integer operator-(const Integer& lhs, const Integer& rhs) {
		Integer result = lhs;
		result -= rhs;
		return result;
	}

	/**
	 * @brief Multiplication operator for Integer objects.
	 * @param lhs The left-hand side Integer object.
	 * @param rhs The right-hand side Integer object.
	 * @return The result of the multiplication operation.
	 */
	Integer operator*(const Integer& lhs, const Integer& rhs) {
		Integer result = lhs;
		result *= rhs;
		return result;
	}

	/**
	 * @brief Division operator for Integer objects.
	 * @param lhs The left-hand side Integer object.
	 * @param rhs The right-hand side Integer object.
	 * @return The result of the division operation.
	 */
	Integer operator/(const Integer& lhs, const Integer& rhs) {
		Integer result = lhs;
		result /= rhs;
		return result;
	}

	/**
	 * @brief Modulo operator for Integer objects.	 *
	 * @param lhs The left-hand side Integer object.
	 * @param rhs The right-hand side Integer object.
	 * @return The result of the modulo operation.
	 */
	Integer operator%(const Integer& lhs, const Integer& rhs) {
		Integer result = lhs;
		result %= rhs;
		return result;
	}


	/**
	 * @brief Overload of the output stream operator (<<) to output the Integer object.
	 *
	 * @param os The output stream to write to.
	 * @param i The Integer object to be output.
	 * @return The reference to the output stream.
	 */
	std::ostream& operator<<(std::ostream& os, const Integer& i) {
		if (i.sign == -1) {
			os << "-";
		}
		for (const auto& digit : i.number) {
			os << digit;
		}
		return os;
	}

	/**
	 * @brief Overload of the input stream operator (>>) to read input into the Integer object.
	 *
	 * @param is The input stream to read from.
	 * @param i The Integer object to store the input.
	 * @return The reference to the input stream.
	 */
	std::istream& operator>>(std::istream& is, Integer& i) {
		std::string input;
		is >> input;
		i = Integer(input);
		return is;
	}

	/**
	 * @brief Checks if the left-hand side Integer is less than the right-hand side Integer.
	 * @param lhs The left-hand side Integer.
	 * @param rhs The right-hand side Integer.
	 * @return True if lhs is less than rhs, False otherwise.
	 */
	bool operator<(const Integer& lhs, const Integer& rhs) {
		// Return the opposite if both are negative
		if (lhs.sign == -1 && rhs.sign == -1) {
			return +lhs > +rhs;
		}

		// Compare based on the sign
		if (lhs.sign != rhs.sign) {
			return lhs.sign < rhs.sign;
		}

		// Compare based on size
		if (lhs.number.size() != rhs.number.size()) {
			return lhs.number.size() < rhs.number.size();
		}

		// Compare each digit starting at the most significant
		for (std::size_t i = 0; i < lhs.number.size(); i++) {
			if (lhs.number[i] != rhs.number[i]) {
				return lhs.number[i] < rhs.number[i];
			}
		}

		// If the numbers are equal
		return false;
	}

	/**
	 * @brief Checks if the left-hand side Integer is greater than the right-hand side Integer.
	 * @param lhs The left-hand side Integer.
	 * @param rhs The right-hand side Integer.
	 * @return True if lhs is greater than rhs, False otherwise.
	 */
	bool operator>(const Integer& lhs, const Integer& rhs) {
		// if they are equal then return false
		if (lhs == rhs) {
			return false;
		}
		return !(lhs < rhs);
	}

	/**
	 * @brief Checks if the left-hand side Integer is less than or equal to the right-hand side Integer.
	 * @param lhs The left-hand side Integer.
	 * @param rhs The right-hand side Integer.
	 * @return True if lhs is less than or equal to rhs, False otherwise.
	 */
	bool operator<=(const Integer& lhs, const Integer& rhs) {
		if (lhs == rhs) {
			return true;
		}
		return lhs < rhs;
	}

	/**
	 * @brief Checks if the left-hand side Integer is greater than or equal to the right-hand side Integer.
	 * @param lhs The left-hand side Integer.
	 * @param rhs The right-hand side Integer.
	 * @return True if lhs is greater than or equal to rhs, False otherwise.
	 */
	bool operator>=(const Integer& lhs, const Integer& rhs) {
		if (lhs == rhs) {
			return true;
		}
		return lhs > rhs;
	}

	/**
	 * @brief Checks if the left-hand side Integer is equal to the right-hand side Integer.
	 * @param lhs The left-hand side Integer.
	 * @param rhs The right-hand side Integer.
	 * @return True if lhs is equal to rhs, False otherwise.
	 */
	bool operator==(const Integer& lhs, const Integer& rhs) {
		if (lhs.number == rhs.number && lhs.sign == rhs.sign){
			return true;
		}
		return false;
	}

	/**
	 * @brief Checks if the left-hand side Integer is not equal to the right-hand side Integer.
	 * @param lhs The left-hand side Integer.
	 * @param rhs The right-hand side Integer.
	 * @return True if lhs is not equal to rhs, False otherwise.
	 */
	bool operator!=(const Integer& lhs, const Integer& rhs) {
		return !(rhs == lhs);
	}

	/**
	 * @brief Calculates the greatest common divisor (GCD) of two integers using the Euclidean algorithm.
	 *
	 * @param a The first integer.
	 * @param b The second integer.
	 * @return The greatest common divisor of a and b.
	 */
	Integer gcd(const Integer& a, const Integer& b) {
		if (a == Integer("0")) {
			//sign is always positive
			return +b;
		}

		if (b == Integer("0")) {
			//sign is always positive
			return +a;
		}

		Integer remainder = a % b;
		return gcd(b, remainder);
	}
}
