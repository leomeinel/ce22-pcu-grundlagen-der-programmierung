/*
 * File: help.cpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#include "../include/help.hpp"
#include "../include/program.hpp"
#include <iostream>

namespace {

/**
 * @brief Template for help text
 *
 */
constexpr std::string_view HELP_TEMPLATE =
    "Compress or decompress the INPUT file or directory.\n"
    "If neither is present, the INPUT file or directory will be copied "
    "recursively.\n\n"
    "Usage: {}"
    " [OPTION...] [-i INPUT] [-o OUTPUT]\n\n"
    "Options:\n"
    " -c, --create            Create a new archive.\n"
    " -x, --extract, --get    Extract files from an archive.\n"
    " -f, --force             Overwrite existing OUTPUT, otherwise this is "
    "skipped.\n"
    " -i INPUT                Read input from a single file or directory, "
    "INPUT.\n"
    " -o OUTPUT               Write output to a single file, OUTPUT.\n"
    " -h                      Display usage and exit.\n";

} // namespace

namespace help {

/**
 * @brief Handle help
 *
 */
void handle_help() {
  std::cout << std::format(HELP_TEMPLATE, program::PROGRAM_NAME);
}

} // namespace help
