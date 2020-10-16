#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

map<char, function<tuple<int,int>(int N1, int D1, int N2, int D2)>> operations = 
{
  { '+', [](int N1, int D1, int N2, int D2) { return tuple<int, int>(N1 * D2 + N2 * D1, D1 * D2); } },
  { '-', [](int N1, int D1, int N2, int D2) { return tuple<int, int>(N1*D2 - N2*D1, D1*D2); } },
  { '*', [](int N1, int D1, int N2, int D2) { return tuple<int, int>(N1*N2, D1*D2); } },
  { '/', [](int N1, int D1, int N2, int D2) { return tuple<int, int>(N1*D2, N2*D1); } }
};

tuple<int,int> Simplified(tuple<int,int>& v)
{
  int denominator = get<1>(v), numerator = get<0>(v);

  for (int i = denominator * numerator; i > 1; i--)
  {
      if ((denominator % i == 0) && (numerator % i == 0))
      {
          denominator /= i;
          numerator /= i;
      }
  }

  return tuple<int,int>(numerator, denominator);
}

ostream& operator << (ostream& os, const tuple<int, int>& v)
{
  os << get<0>(v) << '/' << get<1>(v);
  return os;
}

int main()
{
  int N;
  vector<tuple<int, int>> results;

  cin >> N;

  for (int i = 0; i < N; ++i)
  {
    int N1, D1, N2, D2;
    char div1, div2, op;

    cin >> N1 >> div1 >> D1 >> op >> N2 >> div2 >> D2;

    auto res = operations[op](N1, D1, N2, D2);
    results.push_back(res);
  }

  for (auto res : results)
  {
    cout << res << " = " << Simplified(res) << endl;
  }
}

