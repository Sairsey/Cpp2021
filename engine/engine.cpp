#include "Engine.h"

struct Subject
{
  int f3(int a, int b)
  {
    return a - b;
  }
};

int main(void)
{
  Subject subj;

  Wrapper wrap(&subj, &Subject::f3, { {"arg1", 0 }, {"arg2", 0 } });
  Wrapper wrap2(&subj, &Subject::f3, { {"arg1", 0 }, {"arg2", 0 } });

  Engine engine;
  engine.register_command(&wrap, "command1");
  engine.register_command(&wrap, "command2");
  std::cout << engine.execute("command1", { {"arg1", 4}, {"arg2", 5} }) << std::endl;
  std::cout << engine.execute("command2", { {"arg2", 30}, {"arg1", 123} }) << std::endl;

}
