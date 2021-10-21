#pragma once
#include <string>
#include <queue>
#include <stack>

struct token
{
  enum // for simple RTTI
  {
    token_type_number,
    token_type_operation,
    token_type_function
  } type;
};

struct token_number : public token
{
  double value;

  token_number()
  {
    type = token_type_number;
  }
};

struct token_operation : public token
{
  std::string symbol; // symbol that this operation have

  token_operation()
  {
    type = token_type_operation;
  }
};

struct token_function : public token
{
  std::string name; // name of this function

  token_function()
  {
    type = token_type_function;
  }
};

using token_queue = std::queue<token *>;
using token_stack = std::stack<token *>;
