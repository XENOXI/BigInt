#include "BigInt.h"

TEST(Converting, All) {
  EXPECT_EQ(int(BigInt(65536)), 65536);
  EXPECT_EQ(int(BigInt(-65536)), -65536);
  EXPECT_EQ(int(BigInt("65536")), 65536);
  EXPECT_EQ(std::string(BigInt("-65536")), "-65536");
  EXPECT_EQ(std::string(BigInt("65536")), "65536");
}

TEST(Equating, All) {
	BigInt x = BigInt(65536);
	EXPECT_EQ(x, BigInt(65536));
	x = -x;
	EXPECT_EQ(x, BigInt(-65536));
	x = x;
	EXPECT_EQ(x, BigInt(-65536));
}

TEST(Bitwise_op, negation)
{
	EXPECT_EQ(~BigInt(1002), BigInt(-64533));
}

TEST(Substract, Easy)
{
	EXPECT_EQ(BigInt(65536)-BigInt(1), BigInt(65535));
}
TEST(Substract, Zero)
{
	EXPECT_EQ(BigInt(1) - BigInt(2), BigInt(-1));
	EXPECT_EQ(BigInt(65536) - BigInt(65536), BigInt(0));
}
TEST(Substract, Negative)
{
	EXPECT_EQ(BigInt(-1) - BigInt(-65536), BigInt(65535));
	EXPECT_EQ(BigInt(1) - BigInt(-65535), BigInt(65536));
	EXPECT_EQ(BigInt(-65535) - BigInt(1), BigInt(-65536));
}
TEST(Increment, Prefix)
{
	//shifts test
	BigInt x = BigInt(65535);
	EXPECT_EQ(++x, BigInt(65536));
	EXPECT_EQ(x, BigInt(65536));
	//test without shifts
	EXPECT_EQ(++x, BigInt(65537));
	EXPECT_EQ(x, BigInt(65537));
	//Reverse test
	x = BigInt(-1);
	EXPECT_EQ(++x, BigInt(0));
	EXPECT_EQ(x, BigInt(0));
	//Negative test without shifts
	x = BigInt(-10);
	EXPECT_EQ(++x, BigInt(-9));
	EXPECT_EQ(x, BigInt(-9));
	//Negaative with shifts
	x = BigInt(-65536);
	EXPECT_EQ(++x, BigInt(-65535));
	EXPECT_EQ(x, BigInt(-65535));
}
TEST(Increment, Postfix)
{
	//shifts test
	BigInt x = BigInt(65535);
	EXPECT_EQ(x++, BigInt(65535));
	EXPECT_EQ(x, BigInt(65536));
	//test without shifts
	EXPECT_EQ(x++, BigInt(65536));
	EXPECT_EQ(x, BigInt(65537));
	//Reverse test
	x = BigInt(-1);
	EXPECT_EQ(x++, BigInt(-1));
	EXPECT_EQ(x, BigInt(0));
	//Negative test without shifts
	x = BigInt(-10);
	EXPECT_EQ(x++, BigInt(-10));
	EXPECT_EQ(x, BigInt(-9));
	//Negaative with shifts
	x = BigInt(-65536);
	EXPECT_EQ(x++, BigInt(-65536));
	EXPECT_EQ(x, BigInt(-65535));
}
TEST(Decrement, Prefix)
{
	//shifts test
	BigInt x = BigInt(65536);
	EXPECT_EQ(--x, BigInt(65535));
	EXPECT_EQ(x, BigInt(65535));
	//test without shifts
	EXPECT_EQ(--x, BigInt(65534));
	EXPECT_EQ(x, BigInt(65534));
	//Reverse test
	x = BigInt(0);
	EXPECT_EQ(--x, BigInt(-1));
	EXPECT_EQ(x, BigInt(-1));
	//Negative test without shifts
	EXPECT_EQ(--x, BigInt(-2));
	EXPECT_EQ(x, BigInt(-2));
	//Negative with shifts
	x = BigInt(-65535);
	EXPECT_EQ(--x, BigInt(-65536));
	EXPECT_EQ(x, BigInt(-65536));
}
TEST(Decrement, Postfix)
{
	//shifts test
	BigInt x = BigInt(65536);
	EXPECT_EQ(x--, BigInt(65536));
	EXPECT_EQ(x, BigInt(65535));
	//test without shifts
	EXPECT_EQ(x--, BigInt(65535));
	EXPECT_EQ(x, BigInt(65534));
	//Reverse test
	x = BigInt(0);
	EXPECT_EQ(x--, BigInt(0));
	EXPECT_EQ(x, BigInt(-1));
	//Negative test without shifts
	EXPECT_EQ(x--, BigInt(-1));
	EXPECT_EQ(x, BigInt(-2));
	//Negative with shifts
	x = BigInt(-65535);
	EXPECT_EQ(x--, BigInt(-65535));
	EXPECT_EQ(x, BigInt(-65536));
}
TEST()
{

}