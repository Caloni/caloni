#include <string>
#include <iostream>

#define switch(a) auto switch_cmp = a;
#define case(a) if( switch_cmp == a )

int main()
{
    std::string test = "3";

    switch(test)
    {
        case("1")
        {
            std::cout << "1\n";
        }
        case("2")
        {
            std::cout << "2\n";
        }
        case("3")
        {
            std::cout << "3\n";
        }
    }
}

