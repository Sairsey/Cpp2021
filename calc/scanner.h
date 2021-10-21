#pragma once
#include <string>
#include <memory>

#include "token.h"

class scanner
{
  private:
    token_queue my_queue;
  public:

  // scan string and translate it to token_queue
  token_queue& scan(const std::string& expression);

  // clean memory
  void cleanQueue(void);

  // Destructor
  ~scanner();
};