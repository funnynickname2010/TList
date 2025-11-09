// tests/test_tlist.cpp
#include "../src/TList.h"
#include <gtest/gtest.h>
#include <string>

TEST(TList, newly_created_is_empty)
{
  TList<int> lst;
  EXPECT_TRUE(lst.IsEmpty());
  EXPECT_EQ(lst.GetSize(), 0u);
}


TEST(TList, push_front_and_front_back_behavior)
{
  TList<int> lst;
  lst.PushFront(10);
  EXPECT_FALSE(lst.IsEmpty());
  EXPECT_EQ(lst.GetSize(), 1u);
  EXPECT_EQ(lst.Front(), 10);
  EXPECT_EQ(lst.Back(), 10);

  lst.PushFront(5);
  EXPECT_EQ(lst.GetSize(), 2u);
  EXPECT_EQ(lst.Front(), 5);
  EXPECT_EQ(lst.Back(), 10);
}

TEST(TList, push_back_and_back_front_behavior)
{
  TList<int> lst;
  lst.PushBack(1);
  EXPECT_EQ(lst.Front(), 1);
  EXPECT_EQ(lst.Back(), 1);

  lst.PushBack(2);
  EXPECT_EQ(lst.Front(), 1);
  EXPECT_EQ(lst.Back(), 2);
  EXPECT_EQ(lst.GetSize(), 2u);
}

TEST(TList, pop_front_and_pop_back_on_single_and_multiple)
{
  TList<int> lst;
  lst.PushBack(1);
  lst.PushBack(2);
  lst.PushBack(3);

  EXPECT_EQ(lst.GetSize(), 3u);

  lst.PopFront();
  EXPECT_EQ(lst.GetSize(), 2u);
  EXPECT_EQ(lst.Front(), 2);

  lst.PopBack();
  EXPECT_EQ(lst.GetSize(), 1u);
  EXPECT_EQ(lst.Front(), 2);
  EXPECT_EQ(lst.Back(), 2);

  // removing last element
  lst.PopFront();
  EXPECT_TRUE(lst.IsEmpty());
  EXPECT_EQ(lst.GetSize(), 0u);
}

TEST(TList, pop_from_empty_throws)
{
  TList<int> lst;
  EXPECT_ANY_THROW(lst.PopFront());
  EXPECT_ANY_THROW(lst.PopBack());
}

TEST(TList, clear_empties_list)
{
  TList<int> lst;
  lst.PushBack(1);
  lst.PushBack(2);
  lst.PushBack(3);

  EXPECT_FALSE(lst.IsEmpty());
  lst.Clear();
  EXPECT_TRUE(lst.IsEmpty());
  EXPECT_EQ(lst.GetSize(), 0u);

  // can reuse after clear
  lst.PushFront(7);
  EXPECT_EQ(lst.Front(), 7);
  EXPECT_EQ(lst.GetSize(), 1u);
}

TEST(TList, copy_constructor_performs_deep_copy)
{
  TList<int> a;
  a.PushBack(1);
  a.PushBack(2);
  a.PushBack(3);

  TList<int> b(a); // copy
  EXPECT_EQ(b.GetSize(), 3u);
  EXPECT_EQ(b.Front(), 1);
  EXPECT_EQ(b.Back(), 3);

  // modify copy and ensure original unchanged
  b.PopFront();
  EXPECT_EQ(b.GetSize(), 2u);
  EXPECT_EQ(a.GetSize(), 3u);
  EXPECT_EQ(a.Front(), 1);
}

TEST(TList, assignment_operator_performs_deep_copy_and_self_assignment_safe)
{
  TList<std::string> a;
  a.PushBack("one");
  a.PushBack("two");

  TList<std::string> b;
  b = a;
  EXPECT_EQ(b.GetSize(), 2u);
  EXPECT_EQ(b.Front(), "one");
  EXPECT_EQ(b.Back(), "two");

  // self-assignment should be safe
  a = a;
  EXPECT_EQ(a.GetSize(), 2u);
  EXPECT_EQ(a.Front(), "one");
}

TEST(TList, many_operations_stress_and_circularity)
{
  TList<int> lst;

  // push a number of elements
  for (int i = 0; i < 20; i++)
  {
    lst.PushBack(i);
  }

  EXPECT_EQ(lst.GetSize(), 20u);
  EXPECT_EQ(lst.Front(), 0);
  EXPECT_EQ(lst.Back(), 19);

  // pop some from front and back and ensure order preserved
  for (int i = 0; i < 5; i++)
  {
    lst.PopFront();
  }
  EXPECT_EQ(lst.Front(), 5);
  for (int i = 0; i < 5; i++)
  {
    lst.PopBack();
  }
  EXPECT_EQ(lst.Back(), 14);

  // finally clear
  lst.Clear();
  EXPECT_TRUE(lst.IsEmpty());
}

TEST(TList, mixing_push_front_and_push_back_preserves_order)
{
  TList<int> lst;
  lst.PushBack(2);   // [2]
  lst.PushFront(1);  // [1,2]
  lst.PushBack(3);   // [1,2,3]
  lst.PushFront(0);  // [0,1,2,3]

  EXPECT_EQ(lst.GetSize(), 4u);
  EXPECT_EQ(lst.Front(), 0);
  EXPECT_EQ(lst.Back(), 3);

  // pop to verify
  lst.PopFront();
  EXPECT_EQ(lst.Front(), 1);
  lst.PopBack();
  EXPECT_EQ(lst.Back(), 2);
}
