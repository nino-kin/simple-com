#!/bin/bash
# vim: et ts=2 sts=2 sw=2
###################################################################
# Script Name  : package.sh
# Description  : Create packages based on projet info definitions.
# Args         : none
###################################################################
set -eu

readonly DIST_DIR='dist'
readonly JSON_FILEPATH='.home/project_info.json'

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
REPO_ROOT_DIR=$(cd "$SCRIPT_DIR/.." && pwd)

package_name=$(jq -r .package[0].name $JSON_FILEPATH)
extension=$(jq -r .package[0].file_extension $JSON_FILEPATH)

case "$extension" in
    "tar")
        option='-cvf'
        ;;
    "tar.gz")
        option='-zcvf'
        ;;
    "tar.bz2")
        option='-jcvf'
        ;;
    "tar.xz")
        option='-Jcvf'
        ;;
    *)
        echo "Unsupported extension type: $extension"
        exit 1
        ;;
esac

# Setup the package name
package="$package_name.$extension"
echo "INFO: package name : $package"

mkdir -p "$REPO_ROOT_DIR/$DIST_DIR/lib"

# Copy header files
cp -r $REPO_ROOT_DIR/include/ $REPO_ROOT_DIR/$DIST_DIR

# Copy libraries
cp $REPO_ROOT_DIR/build/source/*/*.a $REPO_ROOT_DIR/$DIST_DIR/lib

# Copy configuration files
cp $REPO_ROOT_DIR/pkg/* $REPO_ROOT_DIR/$DIST_DIR/

# Create a temporary copy of the package directory
tmp_dir=$(mktemp -d)
cp -r $REPO_ROOT_DIR/$DIST_DIR/* $tmp_dir

# Create release packages
tar $option $REPO_ROOT_DIR/$DIST_DIR/$package -C $tmp_dir .
rm -r $tmp_dir
