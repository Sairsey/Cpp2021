// deque.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "deque.h"

template<class ValueType>
void printDeque(Deque<ValueType> d)
{
  for (auto &i : d)
    std::cout << i << " ";

  std::cout << std::endl;
}

int main()
{
  // check default constructor
  Deque<int> deque1;
  printDeque(deque1);

  // check initializer list constructor
  Deque<int> deque2({ 1, 2, 3, 4, 5 });
  printDeque(deque2);

  // check copy constructor
  Deque<int> deque3(deque2);
  printDeque(deque3);

  // check move constructor
  Deque<int> deque4(Deque<int>({ 1, 2, 3, 4, 5 }));
  printDeque(deque4);

  // check copy operator=
  Deque<int> deque5 = deque2;
  printDeque(deque5);

  // check move operator=
  Deque<int> deque6 = Deque<int>({ 1, 2, 3, 4, 5 });
  printDeque(deque6);

  // check PeekHead
  std::cout << deque2.PeekHead() << std::endl;

  // check PeekTail
  std::cout << deque6.PeekTail() << std::endl;

  // check PushHead
  deque3.PushHead(30);
  printDeque(deque3);

  // check PushTail
  deque4.PushTail(47);
  printDeque(deque4);

  // check PopHead
  deque2.PopHead();
  printDeque(deque2);

  // check PopTail
  deque5.PopTail();
  printDeque(deque5);

  // check move concatinate
  printDeque(Deque<int>({1, 2, 3, 4, 5}).Concatinate({6, 7, 8, 9, 10}));
  
  // check copy concatinate
  printDeque(Deque<int>({ 1, 2, 3, 4, 5 }).Concatinate(deque2));

  // check clear and IsEmpty
  std::cout << deque2.IsEmpty() << std::endl;
  deque2.Clear();
  std::cout << deque2.IsEmpty() << std::endl;
	return 0;
}
