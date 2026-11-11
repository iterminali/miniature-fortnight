
#!/usr/bin/env bash
set -euo pipefail

echo "Starting Sanity Check build..."

make clean
make

if [ ! -s payload.bin ]; then
    echo "ERROR: payload.bin was not generated"
    exit 1
fi

echo "Build successful: payload.bin"
ls -lh payload.bin
