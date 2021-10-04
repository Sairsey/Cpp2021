#pragma once

#include <string>
#include <exception>
#include "MemoryHeapStrategy.h" // as default


/*!
  \brief Deque class
  \author Vladimir Parusov
  \version 1.0
  \see DequeIterator, ConstDequeIterator
  \tparam ValueType type of stored values
  \tparam MemoryStrategyType strategy of memory allocation
*/
template<class ValueType, class MemoryStrategyType = MemoryHeapStrategy>
class Deque
{
  private:
    
    /*! structure that represents an element of Deque. */
    struct DequeElement
    {
      ValueType Value;       /*!< Stored Value */
      DequeElement *Next;    /*!< Pointer on next element in deque (may be nullptr) */
      DequeElement *Prev;    /*!< Pointer on previous element in deque (may be nullptr) */
    };

    DequeElement *Head; /*!< Pointer on first element in deque (may be nullptr if Deque is empty) */
    DequeElement *Tail; /*!< Pointer on last element in deque (may be nullptr if Deque is empty) */

    MemoryStrategyType Allocator; /*!< Memory allocator which chosen by template */

  public:

    /*!
      \brief Default Iterator for Deque
      \warning Because i think range-for are cool
    */
    class DequeIterator
    {
    public:

      /*! Default constructor for DequeIterator */
      DequeIterator() : CurrentNode(Head)
      {
      }

      /*! Constructor from pointer on DequeElement 
       * \param[in] Node - pointer on element we want to build Iterator from
       */
      DequeIterator(DequeElement* Node) : CurrentNode(Node)
      {
      }

      /*! Operator= from from pointer on DequeElement 
       * \param[in] Node - pointer on element we want to build Iterator from
       */
      DequeIterator& operator=(DequeElement* Node)
      {
        this->CurrentNode = Node;
        return *this;
      }

      /*! Prefix ++ overload */
      DequeIterator& operator++()
      {
        if (CurrentNode)
          CurrentNode = CurrentNode->Next;
        return *this;
      }

      /*! Postfix ++ overload */
      DequeIterator operator++(int)
      {
        DequeIterator iterator = *this;
        ++*this;
        return iterator;
      }

      /*! Comparison operator.
       * \param[in] iterator - Operator we want to compare with
       * \return false if equals, true otherwise
       */
      bool operator!=(const DequeIterator& iterator)
      {
        return CurrentNode != iterator.CurrentNode;
      }

      /*! Operator *.
       * \return reference on Value this iterator represents
       */
      ValueType & operator*()
      {
        return CurrentNode->Value;
      }
    private:
      DequeElement* CurrentNode; /*!< Pointer on DequeElement this iterator represents */
    };

    /*!
     \brief Const Iterator for Deque
     */
    class ConstDequeIterator
    {
    public:
      /*! Default constructor for DequeIterator */
      ConstDequeIterator() : CurrentNode(Head)
      {
      }

      /*! Constructor from pointer on DequeElement
       * \param[in] Node - pointer on element we want to build Iterator from
       */
      ConstDequeIterator(const DequeElement* Node) : CurrentNode(Node)
      {
      }

      /*! Operator= from from pointer on DequeElement
       * \param[in] Node - pointer on element we want to build Iterator from
       */
      ConstDequeIterator& operator=(DequeElement* Node)
      {
        this->CurrentNode = Node;
        return *this;
      }

      /*! Prefix ++ overload */
      ConstDequeIterator& operator++()
      {
        if (CurrentNode)
          CurrentNode = CurrentNode->Next;
        return *this;
      }

      /*! Postfix ++ overload */
      ConstDequeIterator operator++(int)
      {
        ConstDequeIterator iterator = *this;
        ++*this;
        return iterator;
      }

      /*! Comparison operator.
       * \param[in] iterator - Operator we want to compare with
       * \return false if equals, true otherwise
       */
      bool operator!=(const ConstDequeIterator& iterator)
      {
        return CurrentNode != iterator.CurrentNode;
      }

      /*! Operator *.
       * \return reference on Value this iterator represents
       */
      const ValueType & operator*()
      {
        return CurrentNode->Value;
      }

    private:
      const DequeElement* CurrentNode; /*!< Pointer on DequeElement this iterator represents */
    };

    /*! function begin for iterator support
     * \return DequeIterator that represents first element
     */
    DequeIterator begin()
    {
      return DequeIterator(Head);
    }

    /*! function end for iterator support
     * \return DequeIterator that represents element after last
     */
    DequeIterator end()
    {
      return DequeIterator(nullptr);
    }

    /*! function cbegin for const iterator support
     * \return ConstDequeIterator that represents first element
     */
    ConstDequeIterator cbegin() const
    {
      return ConstDequeIterator(Head);
    }

    /*! function cend for const iterator support
     * \return ConstDequeIterator that represents last element
     */
    ConstDequeIterator cend() const
    {
      return ConstDequeIterator(nullptr);
    }

    /*! Default constructor for Deque */
    Deque() : Head(nullptr), Tail(nullptr)
    {
    }

    /*! Constructor from initializer_list
     *  \param[in] List initializer list from template ValueType 
     */
    Deque(std::initializer_list<ValueType> List) : Head(nullptr), Tail(nullptr)
    {
      for (auto &i : List)
        PushTail(i);
    }

    /*! Copy constructor
     *  \param[in] Other const reference on lvalue element
     */
    Deque(Deque const & Other) : Head(nullptr), Tail(nullptr)
    {
      for (auto & i : Other)
        PushTail(i);
    }

    /*! Move constructor
     *  \param[in] Other rvalue reference on rvalue element
     */
    Deque(Deque && Other) : Head(nullptr), Tail(nullptr)
    {
      this->Head = Other.Head;
      this->Tail = Other.Tail;
      Other.Head = nullptr;
      Other.Tail = nullptr;
    }

    /*! Copy operator=
     *  \param[in] Other const reference on lvalue element
     */
    Deque & operator=(Deque const & Other)
    {
      for (auto & i : Other)
        PushTail(*i);
      return *this;
    }

    /*! Move operator=
     *  \param[in] Other rvalue reference on rvalue element
     */
    Deque & operator=(Deque && Other)
    {
      Clear();
      this->Head = Other.Head;
      this->Tail = Other.Tail;
      Other.Head = nullptr;
      Other.Tail = nullptr;
      return *this;
    }

    /*! Destructor */
    ~Deque()
    {
      Clear();
    }

    /*! Method to see what first element is. Cannot be modified.
     *  \returns const reference on element
     */
    ValueType const & PeekHead(void) const
    {
      if (!Head)
        throw std::exception("Cannot Peek Head if Deque empty");
      return Head->Value;
    }

    /*! Method to see what last element is. Cannot be modified.
     *  \returns const reference on element
     */
    ValueType const & PeekTail(void) const
    {
      if (!Tail)
        throw std::exception("Cannot Peek Tail if Deque empty");
      return Tail->Value;
    }

    /*! Method to get first element. Can be modified.
     *  \returns reference on element
     */
    ValueType & GetHead(void) const
    {
      if (!Head)
        throw std::exception("Cannot Get Head if Deque empty");
      return Head->Value;
    }

    /*! Method to get last element. Can be modified.
     *  \returns reference on element
     */
    ValueType & GetTail(void) const
    {
      if (!Tail)
        throw std::exception("Cannot Peek Tail if Deque empty");
      return Tail->Value;
    }

    /*! Method put element to begin of deque. Using copy semantics
     *  \param[in] Element const reference on element(lvalue)
     */
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

    /*! Method put element to end of deque. Using copy semantics
     *  \param[in] Element const reference on element(lvalue)
     */
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

    /*! Method put element to begin of deque. Using move semantics
     *  \param[in] Element rvalue reference on element
     */
    void PushHead(ValueType &&Element)
    {
      DequeElement *tmp = (DequeElement *)Allocator.alloc(sizeof(DequeElement));
      tmp->Value = std::move(Element);
      tmp->Next = Head;
      tmp->Prev = nullptr;

      if (Head != nullptr)
        Head->Prev = tmp;

      Head = tmp;

      if (Tail == nullptr)
        Tail = Head;
    }

    /*! Method put element to end of deque. Using move semantics
     *  \param[in] Element rvalue reference on element
     */
    void PushTail(ValueType &&Element)
    {
      DequeElement *tmp = (DequeElement *)Allocator.alloc(sizeof(DequeElement));
      tmp->Value = std::move(Element);
      tmp->Next = nullptr;
      tmp->Prev = Tail;

      if (Tail != nullptr)
        Tail->Next = tmp;

      Tail = tmp;

      if (Head == nullptr)
        Head = Tail;
    }

    /*! Method to remove first element from deque. */
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

    /*! Method to remove first element from deque. */
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

    /*! Method to concatinate to Deques together. Using move semantics.
     * \param[in] Other rvalue reference on other element
     * \returns refernece on self
     */
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

    /*! Method to concatinate to Deques together. Using copy semantics.
     * \param[in] Other const reference on other element
     * \returns refernece on self
     */
    Deque & Concatinate(const Deque &Other)
    {
      for (auto &i : Other)
        PushTail(i);
      return *this;
    }

    /*! Method to clear deque. */
    void Clear(void)
    {
      if (Head == nullptr)
        return;

      while (Head != nullptr)
        PopHead();
    }

    /*! Method for checking if deque is empty
     * \returns true if empty, false otherwise
     */
    bool IsEmpty(void)
    {
      return Head == nullptr;
    }
};
