#pragma once
#include <utility>

template <typename T>
class TListNode
{
private:
  T data;
  TListNode<T>* prev;
  TListNode<T>* next;

public:
  explicit TListNode(const T& value);
  explicit TListNode(T&& value);

  T& Get();
  const T& Get() const;

  void Set(const T& value);
  void Set(T&& value);

  TListNode<T>* Next() noexcept;
  TListNode<T>* Prev() noexcept;

	void SetNext(TListNode<T>* p) noexcept {
		next = p;
	}
  void SetPrev(TListNode<T>* p) noexcept {
    prev = p;
  }

  const TListNode<T>* Next() const noexcept;
  const TListNode<T>* Prev() const noexcept;

  void InsertAfter(TListNode<T>* node);
  void InsertBefore(TListNode<T>* node);

  // Unlink this node from its neighbors, leaving prev/next nullified.
  void Unlink() noexcept;

  // Returns true if this node points to itself (isolated single-node circle).
  bool IsSingleton() const noexcept;
};


// -------------------- Definitions --------------------

template <typename T>
TListNode<T>::TListNode(const T& value)
  : data(value), prev(nullptr), next(nullptr)
{
}

template <typename T>
TListNode<T>::TListNode(T&& value)
  : data(std::move(value)), prev(nullptr), next(nullptr)
{
}

template <typename T>
T& TListNode<T>::Get()
{
  return data;
}

template <typename T>
const T& TListNode<T>::Get() const
{
  return data;
}

template <typename T>
void TListNode<T>::Set(const T& value)
{
  data = value;
}

template <typename T>
void TListNode<T>::Set(T&& value)
{
  data = std::move(value);
}

template <typename T>
TListNode<T>* TListNode<T>::Next() noexcept
{
  return next;
}

template <typename T>
TListNode<T>* TListNode<T>::Prev() noexcept
{
  return prev;
}

template <typename T>
const TListNode<T>* TListNode<T>::Next() const noexcept
{
  return next;
}

template <typename T>
const TListNode<T>* TListNode<T>::Prev() const noexcept
{
  return prev;
}

template <typename T>
void TListNode<T>::InsertAfter(TListNode<T>* node)
{
  // Insert 'node' immediately after this node.
  if (node == nullptr)
  {
    return;
  }

  node->prev = this;
  node->next = this->next;

  if (this->next != nullptr)
  {
    this->next->prev = node;
  }
  this->next = node;
}

template <typename T>
void TListNode<T>::InsertBefore(TListNode<T>* node)
{
  // Insert 'node' immediately before this node.
  if (node == nullptr)
  {
    return;
  }

  node->next = this;
  node->prev = this->prev;

  if (this->prev != nullptr)
  {
    this->prev->next = node;
  }
  this->prev = node;
}

template <typename T>
void TListNode<T>::Unlink() noexcept
{
  if (prev != nullptr)
  {
    prev->next = next;
  }
  if (next != nullptr)
  {
    next->prev = prev;
  }
  prev = nullptr;
  next = nullptr;
}

template <typename T>
bool TListNode<T>::IsSingleton() const noexcept
{
  return (prev == this && next == this);
}
