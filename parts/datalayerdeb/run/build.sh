#!/bin/bash
set -e
# Environment
## Part Environment
export SNAPCRAFT_ARCH_TRIPLET="x86_64-linux-gnu"
export SNAPCRAFT_EXTENSIONS_DIR="/snap/snapcraft/7201/share/snapcraft/extensions"
export SNAPCRAFT_PARALLEL_BUILD_COUNT="4"
export SNAPCRAFT_PRIME="/home/boschrexroth/ctrlx-automation-sdk/samples-python/webserver/prime"
export SNAPCRAFT_PROJECT_NAME="sdk-py-webserver"
export SNAPCRAFT_PROJECT_VERSION="1.0.8"
export SNAPCRAFT_PROJECT_DIR="/home/boschrexroth/ctrlx-automation-sdk/samples-python/webserver"
export SNAPCRAFT_PROJECT_GRADE="stable"
export SNAPCRAFT_STAGE="/home/boschrexroth/ctrlx-automation-sdk/samples-python/webserver/stage"
export SNAPCRAFT_TARGET_ARCH="amd64"
export SNAPCRAFT_PART_SRC="/home/boschrexroth/ctrlx-automation-sdk/samples-python/webserver/parts/datalayerdeb/src"
export SNAPCRAFT_PART_SRC_WORK="/home/boschrexroth/ctrlx-automation-sdk/samples-python/webserver/parts/datalayerdeb/src/"
export SNAPCRAFT_PART_BUILD="/home/boschrexroth/ctrlx-automation-sdk/samples-python/webserver/parts/datalayerdeb/build"
export SNAPCRAFT_PART_BUILD_WORK="/home/boschrexroth/ctrlx-automation-sdk/samples-python/webserver/parts/datalayerdeb/build/"
export SNAPCRAFT_PART_INSTALL="/home/boschrexroth/ctrlx-automation-sdk/samples-python/webserver/parts/datalayerdeb/install"
## Plugin Environment
## User Environment

set -xeuo pipefail
cp --archive --link --no-dereference . "${SNAPCRAFT_PART_INSTALL}"
