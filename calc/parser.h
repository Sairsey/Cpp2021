#pragma once
#include <map>
#include "token.h"

/*!
  \brief Parser from queue to RPN queue
  \author Vladimir Parusov
  \version 1.0
  \see calc
*/
class parser
{
  private:
    //! Result queue with tokens.
    token_queue rns_queue;

    //! States for state-machine based algorithm
    enum state_t {
      STATE_PREFIX, STATE_SUFFIX, STATE_DONE, STATE_END
    };

    /*! Provide actions for STATE_PREFIX
     * \param[in] t - Current token
     * \param[in] numbers - stack which contatin numbers
     * \param[in] oper - stack which contatin operations and functions
     * \return next state
     */
    state_t doPrefix(token* t, token_stack& numbers, token_stack& oper);

    /*! Provide actions for STATE_SUFFIX
     * \param[in] t - Current token
     * \param[in] numbers - stack which contatin numbers
     * \param[in] oper - stack which contatin operations and functions
     * \return next state
     */
    state_t doPostfix(token* t, token_stack& numbers, token_stack& oper);

    /*! Provide actions for STATE_DONE
     * \param[in] t - Current token
     * \param[in] numbers - stack which contatin numbers
     * \param[in] oper - stack which contatin operations and functions
     * \return next state
     */
    state_t doDone(token* t, token_stack& numbers, token_stack& oper);

    /*! Send operators from stack with operators to stack with numbers so
     * token op can be added to stack oper
     * \param[in] op - Current token
     * \param[in] numbers - stack which contatin numbers
     * \param[in] oper - stack which contatin operations and functions
     */
    void sendOperators(token* op, token_stack& numbers, token_stack& oper);

    /*! check which of operators has higher proprity
     * \param[in] op1 - first token
     * \param[in] op2 - second token
     * \return TRUE if op1 has higher priority than op2
     */
    bool checkAssoc(token *op1, token *op2);

    /*! Get priority for token op
     * \param[in] op token of function or operator
     * \return priority of this token
     */
    int getPrior(token* op);

  public:
   /*! parse queue and transform it to RPN queue
    * \param[in] tokens queue of tokens
    * \return queue of tokens in RPN
    */
    token_queue& parse(token_queue tokens);
};