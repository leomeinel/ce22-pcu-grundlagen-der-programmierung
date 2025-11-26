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

#include <filesystem>

namespace fs = std::filesystem;

namespace cli {

/**
 * @brief Operation to execute on filesystem
 *
 */
struct fs_operation {
public:
  /// Create a new archive
  bool create = false;
  /// Extract files from an archive
  bool extract = false;
  /// Overwrite existing OUTPUT without confirmation
  bool force = false;

  /// INPUT path
  fs::path input_path;
  /// OUTPUT path
  fs::path output_path;

  /**
   * @brief Execute operation
   *
   * @return int Success value
   */
  [[nodiscard]] int execute();

private:
  /**
   * @brief Handle copying
   *
   */
  void handle_copy();

  /**
   * @brief Handle archive creation
   *
   */
  void handle_create();

  /**
   * @brief Handle archive extraction
   *
   */
  void handle_extract();

  /**
   * @brief Check if incompatible flags are present
   *
   * @return true If incompatible flags are present
   * @return false If incompatible flags are not present
   */
  [[nodiscard]] bool has_incompatible_flags() const noexcept;

  /**
   * @brief Check if invalid path is present
   *
   * @return true If invalid path is present
   * @return false If invalid path is not present
   */
  [[nodiscard]] bool has_invalid_path() const noexcept;

  /**
   * @brief Validate operation
   *
   * @param error Reference to error that this will assign to
   * @return true If operation is valid
   * @return false If operation is invalid
   */
  [[nodiscard]] bool validate(std::errc &error) const noexcept;
};

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
  fs_operation operation;

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
  arg_parser(std::span<char *> &args_) { this->args = args_; }

private:
  /**
   * @brief State tracking object
   *
   */
  enum class parsing_state {
    /// Handle flag
    handle_flag,
    /// Expect `input_path` in the next step
    expect_input_path,
    /// Expect `output_path` in the next step
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
   * @brief Set the input path object
   *
   * @return parsing_state State tracking object
   */
  parsing_state set_input_path();

  /**
   * @brief Set the output path object
   *
   * @return parsing_state State tracking object
   */
  parsing_state set_output_path();
};

}; // namespace cli

#endif
