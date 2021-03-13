#include <iostream>
#include <time.h>

class Rand;

typedef void (Rand::*FP)();

class Rand
{
  public:
    Rand()
    {
      srand(time(NULL));
    }

    FP GiveMeFunc()
    {
      return m_funcs[rand() % 3];
    }

  private:
    void FuncOne()   { std::cout << "One!\n"; }
    void FuncTwo()   { std::cout << "Two!\n"; }
    void FuncThree() { std::cout << "Three!\n"; }

    static FP m_funcs[3];
};

FP Rand::m_funcs[3] = { &FuncOne, &FuncTwo, &FuncThree };

void passThrough(FP fp)
{
  Rand r;
  ( r.*fp )(); // <<-- this
}

/** No princípio Deus disse:
  'int main!'
 */
int main()
{
  Rand r;
  FP fp;

  fp = r.GiveMeFunc();
  passThrough(fp);
}
