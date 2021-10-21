#pragma once
#include <map>
#include "token.h"
#include "plugin_loader.h"

class evaluator
{
private:
  binary_table operations;
  unary_table functions;
public:
  void set_op(binary_table& op, unary_table& func)
  {
      operations = op;
      functions = func;
  }
  //parsed string and translate it to token_queue
  double eval(token_queue rpn_tokens);
};