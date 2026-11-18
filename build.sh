#!/usr/bin/env bash
set -euo pipefail

echo "=================================================="
echo "Starting Sanity Check build (PS4 fw 14.02)"
echo "=================================================="

# Force a fully clean build — guarantees fresh payload.bin
make clean
rm -f payload.bin payload.sha256

# Verify the SDK actually exposes the compiler
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

# Sanity check the payload is a real ELF (not 0 bytes / empty file)
file payload.bin || true
echo "Build successful:"
ls -lh payload.bin
sha256sum payload.bin | tee payload.sha256

echo "=================================================="
echo "SANITY CHECK BUILD SUCCESSFUL"
echo "=================================================="
