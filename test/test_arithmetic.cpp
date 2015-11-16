#include <gtest.h>
#include <iostream>
#include "arithmetic.h"

TEST(TStack, can_create_arithmetic)
{
  string str = "(a+b-3)*7-213/3";
  ASSERT_NO_THROW(TArithmetic(srt));
}

TEST(TStack, can_split_string_on_tokens)
{
  string str = "(a+b-3)*7-213/3*123.321";
  string strT = "( a + b - 3 ) * 7 - 213 / 3 * 123.321 ";
  TArithmetic Ar(str);
  Ar.SplitIntoTokens();
  EXPECT_EQ(Ar.GetTokens(),strT);
}
