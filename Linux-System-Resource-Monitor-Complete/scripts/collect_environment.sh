#!/usr/bin/env bash
set -euo pipefail
mkdir -p evidence/stage-1 evidence/stage-5
{
  echo '=== DATE ==='; date
  echo '=== UNAME ==='; uname -a
  echo '=== OS ==='; cat /etc/os-release
  echo '=== KERNEL HEADERS ==='; ls -ld "/lib/modules/$(uname -r)/build"
  echo '=== GCC ==='; gcc --version | head -1
  echo '=== G++ ==='; g++ --version | head -1
  echo '=== MAKE ==='; make --version | head -1
  echo '=== GIT ==='; git --version
} | tee evidence/stage-1/environment.txt
