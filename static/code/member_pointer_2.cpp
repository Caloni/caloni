#include <iostream>
#include <time.h>

class Rand;
typedef void (Rand::*FP)();
typedef int Rand::*MP;

class Rand
{
public:
  Rand()
  {
    m_num = rand() % 100;
  }

  int m_num;

  void Print()
  {
    std::cout << "this: " 
      << std::hex << this 
      << ", member: " 
      << std::dec << m_num
      << std::endl;
  }
};

/** No princípio Deus disse: 
    'int main!'
*/
int main()
{
  srand(time(NULL));

  Rand r1, r2, r3;
  FP fp = &Rand::Print;
  MP mp = &Rand::m_num;

  (r1.*fp)();
  (r2.*fp)();
  (r3.*fp)();

  std::cout << std::endl;
  
  std::cout << "this: " 
    << std::hex << &r1 
    << ", member: " 
    << std::dec << r1.*mp 
    << std::endl;

  std::cout << "this: " 
    << std::hex << &r2 
    << ", member: " 
    << std::dec << r2.*mp 
    << std::endl;

  std::cout << "this: " 
    << std::hex << &r3 
    << ", member: " 
    << std::dec << r3.*mp 
    << std::endl;
} 
