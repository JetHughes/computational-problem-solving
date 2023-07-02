# Etude 08: Rational Thinking - exact precision Intgers and Rationals
By Jet Hughes, and Jack Searle

# Overview
For the Integer class we chose to use an array of `int` to store the number. This is because this would allow us to more easily perform long addition, subtraction, multiplication and division. We chose to use a c++ `std::vector<int>` to store the numbers. We also decided to store the sign of the number separately as an `int` which is either `1` or `-1`. This allowed us to easily calculate the sign when performing operations. To implement the operations, we performed long addition, subtraction, multiplication, and division using the vector of integers. This was reasonably simple because the numbers were stored in a `std::vector<int>`

For the Rational class we initally stored three numbers: whole, numerator, and denominator. But later switched to storing only the numerator and the denominator. The sign was stored as part of the numerator. Implementing the operations for this class was far simpler than the Integer class.

# Problems we faced
The first major problem was with addition. We had some issues with finding a way to deal with the different signs when adding and subtracting. Eventually we found a to make the code clean and readable. The second major problem we had was with the implementation of long division. It took some time to figure out a suitable method, we got there eventually using a relatively simple algorithm. After that Integer went smoothly

Initially, when creating the Rational class, we implemented it by storing each of the three parts (whole, numerator and denominator) separately. This made it far more complicated that it needed to be to implement the operations. we ran into some issues then we decided to store the rational number as an improper fraction. This worked much better and we were able to redo the entire Rational class very easily this way. It also made the code much cleaner and fixed some small issues with my original implementation.

# Testing
While creating the Integer class, we tested each method as we created it. This worked well because It ensured that each operation worked and we could use it to help us implement the other operations. Creating the Rational class was much easier so we created all the methods before testing. This did not work so well because then we had to write all the tests in one go, which was not fun. However as a result of this, we rewrote the entire testing script which made it much cleaner and more extentable. After doing this, we discovered a lot of bugs and were able to fix them

To created test cases we used ChatGPT to generate cases and verified the tests using various online calculators including [wolframalpha](https://www.wolframalpha.com) and [mathsisfun](https://www.mathsisfun.com/calculator-precision.html). These allowed us to test operations with very large numbers.

# Debugging
Since we used Visual Studio it was very easy to use the built in debugger. This tool was crucial as it made it a lot easier to find and fix issues in the code.