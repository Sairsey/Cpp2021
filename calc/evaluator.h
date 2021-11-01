#pragma once
#include <map>
#include "token.h"
#include "plugin_loader.h"

/*!
  \brief Evaluator of RPN queue`s class
  \author Vladimir Parusov
  \version 1.0
  \see calc
*/
class evaluator
{
private:
  //! Table which stores all known binary operations
  binary_table operations;
  //! Table which stores all known unary functions
  unary_table functions;

  //! Stack used for evaluation
  token_stack evaluation_stack;

  //! Helper function to process Numbers
  void processNumber(token_number *t);

  //! Helper function to process operations
  void processOperation(token_operation *t);

  //! Helper function to process functions
  void processFunction(token_function *t);

  //! Helper function to process elements from unary_table
  void processUnary(std::string &symbol);

  //! Helper function to process elements from binary_table
  void processBinary(std::string &symbol);

public:
  /*! Set table of operations and functions
   * \param[in] op - table with binary operations
   * \param[in] func - table with unary functions
   */
  void set_op(binary_table& op, unary_table& func)
  {
      operations = op;
      functions = func;
  }

  /*! Evaluate RPN queue
   * \param[in] rpn_tokens - RPN queue
   * \returns result of evaluation
   */
  double eval(token_queue rpn_tokens);
};