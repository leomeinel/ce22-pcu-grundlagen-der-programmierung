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
#include <string_view>

namespace {

/**
 * @brief Program name
 *
 */
inline constexpr std::string_view PROGRAM_NAME = "archiver";

/**
 * @brief Help text template
 *
 */
constexpr std::string_view HELP_TEMPLATE =
    "Create or extract an archive from the INPUT path.\n"
    "If no create or extract flag is present, the object at INPUT path will be "
    "copied recursively.\n\n"
    "Usage: {}"
    " [OPTION...] [-i INPUT] [-o OUTPUT]\n\n"
    "Options:\n"
    " -c, --create            Create a new archive.\n"
    " -x, --extract, --get    Extract files from an archive.\n"
    " -f, --force             Overwrite existing OUTPUT, otherwise this is "
    "skipped.\n"
    " -i INPUT                Read input from a single object at INPUT path.\n"
    " -o OUTPUT               Write output to a single object at OUTPUT path.\n"
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
  // If at max one cli argument, print help and exit
  const std::span<char *> &args_ = this->args;
  if (args_.size() <= 1) {
    cli::print_help();
    exit(EXIT_SUCCESS);
  }

  // Loop through cli arguments, except first
  parsing_state current_state = parsing_state::handle_flag;
  for (std::string_view arg : std::ranges::views::drop(args_, 1)) {
    this->current_arg = arg;

    switch (current_state) {
    case parsing_state::handle_flag: {
      current_state = this->parse_flag();
      break;
    }
    case parsing_state::expect_input_path: {
      current_state = this->parse_input_path();
      break;
    }
    case parsing_state::expect_output_path: {
      current_state = this->parse_output_path();
      break;
    }
    }
  }
}

/// @copydoc arg_parser::arg_parser(std::span<char *> &)
arg_parser::arg_parser(std::span<char *> &args_) { this->args = args_; }

/*
 * arg_parser private:
 */

/// @copydoc arg_parser::parse_flag()
[[nodiscard]] arg_parser::parsing_state arg_parser::parse_flag() {
  // Assign to operation members or return state or print help and exit
  const std::string_view &current_arg_ = this->current_arg;
  filesystem::fs_operation &operation_ = this->operation;
  if (current_arg_ == "-c" || current_arg_ == "--create") {
    operation_.create = true;
  } else if (current_arg_ == "-x" || current_arg_ == "--extract" ||
             current_arg_ == "--get") {
    operation_.extract = true;
  } else if (current_arg_ == "-f" || current_arg_ == "--force") {
    operation_.force = true;
  } else if (current_arg_ == "-i") {
    return parsing_state::expect_input_path;
  } else if (current_arg_ == "-o") {
    return parsing_state::expect_output_path;
  } else {
    cli::print_help();
    exit(EXIT_SUCCESS);
  }

  return parsing_state::handle_flag;
}

/// @copydoc arg_parser::parse_input_path()
[[nodiscard]] arg_parser::parsing_state arg_parser::parse_input_path() {
  // Set input path and return state
  const std::string_view &current_arg_ = this->current_arg;
  filesystem::fs_operation &operation_ = this->operation;
  operation_.input_path = fs::path(current_arg_);

  return parsing_state::handle_flag;
}

/// @copydoc arg_parser::parse_output_path()
[[nodiscard]] arg_parser::parsing_state arg_parser::parse_output_path() {
  // Set output path and return state
  const std::string_view &current_arg_ = this->current_arg;
  filesystem::fs_operation &operation_ = this->operation;
  operation_.output_path = fs::path(current_arg_);

  return parsing_state::handle_flag;
}

} // namespace cli
