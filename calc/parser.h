#pragma once
#include <map>
#include "token.h"

// will transform to RPN
class parser
{
  private:
    token_queue rns_queue;

    // fot state machine
    typedef enum {
      STATE_PREFIX, STATE_SUFFIX, STATE_DONE, STATE_END
    } state_t;

    state_t doPrefix(token* t, token_stack& numbers, token_stack& oper);
    state_t doPostfix(token* t, token_stack& numbers, token_stack& oper);
    state_t doDone(token* t, token_stack& numbers, token_stack& oper);
    void sendOperators(token* op, token_stack& numbers, token_stack& oper);
    bool checkAssoc(token *op1, token *op2);
    int getPrior(token* op);

  public:

    //parsed string and translate it to token_queue
    token_queue& parse(token_queue tokens);

    // clean memory
    void cleanQueue(void);
};