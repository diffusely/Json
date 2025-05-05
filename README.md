# 📦 JSON Parser in C++

A lightweight JSON parser and validator written in modern C++. This project allows you to parse, validate, and pretty-print JSON files using a simple object-oriented API.

---

## 📁 Project Structure

- **`Json`**: Core class that represents JSON values — object, array, string, number, boolean, and null.
- **`JsonValid`**: Validates JSON file syntax before parsing.
- **`JsonSrl`**: Responsible for reading and parsing JSON files into usable `Json` objects.

---


## 🧱 Supported JSON Types

| Type     | Example                         |
|----------|----------------------------------|
| String   | `"hello"`                       |
| Number   | `123`, `3.14`                   |
| Boolean  | `true`, `false`                 |
| Null     | `null`                          |
| Array    | `[1, 2, 3]`                     |
| Object   | `{ "key": "value" }`            |

---

## ⚙️ Build Instructions

```bash
make


#include "json.hpp"
#include "json_valid.hpp"
#include "json_srl.hpp"

int main() 
{
    Json j = JsonSrl::load("example.json");
    j.print();  // Pretty-print the loaded JSON
}