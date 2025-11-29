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

namespace filesystem
{

  /**
   * @brief Alignment of `fs_operation`
   *
   */
  inline constexpr uint8_t ALIGNMENT_FS_OPERATION = 128;

  /**
   * @brief Operation to execute on filesystem
   *
   */
  class fs_operation
  {
   public:
    /**
     * @brief Get the create object
     *
     * @return true
     * @return false
     */
    [[nodiscard]] const bool& get_create() const&
    {
      return create;
    }

    /**
     * @brief Set the create object
     *
     * @param create_
     */
    void set_create(const bool& create_)
    {
      create = create_;
    }

    /**
     * @brief Get the extract object
     *
     * @return true
     * @return false
     */
    [[nodiscard]] const bool& get_extract() const&
    {
      return extract;
    }

    /**
     * @brief Set the extract object
     *
     * @param extract_
     */
    void set_extract(const bool& extract_)
    {
      extract = extract_;
    }

    /**
     * @brief Get the force object
     *
     * @return true
     * @return false
     */
    [[nodiscard]] const bool& get_force() const&
    {
      return force;
    }

    /**
     * @brief Set the force object
     *
     * @param force_
     */
    void set_force(const bool& force_)
    {
      force = force_;
    }

    /**
     * @brief Get the input path object
     *
     * @return const fs::path&
     */
    [[nodiscard]] const fs::path& get_input_path() const&
    {
      return input_path;
    }

    /**
     * @brief Set the input path object
     *
     * @param input_path_
     */
    void set_input_path(const fs::path& input_path_)
    {
      input_path = input_path_;
    }

    /**
     * @brief Get the output path object
     *
     * @return const fs::path&
     */
    [[nodiscard]] const fs::path& get_output_path() const&
    {
      return output_path;
    }

    /**
     * @brief Set the output path object
     *
     * @param output_path_
     */
    void set_output_path(const fs::path& output_path_)
    {
      output_path = output_path_;
    }

    /**
     * @brief Execute operation
     *
     * @return int Success value
     */
    [[nodiscard]] int execute();

   private:
    /// Create a new archive
    bool create = false;
    /// Extract an archive
    bool extract = false;
    /// Overwrite existing output path without confirmation
    bool force = false;

    /// Input path
    fs::path input_path;
    /// Output path
    fs::path output_path;

    /**
     * @brief Copy object
     *
     */
    void copy() const;

    /**
     * @brief Create a new archive
     *
     */
    void create_archive() const;

    /**
     * @brief Extract an archive
     *
     */
    void extract_archive() const;

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
     * @param error Reference to error that this might assign to
     * @return true If operation is valid
     * @return false If operation is invalid
     */
    [[nodiscard]] bool validate(std::errc& error) const noexcept;
  } __attribute__((aligned(ALIGNMENT_FS_OPERATION)));

}  // namespace filesystem

#endif
