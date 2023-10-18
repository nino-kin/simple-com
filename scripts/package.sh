#!/bin/bash
# vim: et ts=2 sts=2 sw=2
###########################################################################
#
# @(#) package.sh
#
# Usage:
#   package.sh [param1] [param2]
#       (Optinal)param1: project file name (e.g. simple-com)
#       (Optinal)param2: tag name (e.g. 1.0.0)
#
# Description:
#   Create packages.
#
###########################################################################
readonly PACKAGE_DIR='package'
readonly EXTENSION='tar.gz'
project_name=$1
tag=$2

REPO_NAME=$(basename -s .git "$(git config --get remote.origin.url)")
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
REPO_ROOT_DIR=$(cd "$SCRIPT_DIR/.." && pwd)

# Setup the package name
if [ $# -ne 2 ]; then
    echo "INFO: Set up the default package name..."
    project_name=$REPO_NAME
    tag=$(git describe --tags --abbrev=0) > /dev/null 2>&1
fi
package_name="$project_name-$tag.$EXTENSION"
echo "INFO: package name : $package_name"

mkdir -p "$REPO_ROOT_DIR/$PACKAGE_DIR/lib"

# Copy header files
cp -r include/ $PACKAGE_DIR

# Copy libraries
cp $REPO_ROOT_DIR/build/source/*/*.a $REPO_ROOT_DIR/$PACKAGE_DIR/lib

# Copy configuration files
cp pkg/* $REPO_ROOT_DIR/$PACKAGE_DIR/

# Create a temporary copy of the package directory
tmp_dir=$(mktemp -d)
cp -r $PACKAGE_DIR/* $tmp_dir

# Create release packages
tar -czvf $PACKAGE_DIR/"$package_name" -C $tmp_dir .
rm -r $tmp_dir
