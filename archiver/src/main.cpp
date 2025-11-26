/*
 * File: main.cpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#include "../include/cli.hpp"

/**
 * @brief Main class
 *
 * Source: https://en.cppreference.com/w/cpp/language/main_function.html
 *
 * @param argc Non-negative value representing the number of arguments passed to
 * the program from the environment in which the program is run.
 * @param argv Pointer to the first element of an array of `argc + 1` pointers,
 * of which the last one is null and the previous ones, if any, point to
 * null-terminated multibyte strings that represent the arguments passed to the
 * program from the execution environment. If `argv[0]` is not a null pointer
 * (or, equivalently, if `argc > 0`), it points to a string that represents the
 * name used to invoke the program, or to an empty string.
 * @return int Success value
 */
int main(int argc, char *argv[]) {
  // Parse cli arguments and run operation
  std::span<char *> args{argv, static_cast<uint32_t>(argc)};
  cli::arg_parser parser(args);

  parser.parse();
  return parser.operation.execute();
}
