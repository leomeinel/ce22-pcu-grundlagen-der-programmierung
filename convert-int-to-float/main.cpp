/*
 * File: main.cpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>

void print_result(auto result) {
  std::cout << "As " << typeid(result).name() << ": " << result << "\n";
}

int main(int argc, char *argv[]) {
  using namespace std::literals;

  std::cout << "INFO: This program converts any integer to either a float or a "
            << "double."
            << "\n";

  int precision;
  std::cout << "Choose precision as int: ";
  std::cin >> precision;
  std::cout << std::fixed << std::setprecision(precision);

  int convert_from;
  std::cout << "Integer to convert: ";
  std::cin >> convert_from;

  std::string expected_types[] = {"float"s, "f.*"s, "double"s, "d.*"s};
  std::cout << "\n" << "Valid target types: " << "\n";
  for (std::string type : expected_types) {
    std::cout << "\t" << type << "\n";
  }
  std::string choice;
  std::cout << "Choose target type: ";
  std::cin >> choice;
  if (choice.starts_with("f")) {
    std::cout << "Converting " << convert_from << " to float." << "\n";
    print_result((float)convert_from);
  } else if (choice.starts_with("d")) {
    std::cout << "Converting " << convert_from << " to double." << "\n";
    print_result((double)convert_from);
  } else {
    std::cerr << "ERROR: Not a valid choice." << "\n";
    return 1;
  }

  return 0;
}
