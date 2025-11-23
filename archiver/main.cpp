/*
 * File: main.cpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#include <filesystem>
#include <iostream>
#include <utility>

namespace fs = std::filesystem;

/**
 * @brief Name of program.
 *
 */
constexpr std::string PROGRAM_NAME = "archiver";

/**
 * @brief Template for help text.
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

/**
 * @brief States for execution flow.
 *
 */
enum class states_t {
  /// Handle flag.
  HANDLE_FLAG,
  /// Handle `input_path_name` in next step.
  SET_INPUT_PATH_NAME,
  /// Handle `output_path_name` in next step.
  SET_OUTPUT_PATH_NAME
};

/**
 * @brief Actions to execute after parameter processing.
 *
 */
struct program_actions {
public:
  /// Create a new archive.
  bool create = false;
  /// Extract files from an archive.
  bool extract = false;
  /// Overwrite existing OUTPUT without confirmation.
  bool force = false;

  /// Name of `input_path`.
  std::string input_path_name = "";
  /// Name of `output_path`.
  std::string output_path_name = "";

  /**
   * @brief Get the input path object
   *
   * @return fs::path
   */
  [[nodiscard]] fs::path get_input_path() const {
    return fs::path(input_path_name);
  };

  /**
   * @brief Get the output path object
   *
   * @return fs::path
   */
  [[nodiscard]] fs::path get_output_path() const {
    return fs::path(output_path_name);
  };

  /**
   * @brief Validate actions.
   *
   * @param error Reference to error that will be assigned to.
   * @return true If actions are valid.
   * @return false If actions are invalid.
   */
  [[nodiscard]] bool validate(std::errc &error) const noexcept {
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

  /**
   * @brief Check if actions are valid.
   *
   * This is a simple check that will not try to handle error codes.
   *
   * @return true If actions are valid.
   * @return false If actions are invalid.
   */
  [[nodiscard]] bool is_valid() const noexcept {
    std::errc error;
    return validate(error);
  }

private:
  /**
   * @brief Check if operation is valid.
   *
   * @return true If operation is valid.
   * @return false If operation is invalid.
   */
  [[nodiscard]] bool has_invalid_operation() const noexcept {
    return create && extract;
  }

  /**
   * @brief Check if no path name is empty.
   *
   * @return true If no path name is empty.
   * @return false If any path name is empty.
   */
  [[nodiscard]] bool has_empty_path_name() const noexcept {
    return input_path_name.empty() || output_path_name.empty();
  }

  /**
   * @brief Check if paths are invalid.
   *
   * @return true If paths are invalid.
   * @return false If paths are valid.
   */
  [[nodiscard]] bool has_invalid_paths() const noexcept {
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
};

/**
 * @brief Handle copying.
 *
 * @param input_path INPUT path.
 * @param output_path OUTPUT path.
 * @param force Overwrite existing OUTPUT without confirmation.
 */
void handle_copy(fs::path input_path, fs::path output_path, bool &force) {
  const fs::copy_options options =
      (fs::is_directory(output_path) ? fs::copy_options::recursive
                                     : fs::copy_options{}) |
      (force ? fs::copy_options::overwrite_existing : fs::copy_options{});
  fs::copy(input_path, output_path, options);
}

/**
 * @brief Handle archive creation.
 *
 * @param input_path INPUT path.
 * @param output_path OUTPUT path.
 */
void handle_create(fs::path input_path, fs::path output_path) {
  // FIXME: Implement this.
  throw std::runtime_error("FIXME: Implement this!");
}

/**
 * @brief Handle archive extraction.
 *
 * @param input_path INPUT path.
 * @param output_path OUTPUT path.
 */
void handle_extract(fs::path input_path, fs::path output_path) {
  // FIXME: Implement this.
  throw std::runtime_error("FIXME: Implement this!");
}

/**
 * @brief Handle actions.
 *
 * @param actions Actions to execute after parameter processing.
 * @return int Success value.
 */
int handle_actions(program_actions &actions) {
  // Return error if actions are invalid
  std::errc error;
  if (!actions.validate(error)) {
    std::string error_message;
    if (error == std::errc::operation_not_supported) {
      error_message = "Operation not supported";
    } else if (error == std::errc::no_such_file_or_directory) {
      error_message = "No such file or directory";
    } else {
      std::unreachable();
    }
    const std::uint8_t error_code = static_cast<uint8_t>(error);
    std::cerr << PROGRAM_NAME << ": " << error_message << "\n";
    return EXIT_FAILURE;
  }

  // Execute actions
  if (!actions.create && !actions.extract) {
    handle_copy(actions.get_input_path(), actions.get_output_path(),
                actions.force);
  } else if (actions.create) {
    handle_create(actions.get_input_path(), actions.get_output_path());
  } else if (actions.extract) {
    handle_extract(actions.get_input_path(), actions.get_output_path());
  }
  return EXIT_SUCCESS;
}

/**
 * @brief Handle help.
 *
 */
void handle_help() { std::cout << std::format(HELP_TEMPLATE, PROGRAM_NAME); }

/**
 * @brief
 *
 * @param params All parameters.
 * @param param Current parameter.
 * @param actions Actions to execute after parameter processing.
 * @return states_t States for execution flow.
 */
states_t handle_flags(std::span<char *> &params, std::string_view &param,
                      program_actions &actions) {
  if (param == "-c" || param == "--create") {
    actions.create = true;
  } else if (param == "-x" || param == "--extract" || param == "--get") {
    actions.extract = true;
  } else if (param == "-f" || param == "--force") {
    actions.force = true;
  } else if (param == "-i") {
    return states_t::SET_INPUT_PATH_NAME;
  } else if (param == "-o") {
    return states_t::SET_OUTPUT_PATH_NAME;
  } else if (param != params[0] || params.size() == 1) {
    handle_help();
    exit(EXIT_SUCCESS);
  }
  return states_t::HANDLE_FLAG;
}

/**
 * @brief Set `input_path_name`.
 *
 * @param param Current parameter.
 * @param actions Actions to execute after parameter processing.
 * @return states_t States for execution flow.
 */
states_t set_input_path_name(std::string_view &param,
                             program_actions &actions) {
  actions.input_path_name = param;
  return states_t::HANDLE_FLAG;
}

/**
 * @brief Set `output_path_name`.
 *
 * @param param Current parameter.
 * @param actions Actions to execute after parameter processing.
 * @return states_t States for execution flow.
 */
states_t set_output_path_name(std::string_view &param,
                              program_actions &actions) {
  actions.output_path_name = param;
  return states_t::HANDLE_FLAG;
}

/**
 * @brief Main class.
 *
 * Source: https://en.cppreference.com/w/cpp/language/main_function.html
 *
 * @param argc Non-negative value representing the number of arguments passed to
 * the program from the environment in which the program is run.
 * @param argv Pointer to the first element of an array of `argc + 1` pointers,
 * of which the last one is null and the previous ones, if any, point to
 * null-terminated multibyte strings that represent the arguments passed to the
 * program from the execution environment. If `argv[0]` is not a null pointer
 * (or, equivalently, if `argc > 0`), it points to a string that represents the
 * name used to invoke the program, or to an empty string.
 * @return int Success value.
 */
int main(int argc, char *argv[]) {
  // Initialize actions, states_t and params
  program_actions actions;
  states_t state = states_t::HANDLE_FLAG;
  std::span<char *> params{argv, static_cast<uint32_t>(argc)};

  // Loop through params
  for (std::string_view param : params) {
    // Skip first param if others exist
    if (param == params[0] && params.size() > 1) {
      continue;
    }
    // Switch on state
    switch (state) {
    case states_t::HANDLE_FLAG: {
      state = handle_flags(params, param, actions);
      break;
    }
    case states_t::SET_INPUT_PATH_NAME: {
      state = set_input_path_name(param, actions);
      break;
    }
    case states_t::SET_OUTPUT_PATH_NAME: {
      state = set_output_path_name(param, actions);
      break;
    }
    }
  }
  // Return success value of `handle_actions()`
  return handle_actions(actions);
}
