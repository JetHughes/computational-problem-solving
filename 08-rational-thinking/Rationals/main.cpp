/*
	Test main for Rational and Integer
*/

#include <iostream>
#include <cassert>
#include <type_traits>
using namespace std;

#include "Integer.h"
#include "Rational.h"

using namespace cosc326;

template <typename T>
void testArithmetic(string a, string b, string answer, string operation) {
	T objA = T(a);
	T objB = T(b);
	T objC = objA;
	T result;

	if (operation == "+") {
		result = objA + objB;
		objC += objB;
	}
	else if (operation == "-") {
		result = objA - objB;
		objC -= objB;
	}
	else if (operation == "*") {
		result = objA * objB;
		objC *= objB;
	}
	else if (operation == "/") {
		result = objA / objB;
		objC /= objB;
	}
	cout << a << " " << operation << " " << b << " = " << result;
	assert(result == T(answer));
	assert(objC == T(answer));
	cout << " passed" << endl;
}

template <typename T>
void testComparison(string a, string b, string operation, bool answer) {
	bool result = NAN;
	if (operation == "==") {
		result = T(a) == T(b);
	}
	else if (operation == ">") {
		result = T(a) > T(b);
	}
	else if (operation == "<") {
		result = T(a) < T(b);
	}
	else if (operation == ">=") {
		result = T(a) >= T(b);
	}
	else if (operation == "<=") {
		result = T(a) <= T(b);
	}
	else if (operation == "!=") {
		result = T(a) != T(b);
	}

	cout << a << " " << operation << " " << b << " = " << result;
	assert(result == answer);
	cout << " passed" << endl;
}

template <typename T>
void testStringConstructor(string str) {
	cout << str << ": " << T(str) << endl;
}

template <typename T>
void testUnary(string a, string operation, string answer) {
	T result = operation == "+" ? +T(a) : -T(a);
	cout << operation << "(" << a << ") : " << result;
	assert(result == T(answer));
	cout << " passed" << endl;
}

void testIntegerModulo(string a, string b, string answer) {
	Integer result = Integer(a) % Integer(b);
	Integer ci(a);
	ci %= Integer(b);
	cout << a << " % " << b << " = " << result;
	assert(result == Integer(answer));
	assert(ci == Integer(answer));
	cout << " passed" << endl;
}

void testIntegerGcd(string a, string b, string answer) {
	Integer result = gcd(Integer(a), Integer(b));
	cout << "gcd(" << a << ", " << b << ") = " << result;
	assert(result == Integer(answer));
	cout << " passed" << endl;
}

void testIntegerConstructors() {
	// Test Default constructor
	assert(Integer() == Integer("0"));
	cout << "\nTest Constructors" << endl;
	// Test String constructor
	Integer number = Integer("234234");
	cout << "234234: " << number << endl;
	Integer negativeNumber = Integer("-234234");
	cout << "-234234: " << negativeNumber << endl;
	// Test Copy constructor
	assert(number == Integer(number));
	// Test assignment operator
	Integer temp = number;
	assert(temp == number);
}

void testInteger() {
	cout << "\n\n****************** Test Integer ******************\n" << endl;

	cout << "\nTest constructors" << endl;
	testIntegerConstructors();
	testStringConstructor<Integer>("10.7/8");
	testStringConstructor<Integer>("6.7/8");
	testStringConstructor<Integer>("4/3");
	testStringConstructor<Integer>("-1.1/2");
	testStringConstructor<Integer>("-3.2/4");
	testStringConstructor<Integer>("+15.32/2");
	testStringConstructor<Integer>("+12342345.300000/70000");
	testStringConstructor<Integer>("10");
	testStringConstructor<Integer>("80");

	cout << "\nTest comparisons" << endl;
	testComparison<Integer>("31", "12", ">=", true);
	testComparison<Integer>("-123", "-124", "<", false);
	testComparison<Integer>("-123", "123", "<", true);
	testComparison<Integer>("123", "-123", "<", false);
	testComparison<Integer>("123", "123", "<", false);
	testComparison<Integer>("-22", "-123", "<", false);
	testComparison<Integer>("1", "2", ">", false);
	testComparison<Integer>("2", "1", ">", true);
	testComparison<Integer>("-123", "-124", ">", true);
	testComparison<Integer>("-123", "-124", ">", true);
	testComparison<Integer>("0", "0", ">", false);

	cout << "\nTest addition" << endl;
	testArithmetic<Integer>("1", "1", "2", "+");
	testArithmetic<Integer>("5", "10", "15", "+");
	testArithmetic<Integer>("112", "2", "114", "+");
	testArithmetic<Integer>("48", "7", "55", "+");
	testArithmetic<Integer>("122342344344", "13924342434", "136266686778", "+");
	testArithmetic<Integer>("975948575958", "96796969698", "1072745545656", "+");
	testArithmetic<Integer>("975948575958", "967969696985676", "968945645561634", "+");
	testArithmetic<Integer>("697878599184027492747", "99483929374928709384937393743", "99483930072807308568964886490", "+");

	cout << "\nTest negative addition" << endl;
	testArithmetic<Integer>("2", "-1", "1", "+");
	testArithmetic<Integer>("-1", "-1", "-2", "+");
	testArithmetic<Integer>("768", "-12", "756", "+");
	testArithmetic<Integer>("768", "-75", "693", "+");
	testArithmetic<Integer>("721", "-84", "637", "+");
	testArithmetic<Integer>("-84", "721", "637", "+");
	testArithmetic<Integer>("-721", "84", "-637", "+");
	testArithmetic<Integer>("-0", "-1", "-1", "+");
	testArithmetic<Integer>("-2", "-45", "-47", "+");
	testArithmetic<Integer>("-45", "-2", "-47", "+");
	testArithmetic<Integer>("-45", "-89", "-134", "+");

	cout << "\nTest subtraction" << endl;
	testArithmetic<Integer>("2", "1", "1", "-");
	testArithmetic<Integer>("2", "-1", "3", "-");
	testArithmetic<Integer>("-12", "-12", "0", "-");
	testArithmetic<Integer>("1233", "9287121", "-9285888", "-");
	testArithmetic<Integer>("-45", "2", "-47", "-");
	testArithmetic<Integer>("-456", "-98", "-358", "-");
	testArithmetic<Integer>("122342344344", "139243424312341341413393874", "-139243424312341219071049530", "-");

	cout << "\nTest multiplication" << endl;
	testArithmetic<Integer>("2", "1", "2", "*");
	testArithmetic<Integer>("2", "-1", "-2", "*");
	testArithmetic<Integer>("1233", "9287121", "11451020193", "*");
	testArithmetic<Integer>("-45", "2", "-90", "*");
	testArithmetic<Integer>("-456", "-98", "44688", "*");

	cout << "\nTest division" << endl;
	testArithmetic<Integer>("-1", "4", "0", "/");
	testArithmetic<Integer>("170", "1", "170", "/");
	testArithmetic<Integer>("62", "2", "31", "/");
	testArithmetic<Integer>("16342", "12", "1361", "/");
	testArithmetic<Integer>("1", "2", "0", "/");
	testArithmetic<Integer>("4", "2", "2", "/");
	testArithmetic<Integer>("16", "-4", "-4", "/");
	testArithmetic<Integer>("-45", "9", "-5", "/");
	testArithmetic<Integer>("-10", "90", "0", "/");
	testArithmetic<Integer>("321294949936", "9383937", "34238", "/");

	try {
		testArithmetic<Integer>("321236", "0", "0", "/");
	}
	catch (const invalid_argument e) {
		cout << e.what() << endl;
	}

	cout << "\nTest modulo" << endl;
	testIntegerModulo("16342", "12", "10");
	testIntegerModulo("1500", "-7", "2");
	testIntegerModulo("5", "-2", "1");
	testIntegerModulo("-10", "4", "2");
	testIntegerModulo("4928339173", "9483739472943729376", "4928339173");

	cout << "\nTest gcd" << endl;
	testIntegerGcd("72", "48", "24");
	testIntegerGcd("-10", "19383848", "2");
	testIntegerGcd("-72", "48", "24");
	testIntegerGcd("-48", "72", "24");
	testIntegerGcd("32084032434", "2343207482974380234", "6");
}

void testRationalConstructors() {
	// Test constructors and output stream
	// !!! Need to Manually verify !!!
	// Default constructor
	cout << "Default rational: " << Rational() << endl;
	// Single Integer constructor
	cout << "9: " << Rational(Integer("9")) << endl;
	cout << "-9: " << Rational(Integer("-9")) << endl;
	cout << "-0: " << Rational(Integer("0")) << endl;
	cout << "0: " << Rational(Integer("0")) << endl;
	// Double Integer constructor
	cout << "9, 4: " << Rational(Integer("9"), Integer("4")) << endl;
	cout << "9, -4: " << Rational(Integer("9"), Integer("-4")) << endl;
	cout << "0, -4: " << Rational(Integer("9"), Integer("-4")) << endl;
	cout << "-1, -4: " << Rational(Integer("9"), Integer("-4")) << endl;
	cout << "187897374293749, -3249349324987374897432387: ";
	cout << Rational(Integer("187897374293749"), Integer("-3249349324987374897432387")) << endl;
	cout << "1878973723432432432344293749, -3249323: ";
	cout << Rational(Integer("1878973723432432432344293749"), Integer("-3249323")) << endl;
	// Triple Integer constructor
	cout << "9, 4, 18: " << Rational(Integer("9"), Integer("4"), Integer("18")) << endl;
	cout << "9, 4, -18: " << Rational(Integer("9"), Integer("4"), Integer("-18")) << endl;
	cout << "0, 4, -18: " << Rational(Integer("0"), Integer("4"), Integer("-18")) << endl;
	// Copy constructor
	Rational temp = Rational(Integer("0"), Integer("4"), Integer("-18"));
	cout << "copy " << temp << ": " << Rational(temp) << endl;
}

void testRational() {
	cout << "\n\n****************** Test Rational ******************\n" << endl;

	cout << "\nTest constructors" << endl;
	testRationalConstructors();
	// String constructor
	testStringConstructor<Rational>("10.7/8");
	testStringConstructor<Rational>("6.7/8");
	testStringConstructor<Rational>("4/3");
	testStringConstructor<Rational>("-1.1/2");
	testStringConstructor<Rational>("-3.2/4");
	testStringConstructor<Rational>("+15.32/2");
	testStringConstructor<Rational>("+12342345.300000/70000");
	testStringConstructor<Rational>("10");
	testStringConstructor<Rational>("80");

	cout << "\nTest unary operators" << endl;
	testUnary<Rational>("0", "-", "0");
	testUnary<Rational>("-5/3", "-", "5/3");
	testUnary<Rational>("-2/4", "-", "2/4");
	testUnary<Rational>("3/5", "-", "-3/5");
	testUnary<Rational>("5/2", "-", "-5/2");
	testUnary<Rational>("8", "-", "-8");
	testUnary<Rational>("8.1/2", "-", "-8.1/2");
	testUnary<Rational>("-3/4", "+", "3/4");
	testUnary<Rational>("0/1", "+", "0/1");

	cout << "\nTest comparison" << endl;
	testComparison<Rational>("1/2", "2/4", "==", true);
	testComparison<Rational>("1/2", "2/4", "==", true);
	testComparison<Rational>("3/4", "1/2", ">", true);
	testComparison<Rational>("-5/6", "1/4", "<", true);
	testComparison<Rational>("1", "1/2", ">", true);
	testComparison<Rational>("-2/3", "-1/2", "<", true);
	testComparison<Rational>("0", "0", "==", true);
	testComparison<Rational>("1/3", "2/3", "<=", true);
	testComparison<Rational>("-1/2", "1/2", "!=", true);
	testComparison<Rational>("2", "4/2", ">=", true);
	testComparison<Rational>("-2/5", "1/5", "!=", true);

	cout << "\nTest Addition" << endl;
	testArithmetic<Rational>("17", "8.1/2", "25.1/2", "+");
	testArithmetic<Rational>("1/3", "2/3", "1", "+");
	testArithmetic<Rational>("-5/8", "3/4", "1/8", "+");
	testArithmetic<Rational>("-2/7", "5/7", "3/7", "+");
	testArithmetic<Rational>("1", "1/2", "3/2", "+");
	testArithmetic<Rational>("-3", "-4", "-7", "+");
	testArithmetic<Rational>("0", "0", "0", "+");
	testArithmetic<Rational>("0", "1/4", "1/4", "+");
	testArithmetic<Rational>("-2/5", "-1/5", "-3/5", "+");

	cout << "\nTest Subtraction" << endl;
	testArithmetic<Rational>("8.4/8", "10", "-1.1/2", "-");
	testArithmetic<Rational>("5/6", "1/3", "1/2", "-");
	testArithmetic<Rational>("-7/8", "1/4", "-1.1/8", "-");
	testArithmetic<Rational>("-1/2", "-1/3", "-1/6", "-");
	testArithmetic<Rational>("2", "1/2", "3/2", "-");
	testArithmetic<Rational>("0", "0", "0", "-");
	testArithmetic<Rational>("1", "1", "0", "-");
	testArithmetic<Rational>("1/2", "1/4", "1/4", "-");
	testArithmetic<Rational>("-2/5", "1/5", "-3/5", "-");

	cout << "\nTest Multiplication" << endl;
	testArithmetic<Rational>("-6.7/8", "10", "-68.3/4", "*");
	testArithmetic<Rational>("3/4", "2/3", "1/2", "*");
	testArithmetic<Rational>("-5/6", "2/5", "-1/3", "*");
	testArithmetic<Rational>("-1/2", "-2/3", "1/3", "*");
	testArithmetic<Rational>("2", "1/2", "1", "*");
	testArithmetic<Rational>("0", "5/7", "0", "*");
	testArithmetic<Rational>("1", "1", "1", "*");
	testArithmetic<Rational>("1/2", "1/4", "1/8", "*");
	testArithmetic<Rational>("-2/5", "1/5", "-2/25", "*");

	cout << "\nTest Division" << endl;
	testArithmetic<Rational>("8.1/2", "10", "17/20", "/");
	testArithmetic<Rational>("1/2", "2/3", "3/4", "/");
	testArithmetic<Rational>("-5/6", "1/4", "-10/3", "/");
	testArithmetic<Rational>("-1/2", "-2/3", "3/4", "/");
	testArithmetic<Rational>("2", "1/2", "4", "/");
	testArithmetic<Rational>("0", "5/7", "0", "/");
	testArithmetic<Rational>("1", "1", "1", "/");
	testArithmetic<Rational>("1/2", "1/4", "2", "/");
	testArithmetic<Rational>("-2/5", "1/5", "-2", "/");
}

int main() {
	testInteger();
	testRational();
  cout << "All Tests Passed :)" << endl; 
	return 0;
}