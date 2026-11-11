
#!/usr/bin/env bash
set -euo pipefail

echo "Starting Sanity Check build..."

make clean
make

if [ ! -s sanity-check ]; then
    echo "Build failed!"
    exit 1
fi

echo "Build successful!"
