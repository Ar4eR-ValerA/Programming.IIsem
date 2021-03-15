#include <iostream>
#include "src\pugixml.hpp"

int main() {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("qwe", 256);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}