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

# Source config
SCRIPT_DIR="$(dirname -- "$(readlink -f -- "${0}")")"

# Out of source build
mkdir "${SCRIPT_DIR}"/build || true
cd "${SCRIPT_DIR}"/build
cmake "${SCRIPT_DIR}"
cmake --build "${SCRIPT_DIR}"/build
