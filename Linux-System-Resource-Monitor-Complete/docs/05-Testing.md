# Stage 5 — Testing, Integration & Improvement

## Test Environment

Fill these from your actual machine:

```text
Distribution:
Kernel:
GCC version:
G++ version:
CPU:
RAM:
```

## Test Cases

| ID | Test | Expected Result | Actual Result | Status |
|---|---|---|---|---|
| T01 | Build driver | `.ko` created | Fill | Fill |
| T02 | Load driver | Module visible | Fill | Fill |
| T03 | Device creation | `/dev/sysmon` exists | Fill | Fill |
| T04 | Build app | Executable created | Fill | Fill |
| T05 | Open device | Application opens device | Fill | Fill |
| T06 | ioctl | Statistics returned | Fill | Fill |
| T07 | CPU | Percentage displayed | Fill | Fill |
| T08 | Memory | Values displayed | Fill | Fill |
| T09 | Processes | Process count displayed | Fill | Fill |
| T10 | Invalid input | Error handled | Fill | Fill |
| T11 | Driver unload | Clean unload | Fill | Fill |

## Integration Test

Verify the complete chain:

```text
C++ Application
      |
    ioctl
      |
/dev/sysmon
      |
Kernel Driver
      |
Linux Kernel
```

## Bugs and Fixes

For every important problem:

```text
Problem:
Cause:
Solution:
Result:
```

## Improvements

Record actual improvements made during Stage 5.
