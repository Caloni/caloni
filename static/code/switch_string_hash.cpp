#include <string>
#include <iostream>

enum string_code
{
    sc_1,
    sc_2,
    sc_3,
    sc_none
};

string_code hashit(std::string const& inString)
{
    if (inString == "1") return sc_1;
    if (inString == "2") return sc_2;
    if (inString == "3") return sc_3;
    return sc_none;
}

int main()
{
    switch (hashit("3"))
    {
        case sc_1:
            std::cout << "1\n";
            break;

        case sc_2:
            std::cout << "2\n";
            break;

        case sc_3:
            std::cout << "3\n";
            break;

        default:
            std::cout << "none\n";
            break;
    }
}
