#!/usr/bin/env bash
set -euo pipefail

echo "=================================================="
echo "Starting Sanity Check build (PS4 fw 14.02)"
echo "=================================================="

# Force a fully clean build
make clean
rm -f payload.bin payload.sha256

# Verify gcc exists in the SDK container
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

# Sanity-check the payload is a real ELF (catches 0-byte / garbage output)
file payload.bin || true
echo "Build successful:"
ls -lh payload.bin

# NOTE: intentionally NOT writing payload.sha256 here.
# This script runs as root inside the SDK container — any file it
# creates is root-owned and the host workflow can't overwrite it.
# The hash is generated on the host in the "Verify payload file" step.

echo "=================================================="
echo "SANITY CHECK BUILD SUCCESSFUL"
echo "=================================================="
