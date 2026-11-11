
#!/usr/bin/env bash
set -euo pipefail

make
test -s hen.bin
echo "Build successful: hen.bin"
