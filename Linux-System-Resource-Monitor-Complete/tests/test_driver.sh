#!/bin/bash

set -u

echo "================================"
echo " Linux System Monitor Driver Test"
echo "================================"

if lsmod | grep -q '^sysmon_driver'; then
    echo "[PASS] sysmon_driver is loaded"
else
    echo "[FAIL] sysmon_driver is not loaded"
    exit 1
fi

if [ -e /dev/sysmon ]; then
    echo "[PASS] /dev/sysmon exists"
else
    echo "[FAIL] /dev/sysmon does not exist"
    exit 1
fi

echo "[PASS] Driver checks completed"
