# Json

📦 JSON Parser in C++

This project is a basic JSON parser and validator written in C++. It includes:

-Json: the main class representing JSON values (objects, arrays, strings, etc.)

-JsonValid: validates whether a file contains valid JSON syntax

-JsonSrl: handles reading and parsing JSON files into Json objects


 It supports basic JSON types such as:

-Strings
-Numbers (integers and floats)
-Booleans (true, false)
-Null
-Arrays
-Objects

⚙️ How to Build

make

🧪 Example Usage

#include "json.hpp"
#include "json_valid.hpp"
#include "json_srl.hpp"

int main() 
{
    Json j = JsonSrl::load("example.json");
    j.print();  // Pretty-print the loaded JSON
}
