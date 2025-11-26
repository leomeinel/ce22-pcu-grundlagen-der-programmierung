/*
 * File: main.cpp
 * Author: Leopold Johannes Meinel (leo@meinel.dev)
 * -----
 * Copyright (c) 2025 Leopold Johannes Meinel & contributors
 * SPDX ID: Apache-2.0
 * URL: https://www.apache.org/licenses/LICENSE-2.0
 */

#include "../include/actions.hpp"
#include "../include/state.hpp"

/**
 * @brief Main class
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
 * @return int Success value
 */
int main(int argc, char *argv[]) {
  // Initialize actions, exec_state and params
  actions::param_actions actions;
  state::exec_state state = state::exec_state::HANDLE_FLAG;
  std::span<char *> params{argv, static_cast<uint32_t>(argc)};

  // Loop through params
  for (std::string_view param : params) {
    // Skip first param if others exist
    if (param == params[0] && params.size() > 1) {
      continue;
    }
    // Switch on state
    switch (state) {
    case state::exec_state::HANDLE_FLAG: {
      state = state::handle_flags(params, param, actions);
      break;
    }
    case state::exec_state::SET_INPUT_PATH_NAME: {
      state = state::set_input_path_name(param, actions);
      break;
    }
    case state::exec_state::SET_OUTPUT_PATH_NAME: {
      state = state::set_output_path_name(param, actions);
      break;
    }
    }
  }
  // Return success value of `actions.run()`
  return actions.run();
}
