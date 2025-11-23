/*
 * File: states.hpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef STATES_HPP
#define STATES_HPP

#include "actions.hpp"

namespace states {

/**
 * @brief States for execution flow
 *
 */
enum class exec_states {
  /// Handle flag
  HANDLE_FLAG,
  /// Handle `input_path_name` in next step
  SET_INPUT_PATH_NAME,
  /// Handle `output_path_name` in next step
  SET_OUTPUT_PATH_NAME
};

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
                                       actions::param_actions &actions);

/**
 * @brief Set the input path name object
 *
 * @param target Target value for input path name object
 * @param actions Actions to execute after parameter processing
 * @return exec_states
 */
[[nodiscard]] exec_states set_input_path_name(std::string_view &target,
                                              actions::param_actions &actions);

/**
 * @brief Set the output path name object
 *
 * @param target Target value for output path name object
 * @param actions Actions to execute after parameter processing
 * @return exec_states States for execution flow
 */
[[nodiscard]] exec_states set_output_path_name(std::string_view &target,
                                               actions::param_actions &actions);

}; // namespace states

#endif
