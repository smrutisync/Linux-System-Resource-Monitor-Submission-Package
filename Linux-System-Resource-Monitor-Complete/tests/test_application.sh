#!/bin/bash

set -u

echo "================================"
echo " Linux System Monitor App Test"
echo "================================"

if [ -x ./src/application/sysmon ]; then
    echo "[PASS] Application executable exists"
else
    echo "[FAIL] Application executable does not exist"
    exit 1
fi

if [ -e /dev/sysmon ]; then
    echo "[PASS] Device exists"
else
    echo "[FAIL] /dev/sysmon does not exist"
    exit 1
fi

echo "[PASS] Application prerequisites completed"
