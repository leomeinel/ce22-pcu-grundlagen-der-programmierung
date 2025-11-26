/*
 * File: cli.hpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef CLI_HPP
#define CLI_HPP

#include "filesystem.hpp"
#include <span>
#include <string_view>

namespace cli {

/**
 * @brief Print help
 *
 */
void print_help();

/**
 * @brief Argument parser
 *
 */
struct arg_parser {
public:
  /**
   * @brief Operation to execute on filesystem
   *
   */
  filesystem::fs_operation operation;

  /**
   * @brief Parse args and initialize operation
   *
   */
  void parse();

  /**
   * @brief Construct a new arg parser object
   *
   * @param args_ cli arguments
   */
  arg_parser(std::span<char *> &args_);

private:
  /**
   * @brief State tracking object
   *
   */
  enum class parsing_state {
    /// Handle flag
    handle_flag,
    /// Expect input path in the next step
    expect_input_path,
    /// Expect output path in the next step
    expect_output_path
  };

  /**
   * @brief cli arguments
   *
   */
  std::span<char *> args;

  /**
   * @brief Current iteration of cli arguments
   *
   */
  std::string_view current_arg;

  /**
   * @brief Parse flag
   *
   * @return parsing_state State tracking object
   */
  parsing_state parse_flag();

  /**
   * @brief Parse the input path
   *
   * @return parsing_state State tracking object
   */
  parsing_state parse_input_path();

  /**
   * @brief Parse the output path
   *
   * @return parsing_state State tracking object
   */
  parsing_state parse_output_path();
};

}; // namespace cli

#endif
