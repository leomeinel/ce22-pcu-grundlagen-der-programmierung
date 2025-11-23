/*
 * File: states.cpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#include "../include/states.hpp"
#include "../include/help.hpp"

namespace states {
/**
 * @brief Handle program flags
 *
 * @param params All parameters
 * @param param Current parameter
 * @param actions  Actions to execute after parameter processing
 * @return exec_states
 */
[[nodiscard]] exec_states handle_flags(std::span<char *> &params,
                                       std::string_view &param,
                                       actions::param_actions &actions) {
  if (param == "-c" || param == "--create") {
    actions.create = true;
  } else if (param == "-x" || param == "--extract" || param == "--get") {
    actions.extract = true;
  } else if (param == "-f" || param == "--force") {
    actions.force = true;
  } else if (param == "-i") {
    return exec_states::SET_INPUT_PATH_NAME;
  } else if (param == "-o") {
    return exec_states::SET_OUTPUT_PATH_NAME;
  } else if (param != params[0] || params.size() == 1) {
    help::handle_help();
    exit(EXIT_SUCCESS);
  }
  return exec_states::HANDLE_FLAG;
}

/**
 * @brief Set the input path name object
 *
 * @param target Target value for input path name object
 * @param actions Actions to execute after parameter processing
 * @return exec_states
 */
[[nodiscard]] exec_states set_input_path_name(std::string_view &target,
                                              actions::param_actions &actions) {
  actions.input_path_name = target;
  return exec_states::HANDLE_FLAG;
}

/**
 * @brief Set the output path name object
 *
 * @param target Target value for output path name object
 * @param actions Actions to execute after parameter processing
 * @return exec_states States for execution flow
 */
[[nodiscard]] exec_states
set_output_path_name(std::string_view &target,
                     actions::param_actions &actions) {
  actions.output_path_name = target;
  return exec_states::HANDLE_FLAG;
}
} // namespace states
