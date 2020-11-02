#include <../gtest/gtest.h>
#include <../memorylib/MultiStack.h>

TEST(multistack, can_create_defult_multistack)
{
	ASSERT_NO_THROW(TMultiStack<int> A);
}

TEST(multistack, can_create_multistack)
{
	ASSERT_NO_THROW(TMultiStack<int> A(10,3));
}

TEST(multistack, can_copy_multistack)
{
	TMultiStack<int> B(10, 3);
	ASSERT_NO_THROW(TMultiStack<int> A(B));
}

TEST(multistack, can_push_and_pull)
{
	TMultiStack<int> B(10, 3);
	B.push(1, 0);
	B.push(2, 1);
	B.push(3, 2);
	EXPECT_EQ(1, B.pull(0));
	EXPECT_EQ(2, B.pull(1));
	EXPECT_EQ(3, B.pull(2));
}

TEST(multistack, can_use_operator_equal)
{
	TMultiStack<int> A(10, 3);
	A.push(1, 0);
	A.push(2, 1);
	A.push(3, 2);
	TMultiStack<int> B = A;
	EXPECT_EQ(1, B.pull(0));
	EXPECT_EQ(2, B.pull(1));
	EXPECT_EQ(3, B.pull(2));
}


TEST(multistack, can_push_and_pull_out_of_size)
{
	TMultiStack<int> B(10, 3);
	B.push(1, 0);
	B.push(2, 0);
	B.push(3, 0);
	B.push(4, 0);
	EXPECT_EQ(4, B.pull(0));
	EXPECT_EQ(3, B.pull(0));
	EXPECT_EQ(2, B.pull(0));
	EXPECT_EQ(1, B.pull(0));
}

TEST(multistack, can_push_and_pull_out_of_size_2)
{
	TMultiStack<char> B(20, 5);
	B.push('U', 0);
	B.push('O', 0);
	B.push('Q', 1);
	B.push('T', 1);
	B.push('I', 1);
	B.push('A', 1);
	B.push('W', 2);
	B.push('Y', 2);
	B.push('P', 2);
	B.push('E', 3);
	B.push('R', 4);

	B.push('L', 1);
	EXPECT_EQ('L', B.pull(1));
	EXPECT_EQ('A', B.pull(1));
	EXPECT_EQ('I', B.pull(1));
	EXPECT_EQ('T', B.pull(1));
	EXPECT_EQ('Q', B.pull(1));

	EXPECT_EQ('O', B.pull(0));
	EXPECT_EQ('U', B.pull(0));

	EXPECT_EQ('P', B.pull(2));
	EXPECT_EQ('Y', B.pull(2));
	EXPECT_EQ('W', B.pull(2));

	EXPECT_EQ('E', B.pull(3));

	EXPECT_EQ('R', B.pull(4));

	EXPECT_TRUE(B.IsEmpty(0));
	EXPECT_TRUE(B.IsEmpty(1));
	EXPECT_TRUE(B.IsEmpty(2));
	EXPECT_TRUE(B.IsEmpty(3));
	EXPECT_TRUE(B.IsEmpty(4));
}

TEST(multistack, multisatck_is_full)
{
	TMultiStack<char> B(7, 3);
	B.push('U', 0);
	B.push('O', 0);
	B.push('Q', 1);
	B.push('T', 1);
	B.push('I', 1);
	B.push('A', 1);
	B.push('W', 2);

	ASSERT_ANY_THROW(B.push('L', 2));
}


TEST(multistack, multisatck_is_empty)
{
	TMultiStack<char> B(7, 3);
	B.push('U', 0);
	B.push('O', 0);
	B.push('Q', 1);
	B.push('T', 1);

	ASSERT_ANY_THROW(B.pull(2));
}