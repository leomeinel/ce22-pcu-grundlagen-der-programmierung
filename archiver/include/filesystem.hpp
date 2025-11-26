/*
 * File: filesystem.hpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <filesystem>
#include <system_error>

namespace fs = std::filesystem;

namespace filesystem {

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

} // namespace filesystem

#endif
