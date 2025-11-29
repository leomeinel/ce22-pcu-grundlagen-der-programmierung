/*
 * File: filesystem.cpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#include "../include/filesystem.hpp"

namespace filesystem
{

  /*
   * fs_operation public:
   */

  /// @copydoc fs_operation::execute()
  [[nodiscard]] int fs_operation::execute()
  {
    // Throw error if operation is invalid
    std::errc error = {};
    if (!this->validate(error))
    {
      throw std::system_error(std::make_error_code(error));
    }

    // Run operation
    if (!this->create && !this->extract)
    {
      this->copy();
    }
    else if (this->create)
    {
      this->create_archive();
    }
    else if (this->extract)
    {
      this->extract_archive();
    }

    return EXIT_SUCCESS;
  }

  /*
   * fs_operation private:
   */

  /// @copydoc fs_operation::copy()
  void fs_operation::copy() const
  {
    // Copy file with specific options
    const fs::copy_options options =
        (fs::is_directory(this->output_path) ? fs::copy_options::recursive : fs::copy_options{}) |
        (this->force ? fs::copy_options::overwrite_existing : fs::copy_options{});
    fs::copy(this->input_path, this->output_path, options);
  }

  /// @copydoc fs_operation::create_archive()
  // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
  void fs_operation::create_archive() const
  {
    // FIXME: Implement this
    throw std::runtime_error("FIXME: Implement this");
  }

  /// @copydoc fs_operation::extract_archive()
  // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
  void fs_operation::extract_archive() const
  {
    // FIXME: Implement this
    throw std::runtime_error("FIXME: Implement this");
  }

  /// @copydoc fs_operation::has_incompatible_flags()
  [[nodiscard]] bool fs_operation::has_incompatible_flags() const noexcept
  {
    return this->create && this->extract;
  }

  /// @copydoc fs_operation::has_invalid_path()
  [[nodiscard]] bool fs_operation::has_invalid_path() const noexcept
  {
    // paths cannot be empty and input path must exist
    if (this->input_path.empty() || this->output_path.empty() || !fs::exists(this->input_path))
    {
      return true;
    }

    // parent of ouput path must exist, except if output path is root
    const fs::path output_parent = this->output_path.parent_path();
    const fs::path output_root = this->output_path.root_path();
    return !fs::exists(output_parent) && !(output_parent == output_root);
  }

  /// @copydoc fs_operation::validate(std::errc &)
  [[nodiscard]] bool fs_operation::validate(std::errc& error) const noexcept
  {
    if (this->has_incompatible_flags())
    {
      error = std::errc::operation_not_supported;
      return false;
    }
    if (this->has_invalid_path())
    {
      error = std::errc::no_such_file_or_directory;
      return false;
    }
    return true;
  }

}  // namespace filesystem
