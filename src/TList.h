#pragma once
#include "TListNode.h"
#include <stdexcept>
#include <cstddef>

template <typename T>
class TList
{
private:
  TListNode<T>* head;   // points to first element (nullptr if empty)
  size_t size;

  // helper: create a single-node circular list from node and set head to it
  void MakeSingleton(TListNode<T>* node);

public:
  TList();
  TList(const TList& other);
  TList& operator=(const TList& other);
  ~TList();

  bool IsEmpty() const noexcept;
  size_t GetSize() const noexcept;

  void PushFront(const T& value);
  void PushBack(const T& value);

  void PopFront();
  void PopBack();

  T& Front();
  const T& Front() const;

  T& Back();
  const T& Back() const;

  void Clear() noexcept;
};

// ============================
// Implementation
// ============================

template <typename T>
TList<T>::TList() : head(nullptr), size(0) {
}

template <typename T>
void TList<T>::MakeSingleton(TListNode<T>* node)
{
  node->SetNext(node);
  node->SetPrev(node);
  head = node;
  size = 1;
}

template <typename T>
TList<T>::TList(const TList& other) : head(nullptr), size(0)
{
  if (!other.head) return;

  TListNode<T>* cur = other.head;
  do {
    PushBack(cur->Get());
    cur = cur->Next();
  } while (cur != other.head);
}

template <typename T>
TList<T>& TList<T>::operator=(const TList& other)
{
  if (this == &other) return *this;
  Clear();

  if (!other.head) return *this;

  TListNode<T>* cur = other.head;
  do {
    PushBack(cur->Get());
    cur = cur->Next();
  } while (cur != other.head);

  return *this;
}

template <typename T>
TList<T>::~TList()
{
  Clear();
}

template <typename T>
bool TList<T>::IsEmpty() const noexcept
{
  return size == 0;
}

template <typename T>
size_t TList<T>::GetSize() const noexcept
{
  return size;
}

// ============================
// Push / Pop
// ============================

template <typename T>
void TList<T>::PushFront(const T& value)
{
  auto* node = new TListNode<T>(value);

  if (!head)
  {
    MakeSingleton(node);
  }
  else
  {
    TListNode<T>* tail = head->Prev();
    node->SetNext(head);
    node->SetPrev(tail);
    tail->SetNext(node);
    head->SetPrev(node);
    head = node;
    ++size;
  }
}

template <typename T>
void TList<T>::PushBack(const T& value)
{
  auto* node = new TListNode<T>(value);

  if (!head)
  {
    MakeSingleton(node);
  }
  else
  {
    TListNode<T>* tail = head->Prev();
    node->SetPrev(tail);
    node->SetNext(head);
    tail->SetNext(node);
    head->SetPrev(node);
    ++size;
  }
}

template <typename T>
void TList<T>::PopFront()
{
  if (!head) throw std::underflow_error("PopFront from empty list");

  if (size == 1)
  {
    delete head;
    head = nullptr;
    size = 0;
    return;
  }

  TListNode<T>* tail = head->Prev();
  TListNode<T>* newHead = head->Next();

  tail->SetNext(newHead);
  newHead->SetPrev(tail);

  delete head;
  head = newHead;
  --size;
}

template <typename T>
void TList<T>::PopBack()
{
  if (!head) throw std::underflow_error("PopBack from empty list");

  if (size == 1)
  {
    delete head;
    head = nullptr;
    size = 0;
    return;
  }

  TListNode<T>* tail = head->Prev();
  TListNode<T>* newTail = tail->Prev();

  newTail->SetNext(head);
  head->SetPrev(newTail);

  delete tail;
  --size;
}

// ============================
// Accessors
// ============================

template <typename T>
T& TList<T>::Front()
{
  if (!head) throw std::out_of_range("Front from empty list");
  return head->Get();
}

template <typename T>
const T& TList<T>::Front() const
{
  if (!head) throw std::out_of_range("Front from empty list");
  return head->Get();
}

template <typename T>
T& TList<T>::Back()
{
  if (!head) throw std::out_of_range("Back from empty list");
  return head->Prev()->Get();
}

template <typename T>
const T& TList<T>::Back() const
{
  if (!head) throw std::out_of_range("Back from empty list");
  return head->Prev()->Get();
}

// ============================
// Clear
// ============================

template <typename T>
void TList<T>::Clear() noexcept
{
  if (!head) return;

  TListNode<T>* cur = head;
  do {
    TListNode<T>* next = cur->Next();
    delete cur;
    cur = next;
  } while (cur != head);

  head = nullptr;
  size = 0;
}
