#pragma once
#include <string>
#include <queue>
#include <stack>

/*!
  \brief Base token class. Token is an abstraction which covers numbers, functions and operations.
  \author Vladimir Parusov
  \version 1.0
  \see token_number, token_operation, token_function, calc, scanner
*/
struct token
{
  //! For simple Real Time Type Identefication (RTTI)
  enum
  {
    token_type_number,    //!< token which represents number
    token_type_operation, //!< token which represents operation
    token_type_function   //!< token which represents function
  } type; //!< type of current token

  virtual ~token() = default;
};

/*!
  \brief Number token class
  \author Vladimir Parusov
  \version 1.0
  \see calc, token
*/
struct token_number : public token
{
  double value; //!< value of this number

  //! default constructor which just fill fields in base token
  token_number()
  {
    type = token_type_number;
  }

  virtual ~token_number() = default;
};

/*!
  \brief operation token class
  \author Vladimir Parusov
  \version 1.0
  \see calc, token
*/
struct token_operation : public token
{
  std::string symbol;    //!< symbol that this operation have
  bool is_unary = false; //!< true for unary operations

  //! default constructor which just fill fields in base token
  token_operation()
  {
    type = token_type_operation;
  }

  virtual ~token_operation() = default;
};

/*!
  \brief operation token class
  \author Vladimir Parusov
  \version 1.0
  \see calc, token
*/
struct token_function : public token
{
  std::string name; //!< name of this function

  //! default constructor which just fill fields in base token
  token_function()
  {
    type = token_type_function;
  }

  virtual ~token_function() = default;
};

//! Queue of pointer on tokens
using token_queue = std::queue<token *>;
//! Stack of pointer on tokens
using token_stack = std::stack<token *>;

#ifdef _DEBUG
#define DEBUG_NEW_PLACEMENT (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW_PLACEMENT
#endif
