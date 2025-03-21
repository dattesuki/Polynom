#include "List.h"
#include <gtest.h>

TEST(ListTest, DefaultConstructor) {
    list<int> l;
    EXPECT_EQ(l.GetSize(), 0);
}

TEST(ListTest, PushBack) {
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    EXPECT_EQ(l.GetSize(), 2);
    EXPECT_EQ(l[0], 1);
    EXPECT_EQ(l[1], 2);
}

TEST(ListTest, ConstructorByVector) {
    std::vector<int> v = { 2,1 };
    list<int> l(v);
    EXPECT_EQ(l.GetSize(), 2);
    EXPECT_EQ(l[0], 2);
    EXPECT_EQ(l[1], 1);
    ASSERT_ANY_THROW(l[3]);
}

TEST(ListTest, PushFront) {
    list<int> l;
    l.push_front(1);
    l.push_front(2);
    EXPECT_EQ(l.GetSize(), 2);
    EXPECT_EQ(l[0], 2);
    EXPECT_EQ(l[1], 1);
}

TEST(ListTest, Add) {
    list<int> l;
    l.push_back(1);
    l.push_back(3);
    l.add(2, 1);
    EXPECT_EQ(l.GetSize(), 3);
    EXPECT_EQ(l[0], 1);
    EXPECT_EQ(l[1], 2);
    EXPECT_EQ(l[2], 3);
}

TEST(ListTest, PopBack) {
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.pop_back();
    EXPECT_EQ(l.GetSize(), 1);
    EXPECT_EQ(l[0], 1);
}

TEST(ListTest, PopFront) {
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.pop_front();
    EXPECT_EQ(l.GetSize(), 1);
    EXPECT_EQ(l[0], 2);
}

TEST(ListTest, Remove) {
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    node<int>* temp = l.GetFirst();
    l.remove(temp);
    EXPECT_EQ(l.GetSize(), 2);
    EXPECT_EQ(l[0], 1);
    EXPECT_EQ(l[1], 3);
}


TEST(ListTest, Iterator) {
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    list<int>::iterator it = l.GetFirst();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
}

TEST(ListTest, Clear) {
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.clear();
    EXPECT_EQ(l.GetSize(), 0);
}

TEST(ListTest, AssignmentOperator) {
    list<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);

    list<int> l2;
    l2 = l1;
    EXPECT_EQ(l2.GetSize(), 3);
    EXPECT_EQ(l2[0], 1);
    EXPECT_EQ(l2[1], 2);
    EXPECT_EQ(l2[2], 3);
}



TEST(ListTest, AddAtBeginning) {
    list<int> l;
    l.push_back(2);
    l.push_back(3);
    l.add(1, 0);
    EXPECT_EQ(l.GetSize(), 3);
    EXPECT_EQ(l[0], 1);
    EXPECT_EQ(l[1], 2);
    EXPECT_EQ(l[2], 3);
}

TEST(ListTest, AddAtEnd) {
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.add(3, 2);
    EXPECT_EQ(l.GetSize(), 3);
    EXPECT_EQ(l[0], 1);
    EXPECT_EQ(l[1], 2);
    EXPECT_EQ(l[2], 3);
}



TEST(ListTest, RemoveAtEnd) {
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    node<int>* temp = l.GetFirst();
    temp = temp->GetNext();
    temp = temp->GetNext();
    l.remove(temp);
    EXPECT_EQ(l.GetSize(), 2);
    EXPECT_EQ(l[0], 2);
    EXPECT_EQ(l[1], 3);
}


TEST(ListTest, LenCycleNoCycle) {
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    EXPECT_ANY_THROW(l.LenCycle());
}


TEST(ListTest, IteratorEquality) {
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    list<int>::iterator it1 = l.GetFirst();
    list<int>::iterator it2 = l.GetFirst();
    EXPECT_TRUE(it1 == it2);
    ++it1;
    EXPECT_FALSE(it1 == it2);
}
