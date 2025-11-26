/*
 * File: cli.cpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#include "../include/cli.hpp"
#include <cstdlib>
#include <iostream>
#include <ranges>

namespace {

/**
 * @brief Name of program
 *
 */
inline constexpr std::string_view PROGRAM_NAME = "archiver";

/**
 * @brief Template for help text
 *
 */
constexpr std::string_view HELP_TEMPLATE =
    "Create or extract an archive from the INPUT path.\n"
    "If neither create or extract flag are present, the object at INPUT path "
    "will be copied recursively.\n\n"
    "Usage: {}"
    " [OPTION...] [-i INPUT] [-o OUTPUT]\n\n"
    "Options:\n"
    " -c, --create            Create a new archive.\n"
    " -x, --extract, --get    Extract files from an archive.\n"
    " -f, --force             Overwrite existing OUTPUT, otherwise this is "
    "skipped.\n"
    " -i INPUT                Read input from a single path, INPUT.\n"
    " -o OUTPUT               Write output to a single file, OUTPUT.\n"
    " -h                      Display usage and exit.\n";

} // namespace

namespace cli {

/// @copydoc print_help()
void print_help() { std::cout << std::format(HELP_TEMPLATE, PROGRAM_NAME); }

/*
 * arg_parser public:
 */

/// @copydoc arg_parser::parse()
void arg_parser::parse() {
  // Initialize task
  parsing_state state = parsing_state::handle_flag;

  // If at max one cli argument, print help and exit
  if (this->args.size() <= 1) {
    cli::print_help();
    exit(EXIT_SUCCESS);
  }

  // Loop through cli arguments, except first
  for (std::string_view arg : std::ranges::views::drop(this->args, 1)) {
    this->current_arg = arg;
    // Switch on task
    switch (state) {
    case parsing_state::handle_flag: {
      state = this->parse_flag();
      break;
    }
    case parsing_state::expect_input_path: {
      state = this->set_input_path();
      break;
    }
    case parsing_state::expect_output_path: {
      state = this->set_output_path();
      break;
    }
    }
  }
}

/*
 * arg_parser private:
 */

/// @copydoc arg_parser::parse_flag()
[[nodiscard]] arg_parser::parsing_state arg_parser::parse_flag() {
  if (this->current_arg == "-c" || this->current_arg == "--create") {
    this->operation.create = true;
  } else if (this->current_arg == "-x" || this->current_arg == "--extract" ||
             this->current_arg == "--get") {
    this->operation.extract = true;
  } else if (this->current_arg == "-f" || this->current_arg == "--force") {
    this->operation.force = true;
  } else if (this->current_arg == "-i") {
    return parsing_state::expect_input_path;
  } else if (this->current_arg == "-o") {
    return parsing_state::expect_output_path;
  } else {
    cli::print_help();
    exit(EXIT_SUCCESS);
  }
  return parsing_state::handle_flag;
}

/// @copydoc arg_parser::set_input_path()
[[nodiscard]] arg_parser::parsing_state arg_parser::set_input_path() {
  this->operation.input_path = fs::path(this->current_arg);
  return parsing_state::handle_flag;
}

/// @copydoc arg_parser::set_output_path()
[[nodiscard]] arg_parser::parsing_state arg_parser::set_output_path() {
  this->operation.output_path = fs::path(this->current_arg);
  return parsing_state::handle_flag;
}

} // namespace cli
