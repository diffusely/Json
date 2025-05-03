#include "json.hpp"
#include "json_valid.hpp"

int main()
{
    std::string name = "test.txt";

    JsonValid j(name);

    std::cout << j.validate();
    return 0;
}
