/*
 * File: filesystem.cpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#include "../include/filesystem.hpp"

namespace filesystem {

/*
 * fs_operation public:
 */

/// @copydoc fs_operation::execute()
[[nodiscard]] int fs_operation::execute() {
  // Throw error if operation is invalid
  std::errc error;
  if (!this->validate(error)) {
    const std::system_error sys_error =
        std::system_error(std::make_error_code(error));
    throw sys_error;
  }

  // Run operation
  const bool &create_ = this->create;
  const bool &extract_ = this->extract;
  if (!create_ && !extract_) {
    this->copy();
  } else if (create_) {
    this->create_archive();
  } else if (extract_) {
    this->extract_archive();
  }

  return EXIT_SUCCESS;
}

/*
 * fs_operation private:
 */

/// @copydoc fs_operation::copy()
void fs_operation::copy() {
  // Copy file with specific options
  const fs::path &input_path_ = this->input_path;
  const fs::path &output_path_ = this->output_path;
  const bool &force_ = this->force;
  const fs::copy_options options =
      (fs::is_directory(output_path_) ? fs::copy_options::recursive
                                      : fs::copy_options{}) |
      (force_ ? fs::copy_options::overwrite_existing : fs::copy_options{});
  fs::copy(input_path_, output_path_, options);
}

/// @copydoc fs_operation::create_archive()
void fs_operation::create_archive() {
  // FIXME: Implement this
  throw std::runtime_error("FIXME: Implement this");
}

/// @copydoc fs_operation::extract_archive()
void fs_operation::extract_archive() {
  // FIXME: Implement this
  throw std::runtime_error("FIXME: Implement this");
}

/// @copydoc fs_operation::has_incompatible_flags()
[[nodiscard]] bool fs_operation::has_incompatible_flags() const noexcept {
  return this->create && this->extract;
}

/// @copydoc fs_operation::has_invalid_path()
[[nodiscard]] bool fs_operation::has_invalid_path() const noexcept {
  const fs::path &input_path_ = this->input_path;
  const fs::path &output_path_ = this->output_path;

  // paths cannot be empty and input path must exist
  if (input_path_.empty() || output_path_.empty() || !fs::exists(input_path_)) {
    return true;
  }

  // parent of ouput path must exist, except if output path is root
  const fs::path output_parent = output_path_.parent_path();
  const fs::path output_root = output_path_.root_path();
  return !fs::exists(output_parent) && !(output_parent == output_root);
}

/// @copydoc fs_operation::validate(std::errc &)
[[nodiscard]] bool fs_operation::validate(std::errc &error) const noexcept {
  if (this->has_incompatible_flags()) {
    error = std::errc::operation_not_supported;
    return false;
  } else if (this->has_invalid_path()) {
    error = std::errc::no_such_file_or_directory;
    return false;
  }
  return true;
}

} // namespace filesystem
