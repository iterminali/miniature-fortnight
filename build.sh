#!/usr/bin/env bash
set -euo pipefail

echo "=================================================="
echo "Starting Sanity Check build (PS4 fw 14.02)"
echo "=================================================="

# Force a fully clean build
make clean
rm -f payload.bin payload.sha256

# Verify gcc is available
if [ ! -x "$(command -v gcc)" ]; then
    echo "ERROR: gcc not found in PATH"
    exit 1
fi

make

if [ ! -s payload.bin ]; then
    echo "ERROR: payload.bin was not generated"
    ls -lah
    exit 1
fi

# Sanity check the payload is a real ELF
file payload.bin || true
echo "Build successful:"
ls -lh payload.bin

# NOTE: intentionally NOT writing payload.sha256 here.
# This script runs as root inside the SDK container. Any file
# created here is root-owned and will cause "Permission denied"
# on the host in the next workflow step.
# The hash is generated on the host in the "Verify payload file" step.

echo "=================================================="
echo "SANITY CHECK BUILD SUCCESSFUL"
echo "=================================================="
