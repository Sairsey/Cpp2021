#pragma once
#include "def.h"

template<int N>
struct variadicVector;

/*!
  \brief specification to end recursion
  \author Vladimir Parusov
  \tparam N amount of elements in that array
  \version 1.0
  \see variadicVector
*/
template<>
struct variadicVector<1>
{
  //! element that stored in N-th position in this array
  argument head_;

  /*! Default constructor
   * \param[in] list - array with arguments
   * \param[in] index - index where we must retrieve
   */
  variadicVector(const argument list[], int index = 0) : head_(list[index])
  {
  }

  /*! Call Function F from class Cl with arguments retrieved from this variadicVector
   * \param[in] Cl - Class where we want to grab function
   * \param[in] F - function we want to call
   * \param[in] args - Our unpacked by variadicTemplate arguments
   * \returns result of the function
   */
  template<typename ClassType, typename FuncType, typename ...Args>
  int callBind(ClassType* Cl, FuncType F, Args ...args)
  {
    return std::bind(F, Cl, args..., head_.second)();
  }
};

/*!
  \brief class that can transform array values to values acceptable to variadic templates
  \author Vladimir Parusov
  \tparam N amount of elements in that array
  \version 1.0
  \see variadicVector
*/
template<int N>
struct variadicVector : variadicVector<N - 1>
{
  //! for simplicity
  using base_type = variadicVector<N - 1>;
  //! Pointer on base class to retrive it`s head_
  base_type &base = static_cast<base_type &>(*this);
  
  //! element that stored in position in this array
  argument head_;

  /*! Default constructor
   * \param[in] list - array with arguments
   * \param[in] index - index where we must retrieve
   */
  variadicVector(const argument* list, int index = 0) : variadicVector<N - 1>(list, index + 1), head_(list[index])
  {
  /*
    this thing works this way:
    1) we save our value(with our index) to variable in this class
    2) we call constructor of our parent so he will do the same untill N becomes 1

    Then if we call callBind, we start to building variadic Template by passing to it our variable and calling this function from base
    In the end we have beautiful numbers from array that passed as arguments to std::bind.
  */
  }

  /*! Call Function F from class Cl with arguments retrieved from this variadicVector
   * \param[in] Cl - Class where we want to grab function
   * \param[in] F - function we want to call
   * \param[in] args - Our unpacked by variadicTemplate arguments
   * \returns result of the function
   */
  template<typename ClassType, typename FuncType, typename ...Args>
  int callBind(ClassType* Cl, FuncType F, Args ...args)
  {
    return base.callBind(Cl, F, args..., head_.second);
  }
};