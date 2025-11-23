/*
 * File: actions.cpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#include "../include/actions.hpp"
#include "../include/program.hpp"
#include <iostream>
#include <utility>

namespace {

/**
 * @brief Handle copying
 *
 * @param input_path INPUT path
 * @param output_path OUTPUT path
 * @param force Overwrite existing OUTPUT without confirmation
 */
void handle_copy(fs::path input_path, fs::path output_path, bool &force) {
  const fs::copy_options options =
      (fs::is_directory(output_path) ? fs::copy_options::recursive
                                     : fs::copy_options{}) |
      (force ? fs::copy_options::overwrite_existing : fs::copy_options{});
  fs::copy(input_path, output_path, options);
}

/**
 * @brief Handle archive creation
 *
 * @param input_path INPUT path
 * @param output_path OUTPUT path
 */
void handle_create(fs::path input_path, fs::path output_path) {
  // FIXME: Implement this
  throw std::runtime_error("FIXME: Implement this");
}

/**
 * @brief Handle archive extraction
 *
 * @param input_path INPUT path
 * @param output_path OUTPUT path
 */
void handle_extract(fs::path input_path, fs::path output_path) {
  // FIXME: Implement this
  throw std::runtime_error("FIXME: Implement this");
}

} // namespace

namespace actions {

/*
 * param_actions public:
 */

/**
 * @brief Get the input path object
 *
 * @return fs::path
 */
[[nodiscard]] fs::path param_actions::get_input_path() const {
  return fs::path(input_path_name);
}

/**
 * @brief Get the output path object
 *
 * @return fs::path
 */
[[nodiscard]] fs::path param_actions::get_output_path() const {
  return fs::path(output_path_name);
};

/**
 * @brief Run actions
 *
 * @return int Success value
 */
[[nodiscard]] int param_actions::run() {
  // Return error if actions are invalid
  std::errc error;
  if (!validate(error)) {
    std::string_view error_message;
    if (error == std::errc::operation_not_supported) {
      error_message = "Operation not supported";
    } else if (error == std::errc::no_such_file_or_directory) {
      error_message = "No such file or directory";
    } else {
      std::unreachable();
    }
    const std::uint8_t error_code = static_cast<uint8_t>(error);
    std::cerr << program::PROGRAM_NAME << ": " << error_message << "\n";
    return EXIT_FAILURE;
  }

  // Run actions
  if (!create && !extract) {
    handle_copy(get_input_path(), get_output_path(), force);
  } else if (create) {
    handle_create(get_input_path(), get_output_path());
  } else if (extract) {
    handle_extract(get_input_path(), get_output_path());
  }
  return EXIT_SUCCESS;
}

/**
 * @brief Validate actions
 *
 * @param error Reference to error that this will assign to
 * @return true If actions are valid
 * @return false If actions are invalid
 */
[[nodiscard]] bool param_actions::validate(std::errc &error) const noexcept {
  if (has_invalid_operation()) {
    error = std::errc::operation_not_supported;
    return false;
  } else if (has_empty_path_name()) {
    error = std::errc::no_such_file_or_directory;
    return false;
  } else if (has_invalid_paths()) {
    error = std::errc::no_such_file_or_directory;
    return false;
  }
  return true;
}

/*
 * param_actions private:
 */

/**
 * @brief Check if operation is valid
 *
 * @return true If operation is valid
 * @return false If operation is invalid
 */
[[nodiscard]] bool param_actions::has_invalid_operation() const noexcept {
  return create && extract;
}

/**
 * @brief Check if no path name is empty
 *
 * @return true If no path name is empty
 * @return false If any path name is empty
 */
[[nodiscard]] bool param_actions::has_empty_path_name() const noexcept {
  return input_path_name.empty() || output_path_name.empty();
}

/**
 * @brief Check if paths are invalid
 *
 * @return true If paths are invalid
 * @return false If paths are valid
 */
[[nodiscard]] bool param_actions::has_invalid_paths() const noexcept {
  // `input_path` must exist
  const fs::path input_path = get_input_path();
  if (!fs::exists(input_path)) {
    return true;
  }

  // `output_path` parent must exist, except if output is root
  const fs::path output_path = get_output_path();
  const fs::path output_parent = output_path.parent_path();
  const fs::path output_root = output_path.root_path();
  return !fs::exists(output_parent) && !(output_parent == output_root);
}

} // namespace actions
