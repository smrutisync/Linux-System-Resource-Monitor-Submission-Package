#!/usr/bin/env bash
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

printf '\n=== BUILD ===\n'
make clean && make

printf '\n=== DRIVER LOAD ===\n'
if sudo insmod src/driver/sysmon_driver.ko; then
  echo '[PASS] insmod succeeded'
else
  echo '[FAIL] insmod failed'
  exit 1
fi

printf '\n=== DRIVER CHECK ===\n'
lsmod | grep sysmon || { echo '[FAIL] sysmon_driver not loaded'; exit 1; }
ls -l /dev/sysmon || { echo '[FAIL] /dev/sysmon missing'; exit 1; }

echo '[PASS] Driver and device node verified'

printf '\n=== APPLICATION ===\n'
if [ -x src/application/sysmon ]; then
  echo '[PASS] Application executable exists'
else
  echo '[FAIL] Application executable missing'
  exit 1
fi

echo 'Run the interactive application manually:'
echo '  sudo ./src/application/sysmon'

echo 'Then run:'
echo '  bash tests/test_driver.sh'
echo '  bash tests/test_application.sh'

echo 'Finally unload with:'
echo '  sudo rmmod sysmon_driver'
