#include <gtest/gtest.h>
#include <stdexcept>

#include "cpptemplate/math/calculator.hpp"

using namespace cpptemplate::math;

class CalculatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        calc = std::make_unique<Calculator>();
    }

    void TearDown() override {
        calc.reset();
    }

    std::unique_ptr<Calculator> calc;
};

// Addition tests
TEST_F(CalculatorTest, AddPositiveNumbers) {
    EXPECT_DOUBLE_EQ(calc->add(2.5, 3.7), 6.2);
    EXPECT_DOUBLE_EQ(calc->add(10.0, 5.0), 15.0);
}

TEST_F(CalculatorTest, AddNegativeNumbers) {
    EXPECT_DOUBLE_EQ(calc->add(-2.5, -3.7), -6.2);
    EXPECT_DOUBLE_EQ(calc->add(-10.0, -5.0), -15.0);
}

TEST_F(CalculatorTest, AddMixedNumbers) {
    EXPECT_DOUBLE_EQ(calc->add(5.0, -3.0), 2.0);
    EXPECT_DOUBLE_EQ(calc->add(-7.5, 2.5), -5.0);
}

TEST_F(CalculatorTest, AddZero) {
    EXPECT_DOUBLE_EQ(calc->add(5.0, 0.0), 5.0);
    EXPECT_DOUBLE_EQ(calc->add(0.0, 3.14), 3.14);
    EXPECT_DOUBLE_EQ(calc->add(0.0, 0.0), 0.0);
}

// Subtraction tests
TEST_F(CalculatorTest, SubtractPositiveNumbers) {
    EXPECT_DOUBLE_EQ(calc->subtract(10.0, 3.0), 7.0);
    EXPECT_DOUBLE_EQ(calc->subtract(5.5, 2.2), 3.3);
}

TEST_F(CalculatorTest, SubtractNegativeNumbers) {
    EXPECT_DOUBLE_EQ(calc->subtract(-5.0, -3.0), -2.0);
    EXPECT_DOUBLE_EQ(calc->subtract(-10.0, -15.0), 5.0);
}

TEST_F(CalculatorTest, SubtractFromZero) {
    EXPECT_DOUBLE_EQ(calc->subtract(0.0, 5.0), -5.0);
    EXPECT_DOUBLE_EQ(calc->subtract(5.0, 0.0), 5.0);
}

// Multiplication tests
TEST_F(CalculatorTest, MultiplyPositiveNumbers) {
    EXPECT_DOUBLE_EQ(calc->multiply(4.0, 5.0), 20.0);
    EXPECT_DOUBLE_EQ(calc->multiply(2.5, 3.0), 7.5);
}

TEST_F(CalculatorTest, MultiplyNegativeNumbers) {
    EXPECT_DOUBLE_EQ(calc->multiply(-4.0, -5.0), 20.0);
    EXPECT_DOUBLE_EQ(calc->multiply(-2.5, 3.0), -7.5);
}

TEST_F(CalculatorTest, MultiplyByZero) {
    EXPECT_DOUBLE_EQ(calc->multiply(5.0, 0.0), 0.0);
    EXPECT_DOUBLE_EQ(calc->multiply(0.0, 3.14), 0.0);
    EXPECT_DOUBLE_EQ(calc->multiply(0.0, 0.0), 0.0);
}

TEST_F(CalculatorTest, MultiplyByOne) {
    EXPECT_DOUBLE_EQ(calc->multiply(7.5, 1.0), 7.5);
    EXPECT_DOUBLE_EQ(calc->multiply(1.0, -3.2), -3.2);
}

// Division tests
TEST_F(CalculatorTest, DividePositiveNumbers) {
    EXPECT_DOUBLE_EQ(calc->divide(10.0, 2.0), 5.0);
    EXPECT_DOUBLE_EQ(calc->divide(7.5, 2.5), 3.0);
}

TEST_F(CalculatorTest, DivideNegativeNumbers) {
    EXPECT_DOUBLE_EQ(calc->divide(-10.0, -2.0), 5.0);
    EXPECT_DOUBLE_EQ(calc->divide(-15.0, 3.0), -5.0);
}

TEST_F(CalculatorTest, DivideByOne) {
    EXPECT_DOUBLE_EQ(calc->divide(5.0, 1.0), 5.0);
    EXPECT_DOUBLE_EQ(calc->divide(-3.14, 1.0), -3.14);
}

TEST_F(CalculatorTest, DivideZeroByNumber) {
    EXPECT_DOUBLE_EQ(calc->divide(0.0, 5.0), 0.0);
    EXPECT_DOUBLE_EQ(calc->divide(0.0, -3.14), 0.0);
}

TEST_F(CalculatorTest, DivideByZeroThrowsException) {
    EXPECT_THROW(calc->divide(5.0, 0.0), std::invalid_argument);
    EXPECT_THROW(calc->divide(-3.14, 0.0), std::invalid_argument);
    EXPECT_THROW(calc->divide(0.0, 0.0), std::invalid_argument);
}

// Power tests
TEST_F(CalculatorTest, PowerPositiveBase) {
    EXPECT_DOUBLE_EQ(calc->power(2.0, 3.0), 8.0);
    EXPECT_DOUBLE_EQ(calc->power(5.0, 2.0), 25.0);
    EXPECT_DOUBLE_EQ(calc->power(10.0, 0.0), 1.0);
}

TEST_F(CalculatorTest, PowerNegativeBase) {
    EXPECT_DOUBLE_EQ(calc->power(-2.0, 2.0), 4.0);
    EXPECT_DOUBLE_EQ(calc->power(-3.0, 3.0), -27.0);
}

TEST_F(CalculatorTest, PowerFractionalExponent) {
    EXPECT_NEAR(calc->power(4.0, 0.5), 2.0, 1e-10);
    EXPECT_NEAR(calc->power(8.0, 1.0/3.0), 2.0, 1e-10);
}

// Square root tests
TEST_F(CalculatorTest, SqrtPositiveNumbers) {
    EXPECT_DOUBLE_EQ(calc->sqrt(4.0), 2.0);
    EXPECT_DOUBLE_EQ(calc->sqrt(9.0), 3.0);
    EXPECT_DOUBLE_EQ(calc->sqrt(0.0), 0.0);
    EXPECT_NEAR(calc->sqrt(2.0), 1.414213562373095, 1e-10);
}

TEST_F(CalculatorTest, SqrtNegativeNumberThrowsException) {
    EXPECT_THROW(calc->sqrt(-1.0), std::invalid_argument);
    EXPECT_THROW(calc->sqrt(-0.1), std::invalid_argument);
}