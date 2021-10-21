#pragma once

#include <string>
#include "scanner.h"
#include "parser.h"
#include "evaluator.h"

/*!
  \brief Calculator class
  \author Vladimir Parusov
  \version 1.0
  \see plugin_loader, scanner, parser, evaluator,
*/
class calc
{
  /*! instance of class which can load operations and functions from plugins and 
   * responsible for closing handle
   */
  plugin_loader plugins;

  /*! instance of class which can transform string into queue of tokens and
   * responsible for deleting them
   */
  scanner scan;

  /*! instance of class which can transform queue to Reverse Polish Notation queue */
  parser parse;

  /*! instance of class which can evaluate Reverse Polish Notation queue */
  evaluator eval;
public:
  /*! default constuctor */
  calc();

  /*! run calculaton from string
   * \warning can throw std::exception if string is incorrect
   * \param[in] expression - string with expression
   * \return result of calculation
   */
  double calculate(const std::string& expression);
};