#pragma once

#include <string>
#include "scanner.h"
#include "parser.h"
#include "evaluator.h"

class calc
{
  // load plugins
  plugin_loader plugins;

  // will translate string to queue
  scanner scan;

  // will translate queue to RPN queue
  parser parse;

  // will evaluate RPN expression
  evaluator eval;
public:
  // default constuctor
  calc();

  /* Calculate from string */
  double calculate(const std::string& expression);
};