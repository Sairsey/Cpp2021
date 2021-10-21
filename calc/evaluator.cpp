#include "evaluator.h"

double evaluator::eval(token_queue rpn_queue)
{
  token *t, *a, *b;
  token_stack evaluation_stack;
  while (!rpn_queue.empty())
  {
    t = rpn_queue.front();
    rpn_queue.pop();
    if (t->type == token::token_type_number)
    {
      evaluation_stack.push(t);
    }
    else if (t->type == token::token_type_function)
    {
      token_function *tmp = (token_function*)t;
      if (functions.find(tmp->name) == functions.end())
      {
        throw std::exception("No such function");
      }

      if (evaluation_stack.empty() || 
        evaluation_stack.top()->type != token::token_type_number)
        throw std::exception("invalid function argument");
      
      a = evaluation_stack.top();
      evaluation_stack.pop();
      token_number *a_num = (token_number *)a;
      
      a_num->value = functions[tmp->name].func(a_num->value);

      evaluation_stack.push(a);
    }
    else if (t->type == token::token_type_operation)
    {
      token_operation *op = (token_operation *)t;

      if (op->symbol == "@")
      {
        a = evaluation_stack.top();
        evaluation_stack.pop();
        if (a->type != token::token_type_number)
          throw std::exception("invlaid operand");
        token_number* a_num = (token_number*)a;
        a_num->value = -a_num->value;
        evaluation_stack.push(a);
      }
      else
      {
        if (operations.find(op->symbol) == operations.end())
        {
          throw std::exception("No such operation");
        }

        a = evaluation_stack.top();
        evaluation_stack.pop();
        b = evaluation_stack.top();
        evaluation_stack.pop();
        if (a->type != token::token_type_number ||
          b->type != token::token_type_number)
          throw std::exception("invlaid operands");
        token_number* a_num = (token_number*)a;
        token_number* b_num = (token_number*)b;

        a_num->value = operations[op->symbol].func(b_num->value, a_num->value);

        evaluation_stack.push(a);
      }
    }
  }
  t = evaluation_stack.top();
  if (evaluation_stack.size() > 1 ||
    t->type != token::token_type_number)
  {
    throw std::exception("Incorrect expression");
  }
  return ((token_number*)t)->value;
}