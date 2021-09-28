#pragma once

#include <string>
#include <exception>
#include "MemoryHeapStrategy.h" // as default

template<class ValueType, class MemoryStrategyType = MemoryHeapStrategy>
class Deque
{
  private:
    // element of deque
    struct DequeElement
    {
      ValueType Value;
      DequeElement *Next;
      DequeElement *Prev;
    };

    DequeElement *Head;
    DequeElement *Tail;

    MemoryStrategyType Allocator;

  public:

    // iterator
    class DequeIterator
    {
    public:
      DequeIterator() : CurrentNode(Head)
      {
      }

      DequeIterator(DequeElement* Node) : CurrentNode(Node)
      {
      }

      DequeIterator& operator=(DequeElement* Node)
      {
        this->CurrentNode = Node;
        return *this;
      }

      // Prefix ++ overload
      DequeIterator& operator++()
      {
        if (CurrentNode)
          CurrentNode = CurrentNode->Next;
        return *this;
      }

      // Postfix ++ overload
      DequeIterator operator++(int)
      {
        DequeIterator iterator = *this;
        ++*this;
        return iterator;
      }

      bool operator!=(const DequeIterator& iterator)
      {
        return CurrentNode != iterator.CurrentNode;
      }

      ValueType & operator*()
      {
        return CurrentNode->Value;
      }

    private:
      DequeElement* CurrentNode;
    };

    // const iterator
    class ConstDequeIterator
    {
    public:
      ConstDequeIterator() : CurrentNode(Head)
      {
      }

      ConstDequeIterator(const DequeElement* Node) : CurrentNode(Node)
      {
      }

      ConstDequeIterator& operator=(DequeElement* Node)
      {
        this->CurrentNode = Node;
        return *this;
      }

      // Prefix ++ overload
      ConstDequeIterator& operator++()
      {
        if (CurrentNode)
          CurrentNode = CurrentNode->Next;
        return *this;
      }

      // Postfix ++ overload
      ConstDequeIterator operator++(int)
      {
        ConstDequeIterator iterator = *this;
        ++*this;
        return iterator;
      }

      bool operator!=(const ConstDequeIterator& iterator)
      {
        return CurrentNode != iterator.CurrentNode;
      }

      const ValueType & operator*()
      {
        return CurrentNode->Value;
      }

    private:
      const DequeElement* CurrentNode;
    };

    // begin() for iterators
    DequeIterator begin()
    {
      return DequeIterator(Head);
    }

    // end() for iterators
    DequeIterator end()
    {
      return DequeIterator(nullptr);
    }

    // const begin() for iterators
    ConstDequeIterator begin() const
    {
      return ConstDequeIterator(Head);
    }

    // const end() for iterators
    ConstDequeIterator end() const
    {
      return ConstDequeIterator(nullptr);
    }

    // default constructor
    Deque() : Head(nullptr), Tail(nullptr)
    {
    }

    // constructor from initializer_list
    Deque(std::initializer_list<ValueType> List) : Head(nullptr), Tail(nullptr)
    {
      for (auto &i : List)
        PushTail(i);
    }

    // copy constructor
    Deque(Deque const & Other) : Head(nullptr), Tail(nullptr)
    {
      for (auto & i : Other)
        PushTail(i);
    }

    // move constructor
    Deque(Deque && Other) : Head(nullptr), Tail(nullptr)
    {
      this->Head = Other.Head;
      this->Tail = Other.Tail;
      Other.Head = nullptr;
      Other.Tail = nullptr;
    }

    // copy operator=
    Deque & operator=(Deque const & Other)
    {
      for (auto & i : Other)
        PushTail(*i);
      return *this;
    }

    // move operator=
    Deque & operator=(Deque && Other)
    {
      Clear();
      this->Head = Other.Head;
      this->Tail = Other.Tail;
      Other.Head = nullptr;
      Other.Tail = nullptr;
      return *this;
    }

    // destructor
    ~Deque()
    {
      Clear();
    }

    ///
    /// Operations
    ///

    // peek in head
    ValueType const & PeekHead(void) const
    {
      if (!Head)
        throw std::exception("Cannot Peek Head if Deque empty");
      return Head->Value;
    }

    // peek in tail
    ValueType const & PeekTail(void) const
    {
      if (!Tail)
        throw std::exception("Cannot Peek Tail if Deque empty");
      return Tail->Value;
    }

    // push in head
    void PushHead(ValueType const &Element)
    {
      DequeElement *tmp = (DequeElement *)Allocator.alloc(sizeof(DequeElement));
      tmp->Value = Element;
      tmp->Next = Head;
      tmp->Prev = nullptr;

      if (Head != nullptr)
        Head->Prev = tmp;

      Head = tmp;

      if (Tail == nullptr)
        Tail = Head;
    }

    // push in tail
    void PushTail(ValueType const &Element)
    {
      DequeElement *tmp = (DequeElement *)Allocator.alloc(sizeof(DequeElement));
      tmp->Value = Element;
      tmp->Next = nullptr;
      tmp->Prev = Tail;

      if (Tail != nullptr)
        Tail->Next = tmp;

      Tail = tmp;

      if (Head == nullptr)
        Head = Tail;
    }

    // pop from head
    void PopHead(void)
    {
      if (Head == nullptr)
        throw std::exception("Cannot Pop from empty deque");

      DequeElement *tmp = Head;
      Head = Head->Next;
      Allocator.dealloc((byte *)tmp);

      if (Head == nullptr)
        Tail = nullptr;
      else
        Head->Prev = nullptr;
    }

    // pop from tail
    void PopTail(void)
    {
      if (Tail == nullptr)
        throw std::exception("Cannot Pop from empty deque");

      DequeElement *tmp = Tail;
      Tail = Tail->Prev;
      Allocator.dealloc((byte *)tmp);

      if (Tail == nullptr)
        Head = nullptr;
      else
        Tail->Next = nullptr;
    }

    // move concatinate
    Deque & Concatinate(Deque && Other)
    {
      if (Tail == nullptr)
      {
        this->Head = Other.Head;
        this->Tail = Other.Tail;
        Other.Head = nullptr;
        Other.Tail = nullptr;
      }
      else
      {
        this->Tail->Next = Other.Head;
        Other.Head->Prev = this->Tail;

        this->Tail = Other.Tail;

        Other.Head = nullptr;
        Other.Tail = nullptr;
      }
      return *this;
    }

    // copy concatinate
    Deque & Concatinate(const Deque &Other)
    {
      for (auto &i : Other)
        PushTail(i);
      return *this;
    }

    // clear
    void Clear(void)
    {
      if (Head == nullptr)
        return;

      while (Head != nullptr)
        PopHead();
    }

    // IsEmpty
    bool IsEmpty(void)
    {
      return Head == nullptr;
    }
};
