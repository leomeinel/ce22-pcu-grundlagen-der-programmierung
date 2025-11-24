/*
 * File: actions.cpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#include "../include/actions.hpp"
#include <cstdlib>
#include <system_error>

namespace actions {

/*
 * param_actions public:
 */

/**
 * @brief Run actions
 *
 * @return int Success value
 */
[[nodiscard]] int param_actions::run() {
  // Return error if actions are invalid
  std::errc error;
  if (!validate(error)) {
    const std::system_error sys_error =
        std::system_error(std::make_error_code(error));
    throw sys_error;
  }

  // Run actions
  if (!create && !extract) {
    handle_copy();
  } else if (create) {
    handle_create();
  } else if (extract) {
    handle_extract();
  }
  return EXIT_SUCCESS;
}

/*
 * param_actions private:
 */

/**
 * @brief Handle copying
 *
 */
void param_actions::handle_copy() {
  const fs::path input_path = get_input_path();
  const fs::path output_path = get_output_path();
  const fs::copy_options options =
      (fs::is_directory(output_path) ? fs::copy_options::recursive
                                     : fs::copy_options{}) |
      (force ? fs::copy_options::overwrite_existing : fs::copy_options{});
  fs::copy(input_path, output_path, options);
}

/**
 * @brief Handle archive creation
 *
 */
void param_actions::handle_create() {
  const fs::path input_path = get_input_path();
  const fs::path output_path = get_output_path();
  // FIXME: Implement this
  throw std::runtime_error("FIXME: Implement this");
}

/**
 * @brief Handle archive extraction
 *
 */
void param_actions::handle_extract() {
  const fs::path input_path = get_input_path();
  const fs::path output_path = get_output_path();
  // FIXME: Implement this
  throw std::runtime_error("FIXME: Implement this");
}

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

} // namespace actions
