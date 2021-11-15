#pragma once
#include "def.h"
#include "variadicVector.h"

/*!
  \brief Base class for template wrappers
  \author Vladimir Parusov
  \version 1.0
  \see Engine, Wrapper, Wrapper_templated
*/
class Wrapper_base
{
public:
  /*! method that will be overriden by Wrapper_templated
   * \param[in] args - Our array of arguments
   * \param[in] NumberOfElements - amount of that elements
   */
  virtual int execute(const argument(&args)[], int NumberOfElements) = 0;
};

/*!
  \brief Template class for wrappers
  \author Vladimir Parusov
  \version 1.0
  \see Engine, Wrapper, Wrapper_base
*/
template <typename ClassType, typename FuncType, int N>
class Wrapper_templated : public Wrapper_base
{
private:
  //! our array of arguments
  std::vector<argument> Arguments;
  //! structure for fast replacing values in Arguments
  std::unordered_map<std::string, argument*> FindMap;
  //! Class where we want to grab function
  ClassType* Class;
  //! function we want to call
  FuncType Func;

public:
  Wrapper_templated(void) = delete;

  /*! Contructor of Wrapper from Class, Function and array of arguments
  * \param[in] Cl - Class where we want to grab function
  * \param[in] F - function we want to call
  * \param[in] args - Our array of arguments
  */
  Wrapper_templated(ClassType* Cl, FuncType F, const argument(&args)[N])
  {
    // save function and class
    Func = F;
    Class = Cl;

    // save arguments in order we got them
    for (int i = 0; i < N; i++)
      Arguments.push_back(args[i]);

    // put pointers for fast replacing
    for (int i = 0; i < N; i++)
      FindMap[args[i].first] = &Arguments[i];
  }

  /*! method that will call our function with right arguments
   * \param[in] args - Our array of arguments
   * \param[in] NumberOfElements - amount of that elements
   */
  virtual int execute(const argument(&args)[], int NumberOfElements)
  {
    // incorrect size - error
    if (NumberOfElements != N)
      throw "error";

    // replace all params with that
    for (int i = 0; i < NumberOfElements; i++)
      FindMap[args[i].first]->second = args[i].second;

    // build some structure that can call function with unpacked array
    variadicVector<N> V(&(Arguments[0]));

    // and finally call it
    return V.callBind(Class, Func);
  }
};

/*!
  \brief Wrapper of classes methods to call
  \author Vladimir Parusov
  \version 1.0
  \see Engine, Wrapper_base, Wrapper_templated
*/
class Wrapper
{
private:
  //! pointer to base templated type
  Wrapper_base *wrapper;
public:

  /*! Contructor of Wrapper from Class, Function and array of arguments
   * \param[in] Cl - Class where we want to grab function
   * \param[in] F - function we want to call
   * \param[in] args - Our array of arguments
   */
  template <typename ClassType, typename FuncType, int N>
  Wrapper(ClassType* Cl, FuncType F, const argument(&args)[N])
  {
    wrapper = new Wrapper_templated<ClassType, FuncType, N>(Cl, F, args);
  }

  /*! method that called by Engine to start
   * \param[in] args - Our array of arguments
   * \param[in] NumberOfElements - amount of that elements
   */
  int execute(const argument(&args)[], int NumberOfElements)
  {
    return wrapper->execute(args, NumberOfElements);
  }
};
