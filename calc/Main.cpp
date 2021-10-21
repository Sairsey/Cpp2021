#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>
#include <sstream>
#include "calc.h"

int main(int argc, char* argv[]) {
  calc calc;
  std::string string;
  double rez = 0;

  while (true)
  {
    int i = 0;
    int len;
    std::getline(std::cin, string);
    if (string.size() == 0) {
      break;
    }

    len = string.length();
    // Skip all space symbols
    for (i = 0; i < len; i++) {
      if (isspace(string[i]) == 0) {
        break;
      }
    }

    if (i == string.length()) {/* If space */
      printf("%s\n", string.c_str());
      continue;
    }
    if (i < len && string[i] == '/' && string[i + 1] == '/') { /* If a comment */
      printf("%s\n", string.c_str());
      continue;
    }
    printf("%s == ", string.c_str());

    try
    {
      rez = calc.calculate(string);
      printf("%g\n", rez);
    }
    catch (std::exception& ex)
    {
      printf("ERROR : %s\n", ex.what());
    }
  }
  _CrtDumpMemoryLeaks();
  return 0;
}