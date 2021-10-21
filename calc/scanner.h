#pragma once
#include <string>
#include <memory>

#include "token.h"

/*!
  \brief Scanner and allocator of tokens.
  \author Vladimir Parusov
  \version 1.0
  \see calc, token
*/
class scanner
{
  private:
    token_queue my_queue; //!< resulting queue
  public:

  /*! Scan string and translate it to token_queue
   * \param[in] expression - string we want to translate
   * \return queue of tokens
   */
  token_queue& scan(const std::string& expression);

  //! Clean allocated memory
  void cleanQueue(void);

  //! Destructor
  ~scanner();
};