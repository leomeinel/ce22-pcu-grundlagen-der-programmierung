#!/usr/bin/env bash
###
# File: build.sh
# Author: Leopold Johannes Meinel (leo@meinel.dev)
# -----
# Copyright (c) 2025 Leopold Johannes Meinel & contributors
# SPDX ID: Apache-2.0
# URL: https://www.apache.org/licenses/LICENSE-2.0
###

# Fail on error
set -e

# Set ${SCRIPT_DIR}
SCRIPT_DIR="$(dirname -- "$(readlink -f -- "${0}")")"

# Out of source build
mkdir "${SCRIPT_DIR}"/build || true
cd "${SCRIPT_DIR}"/build
cmake -G Ninja "${SCRIPT_DIR}"
## Build debug build if any cli argument is given, otherwise build release build
if [[ -z "${1}" ]]; then
    cmake -D CMAKE_BUILD_TYPE=Release "${SCRIPT_DIR}"
else
    cmake -D CMAKE_BUILD_TYPE=Debug "${SCRIPT_DIR}"
fi
cmake --build "${SCRIPT_DIR}"/build
