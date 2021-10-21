#include "scanner.h"

void scanner::cleanQueue(void)
{
  while (!my_queue.empty())
  {
    delete my_queue.front();
    my_queue.pop();
  }
}

/* Scan Queue from string */
token_queue &scanner::scan(const std::string &expression)
{
  if (my_queue.size() != 0)
    cleanQueue();

  int index = 0;
  while (index < expression.size()) 
  {
    /* Remove spaces */
    if (isspace(expression[index])) 
    {
      index++;
      continue;
    }
    switch (expression[index]) 
    {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '.':
      {
        token_number *T = new token_number;
        std::string::size_type new_index;
        T->value = std::stod(expression.substr(index), &new_index);
        my_queue.push(T);
        index += new_index;
        break;
      }
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
      case '(':
      case ')':
      {
        token_operation * T = new token_operation;
        T->symbol = expression[index++];
        my_queue.push(T);
        break;
      }
      default:
      {
        /* Read symbols */
        if (isalpha(expression[index])) 
        {
          char buf[300] = { 0 };
          int i = 0;
          do 
          {
            if (i < 300 - 1) 
              buf[i++] = expression[index];
            index++;
          } while (isalpha(expression[index]));

          token_function* T = new token_function;
          T->name = buf;
          my_queue.push(T);
          break;
        }
        /* if unknown symbol */
        {
          cleanQueue();
          throw std::exception("Unknown symbol in Scanner");
        }
        break;
      }
    }
  }
  return my_queue;
}

scanner::~scanner()
{
  cleanQueue();
}