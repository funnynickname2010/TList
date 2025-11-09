// tests/test_tlistnode.cpp
#include "../src/TListNode.h"
#include <gtest/gtest.h>
#include <string>

TEST(TListNode, can_construct_and_get_set_value)
{
  TListNode<int> n(10);
  EXPECT_EQ(n.Get(), 10);

  n.Set(20);
  EXPECT_EQ(n.Get(), 20);

  TListNode<std::string> s(std::string("hello"));
  EXPECT_EQ(s.Get(), "hello");

  s.Set(std::string("world"));
  EXPECT_EQ(s.Get(), "world");
}

TEST(TListNode, next_prev_initially_null)
{
  TListNode<int> n(1);
  EXPECT_EQ(n.Next(), nullptr);
  EXPECT_EQ(n.Prev(), nullptr);
}

TEST(TListNode, insert_after_and_before_updates_neighbors)
{
  TListNode<int> a(1);
  TListNode<int> b(2);
  TListNode<int> c(3);

  // a -> b
  a.InsertAfter(&b);
  EXPECT_EQ(a.Next(), &b);
  EXPECT_EQ(b.Prev(), &a);

  // insert c after b: a -> b -> c
  b.InsertAfter(&c);
  EXPECT_EQ(b.Next(), &c);
  EXPECT_EQ(c.Prev(), &b);

  // insert node d before a (edge): create d and insert before a
  TListNode<int> d(0);
  a.InsertBefore(&d);
  EXPECT_EQ(d.Next(), &a);
  EXPECT_EQ(a.Prev(), &d);

  // cleanup: unlink nodes
  a.Unlink();
  b.Unlink();
  c.Unlink();
  d.Unlink();
}

TEST(TListNode, unlink_removes_links_and_nulls_out_pointers)
{
  TListNode<int> a(1);
  TListNode<int> b(2);
  TListNode<int> c(3);

  // link a <-> b <-> c
  a.InsertAfter(&b);
  b.InsertAfter(&c);

  // unlink middle node b
  b.Unlink();
  EXPECT_EQ(b.Next(), nullptr);
  EXPECT_EQ(b.Prev(), nullptr);

  // neighbors should now connect: a -> c
  EXPECT_EQ(a.Next(), &c);
  EXPECT_EQ(c.Prev(), &a);

  // cleanup
  a.Unlink();
  c.Unlink();
}

TEST(TListNode, is_singleton_true_for_self_loop)
{
  TListNode<int> n(5);

  // manually simulate a singleton loop via interface
  n.InsertAfter(&n);
  EXPECT_TRUE(n.IsSingleton());

  // unlink and check again
  n.Unlink();
  EXPECT_FALSE(n.IsSingleton());
  EXPECT_EQ(n.Next(), nullptr);
  EXPECT_EQ(n.Prev(), nullptr);
}

TEST(TListNode, insert_nullptr_safely_ignored)
{
  TListNode<int> a(1);

  // these should be safe no-ops
  a.InsertAfter(nullptr);
  a.InsertBefore(nullptr);

  EXPECT_EQ(a.Next(), nullptr);
  EXPECT_EQ(a.Prev(), nullptr);
}
