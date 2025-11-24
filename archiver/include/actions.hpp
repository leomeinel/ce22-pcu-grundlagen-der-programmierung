/*
 * File: actions.hpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <filesystem>

namespace fs = std::filesystem;

namespace actions {

/**
 * @brief Actions to execute after parameter processing
 *
 */
struct param_actions {
public:
  /// Create a new archive
  bool create = false;
  /// Extract files from an archive
  bool extract = false;
  /// Overwrite existing OUTPUT without confirmation
  bool force = false;

  /// Name for `input_path`
  std::string_view input_path_name = "";
  /// Name for `output_path`
  std::string_view output_path_name = "";

  /**
   * @brief Execute actions
   *
   * @return int Success value
   */
  [[nodiscard]] int run();

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
   * @brief Get the input path object
   *
   * @return fs::path
   */
  [[nodiscard]] fs::path get_input_path() const;

  /**
   * @brief Get the output path object
   *
   * @return fs::path
   */
  [[nodiscard]] fs::path get_output_path() const;

  /**
   * @brief Check if operation is valid
   *
   * @return true If operation is valid
   * @return false If operation is invalid
   */
  [[nodiscard]] bool has_invalid_operation() const noexcept;

  /**
   * @brief Check if no path name is empty
   *
   * @return true If no path name is empty
   * @return false If any path name is empty
   */
  [[nodiscard]] bool has_empty_path_name() const noexcept;

  /**
   * @brief Check if paths are invalid
   *
   * @return true If paths are invalid
   * @return false If paths are valid
   */
  [[nodiscard]] bool has_invalid_paths() const noexcept;

  /**
   * @brief Validate actions
   *
   * @param error Reference to error that this will assign to
   * @return true If actions are valid
   * @return false If actions are invalid
   */
  [[nodiscard]] bool validate(std::errc &error) const noexcept;
};

}; // namespace actions

#endif
