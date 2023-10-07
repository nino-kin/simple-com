#!/bin/bash

set -eu

readonly SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
readonly REPO_ROOT_DIR=$(cd "$SCRIPT_DIR/.." && pwd)
readonly BUILD_DIR='build'

echo "INFO: Run sample UDP program..."
echo "=============================================="
echo "    Client                            Server  "
echo "  +--------+                        +--------+"
echo "  |        |                        |        |"
echo "  |        |       Send Data        |        |"
echo "  |        | ---------------------> |        |"
echo "  |        |          UDP           |        |"
echo "  +--------+                        +--------+"
echo "=============================================="
sleep 1

echo -e "INFO: Run a server..."
$REPO_ROOT_DIR/$BUILD_DIR/src/sample/udp_server &

echo -e "INFO: Waiting the data from client..."
sleep 3

echo -e "INFO: Send data from a client..."
$REPO_ROOT_DIR/$BUILD_DIR/src/sample/udp_client
echo -e "\nINFO: Test was completed successfully."
