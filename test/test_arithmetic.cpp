#include <gtest.h>
#include <iostream>
#include "arithmetic.h"

TEST(TArithmetic, can_create_arithmetic)
{
  string str = "(a+b-3)*7-213/3";
  ASSERT_NO_THROW(TArithmetic(srt));
}

TEST(TArithmetic, can_check_brackets_1)
{
	string str = "(";
	TArithmetic calc(str);
	ASSERT_ANY_THROW(calc.Calculate());
}

TEST(TArithmetic, can_check_brackets_2)
{
	string str = ")";
	TArithmetic calc(str);
	ASSERT_ANY_THROW(calc.Calculate());
}

TEST(TArithmetic, can_check_brackets_3)
{
	string str = "()";
	TArithmetic calc(str);
	ASSERT_NO_THROW(calc.Calculate());
}

TEST(TArithmetic, can_calculate_0)
{
	string str = "-1";
	TArithmetic calc(str);
	EXPECT_EQ(calc.Calculate(),-1);
}

TEST(TArithmetic, can_calculate_1)
{
	string str = "1+2";
	TArithmetic calc(str);
	EXPECT_EQ(calc.Calculate(),3);
}

TEST(TArithmetic, can_calculate_2)
{
	string str = "10*2+1";
	TArithmetic calc(str);
	EXPECT_EQ(calc.Calculate(),21);
}

TEST(TArithmetic, can_calculate_3)
{
	string str = "(1+2.5)";
	TArithmetic calc(str);
	EXPECT_EQ(calc.Calculate(),3.5);
}

TEST(TArithmetic, can_calculate_4)
{
	string str = "(100*0.5-25)-5*5+1";
	TArithmetic calc(str);
	EXPECT_EQ(calc.Calculate(),1);
}

TEST(TArithmetic, can_calculate_05)
{
	string str = "3-1+2";
	TArithmetic calc(str);
	EXPECT_EQ(calc.Calculate(),4);
}

TEST(TArithmetic, can_calculate_vars_0)
{
	string str = "(100*a-25)-b*b+1";
	char name[2] = {'a','b'};
	double value[2] = {0.5, 5};
	TArithmetic calc(str);
	calc.setvars(2,name,value);
	EXPECT_EQ(calc.Calculate(),1);
}