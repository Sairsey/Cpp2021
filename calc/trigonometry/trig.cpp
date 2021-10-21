#include <Windows.h>
#include "../plugin_loader.h"

unary_table my_unary_table;

extern "C" __declspec(dllexport) unary_table & RetriveUnary(void)
{
  my_unary_table["sin"].func = [](double a) -> double {return sin(a); };
  my_unary_table["cos"].func = [](double a) -> double {return cos(a); };
  return my_unary_table;
}