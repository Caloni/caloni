#include <iostream>
#include <typeinfo>

#define POLYMORPHISM 1

using namespace std;

class Base
{
public:
  Base()
  {
    cout << "Base()\n";
    m_x = 0;
  }

#if POLYMORPHISM
  virtual ~Base()
#else
  ~Base()
#endif
  {
    cout << "~Base()\n";
  }

  int m_x;
};

class Deriv : public Base
{
public:
  Deriv()
  {
    cout << "Deriv()\n";

    m_x = 1;
    m_y = 0;
  }

  virtual ~Deriv()
  {
    cout << "~Deriv()\n";
  }

  int m_y;
};

void func(Base* b)
{
  cout << typeid(*b).name() << '\n';
}

int main()
{
  Base* b = new Deriv();
  func(b);
} 
