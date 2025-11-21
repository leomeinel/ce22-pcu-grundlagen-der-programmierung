/*
 * File: main.cpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#include <cstdlib>
#include <filesystem>
#include <format>
#include <iostream>
#include <stdexcept>
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
 * @brief Template for parameter output.
 *
 * This is meant to help the user understand how their given parameters were
 * interpreted.
 *
 */
constexpr std::string_view PARAMETER_TEMPLATE =
    "  -c, --create:            {}\n"
    "  -x, --extract, --get:    {}\n"
    "  -f, --force:             {}\n"
    "  [-i INPUT]:              {}\n"
    "  [-o OUTPUT]:             {}\n";

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
struct actions {
  /// Create a new archive.
  bool create;
  /// Extract files from an archive.
  bool extract;
  /// Overwrite existing OUTPUT without confirmation.
  bool force;

  /// Name of `input_path`
  std::string input_path_name;
  /// Name of `output_path`
  std::string output_path_name;

  /**
   * @brief Get the input path object
   *
   * @return fs::path
   */
  fs::path get_input_path() { return fs::path(input_path_name); };

  /**
   * @brief Get the output path object
   *
   * @return fs::path
   */
  fs::path get_output_path() { return fs::path(output_path_name); };

  /**
   * @brief Check if path names are valid.
   *
   * @return true If path names are valid.
   * @return false If path names are invalid.
   */
  bool has_existing_paths() {
    return fs::exists(get_input_path()) &&
           (fs::exists(get_output_path().parent_path()) ||
            get_output_path() == get_output_path().root_path());
  }

  /**
   * @brief Check if no path name is empty.
   *
   * @return true If no path name is empty.
   * @return false If any path name is empty.
   */
  bool has_empty_path_name() {
    return input_path_name.empty() || output_path_name.empty();
  }

  /**
   * @brief Check if actions is valid.
   *
   * This checks for conditions that should cause the program to exit with a
   * failure.
   *
   * @return true If actions are valid.
   * @return false If actions are invalid.
   */
  bool is_valid() {
    if ((create && extract) || has_empty_path_name() || !has_existing_paths()) {
      return false;
    }
    return true;
  }
};

/**
 * @brief Handle copying.
 *
 * @param from INPUT path.
 * @param to OUTPUT path.
 * @param force Overwrite existing OUTPUT without confirmation.
 */
void handle_copy(fs::path from, fs::path to, bool &force) {
  const fs::copy_options __copy_options =
      (fs::is_directory(to) ? fs::copy_options::recursive
                            : fs::copy_options{}) |
      (force ? fs::copy_options::overwrite_existing : fs::copy_options{});
  fs::copy(from, to, __copy_options);
}

/**
 * @brief Handle archive creation.
 *
 * @param from INPUT path.
 * @param to OUTPUT path.
 */
void handle_create(fs::path from, fs::path to) {
  // FIXME: Implement this.
  throw std::runtime_error("FIXME: Implement this!");
}

/**
 * @brief Handle archive extraction.
 *
 * @param from INPUT path.
 * @param to OUTPUT path.
 */
void handle_extract(fs::path from, fs::path to) {
  // FIXME: Implement this.
  throw std::runtime_error("FIXME: Implement this!");
}

/**
 * @brief Handle actions.
 *
 * @param __actions Actions to execute after parameter processing.
 * @return int Success value.
 */
int handle_actions(actions &__actions) {
  // Exit if actions are invalid
  if (!__actions.is_valid()) {
    std::cerr << PROGRAM_NAME << ":\n Invalid parameters:\n"
              << std::format(PARAMETER_TEMPLATE, __actions.create,
                             __actions.extract, __actions.force,
                             __actions.input_path_name,
                             __actions.output_path_name);
    return EXIT_FAILURE;
  }

  // Execute actions
  if (!__actions.create && !__actions.extract) {
    handle_copy(__actions.get_input_path(), __actions.get_output_path(),
                __actions.force);
  } else if (__actions.create) {
    handle_create(__actions.get_input_path(), __actions.get_output_path());
  } else if (__actions.extract) {
    handle_extract(__actions.get_input_path(), __actions.get_output_path());
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
 * @param __actions Actions to execute after parameter processing.
 * @return states_t States for execution flow.
 */
states_t state_handle_flags(std::span<char *> &params, std::string_view &param,
                            actions &__actions) {
  if (param == "-c" || param == "--create") {
    __actions.create = true;
  } else if (param == "-x" || param == "--extract" || param == "--get") {
    __actions.extract = true;
  } else if (param == "-f" || param == "--force") {
    __actions.force = true;
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
 * @param __actions Actions to execute after parameter processing.
 * @return states_t States for execution flow.
 */
states_t state_set_input_path_name(std::string_view &param,
                                   actions &__actions) {
  __actions.input_path_name = param;
  return states_t::HANDLE_FLAG;
}

/**
 * @brief Set `output_path_name`.
 *
 * @param param Current parameter.
 * @param __actions Actions to execute after parameter processing.
 * @return states_t States for execution flow.
 */
states_t state_set_output_path_name(std::string_view &param,
                                    actions &__actions) {
  __actions.output_path_name = param;
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
  actions __actions = {
      .create = false,
      .extract = false,
      .force = false,
      .input_path_name = "",
      .output_path_name = "",
  };
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
      state = state_handle_flags(params, param, __actions);
    } break;
    case states_t::SET_INPUT_PATH_NAME: {
      state = state_set_input_path_name(param, __actions);
    } break;
    case states_t::SET_OUTPUT_PATH_NAME: {
      state = state_set_output_path_name(param, __actions);
    } break;
    default: {
      std::unreachable();
      break;
    }
    }
  }
  // Return success value of `handle_actions()`
  return handle_actions(__actions);
}
