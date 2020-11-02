#include <../gtest/gtest.h>
#include <../memorylib/Stack.h>

TEST(stack, can_create_default_stack)
{
	ASSERT_NO_THROW(TStack<int> A);
}

TEST(stack, can_not_create_stack_with_nagative_size)
{
	ASSERT_ANY_THROW(TStack<int> A (-1));
}

TEST(stack, can_create_stack_with_positive_size)
{
	ASSERT_NO_THROW(TStack<int> A(3));
}

TEST(stack, can_copy_stack)
{
	TStack <int> B(3);
	ASSERT_NO_THROW(TStack<int> A(B));
}

TEST(stack, can_push_and_pull)
{
	TStack<int> A(3);
	int k = 1;
	A.push(k);

	EXPECT_EQ(1, A.pull());
}

TEST(stack, can_push_and_pull_all_size)
{
	TStack<int> A(3);
	int x1 = 1, x2 = 2, x3 = 7;
	A.push(x1);
	A.push(x2);
	A.push(x3);

	EXPECT_EQ(7, A.pull());
	EXPECT_EQ(2, A.pull());
	EXPECT_EQ(1, A.pull());
}

TEST(stack, can_not_push_out_of_size)
{
	TStack<int> A(3);
	int x1 = 1, x2 = 2, x3 = 7, x4 = 2;
	A.push(x1);
	A.push(x2);
	A.push(x3);

	ASSERT_ANY_THROW(A.push(x4));
}

TEST(stack, can_not_pull_out_of_size)
{
	TStack<int> A(3);

	ASSERT_ANY_THROW(A.pull());
}

TEST(stack, can_copy_stack_with_any_elements)
{
	TStack<int> A(3);
	int x1 = 1, x2 = 2, x3 = 7, x4 = 2;
	A.push(x1);
	A.push(x2);
	A.push(x3);

	TStack<int> B(A);
	EXPECT_EQ(7, B.pull());
	EXPECT_EQ(2, B.pull());
	EXPECT_EQ(1, B.pull());
}

TEST(stack, find_maximum)
{
	TStack<int> A(3);
	int x1 = -1, x2 = -2, x3 = -7;

	A.push(x1);
	A.push(x2);
	A.push(x3);

	TStack<int> B(A); 


	EXPECT_EQ(-1, A.maximum());

	EXPECT_EQ(A.pull(), B.pull());
	EXPECT_EQ(A.pull(), B.pull());
	EXPECT_EQ(A.pull(), B.pull());

}

TEST(stack, find_element)
{
	TStack<int> A(3);
	int x1 = -1, x2 = 12, x3 = -7;

	A.push(x1);
	A.push(x2);
	A.push(x3);

	EXPECT_EQ(-1, A.elem(0));
	ASSERT_ANY_THROW(A.elem(3));
	ASSERT_ANY_THROW(A.elem(-1));
}

TEST(stack, can_use_resize_stack)
{
	TStack<int> A(3);
	int x1 = -1, x2 = 12, x3 = -7;

	A.push(x1);
	A.push(x2);
	A.push(x3);

	A.ReSize(4);
	ASSERT_NO_THROW(A.push(1));
	EXPECT_EQ(1, A.pull());
	EXPECT_EQ(-7, A.pull());
	EXPECT_EQ(12, A.pull());
	EXPECT_EQ(-1, A.pull());
}

TEST(stack, can_use_resize_stack_reduce)
{
	TStack<int> A(4);
	int x1 = -1, x2 = 12, x3 = -7;

	A.push(x1);
	A.push(x2);
	A.push(x3);

	A.ReSize(3);
	ASSERT_ANY_THROW(A.push(1));
	EXPECT_EQ(-7, A.pull());
	EXPECT_EQ(12, A.pull());
	EXPECT_EQ(-1, A.pull());
}