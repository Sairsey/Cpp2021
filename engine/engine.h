// Engine.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include "def.h"
#include "wrapper.h"


/*!
  \brief Executor of commands class
  \author Vladimir Parusov
  \version 1.0
  \see Wrapper
*/
class Engine
{
private:
  //! unordered map of pointers on Wrappers by given name
  std::unordered_map<std::string, Wrapper*> Commands;
public:

  /*! register Wrapper to system
   * \param[in] wrap - Wrapper with function
   * \param[in] name - name of that function
   */
  void register_command(Wrapper* wrap, std::string name)
  {
    Commands[name] = wrap;
  }

  /*! Execute one of wrappers by name and array of arguments
   * \param[in] name - name of that function
   * \param[in] Args - array of N arguments.
   */
  template<int N>
  int execute(std::string command, const argument(&Args)[N])
  {
    return Commands[command]->execute((const argument (&)[])Args, N);
  }
};